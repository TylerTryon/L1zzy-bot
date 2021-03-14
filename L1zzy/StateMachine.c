/* The state machine that determines what each part of the robot will be doing at any time
*/

#include "Sonar.h"
#include "StateMachine.h"
#include "Utilities.h"


// Persistent current state
static Lizzy_States SystemState = SLEEP;

// Lockout system
// If 
static int lockout = 0;

// Get the system state
Lizzy_States GetCurrentState(void)
{
    return SystemState;
}

// Set the system state
void SetCurrentState(Lizzy_States state)
{
    SystemState = state;
}


// Set the state lock
void SetLock(int locktime)
{
    lockout = locktime;
}

// Decrement the state lock value by 1 per tick
void LockTick()
{
    // Check value to prevent underflow
    if (lockout > 0)
    {
        lockout--;
    }
}


// Wander around
// Where will L1zzy go? Nobody knows
void Wander(void)
{
    // If L1zzy is too close to an object, then it should turn away
    if (GetDistance() > 10)
    {
        // If the state is locked, do not change the state
        if (lockout == 0)
        {
            int randState = randomInt(LAST_STATE);
            int randTime = randomInt(10);

            SetCurrentState(randState);
            SetLock(randTime);
        }
    }
    else
    {
        SetCurrentState(SLEEP);
        SetLock(5);
    }
}