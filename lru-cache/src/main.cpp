#include "test_utils.h"
using namespace std;

int main(){
    TestUtils test = TestUtils();
    test.singleThread_test1();
    test.singleThread_test2();

    test.multiThread_test1();
}