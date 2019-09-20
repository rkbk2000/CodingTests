#include <set>
#include <chrono>
#include<thread>
#include "command.h"

using namespace std;

// Dummy implementation to execute the command
ExecStatus Command::Execute()
{
   execStatus = ExecStatus::Passed;
   std::this_thread::sleep_for(10ms);
   //std::cout << "Executing: " << this->getNumber() << endl;
   return execStatus;
}

// Kahns algorithm to check if there are cycles in the graph
list<int> CommandGraph::topologicalSort()
{
   list<int> noEdgeList;
   set<int> addedNodes;
   bool cycleFound = false;

   // Get all the vertexes with zero incoming edges
   for (auto vertex: noIncomingEdgeSet) {
      noEdgeList.push_back(vertex);      
   }

   list<int> sortedList;
   while (!noEdgeList.empty()) {
      int cmd = noEdgeList.back();
      noEdgeList.pop_back();

      /// check if the node is already in the list
      auto found = addedNodes.find(cmd);
      if (found == addedNodes.end()) {
         sortedList.push_back(cmd);
         addedNodes.insert(cmd);
      }

      // For each node m with edge e from n do
      // Remove edge from e from n to m
      auto edgesToRemove = edges.find(cmd);
      if (edgesToRemove != edges.end()) {
         for (auto dep : edgesToRemove->second) {
            // Remove the edge
            auto inEdges = incomingEdges.find(dep);
            if (incomingEdges.end() != inEdges) {
               auto& edgeSet = inEdges->second;
               edgeSet.erase(cmd);
               if (edgeSet.empty()) {
                  noEdgeList.push_back(dep);
               }
            }
         }
      }      
   }

   for (auto edge : incomingEdges) {
      if (!edge.second.empty()) {
         cycleFound = true;
         break;
      }
   }
   return sortedList;
}