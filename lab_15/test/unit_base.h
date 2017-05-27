#pragma once
#include "linq.h"
#include <vector>

namespace linq_test {

typedef std::pair<int, int> intpair; 

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


    TEST(select, functor) 
    {
        class Square {
        public:
            int operator()(int x) {return x * x;} 
        };
    
        class Pair {
        public:
            intpair operator()(int x) {return {2 * x, 3 * x};}
        };
    
        std::vector<int> v = {1, 2, 3};
        std::vector<int> res = from(v.begin(), v.end()).select(Square()).to_vector();
    
        std::vector<int> ans = {1, 4, 9};
        ASSERT_EQ(res, ans);

        const int a[3] = {1, 2, 3};
        std::vector<intpair> res1 = from(a, a + 3)
                                    .select<intpair>(Pair()).to_vector();
    
        std::vector<intpair> ans1 = {{2, 3}, {4, 6}, {6, 9}};
        ASSERT_EQ(res1, ans1);
    }


    TEST(select, lambda) 
    {
        std::vector<int> v = {1, 2, 3};
        std::vector<int> res = from(v.begin(), v.end())
                        .select([](int x)->int {return x * x;})
                        .to_vector();
        std::vector<int> ans = {1, 4, 9};
        ASSERT_EQ(res, ans);
        
        const int a[3] = {1, 2, 3};
        std::vector<intpair> res1 = from(a, a + 3)
                                    .select<intpair>([](int x)->intpair {return {2 * x, 3 * x};})
                                    .to_vector();
    
        std::vector<intpair> ans1 = {{2, 3}, {4, 6}, {6, 9}};
        ASSERT_EQ(res1, ans1);
    } 

    int select_square(int x) {
        return x * x;
    }

    intpair select_pair(int x) {
        return {2 * x, 3 * x};
    }    
    
    TEST(select, func)
    {
        
        std::vector<int> v = {1, 2, 3};
        std::vector<int> res = from(v.begin(), v.end())
                        .select(select_square)
                        .to_vector();
        std::vector<int> ans = {1, 4, 9};
        ASSERT_EQ(res, ans);
        
        const int a[3] = {1, 2, 3};
        std::vector<intpair> res1 = from(a, a + 3)
                                    .select<intpair>(select_pair)
                                    .to_vector();
    
        std::vector<intpair> ans1 = {{2, 3}, {4, 6}, {6, 9}};
        ASSERT_EQ(res1, ans1);
    }
    
    TEST(take, empty)
    {
        std::vector<int> v, res, ans;
        
        v = {};
        res = from(v.begin(), v.end())
                             .take(0)
                             .to_vector();   
        ans = {};
        ASSERT_EQ(ans, res);

        ASSERT_THROW(from(v.begin(), v.end())
                          .take(3)
                          .to_vector(), EnumeratorException);   
    }

    TEST(take, not_empty)
    {
        std::vector<int> v, res, ans;
        
        v = {1, 2, 3};
        res = from(v.begin(), v.end())
                             .take(0)
                             .to_vector();   
        ans = {};
        ASSERT_EQ(ans, res);

        res = from(v.begin(), v.end())
                               .take(3)
                               .to_vector();   
        ans = {1, 2, 3};
        ASSERT_EQ(res, ans);

        res = from(v.begin(), v.end())
                               .take(1)
                               .to_vector();   
        ans = {1};
        ASSERT_EQ(res, ans);
    }

    TEST(until, functor) {
        
        class LessThenOne {
        public: 
            bool operator()(int x) {
                return x < 1;
            }
        };        
     
        std::vector<int> v, res, ans;
        
        v = {2, 3, 4, 5, -1, 6, 7};
        res = from(v.begin(), v.end())
                               .until(LessThenOne())
                               .to_vector();
        ans = {2, 3, 4, 5};
        ASSERT_EQ(res, ans);                           

        v = {0, 2, 3, 4, 5, 1};
        res = from(v.begin(), v.end())
                               .until(LessThenOne())
                               .to_vector();
        ans = {};
        ASSERT_EQ(res, ans);                           

        v = {};
        res = from(v.begin(), v.end())
                               .until(LessThenOne())
                               .to_vector();
        ans = {};
        ASSERT_EQ(res, ans);                           
    }
}

