/*
 * display.c
 *
 *  Created on: 18 feb 2022
 *      Author: ludon
 */
#include "display.h"


void updatePage(Uint16 page){

    if (currentPage!=page){
    switch(page){
        case PAGE_1:
          currentPage=PAGE_1;
          scic_msg("page 1ÿÿÿ\0");
          setStatus();
        break;
        case PAGE_2:
            currentPage=PAGE_3;
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

void setSelector(){
    n_setup = display.selector;
    if(old_setup != n_setup){

      if (old_setup != old_ack){
          sprintf(tmp, "powercontrol.setup%d.bco=54938ÿÿÿ\0", old_setup);
          scic_msg(tmp);
      }


      old_setup = n_setup;

      if (old_setup != old_ack){
          sprintf(tmp, "powercontrol.setup%d.bco=YELLOWÿÿÿ\0", n_setup);
          scic_msg(tmp);
      }

    }
}

void setAck(){
    //Serial.println(String(msg.buf[0]));
    int i;
    ack = display.ack;
    if (old_ack != ack){
        for (i = 0; i < 8; i++){
            if (i == ack){
                sprintf(tmp, "powercontrol.setup%d.bco=GREENÿÿÿ\0", i);
                old_ack = ack;
                scic_msg(tmp);
            }
            else {
                sprintf(tmp, "powercontrol.setup%d.bco=54938ÿÿÿ\0", i);
                scic_msg(tmp);
            }
        }

    }


    //da fare in cpu2
//    CAN_message_t power_change;
//    power_change.id=0x81;
//    power_change.buf[0]=presets[n_setup];
//    power_change.len=1;
//    Can_veicolo.write(power_change);
}

void setStatus(){

  if(local_sh.status.status_shared & 0b00000001) scic_msg("main_dark.hv.bco=GREENÿÿÿ\0");
  else scic_msg("main_dark.hv.bco=REDÿÿÿ\0");


  if(local_sh.status.status_shared & 0b00000010) scic_msg("main_dark.lv.bco=REDÿÿÿ\0");
  else scic_msg("main_dark.lv.bco=GREENÿÿÿ\0");


  if(local_sh.status.status_shared & 0b00000100) scic_msg("main_dark.temp.bco=REDÿÿÿ\0");
  else scic_msg("main_dark.temp.bco=GREENÿÿÿ\0");


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

void setAMK_fl(){
    sprintf(tmp, "tyre_motor_d.mot1.val=%dÿÿÿ\0",local_sh.motorVal2[0].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt1n.val=%dÿÿÿ\0",local_sh.motorVal2[0].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv1n.val=%dÿÿÿ\0",local_sh.motorVal2[0].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "motor_status.errorfl.txt=%dÿÿÿ\0",local_sh.motorVal2[0].AMK_ErrorInfo);
    scic_msg(tmp);
}

void setAMK_fr(){
    sprintf(tmp, "tyre_motor_d.mot2.val=%dÿÿÿ\0",local_sh.motorVal2[1].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt2n.val=%dÿÿÿ\0",local_sh.motorVal2[1].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv2n.val=%dÿÿÿ\0",local_sh.motorVal2[1].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "motor_status.errorfr.txt=%dÿÿÿ\0",local_sh.motorVal2[1].AMK_ErrorInfo);
    scic_msg(tmp);
}

void setAMK_rl(){
    sprintf(tmp, "tyre_motor_d.mot3.val=%dÿÿÿ\0",local_sh.motorVal2[2].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt3n.val=%dÿÿÿ\0",local_sh.motorVal2[2].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv3n.val=%dÿÿÿ\0",local_sh.motorVal2[2].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "motor_status.errorrl.txt=%dÿÿÿ\0",local_sh.motorVal2[2].AMK_ErrorInfo);
    scic_msg(tmp);
}

void setAMK_rr(){
    sprintf(tmp, "tyre_motor_d.mot4.val=%dÿÿÿ\0",local_sh.motorVal2[3].AMK_TempMotor);
    scic_msg(tmp);
    sprintf(tmp, "igbt.igbt4n.val=%dÿÿÿ\0",local_sh.motorVal2[3].AMK_TempIGBT);
    scic_msg(tmp);
    sprintf(tmp, "inverter.inv4n.val=%dÿÿÿ\0",local_sh.motorVal2[3].AMK_TempInverter);
    scic_msg(tmp);
    sprintf(tmp, "motor_status.errorrr.txt=%dÿÿÿ\0",local_sh.motorVal2[3].AMK_ErrorInfo);
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

void setBMS_voltage(){
    sprintf(tmp, "bms.high.val=%dÿÿÿ\0",local_sh.bms.max_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.medium.val=%dÿÿÿ\0",local_sh.bms.mean_bms_voltage_shared);
    scic_msg(tmp);
    sprintf(tmp, "bms.low.val=%dÿÿÿ\0",local_sh.bms.min_bms_voltage_shared);
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
