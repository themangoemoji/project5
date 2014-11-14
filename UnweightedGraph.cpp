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
  list<int> current_cycle;  
  list<int> subcycle;  
  // Used to terminate full cycle
  bool paths_exhausted = false;

  // These are the indecies of the start and end of a path
  // These will also be used to set the bool values of the matrix
  int pathStart = 0, pathEnd = 0, initial = -1, cycle_start = 0, compare_end = -1;

  // We will use this to count how many nodes point to null pointers
  // so that we can determine whether or not to terminate the cycle
  int count_null = 0;

  // Pointer to the start of the current cycle
  // This tells us whether or not we have completed a cycle
  // Set to greater than the size of the list initially so that we may begin the while loop
  std::vector<std::list<int>::const_iterator> node_iters;

  // Data structures for constructing bool matrix
  std::vector<std::vector<bool> > bool_matrix;
  std::vector<bool> bool_vec; 


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

  // Start the cycle process
  // append first elem of adjList to current cycle
  auto currItr = node_iters[0];
  subcycle.push_back(pathStart);

  while (! paths_exhausted)
  {
    // A single subcycle
    while (cycle_start != compare_end)
    {
      if (! bool_matrix[pathStart][*node_iters[pathStart]])
      {
        // Add the path to the current list, 
        // set paths to true (indicates they have been traversed)
        pathEnd = *node_iters[pathStart];
        if (node_iters[pathStart] != adjList[pathStart].end())
          subcycle.push_back(pathEnd);
        cout << "Pushing back " << pathEnd << endl;
        cout << " pS, PE " << endl;
        cout << pathStart << ' ' << pathEnd << endl;
        cout << " CURR " << endl;
        for (auto elem : subcycle)
          cout << elem << " ";
        cout << endl;
        bool_matrix[pathStart][pathEnd] = 1;
        bool_matrix[pathEnd][pathStart] = 1;

        auto holdStart = *node_iters[pathStart]; 
        //std::advance(node_iters[pathStart], 1);
        cout << " b e f o r e  &  a f t e r " << endl;
        cout << pathStart << ' ' << *node_iters[pathStart] << endl;
        if (node_iters[pathStart] != adjList[pathStart].end())
          node_iters[pathStart]++;
        cout << pathStart << ' ' << *node_iters[pathStart] << endl;
        pathStart = holdStart;
        //pathStart = *node_iters[temp_Start];
        pathEnd = *node_iters[pathStart];
        compare_end = pathStart;

      }
      else
      {
        // Increment pointer to next possible node for next iteration through adjList
        //std::advance(node_iters[pathStart], 1);
        if(node_iters[pathStart] != adjList[pathStart].end())
        {
          node_iters[pathStart]++;
        }


      }
    }


    // Count the number of nullptr paths, if they
    // are equal to the size of the vector of node iterators,
    // the paths are all exhausted --> exit the Algorithm
    for (auto i = 0; i != node_iters.size(); i++)
    {
      if (node_iters[i] == adjList[i].end())
      {
        cout << "COUNTING NULL" << endl;
        count_null++;
        cout << endl;
      }
    }

    // If we should break out of the whole thing
    if (count_null == node_iters.size())
      paths_exhausted = true;
    else
      count_null = 0;


    // Splicing sublist into current_list
    auto currCycItr = current_cycle.begin();
    current_cycle.splice(currCycItr, subcycle);

    cout << endl << " CURRENT CYCLE" << endl;
    for (auto elem : current_cycle)
      cout << elem << ' ';
    cout << endl;

    cout << endl << "SUBCYCLE" << endl;
    for (auto elem : subcycle)
      cout << elem << ' ';
    cout << endl;

    // Continue on next loop
    for (auto elem : subcycle)
    {
      if (node_iters[elem] != adjList[elem].end()) 
      {
        pathStart = elem;
        pathEnd = *node_iters[elem];
        break;
      }
    } 

  }
  return current_cycle;
}

bool UnweightedGraph::VerifyEulerCycle(const list<int>& cycle) const {
  //TODO
  return false;
}
