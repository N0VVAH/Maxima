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

	if (done == true)
	{
		return;
	}


	timeSinceLast += dtime;
	if (timeSinceLast >= timeBetween)
	{
		if (curText.length() == 1)
		{
			int i = 1 + 1;
		}
		curText.append(std::string(props.string), curText.length(), 1);
		text.setString(curText);
		timeSinceLast = 0.0f;
		if (std::string(props.string) == curText)
		{
			done = true;
		}
	}
}

void textAppear::updateText(const char* text)
{
	if (text == curText)
	{
		return;
	}
	curText = "";
	props.string = "";
	props.string = text;
	done = false;
}
