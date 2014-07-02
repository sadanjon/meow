#include "../src/math.h"
#include "gmock/gmock.h"  

using namespace testing;

TEST(MathTest, add) {
	auto math = new meow::Math();
	ASSERT_THAT(math->add(1, 1), Eq(2));
}
