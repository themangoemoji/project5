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
	list<int> current_cycle;  
  // These are the indecies of the start and end of a path
  // These will also be used to set the bool values of the matrix
  int pathStart = 0, pathEnd = 0, initial = -1, cycle_start = 0;

  // Pointer to the start of the current cycle
  // This tells us whether or not we have completed a cycle
  // Set to greater than the size of the list initially so that we may begin the while loop
  std::vector<std::list<int>::const_iterator> node_iters;

  // Data structures for constructing bool matrix
  std::vector<std::vector<bool> > bool_matrix;
  std::vector<bool> bool_vec; 
  cout << "START = " << pathStart << endl;
  // Iterate through length of list, insert "false" into vector of bools
  // that signal whether or not path is visited
  for (auto itr = 0; itr != adjList.size(); itr++)
  {
    bool_vec.push_back(0);
  }
  // Iterate through length and insert "false" lists into matrix
  for (auto itr = 0; itr != adjList.size(); itr++)
  {
    bool_matrix.push_back(bool_vec);
  }

  /*
   * SAMPLE ADJACENCY LIST
   * 0 | 2, 3  <<-- I call the 0, 1, 2, 3, 4.... nodes (the places we can traverse from)
   * 1 | 0, 2
   * 2 | ....
   * 3 | ....
   * 4 | ....
   */

  // Iterate through adjList to get pointers to the start of each list
  // Instantiate pointers to the begining of each of the adjacency lists (node_iters)
  // This will let us retain pointers to the elements in each node
  for (auto itr = adjList.begin(); itr != adjList.end(); itr++)
  {
    node_iters.push_back(itr->begin());
  }

  /*
  // * This prints the current pointer values DEBUG
  for (auto elem : node_iters)
    cout << *elem << ",";
  cout << endl;
  */

  // Start the cycle process
  // append first elem of adjList to current cycle
  auto currItr = node_iters[0];
  current_cycle.push_back(pathStart);
  cout << "start = " << pathStart << " | currItr = " << *currItr << endl;
  
  // append first iterator to current cycle
  
  // A single subcycle
  while (cycle_start != *currItr)
  {
    cout << "enter while" << endl;
    if (! bool_matrix[pathStart][*node_iters[pathStart]])
    {
      // Add the path to the current list, 
      // set paths to true (indicates they have been traversed)
      cout << "The path is fresh" << endl;
      cout << "pS, pE" << endl;
      pathEnd = *node_iters[pathStart];
      cout << pathStart << ", " << pathEnd << ", ";
      //cout  << *(node_iters[pathStart]) << ", " << current_cycle << endl;
      current_cycle.push_back(*currItr);
      bool_matrix[pathStart][pathEnd] = 1;
      bool_matrix[pathEnd][pathStart] = 1;

      auto holdStart = *node_iters[pathStart]; 
      std::advance(node_iters[pathStart], 1);
      pathStart = holdStart;
      //pathStart = *node_iters[temp_Start];
      pathEnd = *node_iters[pathStart];
      cout << endl << "NEW START AND END PATHS: " << pathStart << ' ' << pathEnd << endl;
    }
    else
    {
      // Increment pointer to next possible node for next iteration through adjList
      std::advance(node_iters[pathStart], 1);
    }
    /*
    // look for different path from currItr
    // Advance iterator to look for next path on next pass
    cout << endl << "NEXT IN PATH " << pathStart << endl;
    pathStart = *node_iters[pathStart];
    std::advance(node_iters[pathStart], 1);
    currItr = node_iters[pathStart];
    pathEnd = *node_iters[pathStart];
    cout << "pathStart = " << pathStart << "| currItr = " << *currItr << " | pathEnd = " << pathEnd << endl;
    */
  }

  cout << "CURR" << endl;
  for (auto elem : current_cycle)
    cout << elem << ", ";
  cout << endl;
  /*
     for (auto elem : bool_matrix)
     {
     for (auto item : elem)
     cout << item << ", " ;
     cout << endl;

     } 
     */

  return current_cycle;
}

bool UnweightedGraph::VerifyEulerCycle(const list<int>& cycle) const {
  //TODO
  return false;
}
