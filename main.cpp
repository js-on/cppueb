#include <iostream>
#include "string.cpp"

void print_string(string s) {
    s.print();
}

int main(int argc, char const *argv[])
{
    string test("test");
    print_string(test);
    test.print();
    return 0;
}