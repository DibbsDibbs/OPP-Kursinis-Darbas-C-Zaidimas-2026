#pragma once

class Player;
class Platform;

namespace utils
{
	bool IsBetween(float val, float rangeB, float rangeE);
	bool IsOnPlatform(const Player& player, const Platform& platform);
}
