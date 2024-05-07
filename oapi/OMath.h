#pragma once

static class Math
{
public:
	static float Lerp(float startf, float endf, float delta)
	{
		return startf * (1.0f - delta) + endf * (delta);
	}
};