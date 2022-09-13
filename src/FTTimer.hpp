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

namespace FTTimer
{
  /**
   * \brief returns the library version 
   **/
  std::string getVersion();  

  /**
   el \brief function that returns the current time as a double
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
  class Timer {
    public:
  
      /**
       * \brief function that starts/continues a timer
       **/
      bool start();
  
      /**
       * \brief function that stops a timer
       * \return true on success, false on failure
       *
       * This function will set the running flag to true and record the new
       * start time. 
       **/
      bool stop();
  
      /**
       * \brief function that resets a timer
       **/
      bool reset();
  
      /**
       * \brief function that 
       **/
      int lap();
  
      /**
       * \brief function to indicate if stopwatch is running
       * \return true of running, false if not running
       *
       * Running indicates that the last time entry was at the start of a timing
       * interval.
       */
      bool isRunning(); 
  }

}
