#include "terrainDropwave.h"
#include "utils/mathUtils.h"

#include <math.h>
#include <algorithm>

using namespace LGen;

TerrainDropwave::TerrainDropwave(
	const float width,
	const float height,
	const float period) :
	Terrain(width, height),
	period(period) {

}

float TerrainDropwave::sample(const float x, const float y) const {
	if(period == 0)
		return 0;

	const float dx = x - getWidth() * 0.5f;
	const float dy = y - getHeight() * 0.5f;
	const float dxf = dx / (getWidth() * 0.5f);
	const float dyf = dy / (getHeight() * 0.5f);
	const float falloff = 1 - std::min(1.0f, std::sqrt(dxf * dxf + dyf * dyf));

	return (1 + cos(sqrt(dx * dx + dy * dy) * Utils::Math::PI * 2 / period)) * 0.5f * falloff;
}