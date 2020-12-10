/* This is the scheduler for the system tasks.
*/

#include "Scheduler.h"

/* Constructor for Task
Takes in the fuction to be called when the timer expires
and the time until the task expires
*/ 
Task::Task(FunctionPtrT function, int taskrate)
{
    taskFunctionPointer = function;
    taskRate = taskrate;
    remainingTime = taskrate;
}


/* Function to count down the time ramaining for a task.
Requires the amount of time since the last time it was called in miliseconds.
Time change system is handled in the main loop.
This function will also call the task function if the timer expires.
*/
void Task::Countdown(int timeChange)
{
    // Reduce the remaining time by the amount that time has changed since last run
    remainingTime -= timeChange;

    // If the timer has expired, call the task function
    if (remainingTime <= 0)
    {
        taskFunctionPointer();
    }
}