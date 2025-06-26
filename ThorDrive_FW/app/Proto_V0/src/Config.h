//Serial Port
#define SerialBaud 115200
#define SYSTEM_TICK_HZ 100

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LOW
#define LOW 0
#endif

//3Phase MOSFET DRIVER (Inverted LOGIC)

#define DRIVER_Ah_PinNum 2
#define DRIVER_Ah_ON HIGH

#define DRIVER_Bh_PinNum 3
#define DRIVER_Bh_ON HIGH

#define DRIVER_Ch_PinNum 4
#define DRIVER_Ch_ON HIGH

#define DRIVER_Al_PinNum 5
#define DRIVER_Al_ON LOW

#define DRIVER_Bl_PinNum 6
#define DRIVER_Bl_ON LOW

#define DRIVER_Cl_PinNum 7
#define DRIVER_Cl_ON LOW


//SPEED CONTROL (PWM) NANED with High side pins
#define SPEED_PinNum 10
#define SPEED_ON HIGH


//INVERTED  HALL SENSORS
#define HALL_PORT PORTB

#define HALL_A_PinNum 8
#define HALL_A_ON LOW

#define HALL_B_PinNum 9
#define HALL_B_ON LOW

#define HALL_C_PinNum 11
#define HALL_C_ON LOW

//HALT_LED PIN 
#define CTRL_LED_PinNum 13
#define CTRL_LED_ON LOW

//CTRL_BTN PIN 
#define CTRL_BTN_PinNum 12
#define CTRL_BTN_ON HIGH



//Controller Configuration
#define accelleration_pps 1 //Accelleration in percentage per second (percentage from full speed) 
#define minSpeed_perc 5 //Minimum duty cycle percentage for the motor to start
#define maxSpeed_perc 90 //Maximum duty cycle percentage for the motor to run (Check bootstrap high side drive limits)
#define SWITCHING_FREQ 10000 
#define POLE_PAIRS 1