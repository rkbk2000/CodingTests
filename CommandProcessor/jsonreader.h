#ifndef JSONREADER_H_
#define JSONREADER_H_

#include <string>
#include <list>
#include "rapidjson\document.h"
#include "command.h"

class JSONReader
{
   std::string json;
   Command command;
   bool commandStarted;
   bool dependencyStarted;
   template<typename T> size_t Traverse(const T& value);
   static constexpr const char VERSION[] = "Version";
   static constexpr const char NO[] = "No";
   static constexpr const char COMMAND[] = "Command";
   static constexpr const char DEPENDENCY[] = "Dependency";

public:
   JSONReader(const std::string& inData)
      : json(inData),
        commandStarted(false),
        dependencyStarted(false)
   {

   }

   // Getters
   std::string getJson() const { return json;  }
   //std::list<int> getDependency() const { return dependency;  }
   
   // setters
   void setJson(const std::string& dt) { json = dt; }

   JSONReader(JSONReader&& move) = delete;
   //JSONReader& operator=(JSONReader&& move)    noexcept;
   JSONReader& operator=(JSONReader&& move) = delete;
   JSONReader(JSONReader const&) = delete;
   JSONReader& operator=(JSONReader const&) = delete;

   virtual ~JSONReader() { };

   CommandList GetCommandList();
};

#endif
