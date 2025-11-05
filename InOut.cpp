#include <iostream>
#include <cstdio>

int main() {
    // Redirect standard input to read from "input.txt"
    freopen("input.txt", "r", stdin);
    
    // Redirect standard output to write to "output.txt"
    freopen("output.txt", "w", stdout);
    
    int number;
    while (std::cin >> number) {
        std::cout << "Read number: " << number << std::endl;
    }
    
    return 0;
}