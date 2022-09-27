/**
 * \brief C++ header for the FTTimer class
 * 
 * This class is used as a common wrapper to ensure a consistent way of
 * accessing system time across multiple platforms and software stacks. 
 * 
 * While this software attempts to track resolution to the nanoseconds,
 * hardware limitations can apply, so unit testing is only able to validate
 * microsecond-scale clock resolutions.
 *
 * # Definitions
 * NAME       - TYPE   - Description
 * timestamp  - double - time in seconds to nanosecond precision 
 * timestring - string - time representation as "YYYY-MM-DD HH:MM:SS.000000000"
 *
 * For most date applications, a timestamp of 0 is set to
 * 1970-01-01 00:00:00.000000000.
 */
#include <string>
#include <vector>

namespace FTTimer
{
  /**
   * \brief structure for a lap returned from stopwatch
   **/
  struct StopwatchLap {
    int64_t index;                          //! Lap index or number
    double  duration;                       //! Duration of the lap
  };

  /**
   * \brief returns the library version 
   **/
  std::string getVersion();  

  /**
   * \brief function that returns the current time as a double
   */
  double getTimestamp();

  /**
   * \brief converts a string to a timestamp
   * \param [in] time string
   * \return time stamp
   **/
  double convertStringToTimestamp( std::string );


  /**
   * \brief returns the current time as a string
   *
  std::string getTimeString();
  */

  /**
   * \brief converts the time to a string
   * \param [in] timestamp timestamp t convert
   * \return string representing the timestamp as YYYY-DD-MM HH:MM:SS.xxxxx
  */
  std::string convertTimestampToString( double timestamp );

  /**
   * \brief class that tracks timing inforamtion
   **/
  class Stopwatch {
    public:
      /**
       * \brief constructor
       **/
      Stopwatch(); 


      /**
       * \brief function to indicate if stopwatch is running
       * \return true if running, false if not running
       *
       * Running indicates that the last time entry was at the start of a timing
       * interval.
       */
      bool isRunning();

      /**
       * \brief function that starts/continues a timer
       * \return true if clock starts, false if it is already running 
       *
       * The start function will start tracking
       **/
      bool start();
  
      /**
       * \brief function that stops a timer
       * \return elapsed time on success, a negative value on failure
       *
       * This function will set the running flag to true and record the new
       * start time. 
       **/
      double stop();
  
      /**
       * \brief function that resets a timer
       * \return true on success, false on failure
       *
       * This function clears all times and removes and laps.
       **/
      bool reset();

      /**
       * \brief get elapsed time without changing clock state
       * \return stopwatch time
       **/
      double getElapsed();
  
      /**
       * \brief function that adds a lap marker
       * \return returns the lap duration on success or 0 on failure
       *
       * The lap duration is how long since the last lap. If the function is
       * called while stopped, -1.0 is returned. 
       **/
      double lap();
  
    private: 
      //reference timepoint
      std::chrono::time_point<std::chrono::steady_clock> start_{};

      bool   running_    = false;           //! flag to indicate if running
      double elapsed_    = 0;               //! total elapsed time
      double lapElapsed_ = 0;               //! elapsed lap time
      
      std::vector<double> laps_;            //! vector of recorded laps
 
      /**
       * \brief returns an internal timepoint value
       **/
      std::chrono::time_point<std::chrono::steady_clock> getTimePoint();

      /**
       * \brief sets the reference time
       **/
      bool setTimePoint();

      /**
       * \brief returns the offset between the set time and current iem
       **/
      double getTimeOffset();
  };

}
