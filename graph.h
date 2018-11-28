#ifndef GRAPH_H_
#define GRAPH_H_

#include <iostream>
#include <vector>
#include <string>

// Convenient type name for an adjacency matrix
using  AdjacencyMatrix = std::vector<std::vector<int>>;

extern const int INF;  //  Represents infinity

//  Represents a non-matrix. Useful for 
//  when an adjacency matrix is required
//  but for some reason the necessary matrix
//  is not available.
extern const AdjacencyMatrix NO_MATRIX;

//  Reads an adjacency matrix from a textfile.
//  Returns NO_MATRIX if an adjacency matrix 
//  cannot be made.
AdjacencyMatrix load_matrix(const std::string& filename);

//  Makes graph consisting of a forest of n single 
//  vertex trees.
AdjacencyMatrix disconnected_graph(int n);

// Displays adjacency matrix m using output stream os. 
std::ostream& operator<<(std::ostream& os, const AdjacencyMatrix& m);


#endif