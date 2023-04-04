#pragma once
#include "text.h"



class textAppear : public Text
{
public:
	textAppear();
	textAppear(textProps p, float d);
	void update(float dtime) override;
	void updateText(const char* text);
	inline bool isDone() { return done; }
	inline void changeSpeed(float value) { timeBetween = value; }
	inline float getSpeed() { return timeBetween; }

private:
	float timeBetween;
	float timeSinceLast;
	std::string curText;
	bool done = false;
};