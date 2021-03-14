/* This uses the sonar sensor to see if anything is in front of L1zzy
*/

// Name mangling prevention
#ifdef __cplusplus
extern "C" {
#endif

#define SONAR_ECHO_PIN 8
#define SONAR_TRIGGER_PIN 9

// Get and set functions for distance to target
long GetDistance(void);
void SetPulseWidth(int);


#ifdef __cplusplus
}
#endif