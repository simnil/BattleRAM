#include <iostream>
#include "SDL.h"
#include "GL/glew.h"


#include "BattleRamConfig.h"
#include "sini/math/Vector.h"
#include "sini/util/Grid.h"
#include <unordered_map>
#include "sini/math/Node.h"
#include "sini/util/Pathfinder.h"
#include <algorithm>

using namespace sini;

std::vector<vec2i> path;
bool contains(vec2i);

int main(int argc, char* args[]) {

	std::cout << "Hello, World!" << std::endl;
	std::cout << "version: " << BattleRAM_VERSION_MAJOR << "." << BattleRAM_VERSION_MINOR << std::endl;

	std::cout << "\nVECTOR TESTS" << std::endl;
	vec3 u = { 1, 1, 0 };
	vec3 v = { 0, 1, 1 };
	vec3 w = u^v;
	float scalar = vec2{ 1.5, 1 } | vec2{ 1, 1.5 };

	std::cout << "u :               " << u.x << "\t" << u.y << "\t" << u.z << std::endl;
	std::cout << "v :               " << v.x << "\t" << v.y << "\t" << v.z << std::endl;
	std::cout << "uv cross product: " << w.x << "\t" << w.y << "\t" << w.z << std::endl;
	std::cout << "\nScalar product of (1.5, 1) and (1, 1.5):\t" << scalar << std::endl;

	vec2i v2 = { -1, 1 };
	std::cout << "\nVector (" << v2.x << ", " << v2.y << ")" << std::endl;
	std::cout << "p-norm:  " << norm(v2)	<< std::endl;
	std::cout << "length:  " << length(v2)	<< std::endl;
	
	vec2i temp = abs(v2);
	std::cout << "\nabs: " << temp.x << "\t" << temp.y << std::endl;

	temp = v2 + vec2i{1, 0};
	std::cout << temp.x << "\t" << temp.y << std::endl;


	//std::cout << "\nGRID TEST" << std::endl;
	Grid grid(10, 10);
	grid.node({ 1, 2 })->blocked = true;
	grid.node({ 2, 2 })->blocked = true;
	grid.node({ 3, 2 })->blocked = true;
	grid.node({ 4, 2 })->blocked = true;
	grid.node({ 5, 2 })->blocked = true;
	grid.node({ 6, 2 })->blocked = true;
	grid.node({ 7, 2 })->blocked = true;
	grid.node({ 8, 2 })->blocked = true;
	grid.node({ 6, 3 })->blocked = true;
	grid.node({ 6, 4 })->blocked = true;
	grid.node({ 6, 5 })->blocked = true;
	grid.node({ 6, 6 })->blocked = true;
	grid.node({ 6, 7 })->blocked = true;
	grid.node({ 6, 8 })->blocked = true;


	/*for (int i = 0; i < grid.height; i++) {
		for (int j = 0; j < grid.width; j++) {
			std::cout << (grid.node({j, grid.height-1-i})->blocked ? "T  " : "F  ");
		}
		std::cout << std::endl;
	}*/

	std::cout << "\nPATH TEST" << std::endl;

	Pathfinder<vec2i,float> pathfinder(&grid);
	//pathfinder.heuristic = [](Node<vec2i,float>*, Node<vec2i,float>*) { return 1.0f; };

	path = pathfinder.findPath({ 0, 0 }, { 8, 7 });


	for (int i = 0; i < path.size(); i++)
		std::cout << "(" << path[i].x << ", " << path[i].y << ")  ";
	std::cout << std::endl;

	for (int j = grid.height-1; j >= 0; j--) {
		for (int i = 0; i < grid.width; i++) {
			if (grid.node({ i, j })->blocked)
				std::cout << "#  ";
			else if (contains({ i, j }))
				std::cout << "x  ";
			else
				std::cout << ".  ";
		}
		std::cout << std::endl;
	}

	


	return 0;
}

bool contains(vec2i v) {
	for (int i = 0; i < path.size(); i++)
		if (path[i] == v) return true;
	return false;
}