#include "utils.h"
#include "objects.h"
#include "Platform.h"

bool utils::IsBetween(float val, float rangeB, float rangeE)
{
	return val > rangeB && val < rangeE;
}

bool utils::IsOnPlatform(const Player& player, const Platform& platform)
{
	const bool betweenX =
		IsBetween(player.LegsStartX(), platform.StartX(), platform.EndX()) ||
		IsBetween(player.LegsEndX(),   platform.StartX(), platform.EndX());

	const bool betweenY =
		IsBetween(player.LegsY(), platform.TopY(), platform.BottomY());

	return betweenX && betweenY;
}
