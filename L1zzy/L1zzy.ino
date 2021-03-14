#include "MotorDriver.h"
#include "Scheduler.h"
#include "Sonar.h"
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
  // Set up motor pins
  pinMode(L_MOTOR_DRIVER_PIN, OUTPUT);
  pinMode(R_MOTOR_DRIVER_PIN, OUTPUT);

  digitalWrite(L_MOTOR_DRIVER_PIN, LOW);
  digitalWrite(R_MOTOR_DRIVER_PIN, LOW);

  // Set up Sonar pins
  pinMode(SONAR_TRIGGER_PIN, OUTPUT);
  pinMode(SONAR_ECHO_PIN, INPUT);

  digitalWrite(SONAR_TRIGGER_PIN, LOW);

  // Set the lag clock
  LagClock = millis();
}


void loop() {
  // This is to try to reduce the number of calls to millis()
  unsigned long currentClock = millis();

  // Set the trigger pin high before the task loop in order to prevent a second delay
  digitalWrite(SONAR_TRIGGER_PIN, HIGH); 

  // Tasks loop
  for (int i = 0; i < TasksArraySize; i++)
  {
    SystemTasks[i].Countdown(currentClock - LagClock);
  }

  // Function to run the sonar sensor and calculate the distance to any objects
  // For some reason, this must be in the loop() function
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  SetPulseWidth(pulseIn(SONAR_ECHO_PIN, HIGH));
}
