#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main()
{
	static std::vector<int> chars(255);
	chars['A'] = 12;
	chars['K'] = 11;
	chars['Q'] = 10; chars['J'] = -1; chars['T'] = 8; chars['9'] = 7; chars['8'] = 6; chars['7'] = 5; chars['6'] = 4; chars['5'] = 3; chars['4'] = 2; chars['3'] = 1; chars['2'] = 0;
	std::ifstream stream("..\\input7.txt");
	struct Hand {
		std::string cardsOrg;
		std::string cards;
		int bid;
		int power;
		std::vector<int> c;
		int determinePower(int pos = 0) {
			if (pos == cards.size()) {
				int count[5] = { 0,0,0,0,0 };
				for (int i = 0; i < cards.size(); ++i) {
					int cnt = 0;
					char ch = cards[i];
					for (int j = 0; j < cards.size(); ++j) {
						cnt += ch == cards[j];
					}
					++count[cnt - 1];
				}
				for (int i = 0; i < 5; ++i) {
					count[i] /= (i + 1);
				}
				if (count[4] == 1) {
					power = 6;
				}
				else if (count[3] == 1) {
					power = 5;
				}
				else if (count[2] == 1 && count[1] == 1) {
					power = 4;
				}
				else if (count[2] == 1) {
					power = 3;
				}
				else if (count[1] == 2) {
					power = 2;
				}
				else if (count[1] == 1) {
					power = 1;
				}
				else {
					power = 0;
				}
				return power;
			}
			if (cards[pos] == 'J') {
				int maxPower = 0;
				for (int i = 0; i < cards.size(); ++i) {
					cards[pos] = cardsOrg[i];
					maxPower = std::max(maxPower, determinePower(pos + 1));
				}
				cards[pos] = cardsOrg[pos];
				return maxPower;
			}
			else {
				return determinePower(pos+1);
			}
			
		}
		bool operator<(const Hand& hand) {
			if (hand.power != power) {
				return power < hand.power;
			}
			for (int i = 0; i < cards.size(); ++i) {
				if (cards[i] == hand.cards[i]) {
					continue;
				}
				int val0 = chars[cards[i]];
				int val1 = chars[hand.cards[i]];
				return val0 < val1;
			}
		}
	};
	std::vector<Hand> hands;
	while (!stream.eof()) {
		Hand hand;
		stream >> hand.cards;
		hand.cardsOrg = hand.cards;
		stream >> hand.bid;
		hand.power = hand.determinePower();
		hands.push_back(hand);
	}
	std::sort(hands.begin(), hands.end());

	int64_t sum = 0;
	for (int i = 0; i < hands.size(); ++i) {
		sum += hands[i].bid * (i + 1);
	}
	std::cout << sum << std::endl;
}