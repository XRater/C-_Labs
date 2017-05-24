#include <gtest/gtest.h>
#include <vector>
#include <type_traits>

#include "linq.h"

TEST(range, ptr_and_bool)
{
    std::vector<bool> empty;
	ASSERT_FALSE(from(empty.begin(), empty.end()));

    std::vector<int> v = {1, 2, 3};
	ASSERT_TRUE(from(v.begin(), v.end()));
	ASSERT_FALSE(from(v.end(), v.end()));
	ASSERT_FALSE(from(v.begin(), v.begin()));

    ASSERT_EQ(*from(v.begin(), v.end()), 1);
    ASSERT_EQ(*from(v.begin() + 1, v.end()), 2);
    ASSERT_EQ(*from(v.begin() + 2, v.end()), 3);

    int a[2] = {1, 2};
    
	ASSERT_TRUE(from(a, a + 2));
	ASSERT_FALSE(from(a, a));
	ASSERT_FALSE(from(a + 2, a + 2));

    ASSERT_EQ(*from(a, a + 1), 1);
    
}


TEST(range, operator_plus_plus)
{
    std::vector<double> small = {1};
    ASSERT_TRUE(from(small.begin(), small.end()));
    ASSERT_FALSE(++from(small.begin(), small.end()));

    std::vector<int> v = {1, 2, 3};
    ASSERT_EQ(*++from(v.begin(), v.end()), 2);
    ASSERT_EQ(*++++from(v.begin(), v.end()), 3);
    
    int a[2] = {1, 2};
    ASSERT_EQ(*++from(a, a + 2), 2);
    
    ASSERT_THROW(*++from(a, a + 1), EnumeratorException);    
    ASSERT_THROW(++from(a + 2, a + 2), EnumeratorException);    
}


TEST(drop, main_drop_test)
{
    std::vector<double> small = {1};
    from(small.begin(), small.end()).drop(1);

    ASSERT_TRUE(from(small.begin(), small.end()));
    ASSERT_FALSE(from(small.begin(), small.end()).drop(1));

    std::vector<int> v = {1, 2, 3};
    ASSERT_EQ(*from(v.begin(), v.end()).drop(0), 1);
    ASSERT_EQ(*from(v.begin(), v.end()).drop(2), 3);
    
    int a[2] = {1, 2};
    ASSERT_EQ(*from(a, a + 2).drop(1), 2);
    
    ASSERT_THROW(*from(a, a + 2).drop(2), EnumeratorException);    
    ASSERT_THROW(from(a, a + 2).drop(3), EnumeratorException);    
}


TEST(terminate, to_vector)
{
    std::vector<int> xs = { 1, 2, 3 };
    std::vector<int> res;
    std::vector<int> ans;

    ans = {1, 2, 3};
    res = from(xs.begin(), xs.end()).to_vector();
    ASSERT_EQ(res, ans);

    ans = {};
    res = from(xs.begin(), xs.begin()).to_vector();
    ASSERT_EQ(res, ans);

    xs = {};
    ans = xs;
    res = from(xs.begin(), xs.end()).to_vector();
    ASSERT_EQ(res, ans);
}


TEST(terminate, copy_to)
{
    std::vector<int> xs = { 1, 2, 3 };
    std::vector<int> res = {0, 0, 0, 0};
    std::vector<int> ans;

    ans = {1, 2, 3, 0};
    from(xs.begin(), xs.end()).copy_to(res.begin());
    ASSERT_EQ(res, ans);

    ans = {1, 2, 3, 0};
    from(xs.begin(), xs.begin()).copy_to(res.begin());
    ASSERT_EQ(res, ans);

    std::vector<int> xs1 = {};
    ans = {1, 2, 3, 0};
    from(xs1.begin(), xs1.end()).copy_to(res.begin());
    ASSERT_EQ(res, ans);
}

TEST(constant, small_test) 
{
    const std::vector<int> xs = { 1, 2, 3 };
    const std::vector<int> res =from(xs.begin(), xs.end()).drop(2).to_vector();         

    const std::vector<int> ans = {3};
    ASSERT_EQ(res, ans);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
    std::vector<int> xs = { 1, 2, 3 };
	return RUN_ALL_TESTS();
}
