/* Program to demonstrate time taken by function fun() */
#include <stdio.h>
#include <time.h>
#include <FTTimer.hpp>

namespace FTTimer
{
  /** 
   * \brief returns current time in milliseconds
   */
  double getTime() {
    //auto now = std::chrono::system_clock::now();

    std::chrono::time_point<std::chrono::system_clock> now = 
      std::chrono::system_clock::now();

    auto duration = now.time_since_epoch();
    auto tics = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    double usecs = static_cast<double>(tics);

    return usecs/1e6;
  }
}


/*  
// A function that terminates when enter key is pressed
void fun()
{
    printf("fun() starts \n");
    printf("Press enter to stop fun \n");
    while(1)
    {
        if (getchar())
            break;
    }
    printf("fun() ends \n");
}
  
// The main program calls fun() and measures time taken by fun()
int main()
{
    // Calculate the time taken by fun()
    clock_t t;
    t = clock();
    fun();
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  
    printf("fun() took %f seconds to execute \n", time_taken);
    return 0;
}
*/
