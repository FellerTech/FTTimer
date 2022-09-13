/**
 *
 * References:
 * - 
 */

#include <string>
#include <chrono>
#include <FTTimer.hpp>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <algorithm>

#include <date.h>

#include<vector>

namespace FTTimer
{
  std::string version = BUILD_VERSION;

  /////////////////////////////////////////////
  // returns the timestamp
  /////////////////////////////////////////////
  std::string getVersion() {
    return version;
  }

  /////////////////////////////////////////////
  // returns current time in nanoseconds 
  /////////////////////////////////////////////
  double getNsecTimestamp() {
    std::chrono::time_point<std::chrono::system_clock> now = 
        std::chrono::system_clock::now();

    auto dur = now.time_since_epoch();
    auto tics = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    double usecs = static_cast<double>(tics)/ 1e9;

    return usecs;
  }

  /////////////////////////////////////////////
  // returns current time in milliseconds
  /////////////////////////////////////////////
  double getTimestamp() {
    std::chrono::time_point<std::chrono::system_clock> now = 
        std::chrono::system_clock::now();

    auto dur = now.time_since_epoch();
    auto tics = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    double usecs = static_cast<double>(tics)/ 1e6;

    return usecs;
  }


  /*
  /////////////////////////////////////////////
  // converts a timestamp to a duration
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

    auto usec_dur = nanoseconds{static_cast<uint64_t>(timestamp * 1e9)};

    time_point<system_clock> tp = time_point<system_clock>(nanoseconds(usec_dur));
   
    std::stringstream ss;
    using namespace date;
    ss << tp;
    return ss.str();
  }

  /////////////////////////////////////////////
  // convertsa a string to a timestamp
  /////////////////////////////////////////////
  double convertStringToTimestamp( std::string timeString ) {
    using namespace std;
    using namespace std::chrono;
    istringstream temp_ss(timeString);
    date::sys_time<nanoseconds> tp;
    temp_ss >> date::parse("%F %T", tp);

    double duration = double(tp.time_since_epoch().count()/1.0e9);
    return duration;
  }

  //////////////////////////////////////////////////////////// 
  // Stopwatch class functions
  //////////////////////////////////////////////////////////// 
  bool Stopwatch::isRunning() {
    if(start_ != 0 ) {
      return true;
    }

    return false;
  }

  //start the lap/new lap
  bool Stopwatch::start() {
    double now = getNsecTimestamp();

    //If not running, return false
    if( start_ != 0 ) {
      return false;
    }

    start_ = now;
    return true;
  }

  //Stops the clock
  double Stopwatch::stop() {
    double now = getNsecTimestamp();
    if(start_ == 0 ) {
      return -1.0; 
    }

    elapsed_    = elapsed_    + now;
    lapElapsed_ = lapElapsed_ + now;
    start_ = 0;

    return elapsed_;
  }

  //Resets the clock
  bool Stopwatch::reset() {
    start_       = 0;
    elapsed_     = 0;
    lapElapsed_ = 0;

    laps_.clear();

    return true;
  }

  //Records a lap
  double Stopwatch::lap() {
    double now = getNsecTimestamp();

    if( start_ == 0 ) {
      return -1.0;
    }

    elapsed_ = elapsed_ + now - start_;
    lapElapsed_ = lapElapsed_ + now - start_;
    laps_.push_back(lapElapsed_);

    start_ = now;

    return lapElapsed_;
  }
}

