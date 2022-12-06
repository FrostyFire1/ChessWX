#include "util.h"
bool isOutOfBounds(int x, int y){
	return (x < 0 || x > 7) || (y < 0 || y > 7);
}
int arrIndex(int x, int y, int height) {
	return y * height + x;
}
std::vector<std::string> split(std::string input, char delimiter) {
	std::vector<std::string> splitData;
	std::string curData = "";
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != delimiter) {
			curData += input[i];
		}
		else {
			splitData.push_back(curData);
			curData = "";
		}
	}
	splitData.push_back(curData);
	return splitData;
}