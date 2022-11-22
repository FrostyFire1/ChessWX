#pragma once
#include <string>
class piece {
public:
	virtual std::string getDisplayText(); //virtual methods can be override, great for "downcasting"
	std::string displayText = "piece";
};