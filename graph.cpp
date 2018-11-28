#include "graph.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <climits>  //  For INT_MAX

//  Reads an adjacency matrix from a textfile.
//  Returns NO_MATRIX if an adjacency matrix 
//  cannot be made.
AdjacencyMatrix load_matrix(const std::string& filename) {
	int number_of_vertices;
	//  Open file
	std::fstream fin(filename, std::ios::in);
	if (fin.good()) {
		//  Read number of vertices
		fin >> number_of_vertices;
		//  Create the appropriately-sized matrix
		AdjacencyMatrix matrix(number_of_vertices,
			std::vector<int>(number_of_vertices));
		//  Populate the adjacency matrix
		for (int row = 0; row < number_of_vertices; row++) {
			for (int col = 0; col < number_of_vertices; col++) {
				int in_value;
				fin >> in_value;
				matrix[row][col] = (in_value == -1) ? INF : in_value;
			}
		}
		//  Close file
		fin.close();
		return matrix;
	}
	return NO_MATRIX;   //  Could not load the adjacency matrix
}

//  Makes graph consisting of a forest of n single 
//  vertex trees.
AdjacencyMatrix disconnected_graph(int n) {
	return AdjacencyMatrix(n, std::vector<int>(n, INF));
}

// Displays adjacency matrix m using output stream os. 
std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& m) {
	if (m == NO_MATRIX)
		os << "No adjacency matrix" << '\n';
	else {
		for (const auto& row : m) {
			for (auto elem : row) {
				if (elem == INF)
					os << std::setw(3) << '.';
				else
					os << std::setw(3) << elem;
			}
			os << '\n';

		}
	}
	return os;
}

const AdjacencyMatrix NO_MATRIX;

const int INF = INT_MAX;