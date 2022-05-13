
#include <FTTimer.hpp>
#include <gtest/gtest.h>
//#include <gtest.h>

TEST( FTTimerTest, Sample) { EXPECT_EQ(1, FTTimer::getTime()); };

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
