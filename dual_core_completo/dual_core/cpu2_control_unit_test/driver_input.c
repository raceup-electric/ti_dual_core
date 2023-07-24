#include "driver_input.h"

unsigned char implausibilityCounter = 0;    //NOTA: per regolamento sono ammesse implausibilit� per un massimo di 100ms.
                                            //      Avendo il timer a 20ms bastano 5 implaususibilit� consegutive per andare in fault
                                            //      IL NUMERO DI IMPLAUSIBILITA' VA CAMBIATO SE SI CAMBIA IL TEMPO DEL TIMER


float acc1Pos, acc2Pos, brkPos, strPot, brkAbsPos;
float currSensVal, analogMuxVal;
int temp;
int media_acc_on = 1;
int Read_throttle(){
    AccPot2 = Acc2_temp;
    AccPot1 = Acc1_temp;

    if ((AccPot1 < ACC1_DISC_THRES) || (AccPot2 < ACC2_DISC_THRES))
        return 0;       //return 0 throttle if one APPS is disconnected

    //UNCOMMENT IF USING ONLY ONE POTENTIOMETER
    /*if ((AccPot1 < ACC1_DISC_THRES) && (AccPot2 < ACC1_DISC_THRES))
        return 0;
    else if (((AccPot1 < ACC1_DISC_THRES) || (AccPot2 < ACC1_DISC_THRES)))
        media_acc_on = 0;
    else
        media_acc_on = 1;*/


    acc1Pos = (AccPot1 - pedals_log.acc1_low_calibration) / INPUT_RANGE(pedals_log.acc1_high_calibration, pedals_log.acc1_low_calibration);  // posizione in 0-1 range acc1
    acc2Pos = (AccPot2 - pedals_log.acc2_low_calibration) / INPUT_RANGE(pedals_log.acc2_high_calibration, pedals_log.acc2_low_calibration);  // posizione in 0-1 range acc2

    acc1Pos = changeRange(acc1Pos, 0, 1, 0, 100);
    acc2Pos = changeRange(acc2Pos, 0, 1, 0, 100);

    /*
     * If acc1Pos and acc2Pos differ more than 10%, implausibility occours.
     * This check can be omitted for DEBUG purposes.
     */
    if (abs(acc1Pos - acc2Pos) > ACC_IMPL_THRES)
    {
      return 0;   //implausibility
    }

    //UNCOMMENT IF USING ONLY ONE POTENTIOMETER
    /*if(media_acc_on){
       value = value - 0.2*(value - ((acc1Pos + acc2Pos)/2.0));
    }else{
        value = value - 0.2*(value - (acc1Pos)); //usa solo potenziometro 1
    }*/

    //COMMENT IF USING ONLY ONE POTENTIOMETER
    value = value - 0.2*(value - ((acc1Pos + acc2Pos)/2.0));

    return saturateUnsigned(value, 100, 0);
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

    brkPos = (BrkPot - pedals_log.brk_low_calibration)/INPUT_RANGE(pedals_log.brk_high_calibration, pedals_log.brk_low_calibration);                                    //posizione percentuale freno
    brkPos = changeRange(brkPos, 0, 1, 0, 100);
    return saturateUnsigned(brkPos, 100, 0);
}

int Read_steering() {
    strPot = Steering_temp;
    //strPot = readADC(STEERING);
    float newSteering = changeRange(strPot, STZ_LOW_TH, STZ_HIGH_TH, -STZ_RANGE, STZ_RANGE);
   // newSteering *= -1.0;  // positive -> left, negative -> right
#ifdef NO_STEERING_SENSOR
    return 0;
#else
    return newSteering;
#endif
}


/*
 * After ADC reading a filter is applied
 */
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


void setup_intialValue_pedals(){

    pedals_log.acc1_high_calibration = ACC1_HIGH_TH_INITIAL;
    pedals_log.acc2_high_calibration = ACC2_HIGH_TH_INITIAL;

    pedals_log.acc1_low_calibration = ACC1_LOW_TH_INITIAL;
    pedals_log.acc2_low_calibration = ACC2_LOW_TH_INITIAL;

    pedals_log.brk_high_calibration = BRK_HIGH_TH_INITIAL;
    pedals_log.brk_low_calibration = BRK_LOW_TH_INITIAL;

}

void wheels_angles(){
    w_angles[0] = delta_steer[0] - TOE_F;
    w_angles[1] = delta_steer[1] + TOE_F;
    w_angles[2] = -TOE_R;
    w_angles[3] = TOE_R;
}


