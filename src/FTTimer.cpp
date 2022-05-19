/**
 *
 * References:
 * - 
 */

#include <string>
#include <chrono>
#include <FTTimer.hpp>
#include <sstream>
#include <ctime>

#include <date.h>

#include <iostream>


namespace FTTimer
{
  
  /////////////////////////////////////////////
  // returns current time in milliseconds
  /////////////////////////////////////////////
  double getTimestamp() {
    std::chrono::time_point<std::chrono::system_clock> now = 
    std::chrono::system_clock::now();

    auto dur = now.time_since_epoch();
    auto tics = std::chrono::duration_cast<std::chrono::microseconds>(dur).count();

    double usecs = static_cast<double>(tics)/ 1e6;

    return usecs;
  }


  /*
  /////////////////////////////////////////////
  // converts a tiemstamp to a duration
  /////////////////////////////////////////////
  std::chrono::duration convertTimestampToDuration( double timestamp ) {
    int64_t secs = static_cast<int64_t>(timestamp);
    int64_t nsecs = timestamp *1e9 - secs;

    return duration;
  }
  */

  /////////////////////////////////////////////
  // return the current time as a string
  /////////////////////////////////////////////
  std::string convertTimestampToString( double timestamp ) {
    using namespace std::chrono;

    auto sec_dur  = seconds { static_cast<uint64_t>(timestamp) };
    auto usec_dur = microseconds{static_cast<uint64_t>(timestamp * 1e6)};
//    auto nsec_dur = duration_cast<nanoseconds>( timestamp *1e9);
//
    time_point<system_clock> tp = time_point<system_clock>(nanoseconds(usec_dur));
   
    std::stringstream ss;
    using namespace date;
    ss << tp;
    return ss.str();
    /*
    std::time_t ttp =  system_clock::to_time_t(tp);

    std::string output = std::ctime( &ttp);
    std::string output = put_time( tp, 
    output.pop_back();
    return output;
    */

  }



//    auto duration = duration_cast<std::chrono::nanoseconds>, timestamp * 1e9;
//    auto timePoint  = std::chrono::sytem_clock::time_point<std::chrono::system_clock, std::chrono::duration> (duration);







}

