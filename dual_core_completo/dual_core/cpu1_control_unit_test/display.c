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
           case PAGE_13:
               updatePage13();
           break;
           case PAGE_14:
               updatePage14();
           break;

         }
}

/*
 * It simply sets the right page. Page value is given by cpu2
 */
void updatePage(Uint16 page){

    if (currentPage!=page){
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
        case PAGE_13:
            currentPage=PAGE_13;
            scic_msg("page 13���\0");
        break;
        case PAGE_14:
            currentPage=PAGE_14;
            scic_msg("page 14���\0");
        break;

      }
    }
}

void updatePage1()
{
    if(local_sh.status.status_shared & 0x000000F0) scic_msg("main.hv.bco=GREEN���\0");
    else scic_msg("main.hv.bco=RED���\0");


    if(local_sh.status.status_shared & 0x000F0000) scic_msg("main.air2.bco=GREEN���\0");
    else scic_msg("main.air2.bco=RED���\0");

    // DA Sostituire con fault hv
    //if(local_sh.status.status_shared & 0b00000100) scic_msg("main.temp.bco=RED���\0");
    //else scic_msg("main.temp.bco=GREEN���\0");

    /*
     * PRE is now Implausibility brake/Thrott
     */
    if(local_sh.status.status_shared & 0x0F000000) scic_msg("main.pre.bco=GREEN���\0");
    else scic_msg("main.pre.bco=RED���\0");


    if(local_sh.status.status_shared & 0x00000F00) scic_msg("main.r2d.bco=GREEN���\0");
    else scic_msg("main.r2d.bco=RED���\0");


    if(local_sh.status.status_shared & 0xF0000000) scic_msg("main.brk.bco=RED���\0");
    else scic_msg("main.brk.bco=GREEN���\0");


    //if(local_sh.status.status_shared & 0b01000000) scic_msg("main.imp.bco=RED���\0");
    //else scic_msg("main.imp.bco=GREEN���\0");

    if(car_settings.lauch_ready) scic_msg("main.lc.bco=GREEN���\0");
    else scic_msg("main.lc.bco=RED���\0");


    if(local_sh.status.status_shared & 0x00F00000) scic_msg("main.rf.bco=GREEN���\0");
    else scic_msg("main.rf.bco=RED���\0");


//    sprintf(tmp, "main.speed.val=%d���\0",local_sh.status.actualVelocityKMH_shared);
//    scic_msg(tmp);

    sprintf(tmp, "main.bms_high.val=%d���\0", (int)(local_sh.bms.max_bms_voltage_shared*1000));
    scic_msg(tmp);

    sprintf(tmp, "main.bms_high_temp.val=%d���\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);

    sprintf(tmp, "main.maxmot.val=%d���\0", getMaxTempMot());
    scic_msg(tmp);
    sprintf(tmp, "main.maxinv.val=%d���\0", getMaxTempInv());
    scic_msg(tmp);
//    sprintf(tmp, "main.maxigbt.val=%d���\0", getMaxTempIGBT());
//    scic_msg(tmp);
    sprintf(tmp, "main.maxigbt.val=%d���\0", (int)local_sh.status.steering_shared);
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
    sprintf(tmp, "bms.high.val=%d���\0", (int)(local_sh.bms.max_bms_voltage_shared*1000));
    scic_msg(tmp);
    sprintf(tmp, "bms.med.val=%d���\0", (int)(local_sh.bms.mean_bms_voltage_shared*1000));
    scic_msg(tmp);
    sprintf(tmp, "bms.low.val=%d���\0", (int)(local_sh.bms.min_bms_voltage_shared*1000));
    scic_msg(tmp);
    sprintf(tmp, "bms.high_temp.val=%d���\0", (int)(local_sh.bms.max_bms_temp_shared));
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

    sprintf(tmp, "pwr_set.regcurr.txt=\"%.1f\"���\0", car_settings.max_regen_current);
    scic_msg(tmp);

    sprintf(tmp, "pwr_set.maxpostrq.txt=\"%.1f\"���\0", car_settings.max_pos_torque);
       scic_msg(tmp);

    sprintf(tmp, "pwr_set.maxnegtrq.txt=\"%.1f\"���\0", car_settings.max_neg_torque);
    scic_msg(tmp);

    sprintf(tmp, "pwr_set.powerlim.txt=\"%d\"���\0", (int) (car_settings.power_limit / 1000));
      scic_msg(tmp);

    sprintf(tmp, "pwr_set.speedlim.txt=\"%d\"���\0", (int) (car_settings.max_speed / 1000));
       scic_msg(tmp);

    sprintf(tmp, "pwr_set.trqr.txt=\"%.1f\"���\0", car_settings.rear_motor_scale);
       scic_msg(tmp);

    sprintf(tmp, "pwr_set.trqf.txt=\"%.1f\"���\0", car_settings.front_motor_scale);
    scic_msg(tmp);

}


void updatePage8()
{
    sprintf(tmp, "smu.prerad.val=%d���\0", (int)(local_sh.imu.temperatures_shared[0] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.precold.val=%d���\0", (int)(local_sh.imu.temperatures_shared[1] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.premot.val=%d���\0", (int)(local_sh.imu.temperatures_shared[2] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.postmot.val=%d���\0", (int)(local_sh.imu.temperatures_shared[3] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.prerad2.val=%d���\0", (int)(local_sh.imu.temperatures_shared[4] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.precold2.val=%d���\0", (int)(local_sh.imu.temperatures_shared[5] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.premot2.val=%d���\0", (int)(local_sh.imu.temperatures_shared[6] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.postmot2.val=%d���\0", (int)(local_sh.imu.temperatures_shared[7] - 273.15));
    scic_msg(tmp);
}




void updatePage9(){

    setSelector1_update();
    setSelector2_update();
    setAckSetup();

}


void updatePage10(){

    sprintf(tmp, "pedalSetup.accpot1.val=%d���\0", (int)local_sh.pedals.acc_pot1_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.accpot2.val=%d���\0", (int)local_sh.pedals.acc_pot2_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.brkpot.val=%d���\0", (int)local_sh.pedals.brk_pot_shared);
    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.thr.val=%d���\0", local_sh.status.throttle_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.brk.val=%d���\0", local_sh.status.brake_shared);
    scic_msg(tmp);

    setSelectorPedalConfig();
    setAckPedalConfig();

    sprintf(tmp, "pedalSetup.brk_rel.val=%d���\0", local_sh.pedals.brk_low_calibration);
                    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.brk_pr.val=%d���\0", local_sh.pedals.brk_high_calibration);
                    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.acc1_pr.val=%d���\0", local_sh.pedals.acc1_high_calibration);
                    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.acc2_pr.val=%d���\0", local_sh.pedals.acc2_high_calibration);
                    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.acc1_rel.val=%d���\0", local_sh.pedals.acc1_low_calibration);
                    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.acc2_rel.val=%d���\0", local_sh.pedals.acc2_low_calibration);
                    scic_msg(tmp);
}

void updatePage11(){
    setSelectorMacrosConfig();

    if(macros_settings.torque_vectoring) scic_msg("macros.tv.bco=GREEN���\0");
        else scic_msg("macros.tv.bco=RED���\0");
    if(macros_settings.one_pedal) scic_msg("macros.one.bco=GREEN���\0");
        else scic_msg("macros.one.bco=RED���\0");
    if(macros_settings.traction_ctrl) scic_msg("macros.tr.bco=GREEN���\0");
        else scic_msg("macros.tr.bco=RED���\0");
    if(macros_settings.reg_brake) scic_msg("macros.reg.bco=GREEN���\0");
        else scic_msg("macros.reg.bco=RED���\0");
    if(macros_settings.thermal_power_ctrl) scic_msg("macros.therm.bco=GREEN���\0");
        else scic_msg("macros.therm.bco=RED���\0");

}

void updatePage12(){
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
    sprintf(tmp, "Drv_END.low.val=%d���\0",(int)(local_sh.bms.min_bms_voltage_shared*1000));
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.med.val=%d���\0",(int)(local_sh.bms.mean_bms_voltage_shared*1000));
    scic_msg(tmp);
}


void updatePage13(){

    sprintf(tmp, "Drv_SPEED.actualKmh.val=%d���\0", local_sh.status.actualVelocityKMH_shared);
    scic_msg(tmp);

}


void  updatePage14(){

    setSelector1_fan();
    setSelector2_fan();
    setAckFan();

    sprintf(tmp, "fan_SPEED.speed.val=%d���\0", local_sh.fanSpeed.rightFanSpeed_shared);
    scic_msg(tmp);

}


void setSelector1_fan(){

    n_setup = display.selector_fan;

    if(old_fan != n_setup && n_setup== 0){

        scic_msg("fan_SPEED.setup0.bco=YELLOW���\0");
        scic_msg("fan_SPEED.setup1.bco=54938���\0");

    }
    else if(old_fan != n_setup && n_setup == 1){

        scic_msg("fan_SPEED.setup1.bco=YELLOW���\0");
        scic_msg("fan_SPEED.setup0.bco=54938���\0");

    }

    old_fan = n_setup;

}


void setSelector2_fan(){

    if(display.selector_fan == 1){
        //scic_msg("fan_SPEED.setup1.bco=YELLOW���\0");
        sprintf(tmp, "fan_SPEED.setup1.txt=\"%d\"���\0", display.selector_speed_fan);
        scic_msg(tmp);
    }

}


void setAckFan(){
    if(display.manual_speed_selector){
        scic_msg("fan_SPEED.manual.bco=GREEN���\0");
    }
    else{
        scic_msg("fan_SPEED.manual.bco=RED���\0");
    }
}





void setSelectorMacrosConfig(){

    n_setup = display.selector_macros;

    if(old_macros != n_setup){


      if (old_macros != old_ack_macros){
          sprintf(tmp, "macros.setup%d.bco=0���\0", old_macros);
          scic_msg(tmp);
      }


      old_macros = n_setup;

      if (old_macros != old_ack_macros){
          sprintf(tmp, "macros.setup%d.bco=31695���\0", n_setup);
          scic_msg(tmp);

      }
    }
}


void setSelector1_update(){

    n_setup = display.selector_setup;

    int i = 0;
    for (i = 0; i < 7; i++){
        if (i == display.selector_setup){
            sprintf(tmp, "setupPage.setup%d.bco=YELLOW���\0", i);
            scic_msg(tmp);
        }
        else {
            sprintf(tmp, "setupPage.setup%d.bco=54938���\0", i);
            scic_msg(tmp);
        }
    }
/*
    if(old_setup != n_setup){

      if (old_setup != old_ack_setup){
          sprintf(tmp, "setupPage.setup%d.bco=54938���\0", old_setup);
          scic_msg(tmp);
      }


      old_setup = n_setup;

      if (old_setup != old_ack_setup){
          sprintf(tmp, "setupPage.setup%d.bco=YELLOW���\0", n_setup);
          scic_msg(tmp);

      }
    }*/
}


void setSelector2_update(){

    if(display.selector_setup == 0){
        sprintf(tmp, "setupPage.setup0.txt=\"%.1f\"���\0", car_settings.presets_regen[display.selector_regen]);
        scic_msg(tmp);
    }
   else {
       sprintf(tmp, "setupPage.setup0.txt=\"%.1f\"���\0", car_settings.max_regen_current);
       scic_msg(tmp);
   }

    if(display.selector_setup == 1){
        sprintf(tmp, "setupPage.setup1.txt=\"%.1f\"���\0", car_settings.presets_max_pos[display.selector_maxpos]);
           scic_msg(tmp);
    }
   else {
       sprintf(tmp, "setupPage.setup1.txt=\"%.1f\"���\0", car_settings.max_pos_torque);
          scic_msg(tmp);
   }

    if(display.selector_setup == 2){
        sprintf(tmp, "setupPage.setup2.txt=\"%.1f\"���\0", car_settings.presets_max_neg[display.selector_maxneg]);
        scic_msg(tmp);
    }
   else {
       sprintf(tmp, "setupPage.setup2.txt=\"%.1f\"���\0", car_settings.max_neg_torque);
       scic_msg(tmp);
   }
    if(display.selector_setup == 3){
        sprintf(tmp, "setupPage.setup3.txt=\"%d\"���\0", (int) (car_settings.presets_power[display.selector_power] / 1000));
          scic_msg(tmp);
    }
   else {
       sprintf(tmp, "setupPage.setup3.txt=\"%d\"���\0", (int) (car_settings.power_limit / 1000));
         scic_msg(tmp);
   }
    if(display.selector_setup == 4){
        sprintf(tmp, "setupPage.setup4.txt=\"%d\"���\0", (int) (car_settings.presets_speed[display.selector_speed] / 1000));
           scic_msg(tmp);
    }
   else {
       sprintf(tmp, "setupPage.setup4.txt=\"%d\"���\0", (int) (car_settings.max_speed / 1000));
          scic_msg(tmp);
   }
    if(display.selector_setup == 5){
        sprintf(tmp, "setupPage.setup5.txt=\"%.1f\"���\0", car_settings.presets_coppie_rear[display.selector_trqr]);
           scic_msg(tmp);
    }
   else {
       sprintf(tmp, "setupPage.setup5.txt=\"%.1f\"���\0", car_settings.rear_motor_scale);
          scic_msg(tmp);
   }
    if(display.selector_setup == 6){
        sprintf(tmp, "setupPage.setup6.txt=\"%.1f\"���\0", car_settings.presets_coppie_front[display.selector_trqf]);
        scic_msg(tmp);
    }
   else {
       sprintf(tmp, "setupPage.setup6.txt=\"%.1f\"���\0", car_settings.front_motor_scale);
       scic_msg(tmp);
   }

}



void setAckSetup(){
    int i;
    ack = display.ack_setup;
    if (old_ack_setup != ack){
        for (i = 0; i < 7; i++){
            if (i == ack){
                sprintf(tmp, "setupPage.setup%d.bco=GREEN���\0", i);
                old_ack_setup = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "setupPage.setup%d.bco=54938���\0", i);
                scic_msg(tmp);
            }
        }
    }
}

void setSelectorPedalConfig(){
    n_setup = display.selector_pedal_setup;

    int i = 0;
    for (i = 0; i < 3; i++){
        if (i == display.selector_pedal_setup){
            sprintf(tmp, "pedalSetup.setup%d.bco=YELLOW���\0", i);
            scic_msg(tmp);
        } else {
            sprintf(tmp, "pedalSetup.setup%d.bco=54938���\0", i);
            scic_msg(tmp);
        }
    }
}

void setAckPedalConfig(){

    ack = display.ack_pedal_setup;
    if (old_ack_pedal_setup != ack){

        sprintf(tmp, "pedalSetup.setup%d.bco=GREEN���\0", ack);
        scic_msg(tmp);

        old_ack_pedal_setup = ack;

        int i = 0;
        for (i = 0; i < 3; i++){
            if (i != ack){
                sprintf(tmp, "pedalSetup.setup%d.bco=54938���\0", i);
                scic_msg(tmp);
            }
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
