#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream stream("..\\input1.txt");
    std::string line;
    int sum = 0;
    while (std::getline(stream, line)) {
        char first = -1, last = -1;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] >= '0' && line[i] <= '9') {
                if (first == -1) {
                    first = line[i];
                }
                last = line[i];
            }
        }
        sum += (first - '0') * 10 + (last - '0');
    }
    std::cout << sum << std::endl;
    return 0;
}