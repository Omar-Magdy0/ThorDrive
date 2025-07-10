//Serial Port
#define SerialBaud 115200
#define SYSTEM_TICK_HZ 100



//3Phase MOSFET DRIVER (Inverted LOGIC)

#define DRIVER_Ah_PinNum 2
#define DRIVER_Ah_INVERT false

#define DRIVER_Bh_PinNum 3
#define DRIVER_Bh_INVERT false

#define DRIVER_Ch_PinNum 4
#define DRIVER_Ch_INVERT false

#define DRIVER_Al_PinNum 5
#define DRIVER_Al_INVERT true

#define DRIVER_Bl_PinNum 6
#define DRIVER_Bl_INVERT true

#define DRIVER_Cl_PinNum 7
#define DRIVER_Cl_INVERT true


//SPEED CONTROL (PWM) NANED with High side pins
#define SPEED_PinNum 10
#define SPEED_INVERT false

#define HALL_A_PinNum 8
#define HALL_A_INVERT true

#define HALL_B_PinNum 9
#define HALL_B_INVERT true

#define HALL_C_PinNum 11
#define HALL_C_INVERT true

//HALT_LED PIN 
#define CTRL_LED_PinNum 13
#define CTRL_LED_INVERT true

//CTRL_BTN PIN 
#define CTRL_BTN_PinNum 12
#define CTRL_BTN_INVERT false



//Controller Configuration
#define SWITCHING_FREQ 10000
#define accelleration_pps 2 //Accelleration in percentage per second (percentage from full speed) 
#define minSpeed_duty 0.05 //Minimum duty cycle percentage for the motor to start
#define maxSpeed_duty 0.9 //Maximum duty cycle percentage for the motor to run (Check bootstrap high side drive limits)
#define POLE_PAIRS 23