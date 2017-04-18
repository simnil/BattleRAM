// SiNi Pathfinder uses the AStar graph search algorithm to find the shortest path
// (lowest cost) between two nodes in a Graph.


#pragma once
#ifndef SINI_PATHFINDER_H
#define SINI_PATHFINDER_H

#include "sini/math/Graph.hpp"
#include "sini/math/Node.hpp"
#include <unordered_set>
#include <queue>
#include <functional>

namespace sini {

	// Default predefined heuristic
	template<typename ID, typename COST>
	COST euclideanHeuristic (Node<ID, COST>*, Node <ID, COST>*);

	template<typename ID, typename COST>
	class Pathfinder {

	public:
		// Constructors
		Pathfinder() = default;
		Pathfinder(Graph<ID,Node<ID,COST>>* graph);
		Pathfinder(const Pathfinder& pathfinder) = default;

		// Members
		Graph<ID,Node<ID,COST>>* graph = nullptr;
		COST(*heuristic)(Node<ID, COST>*, Node<ID, COST>*) = euclideanHeuristic;

		// Functions
		std::vector<ID> findPath(ID from, ID to);

	private:

		struct Path {
			std::vector<ID> path;
			COST cost;
			COST heuristic;

			Path() = default;
			Path(const std::vector<ID>& path, const COST& cost, const COST& heuristic)
				: path(path),
				  cost(cost),
				  heuristic(heuristic)
			{}

			bool operator> (const Path& other) const {
				return cost + heuristic > other.cost + other.heuristic;
			}
			bool operator< (const Path& other) const {
				return cost + heuristic < other.cost + other.heuristic;
			}
			ID end() { return path.back(); }

		};
	};
	using Pathfinder2Di = Pathfinder<vec2i, float>;
	using Pathfinder2Df = Pathfinder<vec2, float>;

	template<typename ID, typename COST>
	COST pathlength(const std::vector<ID>& path);


	
}

#include "Pathfinder.inl"

#endif