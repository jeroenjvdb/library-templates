#include <stdio.h>

#include <CppUTest/CommandLineTestRunner.h>


int main(int argc, char **argv) {
    printf("hello, test!\n");

    return CommandLineTestRunner::RunAllTests(argc, argv);
}