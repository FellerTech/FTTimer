#include <string>
#include <chrono>
#include <thread>
#include <FTTimeTracker.hpp>
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

  GTEST_COUT << "Sleeping for "<< delay << " seconds.\n";

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
TEST( FTTimerTest, Accuracy ) {
  double range = 0.0003;
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
  int64_t subsec = (ts - static_cast <int64_t> (ts)) *1e6;
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
// Main function
/////////////////////////////////////////////
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}