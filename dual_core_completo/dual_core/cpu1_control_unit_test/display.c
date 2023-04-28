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
          scic_msg("page 1ÿÿÿ\0");
        break;
        case PAGE_2:
            currentPage=PAGE_2;
            scic_msg("page 2ÿÿÿ\0");
          break;
        case PAGE_3:
          currentPage=PAGE_3;
          scic_msg("page 3ÿÿÿ\0");
        break;
        case PAGE_4:
          currentPage=PAGE_4;
          scic_msg("page 4ÿÿÿ\0");
        break;
        case PAGE_5:
          currentPage=PAGE_5;
          scic_msg("page 5ÿÿÿ\0");
        break;
        case PAGE_6:
          currentPage=PAGE_6;
          scic_msg("page 6ÿÿÿ\0");
        break;
        case PAGE_7:
          currentPage=PAGE_7;
          scic_msg("page 7ÿÿÿ\0");
        break;
        case PAGE_8:
          currentPage=PAGE_8;
          scic_msg("page 8ÿÿÿ\0");
        break;
        case PAGE_9:
          currentPage=PAGE_9;
          scic_msg("page 9ÿÿÿ\0");
        break;
        case PAGE_10:
          currentPage=PAGE_10;
          scic_msg("page 10ÿÿÿ\0");
        break;
        case PAGE_11:
          currentPage=PAGE_11;
          scic_msg("page 11ÿÿÿ\0");
        break;
        case PAGE_12:
            currentPage=PAGE_12;
            scic_msg("page 12ÿÿÿ\0");
        break;
        /*case PAGE_13:
            currentPage=PAGE_13;
            scic_msg("page 13ÿÿÿ\0");
        break;
        case PAGE_14:
            currentPage=PAGE_14;
            scic_msg("page 14ÿÿÿ\0");
        break;
        case PAGE_15:
            currentPage=PAGE_15;
            scic_msg("page 15ÿÿÿ\0");
        break;
        case PAGE_16:
            currentPage=PAGE_16;
            scic_msg("page 16ÿÿÿ\0");
        break;
        case PAGE_17:
            currentPage=PAGE_17;
            scic_msg("page 17ÿÿÿ\0");
        break;
        case PAGE_18:
             currentPage=PAGE_18;
             scic_msg("page 18ÿÿÿ\0");
        break;*/
      }
    }
}

