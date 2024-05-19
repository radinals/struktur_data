#include <algorithm>
#include <iostream>
#include <list>
#include <queue>
#include <vector>

/*
 * TOOD:
 *  - better (safer) adding method
 *  - adjacency matrix
 *  - traversal algorithms
 *  - FIXME: MEMORY MANAGEMENT
 */

class Graph
{
      private:
	struct Edge;

	struct Vertex {
		int label = 0;
		int data = 0;
		std::list<Edge*> edges;
		Vertex() {}
		Vertex(int l, int d) : label(l), data(d){};
	};

	struct Edge {
		Vertex* dest;
		Vertex* src;
		Edge() : dest(nullptr), src(nullptr) {}
		Edge(Vertex* source, Vertex* destination)
		    : src(destination), dest(destination)
		{
		}
	};

	Vertex* source = nullptr;
	std::list<Vertex*> getVertexNeighbours(Vertex* vertex)
	{
		std::list<Vertex*> neighbours;
		std::vector<int> visited;
		visited.push_back(vertex->label);
		for (Edge* edge : vertex->edges) {
			if (std::find(visited.begin(), visited.end(),
			              edge->dest->label) == visited.end()) {
				neighbours.push_back(edge->dest);
				visited.push_back(edge->dest->label);
			};
		}
		return neighbours;
	}

      public:
	Graph() {}

	void addVertex(int label, int data)
	{
		if (source != nullptr) {
			source->data = data;
			source->label = label;
		} else {
			source = new Vertex;
			source->label = label;
			source->data = data;
		}
	}

	void addVertex(int source_vertex_label, int new_vertex_label, int data)
	{
		std::queue<Vertex*> Q;
		std::vector<int> visited;

		visited.push_back(source->label);
		Q.push(source);

		while (!Q.empty()) {
			Vertex* vertex = Q.front();
			Q.pop();

			if (vertex->label == source_vertex_label) {
				vertex->edges.push_back(new Edge(
				    vertex,
				    new Vertex(new_vertex_label, data)));
				return;
			}

			for (Vertex* neighbour : getVertexNeighbours(vertex)) {
				if (std::find(visited.begin(), visited.end(),
				              neighbour->label) ==
				    visited.end()) {
					visited.push_back(neighbour->label);
					Q.push(neighbour);
				}
			}
		}
	}

	void print_data()
	{
		std::queue<Vertex*> Q;
		std::vector<int> visited;

		visited.push_back(source->label);
		Q.push(source);

		while (!Q.empty()) {
			Vertex* vertex = Q.front();
			Q.pop();

			std::cout << "LABEL: " << vertex->label << ' '
			          << "DATA: " << vertex->data << '\n';

			for (Vertex* neighbour : getVertexNeighbours(vertex)) {
				if (std::find(visited.begin(), visited.end(),
				              neighbour->label) ==
				    visited.end()) {
					visited.push_back(neighbour->label);
					Q.push(neighbour);
				}
			}
		}
	}
};

int
main()
{
	Graph G = Graph();

	G.addVertex(0, 1);
	G.addVertex(0, 1, 2);
	G.addVertex(0, 2, 3);

	G.print_data();
	return 0;
}
