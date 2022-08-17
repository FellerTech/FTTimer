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
    auto tics = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    double usecs = static_cast<double>(tics)/ 1e9;

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
  /*
    std::istringstream timestamp(timeString);

    tm tmb;
    double r;

    //Get fraction of seconds as separate value
    

    //Replace dashes with . for consistency
    std::replace( timeString.begin(), timeString.end(), '-', '.');

    timestamp >> std::get_time(&tmb, "%Y.%m.%d %T") >> r;
    const auto output = std::chrono::time_point_cast<std::chrono::nanoseconds>(
        std::chrono::system_clock::from_time_t(
          mktime(&tmb))
        ) + std::chrono::nanoseconds( lround(r * std::nano::den))
        ;

    uint64_t usecs = output.time_since_epoch().count();
    double duration = double(usecs)/double(1e6);

    std::cout << "timeString: "<<timeString<< " => " << duration <<std::endl;

    return duration;
  */
  }

}

