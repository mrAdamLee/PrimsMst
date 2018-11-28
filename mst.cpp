#include "mst.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>

// Uses Prim's algorithm to compute and return a minimal spanning 
// tree of the graph represented by the adjacency matrix m.
AdjacencyMatrix prim(const AdjacencyMatrix& m) {
	// Stores the accessory information about a vertex that 
	// Prim's algorithm needs to do its work.
	
	
	struct VertexInfo {
		const int index;    // Which vertex does this information concern?
		int value;          // Value assigned to a vertex by Prim's algorithm.
		VertexInfo *prev;   // Adjacent vertex in the edge to be added to the MST.
		bool open;          // Has an edge in a MST yet been assigned to this vertex?
		// Creates a VertexInfo object with a given index.  Initializes the other
		// fields with values ready for Prim's algorithm to use.
		VertexInfo(int idx) :
			index(idx), value(INF), prev(nullptr), open(true) {}
	};
	std::vector<VertexInfo>Vtexs;
	for(int i = 0; i < m[0].size(); i++){
		Vtexs.push_back(VertexInfo(i));

	}
	
	// A priority queue of VertexInfo pointers used by the prim function.
	class PriorityQueue {
		std::vector<VertexInfo*>pqvtexs;
		
		

		// Add a collection object to hold the priority queue's data
		// (a std::vector holding VertexInfo pointers is the best choice)
		static bool Comparer(VertexInfo *vi1, VertexInfo *vi2) {
			if (vi1->value > vi2->value) {
				return true;
			}
			else
				return false;
		}
		// Add a static Comparer function to be used to manage the min-heap 
		// (be sure to compare the value fields of the objects that the pointers
		// point to--do not just compare the pointers to each other!

	public:
		
		// Inserts an element into the priority queue
		void enqueue(VertexInfo *vi) {
			pqvtexs.push_back(vi);
			std::make_heap(pqvtexs.begin(), pqvtexs.end(), Comparer);

		}

		// Serves the highest priority element from the priority queue
		VertexInfo *dequeue() {
			VertexInfo* ele = pqvtexs[0];
			std::pop_heap(pqvtexs.begin(), pqvtexs.end(), Comparer);
			pqvtexs.pop_back();
			return ele;
			
		}

		// Returns false if the queue contains any elements; otherwise, returns true.
		bool empty() const {
			return pqvtexs.empty();
		}

		// Reforms the internal heap structure.  Used to simulate the decrease_key
		// operation required by Prim's algorithm.
		void rebuild() {
			std::make_heap(pqvtexs.begin(), pqvtexs.end(), Comparer);
		}
	};
	int randstart  = (rand() % Vtexs.size());
	Vtexs[randstart].value = 0;
	PriorityQueue PQ;
	for (int i = 0; i < Vtexs.size(); i++) {
		PQ.enqueue(&Vtexs[i]);
	}
	while (PQ.empty() == false) {
		auto u = PQ.dequeue();
		u->open = false;
		for (int i = 0; i < m[u->index].size(); i++) {
			if (m[u->index][i] != INF) {
				auto v = m[u->index][i];
				if (Vtexs[i].open && m[u->index][i] < Vtexs[i].value) {
					
					Vtexs[i].value = v;
					Vtexs[i].prev = u;
					PQ.rebuild();
				}
			}	
		}
	}
	AdjacencyMatrix newMatrix(m.size(), std::vector<int>(m.size(), INF));
	for (int i = 0; i < Vtexs.size(); i++)
	{
		if (Vtexs[i].prev) {
			auto r = Vtexs[i].prev->index;
			auto t = Vtexs[i].index;
			auto s = Vtexs[i].value;
			newMatrix[r][t] = s;
			newMatrix[t][r] = s;
		}
		
	}
	/*
	PriorityQueue PQ;

	auto a = new VertexInfo(0);
	a->value = 20;
	auto b = new VertexInfo(1);
	b->value = 3;
	auto c = new VertexInfo(2);
	c->value = 0;
	PQ.enqueue(a);
	PQ.enqueue(b);
	PQ.enqueue(c);
	while (PQ.empty() == false) {
		auto u = PQ.dequeue();
		std::cout << u->value;
		std::cout << "\n";
		

	}
	// Add your code implementing the pseudocode for Prim's algorithm that we
	// examined in class
	*/
	// Replace with your computed MST adjacency matrix
	return newMatrix; ;
}


// Returns the weight of the edges in an undirected graph.
int weight(const AdjacencyMatrix& m) {
	int n = m.size();
	int wt = 0;
	for (int row = 0; row < n - 1; row++)
		for (int col = row + 1; col < n; col++)
			if (m[row][col] != INF)
				wt += m[row][col];
	return wt;
}


