#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main()
{
    std::ifstream stream("..\\input2.txt");
    std::string line;
    int sum = 0;
    const int limitBlue = 14, limitRed = 12, limitGreen = 13;
    while (std::getline(stream, line)) {
        std::istringstream iss(line);
        std::string tmp;
        int id;
        iss >> tmp >> id; // Game ID
        iss >> tmp; // :
        int maxBlue = 0, maxRed = 0, maxGreen = 0;
        do {
            int blue = 0, red = 0, green = 0, cnt;
            do {
                iss >> cnt >> tmp;
                if (tmp.find("blue") != std::string::npos) {
                    blue += cnt;
                }
                if (tmp.find("red") != std::string::npos) {
                    red += cnt;
                }
                if (tmp.find("green") != std::string::npos) {
                    green += cnt;
                }
            } while (tmp[tmp.size() - 1] == ',');
            maxBlue = std::max(blue, maxBlue);
            maxRed = std::max(red, maxRed);
            maxGreen = std::max(green, maxGreen);
        } while (!iss.eof());
        if (maxBlue <= limitBlue && maxRed <= limitRed && maxGreen <= limitGreen) {
            sum += id;
        }
    }
    std::cout << sum << std::endl;
    return 0;
}