CHANGELOG
v1.0 release stabile
v1.1 aggiunto power control 
v1.2 aggiunta "trappola" per RF e HV (chiedi a Fano per info)
v1.3 sistemate diverse "trappole", funzione per RTDS, ripartizione di coppia semplice. Al logger viene mandato solo CarStatus e inoltrati i pacchetti sendyne
v1.4 ora la macchina va in HV se anche solo un motore ha HV on ed esce dall'HV solo se tutti i motori hanno HV off. Stessa cosa per RF.
	 Vengono inviate le temperature al logger ogni secondo. Il pacchetto AMK_ActualValues2 viene inoltrato al logger una volta ogni 100 messaggi ricevuti
v1.5 aggiunto torque vectoring, cambiato il modo in cui si definisce coppia massima e in cui si decide la coppia richiesta. Aggiornata calibrazione potenziometri 


ISTRUZIONI PER TESTARE LA CENTRALINA

1. Nel caso la centralina non fosse flashata, fare riferimento alla guida reperibile 
	nel drive: Electric > Elettronica > Software > Documentazione F28379D > F28379D_manuale.pdf nella sezione "Build, RAM, FLASH e Boot".
	
2. Alternativamente, si può collegare la centralina al PC tramite il cavo mini-USB e procedere con il debug.
	Fare riferimento alla guida per maggiori info.
	
3. Definire il tipo di debug che si vuole fare:

	3.1 Right click on the project > Properties > CCS Build > C2000 Compiler > Predefined Symbols
	3.2 Add...

 	"TSAL_CTRL" (DEPRECATED)to let the ECU control the TSAL (DEPRECATED)
	"DEBUG_NO_HV"  			for debug purposes with no inverter and no HV > HV ON is simulated by ECU
 	"DEBUG_HV"     			for debug purposes, with inverter and/or HV
 	"NO_REG_BRAKE" 			to prevent the ECU from sending negative torque setpoint to the inverter. No regenerative braking
 	"NO_STEERING_SENSOR"	if the steering sensor doesn't work. Steering is always 0°
 	"NO_POWER_CONTROL"		deactivate power control
 	"NO_TORQUE_VECTORING" 	deactivate torque vectoring algorithm
 	"CONST_FAN_SPEED"       constant fan speed at 50
 	
 	ASSICURARSI DI FARLO PER CONFIGURAZIONE FLASH E RAM (A SECONDA DI COSA SI USA)