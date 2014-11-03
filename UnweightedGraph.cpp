/**
 * UnweightedGraph Class
 * Stub written by Sorrachai Yingchareonthawornchai, 29 OCT 2014
 * Completed by [Your Name]
 */
#include "UnweightedGraph.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iterator>

using namespace std;

UnweightedGraph::UnweightedGraph(const string& t)
{
	 //You may add any construction to your private attribute.
	ifstream in(t);
	if(!in.is_open()) {
		cerr << "cannot open file!" << std::endl;
		exit(EXIT_FAILURE);
	}
	string line;
	while(getline(in,line)) {
		istringstream iss(line);
		int v;
		list<int> list_temp;
		while( iss >> v) {
			list_temp.push_back(v);
		}
		adjList.push_back(list_temp);
	}

}

void UnweightedGraph::DisplayInfo() const{
	cout << "Adjacency list of the graph \n";
	auto printItem = [](const list<int>& alist) {
		copy(begin(alist),end(alist), ostream_iterator<int>(cout, " "));
		cout << endl;
	};
	for_each(begin(adjList),end(adjList), printItem);
}

bool UnweightedGraph::IsConnected() const {
	//TODO
	//You can use either DFS or BFS approach
	return false; 
}

bool UnweightedGraph::IsEulerian() const {
	//TODO
	return false;
}

list<int> UnweightedGraph::FindEulerianCycle() const {
	list<int> current_cycle;
	// TODO
	return current_cycle;
}

bool UnweightedGraph::VerifyEulerCycle(const list<int>& cycle) const {
	//TODO
	return false;
}