#include <chrono>
#include <thread>
#include <FTTimer.hpp>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#define GTEST_COUT std::cerr << "[ MSG      ] [ INFO ]"

/**
 * \brief tests te given time delay
 * \param [in] delay time to delay as double
 * \return time between start in milliseconds
 */
double timeDelay( double delay) {
  double start = FTTimer::getTimestamp();
  auto d = static_cast<uint64_t>(delay *1e6);

  GTEST_COUT << "Sleeping for "<< delay << " seconds.\n";

  std::this_thread::sleep_for(std::chrono::microseconds(d));

  double end = FTTimer::getTimestamp();

  return (end-start);
}

::testing::AssertionResult IsBetweenInclusive(double val, double a, double b)
{
    if((val >= a) && (val <= b))
        return ::testing::AssertionSuccess();
    else
        return ::testing::AssertionFailure()
               << val << " is outside the range " << a << " to " << b;
};

//Test timer accuracy
TEST( FTTimerTest, delay) {
  double range = 0.0003;
  double delay = 2;
  double result = timeDelay(delay);
  EXPECT_TRUE( IsBetweenInclusive( result, delay - range, delay + range )) 
    << " Timing Accuracy test";

  EXPECT_FALSE( IsBetweenInclusive( result, delay - range*.1, delay +range*.1)) 
    << " Timing sanity check";
};

//Test date output string
TEST( FTTimerTest, string_output ) {

  //Test time = 0;
  std::string dateString = FTTimer::convertTimestampToString( 0 );
  std::string UTCString =  "1970-01-01 00:00:00.000000000";
  EXPECT_EQ( UTCString, dateString ) << "UTC 0 Date string "<<dateString << " != "<<UTCString ;

  /*
  //Establish reference date
  auto now = std::chrono::system_clock::now();

  std::stringstream ss;
  ss << std::ctime(now);
  std::string refDate = ss.str();

  double ts = FTTimer::getTimestamp();
  GTEST_COUT << "Timestamp: "<< ts << ".";
  std::string dateString = FTTimer::convertTimestampToString( ts );
//  EXPECT_EQ( dateString, refDate );
  EXPECT_TRUE( false ) << "dateString: "+dateString;
  */
};

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
