#ifndef COMMAND_PROCESSOR_H_
#define COMMAND_PROCESSOR_H_
#include <mutex>

#include "command.h"

struct CommandSummary
{
   size_t totalPendingCommands;
   size_t totalPassedCommands;
   size_t totalFailedCommands;
   size_t totalInProgressCommands;

   CommandSummary()
      : totalPendingCommands(0),
      totalPassedCommands(0),
      totalFailedCommands(0),
      totalInProgressCommands(0)
   {

   }
};

class CommandProcessor
{
   CommandSummary commandSummary;
   CommandList commandList;
   std::mutex commandMutex;


public:
   CommandProcessor()
   {

   }

   void UpdateCommandExecutionStatus(ExecStatus status)
   {
      std::lock_guard<std::mutex> cmdLock(this->commandMutex);
      if (ExecStatus::Failed == status) {
         ++commandSummary.totalFailedCommands;
      }
      else {
         ++commandSummary.totalPassedCommands;
      }
      --commandSummary.totalInProgressCommands;
   }

   void UpdateCommandInProgress()
   {
      std::lock_guard<std::mutex> cmdLock(this->commandMutex);
      ++commandSummary.totalInProgressCommands;
      --commandSummary.totalPendingCommands;
   }

   void UpdateCommandPending(size_t count)
   {
      std::lock_guard<std::mutex> cmdLock(this->commandMutex);
      commandSummary.totalPendingCommands += count;
   }

   virtual ~CommandProcessor() { }

   bool ExecuteCommands(const CommandList& cList);

   CommandSummary getCommandSummary() const
   {
      return commandSummary;
   }
};

#endif
