/* This is the motor driver. Based off the state of the system,
it sets the states for each wheel motor.*/

#include "StateMachine.h"
#include "MotorDriver.h"



// Sets the motors based off the state of the system
void SetMotors()
{
    Lizzy_States state = GetCurrentState();

    switch (state)
    {
    case SLEEP:
        digitalWrite(L_MOTOR_DRIVER_PIN, LOW);
        digitalWrite(R_MOTOR_DRIVER_PIN, LOW);
        break;

    case FORWARDS:
        digitalWrite(L_MOTOR_DRIVER_PIN, HIGH);
        digitalWrite(R_MOTOR_DRIVER_PIN, HIGH);
        break;
    
    case TURN_LEFT:
        digitalWrite(L_MOTOR_DRIVER_PIN, LOW);
        digitalWrite(R_MOTOR_DRIVER_PIN, HIGH);
        break;

    case TURN_RIGHT:
        digitalWrite(L_MOTOR_DRIVER_PIN, HIGH);
        digitalWrite(R_MOTOR_DRIVER_PIN, LOW);
        break;

    default:
        break;
    }
}
