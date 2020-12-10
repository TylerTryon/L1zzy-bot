/* This is for assorted utility functions that I may need for various reasons.
*/

#include <stdlib.h>


// Function to get a random number within a certain range
int randomInt(int N)
{
    return (double)rand()/RAND_MAX * N;
}