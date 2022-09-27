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
  Stopwatch::Stopwatch() {
    reset();
  }

  /////////////////////////////////////////////
  // returns current time in nanoseconds 
  /////////////////////////////////////////////
  std::chrono::time_point<std::chrono::steady_clock> Stopwatch::getTimePoint() {
    std::chrono::time_point<std::chrono::steady_clock> now = 
        std::chrono::steady_clock::now();

//    auto dur = now.time_since_epoch();
//    auto tics = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

//    double nsecs = static_cast<double>(tics)/ 1.0e9;
//    double nsecs = now;
//    std::cout << "NOW: "<<now<<std::endl;

    return now;
  }

  
  /////////////////////////////////////////////
  // sets the reference time
  /////////////////////////////////////////////
  bool Stopwatch::setTimePoint() {
    start_ = getTimePoint();
    return true;
  }

  /////////////////////////////////////////////
  // calculates offset
  /////////////////////////////////////////////
  double Stopwatch::getTimeOffset() {
    auto now = getTimePoint();

//    std::chrono::duration<double> diff = now - start_;
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now-start_);
    /*
    elapsed_    = elapsed_ + static_cast<double>(diff);
    lapElapsed_ = lapElapsed_ + static_cast<double>(diff);
    laps_.push_back(lapElapsed_);
    */
    return  diff.count()/1e9;
  }


  //Check if thec clock is running
  bool Stopwatch::isRunning() {
    return running_;
  }

  //start the lap/new lap
  bool Stopwatch::start() {
    if( running_ ) {
      return false;
    }

    bool rc = setTimePoint();
    if( rc ) {
      running_ = true;
    }
    return rc;
  }

  //Stops the clock
  double Stopwatch::stop() {
    if( !running_ ) {
      return -1.0;
    }

    double interval = getTimeOffset();

    elapsed_    = elapsed_    + interval;
    lapElapsed_ = lapElapsed_ + interval;
    running_ = false;

    return elapsed_;
  }

  //Resets the clock
  bool Stopwatch::reset() {
    running_     = false;
    elapsed_     = 0;
    lapElapsed_  = 0;

    laps_.clear();

    return true;
  }

  //Records a lap
  double Stopwatch::lap() {

    if( !running_ ) {
      return -1.0;
    }
    
    double interval = getTimeOffset();

    elapsed_    = elapsed_ + interval;
    lapElapsed_ = lapElapsed_ + interval;
    laps_.push_back(lapElapsed_);

    setTimePoint();

    return lapElapsed_;
  }

  //Returns current elapsed time without changing running state
  double Stopwatch::getElapsed() {
    double interval = 0.0;
    if( running_ ) {
        interval = getTimeOffset();
    }

    return elapsed_ + interval;
  }
}

