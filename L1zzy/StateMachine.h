/* The state machine that determines what each part of the robot will be doing at any time
*/

// Name mangling prevention
#ifdef __cplusplus
extern "C" {
#endif

// Possible states for the state machine
typedef enum
{
    SLEEP,
    FORWARDS,
    BACKWARDS, // Doesn't work yet because I only have one driver.
    TURN_LEFT,
    TURN_RIGHT,
    LAST_STATE
} Lizzy_States;


// Get and set functions for Lizzy
Lizzy_States GetCurrentState(void);
void SetCurrentState(Lizzy_States);

// Lockout functions
void SetLock(int locktime);
void LockTick(void);

// Wander mode
void Wander(void);

#ifdef __cplusplus
}
#endif