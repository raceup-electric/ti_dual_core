#ifndef _ATC_MANAGEMENT_
#define _ATC_MANAGEMENT_

enum type_message {TBS, SUSPS, TEMPS};

// only for compatibility with legacy code
//--------------------------------------
extern int throttle;
extern int brake;
extern int steering;
extern unsigned char imp;
extern float suspensions[4];
extern float temperatures[10];
//--------------------------------------

void atc_update(unsigned int data[], enum type_message t);

#endif
