#include "power_controller.h"

void powerControl()
{
    int i;
    float sTorque = 0;

    for (i = 0; i < NUM_OF_MOTORS; i++)
        sTorque+=posTorquesNM[i];

    power_error = total_power - power_limit;

    reduction_factor = PIController(power_error);
    reduction_factor = reduction_factor/STANDARD_SPEED;

    reduction_factor = saturateFloat(reduction_factor, sTorque*(0.99f), 0)/sTorque;

    if (reduction_factor > 0)
    {
        int i;
        for (i = 0; i < NUM_OF_MOTORS; i++)
            posTorquesNM[i] = posTorquesNM[i] - (reduction_factor*posTorquesNM[i]);
        return;
    }
    else
        return;

}

float PIController(float pi_error)
{
    float pGain = pi_error * KP_PI;
    float iGain = pi_error * KI_PI * T_SAMPLING_ECU;

    iGain+= anti_wind_up;

    iGain = saturateFloat(iGain, PI_UPPER_BOUND, 0);

    anti_wind_up = iGain;

    float pe_red = saturateFloat(iGain + pGain, PI_UPPER_BOUND, 0);

    return pe_red;
}

//DEPRECATED
//
//float proportionalTerm(float power_diff) {
//    return power_diff * K_P;
//}
//
////...
//
//float integralTerm(float power_diff) {
//    //moltiplica per il guadagno e per il tempo di campionamento (10ms)
//    float integral_value = power_diff *= K_I * 0.01;
//    //somma l'anti-wind up
//    integral_value += anti_wind_up;
//    //aggiorna l'anti-wind up e restituisce il nuovo valore
//    return anti_wind_up = integral_value;
//}
//
////...
//
//float calculateUpperBound() {
//    //calcola la potenza totale in uscita dalla batteria
//    total_power = sendyne_current * sendyne_voltage;
//    //calcola la differenza di potenza
//    float power_diff = MAX_PWR_REF - total_power;
//    //combina azione integrale e proporzionale per
//    //calcolare l'errore in potenza
//    pi_error = proportionalTerm(power_diff)
//                       + integralTerm(power_diff);
//
//    //divide per la tensione della batteria
//    pi_error = pi_error/sendyne_voltage;
//    //somma il riferimento di potenza/tensione
//    pi_error += (MAX_PWR_REF/sendyne_voltage);
//    //moltiplica per la costante di proporzionalità K
//    //e divido per 4 in modo da ottenere un limite
//    //superiore di coppia per ciascun motore
//    return pi_error = (pi_error * K_TAU)/4;
//
//}
//
////...
//
//void calculateTorque(int pedal_pressure) {
//    //riceve in input la pressione del pedale
//    //in una scala da 0 a 100 e viene convertita
//    //in una scala da 0 a 21 Nm (coppia massima)
//    float requested_torque = (MAX_TORQUE * pedal_pressure)/100.0;
//
//    //calcola upper bound di coppia
//    upper_bound = calculateUpperBound();
//
//    //controlla ed eventualmente satura la coppia
//    if (requested_torque > upper_bound)
//        requested_torque = upper_bound;
//
//    //converte la requested_torque da Nm
//    //in 0.1% della coppia nominale
//    requested_torque = (1000 * requested_torque) / NOMINAL_TORQUE;
//
//    //imposta il setpoint di coppia per gli inverter
//    throttleAMK(requested_torque);
//
//    //simula il comportamento degli inverter dopo
//    //aver ricevuto il nuovo setpoint di coppia
//    simulateInverter(requested_torque);
//    return;
//}
//
////...
//
//void simulateInverter(float torque_setpoint) {
//    //il setpoint viene convertito in Nm
//    float current_consumption = (NOMINAL_TORQUE * torque_setpoint)/1000;
//
//    //la corrente consumata da un singolo
//    //inverter si ottiene dividendo per
//    //la costante K_TAU
//    current_consumption = current_consumption/K_TAU;
//
//    //la corrente consumata da tutti e 4 gli
//    //inverter si ottiene moltiplicando per 4
//    current_consumption *= 4;
//
//    //viene simulata la lettura di corrente
//    //del sensore Sendyne
//    sendyne_current = current_consumption;
//
//    return;
//}
//
////...
//
//int simulatePedal() {
//    //se viene simulato un segnale di tipo gradino restituisce subito
//    //la pressione massima del pedale
//    if (STEP_SIGNAL)
//        return 100;
//
//    //se viene simulato un segnale di tipo rampa, l'acceleratore
//    //viene aumentato linearmente di 10% fino al massimo
//    if (RAMP_SIGNAL) {
//        if (counter_pedal <=20)
//            return 5 * counter_pedal++;
//        else
//            return 100;
//    }
//}
