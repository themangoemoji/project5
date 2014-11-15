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
  list<int>::iterator current_cycle_itr;
  list<int>::iterator subcycle_itr;
  // Used to terminate full cycle
  bool paths_exhausted = false;

  // These are the indecies of the start and end of a path
  // These will also be used to set the bool values of the matrix
  int pathStart = 0, pathEnd = 0, initial = -1, cycle_start = 0, compare_end = 9999;

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
  bool new_head_found = false;

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
  //  subcycle.push_back(pathStart);
  current_cycle_itr = current_cycle.begin();

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
          subcycle.push_back(pathStart);
        bool_matrix[pathStart][pathEnd] = 1;
        bool_matrix[pathEnd][pathStart] = 1;

        auto holdStart = *node_iters[pathStart]; 
        //std::advance(node_iters[pathStart], 1);
        if (node_iters[pathStart] != adjList[pathStart].end())
          node_iters[pathStart]++;
        pathStart = holdStart;
        //pathStart = *node_iters[temp_Start];
        pathEnd = *node_iters[pathStart];
        compare_end = pathStart;

        if (compare_end == cycle_start) 
        {
          subcycle.push_back(pathStart);     
        }

      }
      // There was not a valid path from the start node
      else
      {
        // Increment pointer to next possible start node for next iteration through adjList
        // Do this only if the next pathEnd would not point to the end of the list
        if(node_iters[pathStart] != adjList[pathStart].end())
        {
          node_iters[pathStart]++;
          pathEnd = *node_iters[pathStart];

        }
        // If the path points to the end of the list,
        // Increment head nodes (from current_cycle) until 
        // we find a successful path
        else
        {
          new_head_found = false;
          while ( ! new_head_found)
          {
            current_cycle_itr++;
            if (current_cycle_itr == current_cycle.end())
            {
              cout << "FIN BETCH" << endl;
              paths_exhausted = true;
              cycle_start = compare_end;
              break;
            }
            pathStart = *current_cycle_itr;
            if(node_iters[pathStart] != adjList[pathStart].end())
            {
              pathEnd = *node_iters[pathStart];
              new_head_found = true;
            }
            else 
            {
            }
            compare_end = 999999;
            cycle_start = pathStart; 
            // Done, bitchz
          }
        }
      }
    }

    if (paths_exhausted == 0) {
      compare_end = 99999;
      // Splicing sublist into current_list

      // Hold the size of the subcycle to adjust iterator after we splice
      // Because the iterator will have been moved right
      int diff_size = subcycle.size();

      // We instantiate and decrement the subcycle iterator, 
      // We do not want the last element
      subcycle_itr = subcycle.end();
      subcycle_itr--;

      if (current_cycle.size() != 0)
      {
        current_cycle.splice(current_cycle_itr, subcycle, subcycle.begin(), (subcycle_itr));
      }
      else
        current_cycle.splice(current_cycle_itr, subcycle);
      subcycle.clear();

      // Continue on next loop
      for (auto elem : current_cycle)
      {
        // If we find a viable path, set up next subcycle
        if (node_iters[elem] != adjList[elem].end()) 
        {
          pathStart = elem;
          pathEnd = *node_iters[elem];
          compare_end = 99999;
          cycle_start = pathStart;
          //subcycle.push_back(pathStart);
          break;
        }
      } 
    }
  }
  return current_cycle;
}

bool UnweightedGraph::VerifyEulerCycle(const list<int>& cycle) const {
  //TODO
  return false;
}
