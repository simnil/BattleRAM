

#include "sini/util/Grid.h"

namespace sini {

	// Constructors
	Grid::Grid(int width, int height)
		: width(width),
		  height(height)
	{

		for (int32_t i = 0; i < width; i++) {
			for (int32_t j = 0; j < height; j++) {

				GridTile* tile = new GridTile(i, j);
				tile->gridPtr = this;
				nodes.insert({ {i, j}, tile });
			}
		}
	}

	Grid::Grid(vec2i dimensions) : Grid(dimensions.x, dimensions.y) {}

	// Destructor
	Grid::~Grid() {

		for (int32_t i = 0; i < width; i++) {
			for (int32_t j = 0; j < height; j++) {

				delete nodes.at({ i, j });
			}
		}
	}


	// Functions

	GridTile* Grid::node(vec2i pos) {
		return dynamic_cast<GridTile*>(nodes.at(pos));
	}
}