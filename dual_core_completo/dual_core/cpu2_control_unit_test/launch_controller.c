    /*
 *  ======= launch_controller ========
 *  launch_controller target-side implementation
 *
 *  Created on: Mar 5, 2022
 *  Author:     Xhemali
 *  email: xhemali.sheshori1@gmail.com
 */
float t = 0;
float t_inst = 0;
float t_last = 0;

#include "launch_controller.h"

void launch_control()
{
    //Conversione del valore del tempo passato dall'inizio
    t_inst = (float)(time_elapsed) * 100.0f; //from [10*ms] to [s]
    t = t_inst - t_last;

    //Logica di controllo
    if(is_launch_inserted){
        if(throttle > 50 && !is_time_saved){
            //Salvo l'ultimo istante di tempo e segnalo il flag del salvataggio
            //Procedura di launch iniziata
            t_last = t;
            is_time_saved = true;
        }else if(is_time_saved && brake > 50){
            //Disattivo LC e "disimparo" il tempo
            is_time_saved = false;
            is_launch_inserted = false;
        }

    }

    //Calcolo dei valori in funzione del tempo
    double T_lc1 = p1[LC]*pow(t,7) + p2[LC]*pow(t,6) + p3[LC]*pow(t,5) + p4[LC]*pow(t,4) + p5[LC]*pow(t,3) +p6[LC]*pow(t,2) +  p7[LC]*t + p8[LC];
    double T_lc = 0.5*(T_lc1*(1+tanh(5000*(t1[LC]-t)))+T1[LC]*(1+tanh(5000*(t-t1[LC]))));

    if(is_launch_inserted && is_time_saved){
        //Saves candidates as if launch calc enable
        posTorqueCandidate[0][3]=T_lc;
        posTorqueCandidate[1][3]=T_lc;
        posTorqueCandidate[2][3]=T1[LC];
        posTorqueCandidate[3][3]=T1[LC];
    }else{
        //Put max torque to saturate output
        posTorqueCandidate[0][3]=21.0f;
        posTorqueCandidate[1][3]=21.0f;
        posTorqueCandidate[2][3]=21.0f;
        posTorqueCandidate[3][3]=21.0f;
    }
}
