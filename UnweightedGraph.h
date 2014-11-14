/**
 * UnweightedGraph Class
 * Interface written by Sorrachai Yingchareonthawornchai, 29 OCT 2014
 * Completed by [Your Name]
 */
#ifndef UnweightedGraph_H
#define UnweightedGraph_H
#include <string>
#include <list>
#include <vector>
#include <map>
#include <iostream>

using std::endl;
using std::cout;

class UnweightedGraph
{
  public:
    UnweightedGraph(const std::string& t);

    void DisplayInfo() const;
    bool IsConnected() const;
    bool IsEulerian() const;

    std::list<int> FindEulerianCycle() const;
    bool VerifyEulerCycle(const std::list<int>& cycle) const;

  private:
    std::vector<std::list<int> > adjList;
    std::list<int> *adj = new std::list<int>[adjList.size()];
    std::vector<std::vector<bool> > bool_matrix;
    std::vector<bool> bool_vec; 
    //Add any attribute or method that can help complete your implementation

};
#endif
