#include <chrono>
#include <thread>

#include <FTTimer.hpp>
#include <gtest/gtest.h>
//#include <gtest.h>

/**
 * \brief tests te given time delay
 * \param [in] delay time to delay in microseconds
 * \return time between start in milliseconds
 */
double timeDelay( long delay) {
  double start = FTTimer::getTime();
  std::this_thread::sleep_for(std::chrono::microseconds(delay));
  double end = FTTimer::getTime();

  return (end-start) * 1e6;
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
  double range = 100;
  double delay = 100;
  double result = timeDelay(delay);
  EXPECT_TRUE( IsBetweenInclusive( result, delay - range, delay + range ));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
