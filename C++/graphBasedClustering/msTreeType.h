#pragma once
#include "unorderedLinkedList.h"
#include "linkedQueueType.h"
#include "linkedListIterator.h"
#include "orderedLinkedList.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <assert.h>

using namespace std;

template<class gType>
class msTreeType {
public:
	void createSpanningGraph(ifstream &infile, ofstream &outfile);
	void needToCut();
	void adjustTree();
	void minimumSpanning(int sVertex);
	void printTreeAndWeight();
	msTreeType(int size = 0);
	~msTreeType();
	//void printGraph() const;
	void clearGraph();
	void breadthFirstTraversal(ofstream &out);
protected:
	int source;
	double **weights;
	int *edges;
	double *edgeWeights;
	int cluster;
	unorderedLinkedList<int> *graph; //array to create adjacency lists
public:
	int gSize; //current number of vertices
	int maxSize; //maximum number of vertices
};

template<class gType>
void msTreeType<gType>::createSpanningGraph(ifstream &infile, ofstream &outfile) {
	for (int i = 0; i < gSize; i++) {
		for (int j = 0; j < gSize; j++) {
			weights[i][j] = -999;
		}
	}

	string line, num;
	int count = 0;
	while (!infile.eof()) {
		getline(infile, line);
		stringstream ss(line);
		if (line == "") {
			break;
		}
		while (ss >> num) {
			int x = stoi(num, nullptr, 10);
			graph[count].insertLast(x);
		}
		count++;
	} count = 0;

	int adjlnct = 0, vertex = 0, adjacentVertex = 0, biggestindex = 0;

	while (!infile.eof()) {
		getline(infile, line);
		stringstream ss(line);
		if (line == "") {
			break;
		}
		while (ss >> num) {
			int x = stoi(num, nullptr, 10);
			weights[vertex][adjacentVertex] = x;
			adjacentVertex++;
		}
		vertex++;

		if (adjacentVertex != gSize) {
			outfile << "";
			exit(0);
		}
		adjacentVertex = 0;
	}
	if (vertex != gSize) {
		outfile << "";
		exit(0);
	}

	//cerr << "Graph" << endl;
	//this->printGraph();

	/*int weight;
	//cerr << "msTreeType Matrix" << endl;
	for (vertex = 0; vertex < gSize; vertex++) {
		for (adjacentVertex = 0; adjacentVertex < gSize; adjacentVertex++) {
			infile >> weight;
			weights[vertex][adjacentVertex] = weight;
			//cerr << weights[vertex][adjacentVertex] << " ";
		}
	//	cerr << endl;
	}*/
	//cerr << endl;

	//infile >> cluster;

	//cerr << cluster << endl << endl;
}

template<class gType>
void msTreeType<gType>::adjustTree() {
	int temp = gSize;
	clearGraph();
	gSize = temp;
	temp = 0;
	for (int x = 0; x < gSize; x++) {
		if (edges[x] == x || edgeWeights[x] == -999) {
			continue;
		}
		else {
			graph[edges[x]].insertLast(x);
			graph[x].insertLast(edges[x]);
		}
	}

	//cerr << "Graph" << endl;
	//printGraph();
}

template<class qType>
void msTreeType<qType>::needToCut() {
	int tempEdge = 0;
	double tempWeight = 0;

	for (int x = 0; x < gSize; x++) {
		if (tempWeight < edgeWeights[x]) {
			tempWeight = edgeWeights[x];
			tempEdge = x;
		}
	}

	edgeWeights[tempEdge] = -999;
}

template<class gType>
void msTreeType<gType>::minimumSpanning(int sVertex) {
	int startVertex, endVertex;
	double minWeight;
	source = sVertex;
	bool *mstv;
	mstv = new bool[gSize];
	for (int j = 0; j < gSize; j++)	{
		mstv[j] = false;
		edges[j] = source;
		edgeWeights[j] = weights[source][j];
	}
	mstv[source] = true;
	edgeWeights[source] = 0;
	for (int i = 0; i < gSize - 1; i++) {
		minWeight = DBL_MAX;
		for (int j = 0; j < gSize; j++)
			if (mstv[j])
				for (int k = 0; k < gSize; k++)
					if (!mstv[k] && weights[j][k] < minWeight && weights[j][k] != -999)
					{
						endVertex = k;
						startVertex = j;
						minWeight = weights[j][k];
					}
		mstv[endVertex] = true;
		edges[endVertex] = startVertex;
		edgeWeights[endVertex] = minWeight;
	} //end for
}

template<class gType>
void msTreeType<gType>::printTreeAndWeight() {
	double treeWeight = 0;
	cout << "Source Vertex: " << source << endl;
	cout << "Edges Weight" << endl;
	for (int j = 0; j < gSize; j++)
	{
		if (edges[j] != j) {
			treeWeight = treeWeight + edgeWeights[j];
			cout << "(" << edges[j] << ", " << j << ") "
				<< edgeWeights[j] << endl;
		}
	}
	cout << endl;
	cout << "Minimum spanning Tree Weight: "
		<< treeWeight << endl;
}

template<class gType>
msTreeType<gType>::msTreeType(int size) {
	if (gSize != 0) //if the graph is not empty, make it empty
		clearGraph();
	maxSize = size * 10;
	gSize = size;
	graph = new unorderedLinkedList<int>[size];
	weights = new double*[size];
	for (int i = 0; i < size; i++)
		weights[i] = new double[size];
	edges = new int[size];
	edgeWeights = new double[size];
}

template<class gType>
msTreeType<gType>::~msTreeType() {
	for (int i = 0; i < gSize; i++)
		delete[] weights[i];
	delete[] weights;
	delete[] edges;
	delete[] edgeWeights;
}

/*template <class gType>
void msTreeType<gType>::printGraph() const
{
	for (int index = 0; index < gSize; index++)
	{
		cout << index << " ";
		graph[index].print();
		cout << endl;
	}
	cout << endl;
} //end printGraph*/

template <class gType>
void msTreeType<gType>::clearGraph() {
	for (int index = 0; index < gSize; index++)
		graph[index].destroyList();
	gSize = 0;
} //end clearGraph

template <class gType>
void msTreeType<gType>::breadthFirstTraversal(ofstream &out) {
	linkedQueueType<int> queue;
	orderedLinkedList<int> temp;
	bool *visited;
	visited = new bool[gSize];
	for (int ind = 0; ind < gSize; ind++)
		visited[ind] = false; //initialize the array
							  //visited to false
	linkedListIterator<int> graphIt;
	for (int index = 0; index < gSize; index++)

		if (!visited[index]) {
			queue.addQueue(index);
			visited[index] = true;
			//out << index << " ";
			//cerr << index << " ";
			temp.destroyList();
			temp.insert(index);
			while (!queue.isEmptyQueue()) {
				int u = queue.front();
				queue.deleteQueue();
				for (graphIt = graph[u].begin();
					graphIt != graph[u].end(); ++graphIt) {
					int w = *graphIt;
					if (!visited[w]) {
						queue.addQueue(w);
						visited[w] = true;
						//out << w << " ";
						//cerr << w << " ";
						temp.insert(w);
					}
				}
			} //end while
			//out << endl;

			temp.print(out);
			out << endl;
			cerr << endl;
		}
	//cout << endl;
	delete[] visited;
} //end breadthFirstTraversal
