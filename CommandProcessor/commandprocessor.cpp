#include <thread>
#include <chrono>
#include "commandprocessor.h"

void ExecuteOneCommand(CommandProcessor& proc, Command& cmd)
{
   proc.UpdateCommandInProgress();
   cmd.Execute();
   proc.UpdateCommandExecutionStatus(cmd.getExecutionStatus());
}

bool CommandProcessor::ExecuteCommands(const CommandList& cList)
{
   using namespace std::chrono_literals;
   commandList = cList;

   // Logic: Commands are executed in parallel. Some commands might have dependency.
   // Hence below logic is used.
   // First level all the commands are executed without any dependencies.
   // In the next level all the commands with the ependent commands being completed are executed an so on.
   // This is done until all commands are executed.
   size_t curCommandCount = commandList.size();
   UpdateCommandPending(curCommandCount);
   while (curCommandCount) {
      for (auto& cmd : commandList) {
         // Check if all dependents are executed
         bool runcmd = true;
         if (cmd.second.getDependency().size()) {
            for (auto dep : cmd.second.getDependency()) {
               if (commandList[dep].getExecutionStatus() == ExecStatus::Unknown) {
                  // Dependent command not executed yet
                  runcmd = false;
                  break;
               }
            }
         }
         if (runcmd && (ExecStatus::Unknown == cmd.second.getExecutionStatus())) {
            std::thread cmdThread(ExecuteOneCommand, std::ref(*this), std::ref(cmd.second));
            cmdThread.detach();
            --curCommandCount;
         }
      }
      std::this_thread::sleep_for(100ms);
   }
   return true;
}