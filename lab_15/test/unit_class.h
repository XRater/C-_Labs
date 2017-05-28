#pragma once
#include "linq.h"
#include <vector>
#include <algorithm>

namespace linq_test {

    template<class T>
    void test() {
        std::vector<T> v, ans, res;    
      
        v = {T(1), T(2), T(3), T(4), T(5)};
        res = from(v.begin(), v.end())
                .take(4)
                .drop(1)
                .select([](T t)->T {return T(t);})
                .until_eq(T(4))
                .where_neq(T(2))
                .to_vector();

        ans = {T(3)};
        ASSERT_EQ(ans, res);
    }

//------------------------------------------------------------------------------------------------------

    class Base {
    public:
        Base(int x = 0) : x(x) {}
        bool operator == (const Base& other) const {return x == other.x;} 
        bool operator != (const Base& other) const {return x != other.x;} 
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
        bool operator == (const NonConstructable& other) const {return x == other.x;} 
        bool operator != (const NonConstructable& other) const {return x != other.x;} 
    private:
        int x;    
    };
 
    class Memory {
    public:
        Memory(int a = 0) { x = new int[20];}
        ~Memory() {delete x;}

        bool operator == (const Memory& other) const {return *x == *other.x;} 
        bool operator != (const Memory& other) const {return *x != *other.x;} 
    private:
        int* x;
    };
    
    TEST(classes, base) {
        test<Base>();
    }
    
//    TEST(classes, nonassignable) {
//        test<NonAssignable>();
//    }

    TEST(classes, nonconstructable) {
        test<NonConstructable>();
    }

    TEST(classes, memory) {
        test<Memory>;
    }
        
//    TEST(classes, bool_) {
//        test<bool>; 
//    }
}
