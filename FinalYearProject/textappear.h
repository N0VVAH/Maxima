#pragma once
#include "text.h"



class textAppear : public Text
{
public:
	textAppear();
	textAppear(textProps p, float d);
	void update(float dtime) override;

private:
	float timeBetween;
	float timeSinceLast;
	std::string curText;
};