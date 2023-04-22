/*
 * display.c
 *
 *  Created on: 18 feb 2022
 *      Author: ludon
 */
#include "display.h"
int counter = 0;

/*
 * The idea is to update only the values of the page we are in
 * to save time.
 */
void updateValues()
{
    switch(currentPage){
           case PAGE_1:
             updatePage1();
           break;
           case PAGE_2:
               updatePage2();
             break;
           case PAGE_3:
               updatePage3();
           break;
           case PAGE_4:
               updatePage4();
           break;
           case PAGE_5:
               updatePage5();
           break;
           case PAGE_6:
               updatePage6();
           break;
           case PAGE_7:
               updatePage7();
           break;
           case PAGE_8:
               updatePage8();
           break;
           case PAGE_9:
               updatePage9();
           break;
           case PAGE_10:
               updatePage10();
           break;
           case PAGE_11:
               updatePage11();
           break;
           case PAGE_12:
               updatePage12();
           break;
           /*case PAGE_13:
               updatePage13();
           break;
           case PAGE_14:
                updatePage14();
           break;
           case PAGE_15:
                updatePage15();
           break;
           case PAGE_16:
                updatePage16();
           break;
           case PAGE_17:
                updatePage17();
           break;
           case PAGE_18:
                updatePage18();
           break; */
         }
}

/*
 * It simply sets the right page. Page value is given by cpu2
 */
void updatePage(Uint16 page){

    if (currentPage!=page || !display.emergencyBrk_isNotSet){
    switch(page){
        case PAGE_1:
          currentPage=PAGE_1;
          scic_msg("page 1���\0");
        break;
        case PAGE_2:
            currentPage=PAGE_2;
            scic_msg("page 2���\0");
          break;
        case PAGE_3:
          currentPage=PAGE_3;
          scic_msg("page 3���\0");
        break;
        case PAGE_4:
          currentPage=PAGE_4;
          scic_msg("page 4���\0");
        break;
        case PAGE_5:
          currentPage=PAGE_5;
          scic_msg("page 5���\0");
        break;
        case PAGE_6:
          currentPage=PAGE_6;
          scic_msg("page 6���\0");
        break;
        case PAGE_7:
          currentPage=PAGE_7;
          scic_msg("page 7���\0");
        break;
        case PAGE_8:
          currentPage=PAGE_8;
          scic_msg("page 8���\0");
        break;
        case PAGE_9:
          currentPage=PAGE_9;
          scic_msg("page 9���\0");
        break;
        case PAGE_10:
          currentPage=PAGE_10;
          scic_msg("page 10���\0");
        break;
        case PAGE_11:
          currentPage=PAGE_11;
          scic_msg("page 11���\0");
        break;
        case PAGE_12:
            currentPage=PAGE_12;
            scic_msg("page 12���\0");
        break;
        /*case PAGE_13:
            currentPage=PAGE_13;
            scic_msg("page 13���\0");
        break;
        case PAGE_14:
            currentPage=PAGE_14;
            scic_msg("page 14���\0");
        break;
        case PAGE_15:
            currentPage=PAGE_15;
            scic_msg("page 15���\0");
        break;
        case PAGE_16:
            currentPage=PAGE_16;
            scic_msg("page 16���\0");
        break;
        case PAGE_17:
            currentPage=PAGE_17;
            scic_msg("page 17���\0");
        break;
        case PAGE_18:
             currentPage=PAGE_18;
             scic_msg("page 18���\0");
        break;*/
      }
    }
}

