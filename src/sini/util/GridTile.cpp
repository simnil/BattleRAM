

#include "sini/util/GridTile.h"

namespace sini {

	// CONSTRUCTORS
	GridTile::GridTile(const vec2i& pos) noexcept
		: position(pos)
	{}

	GridTile::GridTile(int x, int y) noexcept {
		position = vec2i( x, y );
	}
	
	// Returns all a list of edges to adjacent GridTiles (if placed in a grid).
	// This include diagonal GridTiles.
	std::vector< Edge<vec2i,float> > GridTile::edges() {

		static const float sqrt2 = std::sqrt(2.0f);
		std::vector< Edge<vec2i,float> > edges;

		// There are no edges if the GridTile isn't part of a grid
		if (gridPtr == nullptr) return edges;

		int width = gridPtr->width;
		int height = gridPtr->height;

		// Left
		if (position.x > 0) {
			GridTile* to = (*gridPtr)[position + vec2i{ -1, 0 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from	= this;
				edge.to		= to;
				edge.cost	= 1.0f;
				edges.push_back(edge);
			}
		}
		// Down
		if (position.y > 0) {
			GridTile* to = (*gridPtr)[position + vec2i{ 0, -1 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from	= this;
				edge.to		= to;
				edge.cost	= 1.0f;
				edges.push_back(edge);
			}
		}
		// Down-left
		if (position.x > 0 && position.y > 0) {
			GridTile* to = (*gridPtr)[position + vec2i{ -1, -1 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from	= this;
				edge.to		= to;
				edge.cost	= sqrt2;
				edges.push_back(edge);
			}
		}
		// Up-left
		if (position.x > 0 && position.y < height-1) {
			GridTile* to = (*gridPtr)[position + vec2i{ -1, 1 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from	= this;
				edge.to		= to;
				edge.cost	= sqrt2;
				edges.push_back(edge);
			}
		}
		// Down-right
		if (position.x < width - 1 && position.y > 0) {
			GridTile* to = (*gridPtr)[position + vec2i{ 1, -1 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from	= this;
				edge.to		= to;
				edge.cost	= sqrt2;
				edges.push_back(edge);
			}
		}
		// Right
		if (position.x < width - 1) {
			GridTile* to = (*gridPtr)[position + vec2i{ 1, 0 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from = this;
				edge.to = to;
				edge.cost = 1.0f;
				edges.push_back(edge);
			}
		}
		// Up
		if (position.y < height - 1) {
			GridTile* to = (*gridPtr)[position + vec2i{ 0, 1 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from	= this;
				edge.to		= to;
				edge.cost	= 1.0f;
				edges.push_back(edge);
			}
		}
		// Up-right
		if (position.x < width - 1 && position.y < height - 1) {
			GridTile* to = (*gridPtr)[position + vec2i{ 1, 1 }];
			if (to != nullptr && !to->blocked) {
				Edge<vec2i,float> edge;
				edge.from	= this;
				edge.to		= to;
				edge.cost	= sqrt2;
				edges.push_back(edge);
			}
		}

		return edges;
	}


	// Hashing function
	size_t GridTile::hash(const GridTile& tile) {
		return hash(tile.position);
	}

} // namespace sini
