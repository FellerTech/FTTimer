#include <string>
#include <chrono>
#include <thread>
#include <FTTimer.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define GTEST_COUT std::cerr << "[ MSG      ] [ INFO ]"

using ::testing::HasSubstr;

/**
 * \brief implements given time delay
 * \param [in] delay time to delay as double
 * \return time between start in milliseconds
 *
 * This helper function waits for the specified time delay and returns the
 * amount of time passed. Timing is based on the FTTime::getTimestamp function.
 **/
double timeDelay( double delay) {
  double start = FTTimer::getTimestamp();
  auto d = static_cast<uint64_t>(delay *1e6);


  std::this_thread::sleep_for(std::chrono::microseconds(d));

  double end = FTTimer::getTimestamp();

  return (end-start);
}


/////////////////////////////////////////////
// TEST: Helper functin to test range on result
/////////////////////////////////////////////
::testing::AssertionResult IsBetweenInclusive(double val, double a, double b)
{
    if((val >= a) && (val <= b))
        return ::testing::AssertionSuccess();
    else if((val >= b) && (val <= a))
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure()
               << val << " is outside the range " << a << " to " << b;
};

/////////////////////////////////////////////
// Verify that a version is received
/////////////////////////////////////////////
TEST( FTTimerTest, Version ) {
  std::string version = FTTimer::getVersion();

  int expected = 3;
  int dots = std::count(
      version.begin()
      , version.end()
      , '.'
      );

  EXPECT_EQ( dots, expected) << " Expected value "
    << expected <<", format xxx.xxx.xxx.xxx\n"
    ;

}

/////////////////////////////////////////////
// Test timer accuracy
/////////////////////////////////////////////
TEST( FTTimerTest, TestDelayAccuracy ) {
  double range = 0.0005;
  double delay = 2;
  double result = timeDelay(delay);



  EXPECT_TRUE( IsBetweenInclusive( result, delay - range, delay + range )) 
    << " Timing Accuracy test";

  EXPECT_FALSE( IsBetweenInclusive( result, delay - range*.1, delay +range*.1)) 
    << " Timing sanity check";
};

/////////////////////////////////////////////
//Test date output string
/////////////////////////////////////////////
TEST( FTTimerTest, TimestampToString ) {

  //Test time = 0;
  std::string dateString = FTTimer::convertTimestampToString( 0 );
  std::string UTCString =  "1970-01-01 00:00:00.000000000";
  EXPECT_EQ( UTCString, dateString ) << "UTC 0 Date string "<<dateString 
    << " != "<<UTCString 
    ;

  //Test time = 1 ns
  dateString = FTTimer::convertTimestampToString( 1e-9 );
  UTCString =  "1970-01-01 00:00:00.000000001";
  EXPECT_EQ( UTCString, dateString ) << "UTC 0 Date string "<<dateString 
    << " != "<<UTCString 
    ;

  //Test vs. current time
  double ts = FTTimer::getTimestamp();
  int64_t subsec = (ts - static_cast <int64_t> (ts)) *1e5;
  std::string substring = std::to_string(subsec);

  dateString = FTTimer::convertTimestampToString( ts );

  EXPECT_THAT( dateString, HasSubstr(substring));
};

/////////////////////////////////////////////
// Test string to timestamp
/////////////////////////////////////////////
TEST( FTTimerTest, StringToTimestamp ) {
  std::string UTCString =  "1970-01-01 00:00:00.000000000";
  double ts = FTTimer::convertStringToTimestamp( UTCString );
  EXPECT_EQ( ts, 0 ) << "UTCString " << UTCString << " return "<<ts<< " != 0"; 

  UTCString = "1970-01-01 00:00:00.000000001";
  ts        =  FTTimer::convertStringToTimestamp( UTCString );
  EXPECT_EQ( ts, 1e-9 ) << "UTCString " << UTCString << " != 1E-9"; 
}

/////////////////////////////////////////////
// Test start/stop functinoality
////////////////////////////////////////////
TEST( Stopwatch, StartStop ) {
  double range = 0.0003;
  double delay = 2;

  FTTimer::Stopwatch sw;

  //Make sure that elapsed time is 0 before start
  double elapsed = sw.getElapsed();
  EXPECT_EQ( elapsed, 0 ) << "Time before start should be 0";

  //Make sure time is greather than 0
  sw.start();
  double result = sw.stop();
  GTEST_COUT << "Min delay:"<< result<< " seconds.\n";
  EXPECT_GT( result, 0.0);
  EXPECT_LT( result, 1e-6 ) << "Execution time should be less than 1 usec";
  sw.reset();

  //Make sure that elapsed time is 0 after reset
  elapsed = sw.getElapsed();
  EXPECT_EQ( elapsed, 0 ) << "Time should be 0 after reset";

  //Make sure time is within range
  sw.start();
  timeDelay(delay);
  result = sw.stop();
  elapsed = sw.getElapsed();

  EXPECT_TRUE( IsBetweenInclusive( result, delay - range, delay + range )) 
    << " Timing Accuracy test";

  EXPECT_EQ(result, elapsed) << "stopped/elapsed mismatch (" 
    << result - elapsed << ")";
}

/////////////////////////////////////////////
// Test lap functionality
//
// This function creates a stopwatch and vierfies its inital values. The 
// stopwatch then starts multiple laps and compares the different lap times
// to verify correctness.
/////////////////////////////////////////////
TEST( Stopwatch, Lap ) {
  FTTimer::Stopwatch sw;

  //Verify no laps before we wbeing
  std::vector<double> laps = sw.getLaps();
  EXPECT_EQ( laps.size(), 0 ) << "lap size != 0 on initiation";

  //Make sure no laps before lap function call
  sw.start();
  laps = sw.getLaps();
  EXPECT_EQ( laps.size(), 0 ) << "lap size != 0 before lap is set";
  sw.reset();

  //Check single lap
  sw.start();
  double lap1 = sw.lap();
  laps = sw.getLaps();

  EXPECT_EQ( lap1, laps[0]) << "delay != lap value";
  sw.reset();

  //Check multipe laps
  int total = 100.0;
  double interval = 0.1;
  double range = interval/2.0;
  std::vector<double> refLaps;

  GTEST_COUT << "Sleeping for "<< total << " intervals of " 
	  << interval<< " seconds.\n";

  sw.start();
  for( int i = 0; i < total; i++) {
    timeDelay(interval);
    lap1 = sw.lap();
//    GTEST_COUT << "LAP :"<<lap1<<std::endl;

    refLaps.push_back(lap1);
  }
// double end = sw.stop();

  laps =sw.getLaps();

  //Compare all elements
  double sum = 0;
  double avg = 0;
  for( int i = 0; i < total; i++ ) {
    EXPECT_EQ( laps[i], refLaps[i] ) << "laps not equal at index "<<i;
    sum = sum + refLaps[i];
    avg = avg + refLaps[i];
  }

  double totalTime = total * interval;
  avg = avg/total;

  GTEST_COUT << "Total time :"<<totalTime <<", lap sum: "<<sum << std::endl;
  EXPECT_TRUE( IsBetweenInclusive( totalTime, sum - range, sum + range));

  //Check average lap time. Should be very close
  EXPECT_TRUE( IsBetweenInclusive( avg, interval-0.01, interval+0.01));
}


/////////////////////////////////////////////
// Main function
/////////////////////////////////////////////
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
