#ifndef COMMAND_H_
#define COMMAND_H_

#include <string>
#include <list>
#include <map>
#include <set>
#include <iostream>

enum class CommandStatus { Pending, InProgress, Completed};
enum class ExecStatus { Failed, Passed , Unknown};

class Command
{
   int number;
   std::string command;
   std::list<int> dependency;
   ExecStatus execStatus;
   CommandStatus cmdStatus;

public:
   Command()
      : number(0),
      cmdStatus(CommandStatus::Pending),
      execStatus(ExecStatus::Unknown)
   {

   }

   Command(int no, const std::string& cmd, const std::list<int>& dep)
      : number(no),
      command(cmd),
      dependency(dep),
      execStatus(ExecStatus::Unknown)
   {

   }

   // Getters
   int getNumber() const { return number; }
   std::string getCommand() const { return command;  }
   std::list<int> getDependency() const { return dependency;  }
   ExecStatus getExecutionStatus() const { return execStatus; }
   CommandStatus getStatus() const { return cmdStatus; }

   // setters
   void setNumber(int no) { number = no; }
   void setCommand(const std::string& cmd) { command = cmd; }
   void setDependency(std::list<int>& dep) { dependency = dep; }
   void setExecutionResult(ExecStatus status)  { execStatus = status; }
   void setStatus(CommandStatus status) { cmdStatus = status; }


   virtual ~Command() { };

   // Execute the command. Returns true on success, false otherwise
   ExecStatus Execute();
};

// List of incoming commands sorted based on the command number
typedef std::map<int, Command> CommandList;

// Representation of commands in a topologically sorted graph
class CommandGraph
{
   // Edges in the graph
   std::map <int,std::list <int> > edges;

   // all vertexes
   CommandList vertexes;

   // Vertexes with zero incoming edges
   std::set<int> noIncomingEdgeSet;

   // Reverse map of each node having incoming edge vertex set
   std::map <int, std::set <int> > incomingEdges;
   size_t vertexCount;

public:
   CommandGraph(size_t vc)
      : vertexCount(vc)
   {
   }

   /// Create the graph using a command list
   CommandGraph(const CommandList& cmdList)
      : vertexCount(cmdList.size())
   {
      for (auto cmd : cmdList) {
         int cmdNo = cmd.second.getNumber();
         noIncomingEdgeSet.insert(cmdNo);
         incomingEdges.insert(std::pair<int, std::set<int> >(cmdNo, std::set<int>()));
      }

      for (auto cmd : cmdList) {
         int cmdNo = cmd.second.getNumber();
         for (auto dependency : cmd.second.getDependency()) {
            addEdge(cmdNo, dependency);
            noIncomingEdgeSet.erase(dependency);
            incomingEdges[dependency].insert(cmdNo);
         }
         vertexes[cmdNo] = cmd.second;
      }
   }

   void addEdge(int from, int to)
   {
         edges[from].push_back(to);
   }

   void printGraph() const
   {      
      for (auto vertex: edges) {
         for (auto edge : vertex.second) {
            std::cout << vertex.first << "->" << edge << std::endl;
         }
      }
   }

   size_t getEdgeCount() const
   {
      return this->edges.size();
   }

   size_t getVertexCount() const
   {
      return this->vertexCount;
   }

   CommandList getVertexes() const
   {
      return this->vertexes;
   }

   std::list<int> topologicalSort();
};

#endif
