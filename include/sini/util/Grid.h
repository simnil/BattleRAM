#pragma once
#ifndef SINI_GRID_GRAPH_H
#define SINI_GRID_GRAPH_H

#include "sini/math/Vector.h"
#include "sini/math/Graph.h"

namespace sini {

	class GridTile;

	class Grid : public Graph<vec2i,Node<vec2i,float>> { 

	public:
		Grid() = delete;
		Grid(int width, int height);
		Grid(vec2i dimensions);
		Grid(const Grid& grid) = default;
		~Grid();

		// Members
		const int width, height;

		// Member functions
		GridTile* node(vec2i pos);
		GridTile* operator[] (vec2i pos) { return node(pos); };

	private:
	};
}

// Included here to avoid circular dependency error
#include "sini/util/GridTile.h"

#endif