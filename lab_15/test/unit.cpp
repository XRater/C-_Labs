#include <gtest/gtest.h>
#include <vector>
#include <type_traits>
#include <algorithm>

#include "linq.h"
#include "unit_base.h"
#include "unit_class.h"

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
