#include "mst.h"
#include <iostream>

int main(int argc, char *argv[]) {
	if (argc > 0) {
		AdjacencyMatrix adj = load_matrix("graph1.txt");
		std::cout << adj << '\n';
		std::cout << "Weight: " << weight(adj) << '\n';
		auto mst = prim(adj);
		std::cout << mst << '\n';
		std::cout << "Weight: " << weight(mst) << '\n';
	}
	else
		std::cout << "File name required" << '\n';
	system("pause");
}