void updatePage1()
{
    if(local_sh.status.status_shared & 0b00000001) scic_msg("main.hv.bco=GREENÿÿÿ\0");
    else scic_msg("main.hv.bco=REDÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00000010) scic_msg("main.air2.bco=GREENÿÿÿ\0");
    else scic_msg("main.air2.bco=REDÿÿÿ\0");

    // DA Sostituire con fault hv
    //if(local_sh.status.status_shared & 0b00000100) scic_msg("main.temp.bco=REDÿÿÿ\0");
    //else scic_msg("main.temp.bco=GREENÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00001000) scic_msg("main.pre.bco=GREENÿÿÿ\0");
    else scic_msg("main.pre.bco=REDÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00010000) scic_msg("main.r2d.bco=GREENÿÿÿ\0");
    else scic_msg("main.r2d.bco=REDÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00100000) scic_msg("main.brk.bco=REDÿÿÿ\0");
    else scic_msg("main.brk.bco=GREENÿÿÿ\0");


    //if(local_sh.status.status_shared & 0b01000000) scic_msg("main.imp.bco=REDÿÿÿ\0");
    //else scic_msg("main.imp.bco=GREENÿÿÿ\0");

    if(car_settings.lauch_ready) scic_msg("main.lc.bco=GREENÿÿÿ\0");
    else scic_msg("main.imp.bco=REDÿÿÿ\0");


    if(local_sh.status.status_shared & 0b10000000) scic_msg("main.rf.bco=GREENÿÿÿ\0");
    else scic_msg("main.rf.bco=REDÿÿÿ\0");


    sprintf(tmp, "main.speed.val=%dÿÿÿ\0",local_sh.status.actualVelocityKMH_shared);
    scic_msg(tmp);

    sprintf(tmp, "main.bms_high.val=%dÿÿÿ\0", (int)local_sh.bms.max_bms_voltage_shared);
    scic_msg(tmp);

    sprintf(tmp, "main.bms_high_temp.val=%dÿÿÿ\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);

    sprintf(tmp, "main.maxmot.val=%dÿÿÿ\0", getMaxTempMot());
    scic_msg(tmp);
    sprintf(tmp, "main.maxinv.val=%dÿÿÿ\0", getMaxTempInv());
    scic_msg(tmp);
    sprintf(tmp, "main.maxigbt.val=%dÿÿÿ\0", getMaxTempIGBT());
    scic_msg(tmp);
    sprintf(tmp, "main.maxsmu.val=%dÿÿÿ\0", getMaxTempSmu());
    scic_msg(tmp);

    sprintf(tmp, "main.voltage_HV.val=%dÿÿÿ\0", (int)local_sh.power.batteryPack_voltage_shared);
    scic_msg(tmp);

    if(local_sh.gpio.Bms_shared)
            scic_msg("main.bms.bco=REDÿÿÿ\0");
    else
            scic_msg("main.bms.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Imd_shared)
            scic_msg("main.imd.bco=REDÿÿÿ\0");
    else
            scic_msg("main.imd.bco=GREENÿÿÿ\0");
}

void updatePage2()
{
    sprintf(tmp, "bms.high.val=%dÿÿÿ\0", (int)local_sh.bms.max_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.med.val=%dÿÿÿ\0", (int)local_sh.bms.mean_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.low.val=%dÿÿÿ\0", (int)local_sh.bms.min_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.high_temp.val=%dÿÿÿ\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);

    sprintf(tmp, "bms.voltage_HV.val=%dÿÿÿ\0", (int)local_sh.power.batteryPack_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.lem.val=%dfÿÿÿ\0", (int)local_sh.power.lem_current_shared);
    scic_msg(tmp);

}

void updatePage3()
{
        sprintf(tmp, "LV.lv0.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[0]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv1.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[1]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv2.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[2]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv3.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[3]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv4.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[4]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.lv5.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[5]*1000));
        scic_msg(tmp);
        sprintf(tmp, "LV.temp1.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[6]));
        scic_msg(tmp);
        sprintf(tmp, "LV.temp2.val=%dÿÿÿ\0", (int)(local_sh.bms_lv[7]));
        scic_msg(tmp);

        float sum = 0;
        int i = 0;
        for (; i < 6; i++)
        {
            sum += local_sh.bms_lv[i];
        }
        sprintf(tmp, "LV.tot.val=%dÿÿÿ\0", (int)(sum*1000));
        scic_msg(tmp);

}

void updatePage4()
{
    sprintf(tmp, "motor.mot1.val=%dÿÿÿ\0", (int)local_sh.motorVal2[0].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "motor.mot2.val=%dÿÿÿ\0", (int)local_sh.motorVal2[1].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "motor.mot3.val=%dÿÿÿ\0", (int)local_sh.motorVal2[2].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "motor.mot4.val=%dÿÿÿ\0", (int)local_sh.motorVal2[3].AMK_TempMotor);
    scic_msg(tmp);
}


void updatePage5()
{
    sprintf(tmp, "inverter.inv1n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[0].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv2n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[1].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv3n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[2].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv4n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[3].AMK_TempInverter);
    scic_msg(tmp);
}

void updatePage6()
{
    sprintf(tmp, "igbt.igbt1n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[0].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt2n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[1].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt3n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[2].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt4n.val=%dÿÿÿ\0", (int)local_sh.motorVal2[3].AMK_TempIGBT);
    scic_msg(tmp);
}

void updatePage7()
{
    sprintf(tmp, "smu.prerad.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[0] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.precold.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[1] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.premot.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[2] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.postmot.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[3] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.prerad2.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[4] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.precold2.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[5] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.premot2.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[6] - 273.15));
    scic_msg(tmp);
    sprintf(tmp, "smu.postmot2.val=%dÿÿÿ\0", (int)(local_sh.imu.temperatures_shared[7] - 273.15));
    scic_msg(tmp);
}


void updatePage8()
{
    sprintf(tmp, "pwr_set.speedlim.txt=\"%d\"ÿÿÿ\0", (int)( car_settings.max_speed / 1000));
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.trqf.txt=\"%.1f\"ÿÿÿ\0", car_settings.front_motor_scale);
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.trqr.txt=\"%.1f\"ÿÿÿ\0", car_settings.rear_motor_scale);
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.powerlim.txt=\"%d\"uÿÿÿ\0", (int)(car_settings.power_limit / 1000));
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.regcurr.txt=\"%.1f\"uÿÿÿ\0", car_settings.max_regen_current);
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.maxpostrq.txt=\"%.1f\"uÿÿÿ\0", car_settings.max_pos_torque);
    scic_msg(tmp);
    sprintf(tmp, "pwr_set.maxnegtrq.txt=\"%.1f\"uÿÿÿ\0", car_settings.max_neg_torque);
    scic_msg(tmp);
}


void updatePage9(){

    setSelector1_update();
    setSelector2_update();
    setAckSetup();

}


void updatePage10(){

    sprintf(tmp, "pedalSetup.thr_req.val=%dÿÿÿ\0", local_sh.pedals.throttle_req_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.brk_req.val=%dÿÿÿ\0", local_sh.pedals.brk_req_shared);
    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.thr.val=%dÿÿÿ\0", local_sh.status.throttle_shared);
    scic_msg(tmp);
    sprintf(tmp, "pedalSetup.brk.val=%dÿÿÿ\0", local_sh.status.brake_shared);
    scic_msg(tmp);

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
    sprintf(tmp, "Drv_END.tot.val=%dÿÿÿ\0", (int)(sum*1000));
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.low_lv.val=%dÿÿÿ\0", (int)(getLowestLvVoltage()*1000));
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.high_temp.val=%dÿÿÿ\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.low.val=%dÿÿÿ\0",(int)local_sh.bms.min_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "Drv_END.med.val=%dÿÿÿ\0",(int)local_sh.bms.mean_bms_voltage_shared);
    scic_msg(tmp);
}


void updatePage12(){

    sprintf(tmp, "Drv_SPEED.actualKmh.val=%dÿÿÿ\0", local_sh.status.actualVelocityKMH_shared);
    scic_msg(tmp);

}


void setSelector1_update(){

    n_setup = display.selector_setup;

    if(old_setup != n_setup){


      if (old_setup != old_ack_setup){
          sprintf(tmp, "setupPage.setup%d.bco=54938ÿÿÿ\0", old_setup);
          scic_msg(tmp);
      }


      old_setup = n_setup;

      if (old_setup != old_ack_setup){
          sprintf(tmp, "setupPage.setup%d.bco=YELLOWÿÿÿ\0", n_setup);
          scic_msg(tmp);

      }
    }
}


void setSelector2_update(){

    sprintf(tmp, "setupPage.setup0.txt=\"%.1f\"ÿÿÿ\0", car_settings.presets_regen[display.selector_regen]);
    scic_msg(tmp);
    sprintf(tmp, "setupPage.setup1.txt=\"%.1f\"ÿÿÿ\0", car_settings.presets_max_pos[display.selector_maxpos]);
    scic_msg(tmp);
    sprintf(tmp, "setupPage.setup2.txt=\"%.1f\"ÿÿÿ\0", car_settings.presets_max_neg[display.selector_maxneg]);
    scic_msg(tmp);
    sprintf(tmp, "setupPage.setup3.val=\"%d\"ÿÿÿ\0", (int) (car_settings.presets_power[display.selector_power] / 1000));
    scic_msg(tmp);
    sprintf(tmp, "setupPage.setup4.val=\"%d\"ÿÿÿ\0", (int) (car_settings.presets_speed[display.selector_speed] / 1000 ));
    scic_msg(tmp);
    sprintf(tmp, "setupPage.setup5.val=\"%.1f\"ÿÿÿ\0", car_settings.presets_coppie_rear[display.selector_trqr]);
    scic_msg(tmp);
    sprintf(tmp, "setupPage.setup6.txt=\"%.1f\"ÿÿÿ\0", car_settings.presets_coppie_front[display.selector_trqf]);
    scic_msg(tmp);
}



void setAckSetup(){
    int i;
    ack = display.ack_setup;
    if (old_ack_setup != ack){
        for (i = 0; i < 7; i++){
            if (i == ack){
                sprintf(tmp, "setupPage.setup%d.bco=GREENÿÿÿ\0", i);
                old_ack_setup = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "setupPage.setup%d.bco=54938ÿÿÿ\0", i);
                scic_msg(tmp);
            }
        }
    }
}

/*
void setSelectorPowerControl(){
    n_setup = display.selector_p;
    if(old_setup_power != n_setup){


      if (old_setup_power != old_ack_power){
          sprintf(tmp, "powercontrol.setup%d.bco=54938ÿÿÿ\0", old_setup_power);
          scic_msg(tmp);
      }


      old_setup_power = n_setup;

      if (old_setup_power != old_ack_power){
          sprintf(tmp, "powercontrol.setup%d.bco=YELLOWÿÿÿ\0", n_setup);
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
                sprintf(tmp, "powercontrol.setup%d.bco=GREENÿÿÿ\0", i);
                old_ack_power = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "powercontrol.setup%d.bco=54938ÿÿÿ\0", i);
                scic_msg(tmp);
            }
        }

    }
}
*/

void setSelectorPedalConfig(){
    n_setup = display.selector_pedal_setup;

    if(old_setup_pedal_setup != n_setup){


      if (old_setup_pedal_setup != old_ack_pedal_setup){
          sprintf(tmp, "pedalSetup.setup%d.bco=54938ÿÿÿ\0", old_setup_pedal_setup);
          scic_msg(tmp);
      }


      old_setup_pedal_setup = n_setup;

      if (old_setup_pedal_setup != old_ack_pedal_setup){
          sprintf(tmp, "pedalSetup.setup%d.bco=YELLOWÿÿÿ\0", n_setup);
          scic_msg(tmp);

      }

    }
}

void setAckPedalConfig(){

    ack = display.ack_pedal_setup;

    sprintf(tmp, "pedalSetup.brk_rel.val=%dÿÿÿ\0", local_sh.pedals.brk_low_calibration);
                    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.brk_pr.val=%dÿÿÿ\0", local_sh.pedals.brk_high_calibration);
                    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.acc1_pr.val=%dÿÿÿ\0", local_sh.pedals.acc1_high_calibration);
                    scic_msg(tmp);
                    sprintf(tmp, "pedalSetup.acc2_pr.val=%dÿÿÿ\0", local_sh.pedals.acc2_high_calibration);
                    scic_msg(tmp);

    sprintf(tmp, "pedalSetup.acc1_rel.val=%dÿÿÿ\0", local_sh.pedals.acc1_low_calibration);
                    scic_msg(tmp);
                    sprintf(tmp, "pedalSetup.acc2_rel.val=%dÿÿÿ\0", local_sh.pedals.acc1_low_calibration);
                    scic_msg(tmp);

    if (old_ack_pedal_setup != ack){


        sprintf(tmp, "pedalSetup.setup%d.bco=GREENÿÿÿ\0", ack);
        scic_msg(tmp);

        old_ack_pedal_setup = ack;

        int i = 0;
        for (i = 0; i < 4; i++){
            if (i != ack){
                sprintf(tmp, "pedalSetup.setup%d.bco=54938ÿÿÿ\0", i);
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
