#pragma once
#ifndef SINI_MATH_GRAPH_NODE_H
#define SINI_MATH_GRAPH_NODE_H

#include <vector>
#include <cstddef> // For std::size_t

using std::size_t;

namespace sini {

	template<typename ID, typename COST >
	struct Edge;

	template<typename ID, typename COST>
	class Node {
	public:

		// Virtual functions to be overridden by subclasses
		virtual std::vector<Edge<ID, COST>> edges() = 0;
		virtual ID id() = 0;

	};

	template<typename ID, typename COST>
	struct Edge {
		Node<ID, COST>* from;
		Node<ID, COST>* to;
		COST cost;
	};
	
	/*template<typename T>
	class SpatialNode : public Node<float> {

	public:
		SpatialNode() = default;
		SpatialNode(const T& pos) noexcept : position(pos) {}

		T position;
	};*/

}

#endif