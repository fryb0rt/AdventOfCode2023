#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>      // std::setw

int main()
{
    std::ifstream stream("..\\input12.txt");
    std::string line;
    struct Line {
        std::string data;
        std::vector<int> counts;
        struct Interval
        {
            int start, end;
            bool mandatory = false;
        };
        std::vector<Interval> intervals;

        int64_t solve(int intervalIndex = 0, int countIndex = 0) {
            if (countIndex == counts.size())
            {
                for (int i = intervalIndex; i < intervals.size(); ++i)
                {
                    if (intervals[i].mandatory)
                    {
                        return 0;
                    }
                }
                return 1;
            }
            if (intervalIndex == intervals.size())
            {
                return 0;
            }
            const Interval& interval = intervals[intervalIndex];
            int size = interval.end - interval.start;
            int s = 0;
            int64_t sum = interval.mandatory ? 0 : solve(intervalIndex + 1, countIndex);
            for (int lastCountIndex = countIndex; lastCountIndex < counts.size(); ++lastCountIndex)
            {
                s += counts[lastCountIndex];
                if (size >= s)
                {
                    const int64_t next = solve(intervalIndex + 1, lastCountIndex + 1);
                    if (next > 0) {
                        sum += solveInterval(interval.start, interval.end, countIndex, lastCountIndex + 1) * next;
                    }
                }
                else
                {
                    break;
                }
                ++s;
            }
            return sum;
        }

        int64_t solveInterval(int start, int end, int indexS, int indexE) {
            if (indexS == counts.size() || indexS == indexE)
            {
                return 1;
            }
            while (start < end && data[start] == '.')
            {
                ++start;
            }
            if (start == end) {
                return 0;
            }

            int64_t sum = 0;
            if (data[start] != '#') {
                sum += solveInterval(start + 1, end, indexS, indexE);
            }
            for (int i = 0; i < counts[indexS]; ++i, ++start) {
                if (start == end || data[start] == '.') {
                    return sum;
                }
            }
            if (start < end && data[start] == '#') { // # intervals must be separated
                return sum;
            }
            if (indexS + 1 == indexE) { // Last
                while (start < end) { // There should not be any remaining #
                    if (data[start] == '#')
                    {
                        return sum;
                    }
                    ++start;
                }
                return sum + 1;
            }

            // One separator
            if (start == end || data[start] == '#') {
                return sum;
            }
            ++start;

            sum += solveInterval(start, end, indexS + 1, indexE);
            return sum;
        }

        void unfold() {
            std::string total = data;
            std::vector<int> totalC = counts;
            for (int i = 0; i < 4; ++i) {
                total += "?" + data;
                for (int val : counts) {
                    totalC.push_back(val);
                }
            }
            data = total;
            counts = totalC;
            for (int i = 0; i < data.size(); ++i)
            {
                Interval interval;
                interval.start = i;
                while (i < data.size() && data[i] != '.')
                {
                    interval.mandatory |= data[i] == '#';
                    ++i;
                }
                if (interval.start < i)
                {
                    interval.end = i;
                    intervals.push_back(interval);
                }
            }
        }
    };
    std::vector<Line> lines;
    while (std::getline(stream, line)) {
        if (line.empty()) {
            continue;
        }
        std::istringstream iss(line);
        Line dataLine;
        iss >> dataLine.data;
        while (iss) {
            int val;
            iss >> val;
            dataLine.counts.push_back(val);
            char c;
            iss >> c; //,
        }
        dataLine.unfold();
        lines.push_back(dataLine);
    }
    int64_t sum = 0;
    #pragma omp parallel for reduction (+:sum)
    for (int i = 0; i < lines.size(); ++i)
    {
        int64_t val = lines[i].solve();
        sum += val;
        std::cout << i << " " << val << " " << std::endl;
    }
    std::cout << sum << std::endl;
}