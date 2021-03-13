#include "MotorDriver.h"
#include "Scheduler.h"
#include "StateMachine.h"

// Previous time for calculating time delta
unsigned long LagClock;


// Task list has to be defined outside the startup function
Task SystemTasks[] = {
    Task(&SetMotors, 100),
    Task(&LockTick, 1000),
    Task(&Wander, 1000)
  };
const int TasksArraySize = sizeof(SystemTasks) / sizeof(Task);


void setup() {
  // Set up output pins
  pinMode(L_MOTOR_DRIVER_PIN, OUTPUT);
  pinMode(R_MOTOR_DRIVER_PIN, OUTPUT);

  digitalWrite(L_MOTOR_DRIVER_PIN, LOW);
  digitalWrite(R_MOTOR_DRIVER_PIN, LOW);

  // Set the lag clock
  LagClock = millis();
}


void loop() {
  // This is to try to reduce the number of calls to millis()
  unsigned long currentClock = millis();
  
  for (int i = 0; i < TasksArraySize; i++)
  {
    SystemTasks[i].Countdown(currentClock - LagClock);
  }
  
}
