/**
 * \brief C++ header for the FTTimer class
 * 
 * This class is used as a common wrapper to ensure a consistent way of
 * accessing system across multiple platforms and software stacks. 
 */

namespace FTTimer
{
  /**
   * \brief function that returns the current time as a double
   */
  double getTimestamp();

  /**
   * \brief returns the current time as a string
   */
  std::string getTimeString();

  /**
   * \brief converts the time to a stirng
   */
  std::string convertTimestamp( double timestamp );
}
