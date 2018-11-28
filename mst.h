#ifndef MST_H_
#define MST_H_

#include "graph.h"

// Uses Prim's algorithm to computes and return a minimal spanning 
// tree of the graph represented by the adjacency matrix m.
AdjacencyMatrix prim(const AdjacencyMatrix& m);

// Returns the weight of the edges in an undirected graph
int weight(const AdjacencyMatrix& m);

#endif