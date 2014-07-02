#include "gmock/gmock.h"  

#include "../src/my_math.h"


using namespace testing;

TEST(MathTest, add) {
	auto math = new meow::Math();
	ASSERT_THAT(math->add(1, 1), Eq(2));
}
