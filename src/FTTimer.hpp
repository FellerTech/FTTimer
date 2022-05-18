/**
 * \brief C++ header for the FellerTech Timer class
 */
#include <chrono>
#include <string>
#include <vector>
#include <map>


namespace FTTimer
{
  /**
   * \brief function that returns the current time.
   */
  double getTime();
    //auto now = std::chrono::system_clock::now();
    //auto duration = now.time_since_epoch();
    //auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}
