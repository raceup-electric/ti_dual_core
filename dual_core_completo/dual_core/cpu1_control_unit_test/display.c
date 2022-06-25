/*
 * display.c
 *
 *  Created on: 18 feb 2022
 *      Author: ludon
 */
#include "display.h"

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
         }
}
void updatePage(Uint16 page){

    if (currentPage!=page){
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
      }
    }
}

void updatePage1()
{
    if(local_sh.status.status_shared & 0b00000001) scic_msg("main_dark.hv.bco=GREENÿÿÿ\0");
    else scic_msg("main_dark.hv.bco=REDÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00000010) scic_msg("main_dark.lv.bco=REDÿÿÿ\0");
    else scic_msg("main_dark.lv.bco=GREENÿÿÿ\0");

    // DA Sostituire con fault hv
    //if(local_sh.status.status_shared & 0b00000100) scic_msg("main_dark.temp.bco=REDÿÿÿ\0");
    //else scic_msg("main_dark.temp.bco=GREENÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00001000) scic_msg("main_dark.pre.bco=GREENÿÿÿ\0");
    else scic_msg("main_dark.pre.bco=REDÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00010000) scic_msg("main_dark.r2d.bco=GREENÿÿÿ\0");
    else scic_msg("main_dark.r2d.bco=REDÿÿÿ\0");


    if(local_sh.status.status_shared & 0b00100000) scic_msg("main_dark.brk.bco=REDÿÿÿ\0");
    else scic_msg("main_dark.brk.bco=GREENÿÿÿ\0");


    if(local_sh.status.status_shared & 0b01000000) scic_msg("main_dark.imp.bco=REDÿÿÿ\0");
    else scic_msg("main_dark.imp.bco=GREENÿÿÿ\0");


    if(local_sh.status.status_shared & 0b10000000) scic_msg("main_dark.rf.bco=GREENÿÿÿ\0");
    else scic_msg("main_dark.rf.bco=REDÿÿÿ\0");


    sprintf(tmp, "main_dark.speed.val=%dÿÿÿ\0",local_sh.status.actualVelocityKMH_shared);
    scic_msg(tmp);
}

void updatePage2()
{
    sprintf(tmp, "hv_val.voltage_HV.val=%dÿÿÿ\0", (int)local_sh.sendyne.sendyne_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "hv_val.lem.val=%dfÿÿÿ\0", (int)local_sh.sendyne.sendyne_current_shared);
    scic_msg(tmp);
    sprintf(tmp, "hv_val.curr_sens.val=%dÿÿÿ\0", (int)local_sh.sendyne.curr_sens_shared);
    scic_msg(tmp);
    sprintf(tmp, "hv_val.tot_power.val=%dÿÿÿ\0", (int)local_sh.sendyne.total_power_shared);
    scic_msg(tmp);
}
void updatePage3()
{
    if(local_sh.gpio.Sdc1_shared)
        scic_msg("gpio.sdc1.bco=REDÿÿÿ\0");
    else
        scic_msg("gpio.sdc1.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Sdc2_shared)
            scic_msg("gpio.sdc2.bco=REDÿÿÿ\0");
    else
            scic_msg("gpio.sdc2.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Sdc3_shared)
            scic_msg("gpio.sdc3.bco=REDÿÿÿ\0");
    else
            scic_msg("gpio.sdc3.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Sdc4_shared)
            scic_msg("gpio.sdc4.bco=REDÿÿÿ\0");
    else
            scic_msg("gpio.sdc4.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Sdc5_shared)
            scic_msg("gpio.sdc5.bco=REDÿÿÿ\0");
    else
            scic_msg("gpio.sdc5.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Sdc6_shared)
            scic_msg("gpio.sdc6.bco=REDÿÿÿ\0");
    else
            scic_msg("gpio.sdc6.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Bms_shared)
            scic_msg("gpio.bms.bco=REDÿÿÿ\0");
    else
            scic_msg("gpio.bms.bco=GREENÿÿÿ\0");

    if(local_sh.gpio.Imd_shared)
            scic_msg("gpio.imd.bco=REDÿÿÿ\0");
    else
            scic_msg("gpio.imd.bco=GREENÿÿÿ\0");

}

void updatePage4()
{
    sprintf(tmp, "bms.high.val=%dÿÿÿ\0", (int)local_sh.bms.max_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.medium.val=%dÿÿÿ\0", (int)local_sh.bms.mean_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.low.val=%dÿÿÿ\0", (int)local_sh.bms.min_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.highest_temp.val=%dÿÿÿ\0", (int)local_sh.bms.max_bms_temp_shared);
    scic_msg(tmp);
}

void updatePage5()
{
    sprintf(tmp, "tyre_motor_d.mot1.val=%dÿÿÿ\0", (int)local_sh.motorVal2[0].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "tyre_motor_d.mot2.val=%dÿÿÿ\0", (int)local_sh.motorVal2[1].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "tyre_motor_d.mot3.val=%dÿÿÿ\0", (int)local_sh.motorVal2[2].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "tyre_motor_d.mot4.val=%dÿÿÿ\0", (int)local_sh.motorVal2[3].AMK_TempMotor);
    scic_msg(tmp);
}

void updatePage6()
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

void updatePage7()
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


void updatePage8()
{
    setSelectorPowerControl();
    setAckPowerControl();
}

void updatePage9()
{
    setSelectorRegen();
    setAckRegen();
}


void setSelectorPowerControl(){
    n_setup = display.selector_p;
    if(old_setup_power != n_setup){

        /*int v;
        for(v = 0; v < 8; v++){
            if(v != old_setup_power || v != old_ack_power){
                sprintf(tmp, "powercontrol.setup%d.bco=54938ÿÿÿ\0", v);
                scic_msg(tmp);
            }
        }*/

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
    //Serial.println(String(msg.buf[0]));
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
void setSelectorRegen(){
    n_setup = display.selector_r;
    if(old_setup_regen != n_setup){

        /*int v;
        for(v = 0; v < 6; v++){
            if(v != old_setup_regen || v != old_ack_regen){
                sprintf(tmp, "regen.setup%d.bco=54938ÿÿÿ\0", v);
                scic_msg(tmp);
            }
        }*/

      if (old_setup_regen != old_ack_regen){
          sprintf(tmp, "regen.setup%d.bco=54938ÿÿÿ\0", old_setup_regen);
          scic_msg(tmp);
      }


      old_setup_regen = n_setup;

      if (old_setup_regen != old_ack_regen){
          sprintf(tmp, "regen.setup%d.bco=YELLOWÿÿÿ\0", n_setup);
          scic_msg(tmp);
      }

    }
}

void setAckRegen(){
    //Serial.println(String(msg.buf[0]));
    int i;
    ack = display.ack_r;
    if (old_ack_regen != ack){
        for (i = 0; i < 6; i++){
            if (i == ack){
                sprintf(tmp, "regen.setup%d.bco=GREENÿÿÿ\0", i);
                old_ack_regen = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "regen.setup%d.bco=54938ÿÿÿ\0", i);
                scic_msg(tmp);
            }
        }

    }
}




void setAMK_fl(){



    sprintf(tmp, "motor_status.errorfl.txt=%dÿÿÿ\0",(int)local_sh.motorVal2[0].AMK_ErrorInfo);
    scic_msg(tmp);
}

void setAMK_fr(){

    sprintf(tmp, "igbt.igbt2n.val=%dÿÿÿ\0",(int)local_sh.motorVal2[1].AMK_TempIGBT);
    scic_msg(tmp);

    sprintf(tmp, "motor_status.errorfr.txt=%dÿÿÿ\0",(int)local_sh.motorVal2[1].AMK_ErrorInfo);
    scic_msg(tmp);
}

void setAMK_rl(){

    sprintf(tmp, "igbt.igbt3n.val=%dÿÿÿ\0",(int)local_sh.motorVal2[2].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv3n.val=%dÿÿÿ\0",(int)local_sh.motorVal2[2].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "motor_status.errorrl.txt=%dÿÿÿ\0",(int)local_sh.motorVal2[2].AMK_ErrorInfo);
    scic_msg(tmp);
}

void setAMK_rr(){

    sprintf(tmp, "igbt.igbt4n.val=%dÿÿÿ\0",(int)local_sh.motorVal2[3].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv4n.val=%dÿÿÿ\0",(int)local_sh.motorVal2[3].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "motor_status.errorrr.txt=%dÿÿÿ\0",(int)local_sh.motorVal2[3].AMK_ErrorInfo);
    scic_msg(tmp);
}


void setTemps(){

    //da sistemare le temperature dei radiatori nello schermo prima
    /*sprintf(tmp, "fan_dark.rad1N.val=%dÿÿÿ\0",local_sh.Temps[0]);       //rad out L
    scic_msg(tmp);
    sprintf(tmp, "fan_dark.rad2N.val=%dÿÿÿ\0",local_sh.Temps[1]);         //rad out R
    scic_msg(tmp);
    sprintf(tmp, "fan_dark.rad3N.val=%dÿÿÿ\0",local_sh.Temps[2]);         //rad in L
    scic_msg(tmp);
    sprintf(tmp, "fan_dark.rad4N.val=%dÿÿÿ\0",local_sh.Temps[3]);
    scic_msg(tmp);*/
    sprintf(tmp, "fan_dark.n0.val=%dÿÿÿ\0",local_sh.Temps[6]);
    scic_msg(tmp);
    sprintf(tmp, "fan_dark.n1.val=%dÿÿÿ\0",local_sh.Temps[7]);
    scic_msg(tmp);
}



void setFLstatus(){
  if(local_sh.motorVal1[0].AMK_bInverterOn){
 scic_msg("motor_status.invonfl.bco=GREENÿÿÿ\0");
  }
  else{
 scic_msg("motor_status.invonfl.bco=REDÿÿÿ\0");
  }

  if(local_sh.motorVal1[0].AMK_bDerating){
 scic_msg("motor_status.derfl.bco=REDÿÿÿ\0");
  }
  else{
 scic_msg("motor_status.derfl.bco=GREENÿÿÿ\0");
  }
}

void setFRstatus(){
  if(local_sh.motorVal1[1].AMK_bInverterOn){
      scic_msg("motor_status.invonfr.bco=GREENÿÿÿ\0");
  }
  else{
      scic_msg("motor_status.invonfr.bco=REDÿÿÿ\0");
  }

  if(local_sh.motorVal1[1].AMK_bDerating){
      scic_msg("motor_status.derfr.bco=REDÿÿÿ\0");
  }
  else{
      scic_msg("motor_status.derfr.bco=GREENÿÿÿ\0");
  }
}

void setRLstatus(){
  if(local_sh.motorVal1[2].AMK_bInverterOn){
      scic_msg("motor_status.invonrl.bco=GREEN");

  }
  else{
      scic_msg("motor_status.invonrl.bco=RED");
  }

  if(local_sh.motorVal1[2].AMK_bDerating){
      scic_msg("motor_status.derrl.bco=RED");
  }
  else{
      scic_msg("motor_status.derrl.bco=GREEN");
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
