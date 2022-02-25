#include "driver_input.h"

unsigned char implausibilityCounter = 0;    //NOTA: per regolamento sono ammesse implausibilità per un massimo di 100ms.
                                            //      Avendo il timer a 20ms bastano 5 implaususibilità consegutive per andare in fault
                                            //      IL NUMERO DI IMPLAUSIBILITA' VA CAMBIATO SE SI CAMBIA IL TEMPO DEL TIMER

float AccPot1, AccPot2, BrkPot;
float acc1Pos, acc2Pos, brkPos, strPot, brkAbsPos;
float currSensVal, analogMuxVal;
int temp;

int Read_throttle(){
    AccPot2 = Acc2_temp;
    AccPot1 = Acc1_temp;
//    AccPot2 = readADC(ACC_2);
//    AccPot1 = readADC(ACC_1);

    //return 0 throttle if one APPS is disconnected
    if ((AccPot1 < ACC1_DISC_THRES) || (AccPot2 < ACC1_DISC_THRES))
        return 0;

    acc1Pos = (AccPot1 - ACC1_LOW_TH) / ACC1_INPUT_RANGE;  // posizione in 0-1 range acc1
    acc2Pos = (AccPot2 - ACC2_LOW_TH) / ACC2_INPUT_RANGE;  // posizione in 0-1 range acc2

    acc1Pos = changeRange(acc1Pos, 0, 1, 0, 100);
    acc2Pos = changeRange(acc2Pos, 0, 1, 0, 100);

    //DEBUG!!! Unsafe test configuration
//    if (abs(acc1Pos - acc2Pos) > ACC_IMPL_THRES)
//    {
//        return 0;   //implausibility
//    }

//    return saturateUnsigned((acc1Pos + acc2Pos)/2.0, 100, 0); //    //DEBUG!!! Unsafe test configuration
    value = value - 0.2*(value - acc1Pos);
    return saturateUnsigned(value, 100, 0);                   //DEBUG!!! Unsafe test configuration
}

int Read_brake(int overrideProtectionOFF){
    BrkPot = BrakeClean_temp;
    //BrkPot = readADC(BRAKE_CLEAN);
    if(overrideProtectionOFF == 0){
        if(BrkPot <= BRK_DISC_THRES) {      //errore potenziometro disconnesso
            brk_disconnected = true;
            return 0;
        }else{
            brk_disconnected = false;
        }
    }

    brkPos = (BrkPot - BRK_LOW_TH)/BRK_INPUT_RANGE;                                    //posizione percentuale freno
    brkPos = changeRange(brkPos, 0, 1, 0, 100);
    return saturateUnsigned(brkPos, 100, 0);
}

int Read_steering() {
    strPot = Steering_temp;
    //strPot = readADC(STEERING);
    float newSteering = changeRange(strPot, STZ_LOW_TH, STZ_HIGH_TH, -STZ_RANGE, STZ_RANGE);
    newSteering *= -1.0;  // positive -> left, negative -> right
#ifdef NO_STEERING_SENSOR
    return 0;
#else
    return newSteering;
#endif
}

void readThrottleBrakeSteering() {
    throttle = Read_throttle();
    brake = Read_brake(0);
    steering = Read_steering();

    int i;
    for (i = filterValCount - 1; i > 0; i--) {
        throttles[i] = throttles[i-1];
        brakes[i]=brakes[i-1];
        steerings[i]=steerings[i-1];
    }
    throttles[0]=throttle;
    brakes[0]=brake;
    steerings[0]=steering;
    bool bSame = true, tSame = true;
    for (i=1; i<filterValCount; i++){
        if(throttles[i] != throttles[0]){
            tSame = false;
        }

        if(brakes[i] != brakes[0]){
            bSame = false;
        }

    }

    if (bSame) {
        brake = brakes[0];
    } else {
        float mbrake = brake;
        for (i=0; i<filterValCount; i++){
            if (brakes[i] > mbrake){
                mbrake = brakes[i];
            }
        }

        float sbrake = 0, count = 0;
        for(i = 0; i<filterValCount; i++){
            if(brakes[i] < mbrake){
                sbrake += brakes[i];
                count += 1.0;
            }
        }
        if (count > 0) {
            brake = sbrake/ count;
        } else {
            brake = 0;
        }
    }

    if (tSame) {
        throttle = throttles[0];
    } else {
        float mthrottle = throttle;
        for (i=0; i<filterValCount; i++){
            if(throttles[i] > mthrottle){
                mthrottle = throttles[i];
            }
        }

        float sthrottle = 0, count = 0;
        for(i = 0; i<filterValCount; i++){
            if(throttles[i] < mthrottle){
                sthrottle += throttles[i];
                count += 1.0;
            }
        }

        if (count > 0) {
            throttle = sthrottle / count;
        } else {
            throttle = 0;
        }
    }
}

