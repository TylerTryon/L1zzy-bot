/* This uses the sonar sensor to see if anything is in front of L1zzy.
It seems odd to split this between the main loop and here, this is because
the sonar doesn't work unless it is in the main loop, and I want to avoid
as many calls the time to distance conversion function as possible.
*/

#include "MotorDriver.h"
#include "Sonar.h"

static int timeToTarget = 0;

const float alpha = 0.2;


// Converts time in microseconds to centimeters
long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}


// Set the time between the trigger and echo
void SetPulseWidth(int width)
{
    timeToTarget = width;
}


// Get function for distance to target
long GetDistance(void)
{
    return microsecondsToCentimeters(timeToTarget);
}