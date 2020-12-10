/* This is the scheduler for the system tasks.
*/

// Typedef for function pointer
typedef void (*FunctionPtrT)();

class Task
{
    private:
        // Function that the task will call when the timer runs out
        FunctionPtrT taskFunctionPointer;

        // Time remaining until the function is run in ms
        signed int remainingTime;

        // Holds the task rate for reset
        int taskRate;


    public:
        Task(FunctionPtrT function, int taskrate);
        void Countdown(int timeChange);
};