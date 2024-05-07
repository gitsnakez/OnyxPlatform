#pragma once

#include <cmath>
# define PI		3.141592653589793238462643383279502884L /* pi */

class EngineMath
{
public:
	static float RoundTo2(float value)
	{
		return round(value * 100) / 100;
	}

	static float AngleAddition(float value)
	{
		return RoundTo2(value * 90);
	}
};