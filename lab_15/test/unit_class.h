#pragma once
#include "linq.h"
#include <vector>
#include <algorithm>

namespace linq_test {

    template<class T>
    void test_int() {
    
        typedef std::pair<T, T> pairt;
    
        struct Pair {
            pairt operator()(T t) {
                return {t, t};
            }
        };
        
        std::vector<T> v, ans, res;    
      
        v = {T(1), T(2), T(3), T(4), T(5)};
        res = from(v.begin(), v.end())
                .take(4)
                .drop(1)
                .select([](T t)->T {return t;})
                .to_vector();

//        std::vector<pairt> pairres;
//        pairres = from(v.begin(), v.end())
//                .take(4)
//                .drop(1)
//                .select<pairt>(Pair())
//                .to_vector();
    }

//------------------------------------------------------------------------------------------------------

    class Base {
    public:
        Base(int x = 0) : x(x) {}
    
    private:
        int x;
    };

    class NonAssignable {
    public:
        NonAssignable(int x = 0) : x(x) {}
        NonAssignable& operator=(const NonAssignable& other) = delete;
        
    private:
        int x;
    };

    class NonConstructable {
    public:
        NonConstructable(int x) : x(x) {}
    
    private:
        int x;    
    };
    
    TEST(classes, base) {
        test_int<Base>();
    }
    
//    TEST(classes, nonassignable) {
//        test_int<NonAssignable>();
//    }

//    TEST(classes, nonconstructable) {
//        test_int<NonConstructable>();
//    }

}
