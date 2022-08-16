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

namespace FTTimer
{
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
   * \brief converts the time to a stirng
  */
  std::string convertTimestampToString( double timestamp );

}
