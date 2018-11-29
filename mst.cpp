#include "mst.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
//Adam Angel
//11/28/18
//I recieved no help from outside sources and all the work was done by myself

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
	std::vector<VertexInfo>Vtexs;				//vector to hold my vertexinfo objects
	for(int i = 0; i < m[0].size(); i++){		//pushes back vertex info obj to size of a row
		Vtexs.push_back(VertexInfo(i));

	}
	
	// A priority queue of VertexInfo pointers used by the prim function.
	class PriorityQueue {
		std::vector<VertexInfo*>pqvtexs;		//vector to hold the addresses of my vertexinfo objects
		
		

		// Add a collection object to hold the priority queue's data
		// (a std::vector holding VertexInfo pointers is the best choice)
		static bool Comparer(VertexInfo *vi1, VertexInfo *vi2) {
			if (vi1->value > vi2->value) {		//used so that make_heap makes a minimal heap not a max heap
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
			std::pop_heap(pqvtexs.begin(), pqvtexs.end(), Comparer); //overloaded pop_heap that uses comparer function as means of comparison
			pqvtexs.pop_back();		//had to do this because pop_heap doesn't actually pop the last item off.
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
	int randstart  = (rand() % Vtexs.size()); //gets random number to use as index into vector
	Vtexs[randstart].value = 0; //random vertex info obj picked and value set to 0
	PriorityQueue PQ;			//inizializes priority queue object
	for (int i = 0; i < Vtexs.size(); i++) {
		PQ.enqueue(&Vtexs[i]);				//uses enqueue funct to store addresses of vtexs in its own private vector
	}
	//PRIMS ALGORITHM
	while (PQ.empty() == false) {
		auto u = PQ.dequeue(); //dequeues all elements
		u->open = false;
		for (int i = 0; i < m[u->index].size(); i++) { //gows through row of dequeued vertex info
			if (m[u->index][i] != INF) { //if there is a connection
				auto v = m[u->index][i];  //get value at that place
				if (Vtexs[i].open && m[u->index][i] < Vtexs[i].value) {	//if shorter path found set val to shortest path and link the prev
					
					Vtexs[i].value = v;
					Vtexs[i].prev = u;
					PQ.rebuild();
				}
			}	
		}
	}
	AdjacencyMatrix newMatrix(m.size(), std::vector<int>(m.size(), INF));
	for (int i = 0; i < Vtexs.size(); i++)//builds the actual matrix
	{
		if (Vtexs[i].prev) {
			auto r = Vtexs[i].prev->index;
			auto t = Vtexs[i].index;
			auto s = Vtexs[i].value;
			newMatrix[r][t] = s; //undirected so must set both rows and columns to be identical.
			newMatrix[t][r] = s;
		}
		
	}
	
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


