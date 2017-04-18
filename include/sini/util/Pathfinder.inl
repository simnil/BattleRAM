#pragma once

namespace sini {

	// CONSTRUCTORS
	// --------------------------------------------------------------------------------
	template<typename ID, typename COST>
	Pathfinder<ID, COST>::Pathfinder(Graph<ID, Node<ID, COST>>* graph)
		: graph(graph)
	{}


	template<typename ID, typename COST>
	std::vector<ID> Pathfinder<ID, COST>::findPath(ID start, ID finish) {

		//TODO throw exception or warning?
		if (graph == nullptr) return std::vector<ID>();


		std::unordered_set<ID> explored;
		std::priority_queue<Path, std::vector<Path>, std::greater<Path>> frontier;

		// If the heuristic is undefined, use the heuristic f(N) = 0
		if (heuristic == nullptr) {
			heuristic = [](Node<ID, COST>*, Node<ID, COST>*) -> COST { return COST(0); };
		}

		// Add the starting node to the frontier
		Path start_;
		start_.path.push_back(start);
		start_.cost = 0;
		start_.heuristic = heuristic(graph->nodes[start], graph->nodes[finish]);
		frontier.push(start_);

		while (!frontier.empty()) {
			// Look at and remove first path in queue
			Path currentPath = frontier.top();
			frontier.pop();
			Node<ID, COST>* currentNode = graph->nodes[currentPath.path.back()];

			// Is this the node we're looking for?
			if (currentNode->id() == finish) {
				return currentPath.path;
			}

			// Mark node as explored
			explored.insert(currentNode->id());
			// Look at its neighbours
			std::vector<Edge<ID, COST>> edges = currentNode->edges();
			// Check if neighbours are unexplored and if so, add them to the frontier
			for (auto const& edge : edges) {

				// Check whether the node has been explored or not
				if (explored.count(edge.to->id()) > 0) {
					// Already explored
					continue;
				}
				else {
					// Not explored, add to frontier

					// Evaluate heuristic
					COST h = heuristic(edge.to, graph->nodes[finish]);

					Path newPath = currentPath;
					newPath.path.push_back(edge.to->id()); // Add neighbour to current path
					newPath.cost += edge.cost;
					newPath.heuristic = h;

					// Add to frontier
					frontier.push(newPath);

				}
			}
		}

		// Frontier empty -> no path found
		return std::vector<ID>();
	}


	template<typename ID, typename COST>
	COST euclideanHeuristic(Node<ID, COST>* currentNode, Node<ID, COST>* goal) {
		return COST(length(currentNode->id() - goal->id()));
	}

	template<typename ID, typename COST>
	COST pathlength(const std::vector<ID>& path) {

		COST len = COST(0);
		for (int i = 0; i < path.size() - 1; i++)
			len += length(path[i] - path[i + 1]);
		return len;
	}

}