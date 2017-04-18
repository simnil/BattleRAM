#pragma once
#ifndef SINI_GRIDTILE_H
#define	SINI_GRIDTILE_H

#include "sini/util/Grid.h"

namespace sini {

	class GridTile : public Node<vec2i,float> {

	public:
		GridTile() = default;
		GridTile(const vec2i& pos) noexcept;
		GridTile(int x, int y) noexcept;
		~GridTile() noexcept = default;

		// Members
		vec2i position;
		Grid* gridPtr = nullptr;
		bool blocked = false;

		// Member functions
		std::vector< Edge<vec2i,float> > edges();
		vec2i id() { return position; }

		static size_t hash(const GridTile& tile);
		
	};

}

// Hasher injection into std
namespace std {
	template<>
	struct hash<sini::GridTile> {
		size_t operator() (const sini::GridTile& tile) const { return sini::GridTile::hash(tile); }
	};
}

#endif SINI_GRIDTILE_H