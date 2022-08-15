/**
 * \brief C++ header for the FTTimer class
 * 
 * This class is used as a common wrapper to ensure a consistent way of
 * accessing system time across multiple platforms and software stacks. 
 * 
 * While this software attempt toe track resolution to the nanoseconds,
 * hardware limitations can apply, so unit testing is only able to validate
 * microsecond-scale clock resolutions.
 */

namespace FTTimer
{
  /**
   * \brief function that returns the current time as a double
   */
  double getTimestamp();

  /**
   * \brief converts a timestamp to a duration
   */



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
