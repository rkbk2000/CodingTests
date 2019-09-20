#include "jsonreader.h"
#include "command.h"

using namespace std;
using namespace rapidjson;

#define strcmpi _strcmpi


/* {
    "Version": 1,
    "Commands": [
        {

            "No" : 1,
            "command": "ls",
            "dependency" : []
        },
        {
            "No" : 2,
            "command": "sh",
            "dependency":  []
        },
        {
            "No" :3,
            "command": "sleep",
            "dependency":  [ 1, 2 ]
        },
        {
            "No" : 4,
            "command": "sh",
            "dependency":  [ 2,3 ]
        },
        {
            "No" : 5,
            "command": "sh",
            "dependency":  [ 1 ]
        }
    ]
}
*/

template<typename T>
size_t JSONReader::Traverse(const T& value)
{
   size_t count = 1;

   switch (value.GetType()) {
   case kObjectType:
      for (typename T::ConstMemberIterator itr = value.MemberBegin(); itr != value.MemberEnd(); ++itr) {
         const char* cName = itr->name.GetString();
         if (0 == ::strcmpi(cName, VERSION)) {
            // Check if the version is 1
            int version = itr->value.GetInt();
            // TODO: Fail is version not 1
         }
         else if (0 == strcmpi(cName, NO)) {
            command.setNumber(itr->value.GetInt());
            commandStarted = true;
         }
         else if (0 == strcmpi(cName, COMMAND)) {
            command.setCommand(itr->value.GetString());
         }
         else if (0 == strcmpi(cName, this->DEPENDENCY)) {
            // Set dependency
            dependencyStarted = true;
            if (commandStarted) {
               // TODO: Add to the command list
            }
         }
         /*if (0 == strcasecmp(cName, CLASS_NAME)) { // imposes that ClassName should be present
            // Get the classname as filename without full path
            string tempName(itr->value.GetString());
            tempName = tempName.substr(tempName.find_last_of(PATHSEP) + 1);
            tempName = "JSON." + tempName;
            m_rset = new RecordSet(tempName);
            if (m_rset) {
               RecordField rf("STATTIME", "STRING");
               rf.Label("StatTime");
               rf.Unit("DateTime");
               m_rset->AddField(rf);
            }
         }
         else if (0 == strcasecmp(cName, METRIC_NAME)) {
            // Metric for the current class
            if (m_addField) {
               if (m_rset)
                  m_rset->AddField(m_rf);
               m_addField = false;
            }
            string metName = itr->value.GetString();
            m_rf.Name(metName);
         }
         else if (0 == strcasecmp(cName, METRIC_DATA_TYPE)) {
            // Metric data type for the current class
            string datatype = itr->value.GetString();
            m_rf.DataType(datatype);
            m_addField = true; // always unit and label not available
         }
         else if (0 == strcasecmp(cName, LABEL)) {
            string label = itr->value.GetString();
            m_rf.Label(label);

         }
         else if (0 == strcasecmp(cName, UNIT)) {
            string unit = itr->value.GetString();
            m_rf.Unit(unit);
         }
         else if ((0 == strcasecmp(cName, INSTANCES))) {
            if (m_addField) { // Final field to be added
               if (m_rset)
                  m_rset->AddField(m_rf);
               m_addField = false;
            }

         }
         else if ((0 == strcasecmp(cName, URI)) ||
            (0 == strcasecmp(cName, METRIC_META_DATA))) {
            // Do nothing

         }
         else if ((0 == strcasecmp(cName, INSTANCE_NO))) {
            m_instStarted = true;
            if (m_addInst && m_rset) {
               AddRSInstance();
            }
            m_addInst = false;
         }
         else {
            // add all Metric Values to inst
            if (m_instStarted) {
               string value = itr->value.GetString();
#if defined(HPPA)
               m_InstMap.insert(pair<const string, string>(cName, value));
#else
               m_InstMap.insert(pair<string, string>(cName, value));
#endif
               m_addInst = true;
            }
         }*/
         count = Traverse(itr->value);
      }

      break;

   case kArrayType:
      for (typename T::ConstValueIterator itr = value.Begin(); itr != value.End(); ++itr) {
         count = Traverse(*itr);
      }
      break;
   case kNumberType:
   default:
      // Do nothing.          
      break;
   }

   return count;
}


CommandList JSONReader::GetCommandList()
{
   CommandList cmdList;
   bool hasError = false;

   if (!json.empty()) {      
      rapidjson::Document commandDoc;
      commandDoc.Parse<0>((const char*)json.c_str());
      if (!commandDoc.HasParseError()) {
         const rapidjson::Value& commands = commandDoc["Commands"];

         hasError = !(commandDoc.IsObject()) && !(commands.IsArray());

         for (auto&& command = commands.Begin(); command != commands.End() && !hasError; ++command)
         {
            const rapidjson::Value& curCommand = *command;
            assert(curCommand.IsObject()); // each command is an object
            Command cmdObj;
            list<int> dependencies;
            
            for (auto&& cmdValues = curCommand.MemberBegin(); cmdValues != curCommand.MemberEnd(); ++cmdValues)
            {

               if (0 == strcmpi(this->NO, cmdValues->name.GetString())) {
                  cmdObj.setNumber(cmdValues->value.GetInt());
               }
               else if (0 == strcmpi(this->COMMAND, cmdValues->name.GetString())) {
                  cmdObj.setCommand(cmdValues->value.GetString());
               }
               else if (0 == strcmpi(this->DEPENDENCY, cmdValues->name.GetString())) {
                  // Read Array               
                  assert(cmdValues->value.IsArray());

                  for (auto dep = cmdValues->value.Begin(); dep != cmdValues->value.End(); ++dep) {
                     dependencies.push_back(dep->GetInt());
                     }
               }
            }

            for (auto dep : dependencies) {
               // Check for self dependencies
               if (cmdObj.getNumber() == dep) {
                  hasError = true;
                  break;
               }
            }

            if (!hasError) {
               cmdObj.setDependency(dependencies);
               cmdList.insert(std::pair<int, Command>(cmdObj.getNumber(), cmdObj));
            }
         }
      }
   }

   if (hasError) {
      return CommandList();
   }

   return cmdList;
}
