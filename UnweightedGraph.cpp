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
    copy(begin(alist), end(alist), ostream_iterator<int>(cout, " "));
    cout << endl;
  };
  for_each(begin(adjList),end(adjList), printItem);
}

bool UnweightedGraph::IsConnected() const {
  //TODO
  //You can use either DFS or BFS approach
  int startNode = 0;
  bool *visited = new bool[adjList.size()];

  for(auto i = 0; i != adjList.size(); i++)
    visited[i] = false;

  // Queue for list
  std::list<int> queue;

  // Visit start and add it to queue
  visited[startNode] = true;
  queue.push_back(startNode);

  while ( ! queue.empty() )
  {
    // Dequeue a vertex and print it
    startNode = queue.front();
    queue.pop_front();

    for(auto iter = adjList[startNode].begin(); iter != adjList[startNode].end(); ++iter)
    {
      if (! visited[*iter])
      {
        visited[*iter] = true;
        queue.push_back(*iter);
      }
    }
  }
  // Check the array of bools for values
  for(int i = 0; i < adjList.size(); i++)
  {
    if (visited[i] == false) 
    {
      delete(visited);
      return false;
    }
  }
  // If successful escape
  delete(visited);
  return true;
}

// My really bad Euelrian function
bool UnweightedGraph::IsEulerian() const {
  int place = 0;
  std::vector<int> outDegs (adjList.size(), 0);
  std::vector<int> inDegs (adjList.size(), 0);

  for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
  {
    for (auto list = iter->begin(); list != iter->end(); ++list)
    {
      outDegs[place]++;
      outDegs[*list]++;
    }// Of for
    place++;
  }// Of for

  for (int i = 0; i != outDegs.size(); i++)
  {
    if (outDegs[i] % 2 != 0)
      return false;
  }// Of for 
  return true;
}

list<int> UnweightedGraph::FindEulerianCycle() const {
	// Creating the lists that will keep track of the cycles
	// Splice_into will eventually hold the finished cycle
	std::vector<std::list<bool> > boolList;
	list<int> subcycle;  
	list<int> cycle;  
	std::vector< std::pair<int, int> > paths;
	int firstnum = 0, secondnum = 0;
	path = std::make_pair<int,int> (firstnum, secondnum);
	
	// Load values into paths
	for (auto iter = adjList.begin(); iter != adjList.end(); iter++)
	{
		for (auto listIt = iter.begin(); listIt = iter.end(); listIt++)
		{
			// Make paths and insert them into vector of paths
			path.first = *iter;				
			path.second = *listIt;				
			vector.pushback(path)	
				// Reverse path and insert
		}
	}

	for (auto elem : paths)
	{
		cout << elem.first << ", " << elem.second << endl;
	}
	cout << endl;

	// Starting the cycle with the first element of the first list

	return current_cycle;
}

bool UnweightedGraph::VerifyEulerCycle(const list<int>& cycle) const {
	//TODO
	return false;
}
