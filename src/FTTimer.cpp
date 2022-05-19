/* Program to demonstrate time taken by function fun() */
#include <chrono>
#include <FTTimer.hpp>


namespace FTTimer
{
  /////////////////////////////////////////////
  // returns current time in milliseconds
  /////////////////////////////////////////////
  double getTimestamp() {
    //auto now = std::chrono::system_clock::now();

    std::chrono::time_point<std::chrono::system_clock> now = 
      std::chrono::system_clock::now();

    auto duration = now.time_since_epoch();
    auto tics = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();

    double usecs = static_cast<double>(tics);

    return usecs/1e6;
  }

  /////////////////////////////////////////////
  // return the current time as a string
  /////////////////////////////////////////////
  std::string convertTimestampToString( double timestamp ) {
    using std::chrono;

    microseconds usec = timestamp *1e6;
    duration<double, microseconds>



  }

}

