#include <chrono>
#include <thread>

#include <FTTimer.hpp>
#include <gtest/gtest.h>

#define GTEST_COUT std::cerr << "[ MSG      ] [ INFO ]"

/**
 * \brief tests te given time delay
 * \param [in] delay time to delay as double
 * \return time between start in milliseconds
 */
double timeDelay( double delay) {
  double start = FTTimer::getTime();
  auto d = static_cast<uint64_t>(delay *1e6);

  GTEST_COUT << "Sleeping for "<< delay << " seconds.\n";

  std::this_thread::sleep_for(std::chrono::microseconds(d));

  double end = FTTimer::getTime();

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
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
