#pragma once
#ifndef SINI_MATH_GRAPH_H
#define SINI_MATH_GRAPH_H

#include <unordered_map>
#include "sini/math/Node.hpp"

namespace sini {

	template<typename ID, typename Nodetype>
	class Graph {
	public:
		// Constructors
		Graph() = default;
		Graph(const Graph<ID, Nodetype>& graph) = default;
		Graph(const std::unordered_map<ID, Nodetype*>& nodes) : nodes(nodes) {}

		// Members
		std::unordered_map<ID, Nodetype*> nodes;

		size_t size() { return nodes.size(); }
		//TODO add members(?) and functions

	};

	/*template<typename T>
	using SpatialGraph = Graph<T, SpatialNode<T>>;*/

}

#endif