void updatePage1()
{
    if(local_sh.status.status_shared & 0b00000001) scic_msg("main.hv.bco=GREEN���\0");
    else scic_msg("main.hv.bco=RED���\0");


    if(local_sh.status.status_shared & 0b00000010) scic_msg("main.air2.bco=GREEN���\0");
    else scic_msg("main.air2.bco=RED���\0");

    // DA Sostituire con fault hv
    //if(local_sh.status.status_shared & 0b00000100) scic_msg("main.temp.bco=RED���\0");
    //else scic_msg("main.temp.bco=GREEN���\0");


    if(local_sh.status.status_shared & 0b00001000) scic_msg("main.pre.bco=GREEN���\0");
    else scic_msg("main.pre.bco=RED���\0");


    if(local_sh.status.status_shared & 0b00010000) scic_msg("main.r2d.bco=GREEN���\0");
    else scic_msg("main.r2d.bco=RED���\0");


    if(local_sh.status.status_shared & 0b00100000) scic_msg("main.brk.bco=RED���\0");
    else scic_msg("main.brk.bco=GREEN���\0");


    //if(local_sh.status.status_shared & 0b01000000) scic_msg("main.imp.bco=RED���\0");
    //else scic_msg("main.imp.bco=GREEN���\0");

    if(local_sh.settings.lauch_ready) scic_msg("main.lc.bco=GREEN���\0");
    else scic_msg("main.imp.bco=RED���\0");


    if(local_sh.status.status_shared & 0b10000000) scic_msg("main.rf.bco=GREEN���\0");
    else scic_msg("main.rf.bco=RED���\0");


    sprintf(tmp, "main.speed.val=%d���\0",local_sh.status.actualVelocityKMH_shared);
    scic_msg(tmp);

    sprintf(tmp, "main.bms_high.val=%d���\0", (int)local_sh.bms.max_bms_voltage_shared);
    scic_msg(tmp);

    sprintf(tmp, "main.bms_high_temp.val=%d���\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);

    sprintf(tmp, "main.maxmot.val=%d���\0", getMaxTempMot());
    scic_msg(tmp);
    sprintf(tmp, "main.maxinv.val=%d���\0", getMaxTempInv());
    scic_msg(tmp);
    sprintf(tmp, "main.maxigbt.val=%d���\0", getMaxTempIGBT());
    scic_msg(tmp);
    sprintf(tmp, "main.maxsmu.val=%d���\0", getMaxTempSmu());
    scic_msg(tmp);

    sprintf(tmp, "main.voltage_HV.val=%d���\0", (int)local_sh.power.batteryPack_voltage_shared);
    scic_msg(tmp);

    if(local_sh.gpio.Bms_shared)
            scic_msg("main.bms.bco=RED���\0");
    else
            scic_msg("main.bms.bco=GREEN���\0");

    if(local_sh.gpio.Imd_shared)
            scic_msg("main.imd.bco=RED���\0");
    else
            scic_msg("main.imd.bco=GREEN���\0");
}

void updatePage2()
{
    sprintf(tmp, "bms.high.val=%d���\0", (int)local_sh.bms.max_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.med.val=%d���\0", (int)local_sh.bms.mean_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.low.val=%d���\0", (int)local_sh.bms.min_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.high_temp.val=%d���\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);

    sprintf(tmp, "bms.voltage_HV.val=%d���\0", (int)local_sh.power.batteryPack_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.lem.val=%df���\0", (int)local_sh.power.lem_current_shared);
    scic_msg(tmp);

}

void updatePage3()
{
        sprintf(tmp, "LV.lv0.val=%d���\0", (int)(local_sh.bms_lv[0]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv1.val=%d���\0", (int)(local_sh.bms_lv[1]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv2.val=%d���\0", (int)(local_sh.bms_lv[2]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv3.val=%d���\0", (int)(local_sh.bms_lv[3]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv4.val=%d���\0", (int)(local_sh.bms_lv[4]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv5.val=%d���\0", (int)(local_sh.bms_lv[5]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.temp1.val=%d���\0", (int)(local_sh.bms_lv[6]));
        scic_msg(tmp);
        sprintf(tmp, "LV.temp2.val=%d���\0", (int)(local_sh.bms_lv[7]));
        scic_msg(tmp);

        float sum = 0;
        int i = 0;
        for (; i < 6; i++)
        {
            sum += local_sh.bms_lv[i];
        }
        sprintf(tmp, "LV.tot.val=%d���\0", (int)(sum*1000));
        scic_msg(tmp);

}

void updatePage4()
{
    sprintf(tmp, "motor.mot1.val=%d���\0", (int)local_sh.motorVal2[0].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "motor.mot2.val=%d���\0", (int)local_sh.motorVal2[1].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "motor.mot3.val=%d���\0", (int)local_sh.motorVal2[2].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "motor.mot4.val=%d���\0", (int)local_sh.motorVal2[3].AMK_TempMotor);
    scic_msg(tmp);
}


void updatePage5()
{
    sprintf(tmp, "inverter.inv1n.val=%d���\0", (int)local_sh.motorVal2[0].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv2n.val=%d���\0", (int)local_sh.motorVal2[1].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv3n.val=%d���\0", (int)local_sh.motorVal2[2].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv4n.val=%d���\0", (int)local_sh.motorVal2[3].AMK_TempInverter);
    scic_msg(tmp);
}

void updatePage6()
{
    sprintf(tmp, "igbt.igbt1n.val=%d���\0", (int)local_sh.motorVal2[0].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt2n.val=%d���\0", (int)local_sh.motorVal2[1].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt3n.val=%d���\0", (int)local_sh.motorVal2[2].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt4n.val=%d���\0", (int)local_sh.motorVal2[3].AMK_TempIGBT);
    scic_msg(tmp);
}


void updatePage7()
{
    sprintf(tmp, "pwr_set.spd.val=%d���\0", local_sh.power_setup.max_speed_shared);
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.trqf.val=%d���\0", (int)(local_sh.power_setup.front_motor_scale_shared*10));
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.trqr.val=%d���\0", (int)(local_sh.power_setup.rear_motor_scale_shared*10));
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.pow.val=%lu���\0", (Uint32)local_sh.power_setup.power_limit_shared);
    scic_msg(tmp);
}

void updatePage8()
{
    sprintf(tmp, "smu.prerad.val=%d���\0", (int)(local_sh.imu.temperatures_shared[0] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.precold.val=%d���\0", (int)(local_sh.imu.temperatures_shared[1] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.postcold.val=%d���\0", (int)(local_sh.imu.temperatures_shared[2] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.premot.val=%d���\0", (int)(local_sh.imu.temperatures_shared[3] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.postmot.val=%d���\0", (int)(local_sh.imu.temperatures_shared[4] - 273.15));
    scic_msg(tmp);
}

void updatePage9(){



}


void updatePage10(){
    setSelectorPedalConfig();
    setAckPedalConfig();
}

void updatePage11(){
    float sum = 0;
    int i = 0;
    for (; i < 6; i++)
    {
        sum += local_sh.bms_lv[i];
     }
    sprintf(tmp, "Drv_END.tot.val=%d���\0", (int)(sum*1000));
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.low_lv.val=%d���\0", (int)(getLowestLvVoltage()*1000));
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.high_temp.val=%d���\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.low.val=%d���\0",(int)local_sh.bms.min_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.med.val=%d���\0",(int)local_sh.bms.mean_bms_voltage_shared);
    scic_msg(tmp);
}


void updatePage12(){

    sprintf(tmp, "Drv_SPEED.actualKmh.val=%d���\0", local_sh.status.actualVelocityKMH_shared);
    scic_msg(tmp);

}


/*

void updatePage2()
{
    sprintf(tmp, "HV.voltage_HV.val=%d���\0", (int)local_sh.power.batteryPack_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "HV.lem.val=%df���\0", (int)local_sh.power.lem_current_shared);
    scic_msg(tmp);
    sprintf(tmp, "HV.curr_sens.val=%d���\0", (int)local_sh.power.curr_sens_shared);
    scic_msg(tmp);
    sprintf(tmp, "HV.tot_power.val=%d���\0", (int)local_sh.power.total_power_shared);
    scic_msg(tmp);
}
void updatePage3()
{
    if(local_sh.gpio.Sdc1_shared)
        scic_msg("gpio.sdc1.bco=RED���\0");
    else
        scic_msg("gpio.sdc1.bco=GREEN���\0");

    if(local_sh.gpio.Sdc2_shared)
            scic_msg("gpio.sdc2.bco=RED���\0");
    else
            scic_msg("gpio.sdc2.bco=GREEN���\0");

    if(local_sh.gpio.Sdc3_shared)
            scic_msg("gpio.sdc3.bco=RED���\0");
    else
            scic_msg("gpio.sdc3.bco=GREEN���\0");

    if(local_sh.gpio.Sdc4_shared)
            scic_msg("gpio.sdc4.bco=RED���\0");
    else
            scic_msg("gpio.sdc4.bco=GREEN���\0");

    if(local_sh.gpio.Sdc5_shared)
            scic_msg("gpio.sdc5.bco=RED���\0");
    else
            scic_msg("gpio.sdc5.bco=GREEN���\0");

    if(local_sh.gpio.Sdc6_shared)
            scic_msg("gpio.sdc6.bco=RED���\0");
    else
            scic_msg("gpio.sdc6.bco=GREEN���\0");

    if(local_sh.gpio.Bms_shared)
            scic_msg("gpio.bms.bco=RED���\0");
    else
            scic_msg("gpio.bms.bco=GREEN���\0");

    if(local_sh.gpio.Imd_shared)
            scic_msg("gpio.imd.bco=RED���\0");
    else
            scic_msg("gpio.imd.bco=GREEN���\0");

}








void updatePage10()
{
    setSelectorRegen();
    setAckRegen();
}





void updatePage13(){
    sprintf(tmp, "pedals.thr.val=%d���\0", local_sh.status.throttle_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedals.brk.val=%d���\0", local_sh.status.brake_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedals.acc1.val=%d���\0", (int)local_sh.pedals.acc_pot1_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedals.acc2.val=%d���\0", (int)local_sh.pedals.acc_pot2_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedals.brk_pot.val=%d���\0", (int)local_sh.pedals.brk_pot_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedals.thr_req.val=%d���\0", local_sh.pedals.throttle_req_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedals.brk_req.val=%d���\0", local_sh.pedals.brk_req_shared);
    scic_msg(tmp);

}

void updatePage14(){
    sprintf(tmp, "pwr_set.spd.val=%d���\0", local_sh.power_setup.max_speed_shared);
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.trqf.val=%d���\0", (int)(local_sh.power_setup.front_motor_scale_shared*10));
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.trqr.val=%d���\0", (int)(local_sh.power_setup.rear_motor_scale_shared*10));
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.pow.val=%lu���\0", (Uint32)local_sh.power_setup.power_limit_shared);
    scic_msg(tmp);
}

void updatePage15(){
    setSelectorSpeed();
    setAckSpeed();
}

void updatePage16(){
    setSelectorCoppiaFront();
    setAckCoppiaFront();
}

void updatePage17(){
    setSelectorCoppiaRear();
    setAckCoppiaRear();
}
*/


/*
void setSelectorPowerControl(){
    n_setup = display.selector_p;
    if(old_setup_power != n_setup){


      if (old_setup_power != old_ack_power){
          sprintf(tmp, "powercontrol.setup%d.bco=54938���\0", old_setup_power);
          scic_msg(tmp);
      }


      old_setup_power = n_setup;

      if (old_setup_power != old_ack_power){
          sprintf(tmp, "powercontrol.setup%d.bco=YELLOW���\0", n_setup);
          scic_msg(tmp);
      }

    }
}

void setAckPowerControl(){
    int i;
    ack = display.ack_p;
    if (old_ack_power != ack){
        for (i = 0; i < 8; i++){
            if (i == ack){
                sprintf(tmp, "powercontrol.setup%d.bco=GREEN���\0", i);
                old_ack_power = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "powercontrol.setup%d.bco=54938���\0", i);
                scic_msg(tmp);
            }
        }

    }
}
*/

/*
void setSelectorRegen(){
    n_setup = display.selector_r;
    if(old_setup_regen != n_setup){


      if (old_setup_regen != old_ack_regen){
          sprintf(tmp, "regen.setup%d.bco=54938���\0", old_setup_regen);
          scic_msg(tmp);
      }


      old_setup_regen = n_setup;

      if (old_setup_regen != old_ack_regen){
          sprintf(tmp, "regen.setup%d.bco=YELLOW���\0", n_setup);
          scic_msg(tmp);
      }

    }
}

void setAckRegen(){
    int i;
    ack = display.ack_r;
    if (old_ack_regen != ack){
        for (i = 0; i < 6; i++){
            if (i == ack){
                sprintf(tmp, "regen.setup%d.bco=GREEN���\0", i);
                old_ack_regen = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "regen.setup%d.bco=54938���\0", i);
                scic_msg(tmp);
            }
        }

    }
}
*/
/*
void setSelectorSpeed(){
    n_setup = display.selector_speed;
    if(old_setup_speed != n_setup){


      if (old_setup_speed != old_ack_speed){
          sprintf(tmp, "spd_lim.setup%d.bco=54938���\0", old_setup_speed);
          scic_msg(tmp);
      }


      old_setup_speed = n_setup;

      if (old_setup_speed != old_ack_speed){
          sprintf(tmp, "spd_lim.setup%d.bco=YELLOW���\0", n_setup);
          scic_msg(tmp);
      }

    }
}

void setAckSpeed(){
    int i;
    ack = display.ack_speed;
    if (old_ack_speed != ack){
        for (i = 0; i < 6; i++){
            if (i == ack){
                sprintf(tmp, "spd_lim.setup%d.bco=GREEN���\0", i);
                old_ack_speed = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "spd_lim.setup%d.bco=54938���\0", i);
                scic_msg(tmp);
            }
        }

    }
}
*/
/*
void setSelectorCoppiaFront(){
    n_setup = display.selector_coppie_front;
    if(old_setup_coppia_front != n_setup){


      if (old_setup_coppia_front != old_ack_coppia_front){
          sprintf(tmp, "trq_F.setup%d.bco=54938���\0", old_setup_coppia_front);
          scic_msg(tmp);
      }


      old_setup_coppia_front = n_setup;

      if (old_setup_coppia_front != old_ack_coppia_front){
          sprintf(tmp, "trq_F.setup%d.bco=YELLOW���\0", n_setup);
          scic_msg(tmp);
      }

    }
}

void setAckCoppiaFront(){
    int i;
    ack = display.ack_coppie_front;
    if (old_ack_coppia_front != ack){
        for (i = 0; i < 6; i++){
            if (i == ack){
                sprintf(tmp, "trq_F.setup%d.bco=GREEN���\0", i);
                old_ack_coppia_front = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "trq_F.setup%d.bco=54938���\0", i);
                scic_msg(tmp);
            }
        }

    }
}*/
/*

void setSelectorCoppiaRear(){
    n_setup = display.selector_coppie_rear;
    if(old_setup_coppia_rear != n_setup){


      if (old_setup_coppia_rear != old_ack_coppia_rear){
          sprintf(tmp, "trq_R.setup%d.bco=54938���\0", old_setup_coppia_rear);
          scic_msg(tmp);
      }


      old_setup_coppia_rear = n_setup;

      if (old_setup_coppia_rear != old_ack_coppia_rear){
          sprintf(tmp, "trq_R.setup%d.bco=YELLOW���\0", n_setup);
          scic_msg(tmp);
      }

    }
}

void setAckCoppiaRear(){
    int i;
    ack = display.ack_coppie_rear;
    if (old_ack_coppia_rear != ack){
        for (i = 0; i < 6; i++){
            if (i == ack){
                sprintf(tmp, "trq_R.setup%d.bco=GREEN���\0", i);
                old_ack_coppia_rear = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "trq_R.setup%d.bco=54938���\0", i);
                scic_msg(tmp);
            }
        }

    }
}
*/


void setSelectorPedalConfig(){
    n_setup = display.selector_pedal_setup;

    sprintf(tmp, "pedalSetup.thr_req.val=%d���\0", local_sh.pedals.throttle_req_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.brk_req.val=%d���\0", local_sh.pedals.brk_req_shared);
    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.thr.val=%d���\0", local_sh.status.throttle_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.brk.val=%d���\0", local_sh.status.brake_shared);
    scic_msg(tmp);


    if(old_setup_pedal_setup != n_setup){


      if (old_setup_pedal_setup != old_ack_pedal_setup){
          sprintf(tmp, "pedalSetup.setup%d.bco=54938���\0", old_setup_pedal_setup);
          scic_msg(tmp);
      }


      old_setup_pedal_setup = n_setup;

      if (old_setup_pedal_setup != old_ack_pedal_setup){
          sprintf(tmp, "pedalSetup.setup%d.bco=YELLOW���\0", n_setup);
          scic_msg(tmp);

      }

    }
}

void setAckPedalConfig(){

    ack = display.ack_pedal_setup;

    if (old_ack_pedal_setup != ack){

            if (ack==0){

                sprintf(tmp, "pedalSetup.setup%d.bco=GREEN���\0", ack);
                old_ack_pedal_setup = ack;
                scic_msg(tmp);

                sprintf(tmp, "pedalSetup.acc1_pr.val=%d���\0", local_sh.pedals.acc1_high_calibration);
                scic_msg(tmp);
                sprintf(tmp, "pedalSetup.acc2_pr.val=%d���\0", local_sh.pedals.acc2_high_calibration);
                scic_msg(tmp);

            }

            if (ack==1){
                sprintf(tmp, "pedalSetup.setup%d.bco=GREEN���\0", ack);
                old_ack_pedal_setup = ack;
                scic_msg(tmp);

                sprintf(tmp, "pedalSetup.acc1_rel.val=%d���\0", local_sh.pedals.acc1_low_calibration);
                scic_msg(tmp);
                sprintf(tmp, "pedalSetup.acc2_rel.val=%d���\0", local_sh.pedals.acc1_low_calibration);
                scic_msg(tmp);
            }
            if (ack==2){
                sprintf(tmp, "pedalSetup.setup%d.bco=GREEN���\0", ack);
                old_ack_pedal_setup = ack;
                scic_msg(tmp);

                sprintf(tmp, "pedalSetup.brk_pr.val=%d���\0", local_sh.pedals.brk_high_calibration);
                scic_msg(tmp);
            }
            if (ack==3){
                sprintf(tmp, "pedalSetup.setup%d.bco=GREEN���\0", ack);
                old_ack_pedal_setup = ack;
                scic_msg(tmp);

                sprintf(tmp, "pedalSetup.brk_rel.val=%d���\0", local_sh.pedals.brk_low_calibration);
                scic_msg(tmp);
            }


    }
}




void setRRstatus(){
  if(local_sh.motorVal1[3].AMK_bInverterOn){
      scic_msg("motor_status.invonrr.bco=GREEN");

  }
  else{
      scic_msg("motor_status.invonrr.bco=RED");

  }

  if(local_sh.motorVal1[3].AMK_bDerating){
      scic_msg("motor_status.derrr.bco=RED");

  }
  else{
      scic_msg("motor_status.derrr.bco=GREEN");

  }
}

float getLowestLvVoltage()
{
    float min=4300.0f;
    int i;
    for(i =0;i<6;i++)
        if(min>local_sh.bms_lv[i])
            min=local_sh.bms_lv[i];
    return min;
}

int getMaxTempInv()
{
    int max = 0;
    int i;
    for(i =0;i<4;i++)
    {
        int temp = (int)local_sh.motorVal2[i].AMK_TempInverter;
        if(max < temp)
            max = temp;
    }
    return max;
}

int getMaxTempMot()
{
    int max = 0;
    int i;
    for(i =0;i<4;i++)
    {
        int temp = (int)local_sh.motorVal2[i].AMK_TempMotor;
        if(max < temp)
            max = temp;
    }
    return max;
}

int getMaxTempIGBT()
{
    int max = 0;
    int i;
    for(i =0;i<4;i++)
    {
        int temp = (int)local_sh.motorVal2[i].AMK_TempIGBT;
        if(max < temp)
            max = temp;
    }
    return max;
}

int getMaxTempSmu()
{
    int max = 0;
    int i;
    for(i =0;i<8;i++)
    {
        int temp = (int)local_sh.imu.temperatures_shared[i];
        if(max < temp)
            max = temp;
    }
    return max;
}
