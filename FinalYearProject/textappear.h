#pragma once
#include "text.h"



class textAppear : public Text
{
public:
	textAppear(textProps p, float d);
	void update(float dtime) override;

private:
	float timeBetween;
};