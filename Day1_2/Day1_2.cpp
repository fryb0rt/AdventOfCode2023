#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int main()
{
    std::ifstream stream("..\\input1.txt");
    std::string line;
    int sum = 0;
    std::vector<std::string> numbers = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9" };
    std::vector<std::pair<int, int>> found;
    while (std::getline(stream, line)) {
        found.clear();
        int first = -1, last = -1;
        size_t firstPos = std::string::npos, lastPos = 0;
        for (int i = 0; i < numbers.size(); ++i) {
            std::string num = numbers[i];
            size_t fnd = line.find(num);
            if (fnd != std::string::npos) {
                if (firstPos > fnd) {
                    firstPos = fnd;
                    first = i % 10;
                }
            }
            fnd = line.rfind(num);
            if (fnd != std::string::npos) {
                if (lastPos <= fnd) {
                    lastPos = fnd;
                    last = i % 10;
                }
            }
        }
        sum += first * 10 + last;
    }
    std::cout << sum << std::endl;
    return 0;
}