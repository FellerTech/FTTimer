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
  std::string version = BUILD_VERSION;           //! set version at  compile time 

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
  // returns timepoint in nanoseconds 
  /////////////////////////////////////////////
  std::chrono::time_point<std::chrono::steady_clock> Stopwatch::getTimePoint() {
    std::chrono::time_point<std::chrono::steady_clock> now = 
        std::chrono::steady_clock::now();

    return now;
  }

  
  /////////////////////////////////////////////
  // calculates offset
  /////////////////////////////////////////////
  double Stopwatch::getTimeOffset() {
    auto now = getTimePoint();
    auto diff = std::chrono::duration_cast<std::chrono::nanoseconds>(now-referenceTime_ );
    double offset = diff.count()/1e9;
    return offset;
  }


  //Check if thec clock is running
  bool Stopwatch::isRunning() {
    if( intervalStart_ ) {
      return true;
    }

    return false;
  }

  //start the lap/new lap
  double Stopwatch::start() {
    auto now = getTimeOffset();
    end_ = now;

    //If we are not in an interval, start a new one
    if( intervalStart_ == 0 ) {
      intervalStart_ = now;
    }
    else {
      elapsed_ += now - intervalStart_;
      intervalStart_ = now;
    }

    //If this is the first start after a reset, then set the start time
    if( start_ == 0) {
      start_ = now;
    }

    return elapsed_;
  }

  //Stops the clock
  double Stopwatch::stop() {
    double now = getTimeOffset();

    //Calculate timepoint since last inverval
    if( intervalStart_ > 0 ) {
      elapsed_ += now - intervalStart_;
      end_ = now;
    }

    intervalStart_ = 0;

    return elapsed_;
  }

  //Records a lap
  double Stopwatch::lap() {
    auto now = getTimeOffset();
    end_ = now;

    //If we are not in an interval return error (-1)
    if( intervalStart_ == 0 ) {
      return -1;
    }

    //If we are in an interval, accumulate
    elapsed_ += now - intervalStart_;

    //Calculate lap duration and append to laps vector
    double lapElapsed = 0;

    lapElapsed = now - lapStart_;
    laps_.push_back( lapElapsed );	      

    lapStart_ = now;

    //Return time of lap
    return lapElapsed;
  }

  //Resets the clock
  bool Stopwatch::reset() {
    start_         = 0;
    end_           = 0;
    intervalStart_ = 0;
    elapsed_       = 0;

    laps_.clear();

    //Establish a new referencet time
    referenceTime_ = getTimePoint();

    return true;
  }


  std::vector<double> Stopwatch::getLaps() {
    return laps_;
  }

  //Returns current elapsed time without changing running state
  double Stopwatch::getElapsed() {
    auto now = getTimeOffset();
    
    if( intervalStart_ > 0 ) {
      elapsed_ += now - intervalStart_;
    }

    return elapsed_;
  }
}

