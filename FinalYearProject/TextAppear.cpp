#include "textappear.h"


textAppear::textAppear()
{
}

textAppear::textAppear(textProps p, float d) : timeBetween(d), Text(p)
{
	timeSinceLast = 0.0f;
	text.setString(curText);
}

void textAppear::update(float dtime)
{
	if (std::string(props.string) == curText)
	{
		return;
	}

	timeSinceLast += dtime;
	if (timeSinceLast >= timeBetween)
	{
		curText.append(std::string(props.string), curText.length(), 1);
		text.setString(curText);
		timeSinceLast = 0.0f;
	}
}
