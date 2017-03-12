#include <cstddef>
#include <iostream>
#include "my_array.h"
#include <cstdio>

template<typename T, std::size_t N>
void test_core() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.empty();
  ca.empty();
  a.size();
  ca.size();

  a.at(0);
  ca.at(0);
  a[0];
  ca[0];
  (void)static_cast<const T &>(a[0]);
  (void)static_cast<const T &>(ca[0]);
}

template<typename T, std::size_t N>
void test_assign() {
  my_array<T, N> a;
  const my_array<T, N> &ca = a;
  a.fill(T());

  a[0] = T();
  a[0] = a[0];
  a[0] = ca[0];
}

class NonCopyable {
 public:
  NonCopyable() {}
 private:
  NonCopyable(const NonCopyable&);
  NonCopyable& operator=(const NonCopyable);
};


void test_my_bool() {
    my_array<bool, 10> arr;
    arr.fill(true);
    bool b = arr[1];
    assert(b == true);
    arr[4] = false;
    assert(arr[4] == false);
    for (int i = 0; i < 10; i++)
        if (i != 4)
            assert(arr[i] == true);
    arr[4] = arr[3];
    for (int i = 0; i < 10; i++)
        assert(arr[i] == true);
}


int main() {
  test_core<int, 10>();
  test_core<bool, 10>();
  test_core<NonCopyable, 10>();

  test_assign<int, 10>();
  test_assign<bool, 10>();
  test_my_bool();
}
