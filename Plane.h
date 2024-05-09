#pragma once

#include <vector>
#include <array>
#include "IndexedTriangleList.h"
#include "CustomMath.h"

class Plane
{
public:
	template<class V>
	static IndexedTriangleList<V> MaleTesselated(int division_x, int division_y)
	{
		namespace dx = DirectX;
		assert(division_x >= 1);
		assert(division_y >= 1);

		constexpr float width = 2.0f;
		constexpr float height = 2.0f;
		const int nVertices_x = division_x + 1;
		const int nVertices_y = division_y + 1;
		std::vector<V> vertices(nVertices_x * nVertices_y);
		
		{
			const float side_x = width / 2.0f;
			const float sude_y = height / 2.0f;
		}
	}
};