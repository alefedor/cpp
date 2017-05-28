#include <cstddef>
#include <iostream>
#include "my_array.h"

#define DO_CHECK(expr) check(expr, __FUNCTION__, __FILE__, __LINE__)

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

class NonCopyable{
 public:
    NonCopyable(){}
 private:
    NonCopyable(const NonCopyable&);
    NonCopyable& operator=(const NonCopyable);
};

void check(bool expr, const char *func, const char  *filename, size_t lineNum){
    if (!expr)
        std::cout << "Test failed " << func << " in line " << lineNum << " in file " << filename << std::endl;
}

void my_test(){
    my_array<int, 5> a;
    a.fill(3);
    DO_CHECK(a[2] == 3);
    DO_CHECK(a.at(2) == 3);
    a[2] = 15;
    DO_CHECK(a[2] == 15);
    a.at(3) = 8;
    DO_CHECK(a.at(3) == 8);

    my_array<bool, 10> b;
    b.fill(1);
    DO_CHECK(b[8] == 1);
    DO_CHECK(b.at(9) == 1);
    b[3] = 0;
    DO_CHECK(b[3] == 0);
    b.at(4) = 1;
    DO_CHECK(b.at(4) == 1);
    b[4] = b[3];
    DO_CHECK(b[4] == b[3]);
    b[6] = b[5] = b[4];
    DO_CHECK(b[6] == b[5]);
    DO_CHECK(b[6] == 0);
}

int main(){
    test_core<int, 10>();
    test_core<bool, 10>();
    test_core<NonCopyable, 10>();

    test_assign<int, 10>();
    test_assign<bool, 10>();
    my_test();
}
