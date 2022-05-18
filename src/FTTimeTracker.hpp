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

  /**
   * \brief class representing a single timer instance
   * 
   * The timer class provides functionality to track running time for a 
   * single id.
   **/
  class Timer {
    public:
      Timer();
      bool start();
      double stop();
      bool reset();
      double getElapsed();
      double getDuration();

    private:
      std::chrono::time_point<std::chrono::system_clock> timerStart_;
      std::chrono::time_point<std::chrono::system_clock> iterationStartPoint_;

      double elapsed = 0.0;
      double duration;
      bool running = false;

  };

  class StopWatch {
    public:
      std::string start( std::string id );
      double stop( std::string id );
      double lap( std::string id );
      double lap( std::string id, std::vector<std::string> tags );
      bool reset( std::string id );
      bool remove( std::string id );
      double getElapsed( std::string id );

    private:
      //std::map<std::string, Timer>;
  };
}
