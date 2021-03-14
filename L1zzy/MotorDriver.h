/* This is the motor driver. Based off the state of the system,
it sets the states for each wheel motor.
*/

// Name mangling prevention
#ifdef __cplusplus
extern "C" {
#endif

#define L_MOTOR_DRIVER_PIN 11
#define R_MOTOR_DRIVER_PIN 10

// If LOW or HIGH are undefined, define them
#ifndef LOW
#define LOW 0
#endif

#ifndef HIGH
#define HIGH 1
#endif

// Left and right motor 
void SetMotors(void);

#ifdef __cplusplus
}
#endif
