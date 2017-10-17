#include <iostream>

#include "TestCollector.h"

int main(int argc, char *argv[])
{    auto nFailedTests = TestCollector::RunAllTests(argc, argv);
     std::cout << "Total number of failed tests: " << nFailedTests << std::endl;
     return nFailedTests;
}
