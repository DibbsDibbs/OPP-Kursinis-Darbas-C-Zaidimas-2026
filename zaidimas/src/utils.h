#pragma once

class Player;
class Platform;

namespace utils
{
	bool IsBetween(float val, float rangeB, float rangeE);
	bool IsOnPlatform(const Player& player, const Platform& platform);

	// Universali sabloninė funkcija — veikia su int, float, double ir kt.
	template<typename T>
	T clamp(T value, T minVal, T maxVal)
	{
		if (value < minVal) return minVal;
		if (value > maxVal) return maxVal;
		return value;
	}
}
