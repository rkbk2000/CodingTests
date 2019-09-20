#include <iostream>
#include <algorithm>

#include "mongoose.h"
#include "jsonreader.h"
#include "commandprocessor.h"

using namespace std;

bool TestCommandList()
{
   CommandList cmdList;
   Command cmd1(1, "ls", list<int>());
   return true;
}

void TestJSON()
{
   string myJson(
      "{\n"
      "    \"Version\": 1,\n"
      "    \"Commands\": [\n"
      "        {\n"
      "            \n"
      "            \"No\" : 1,\n"
      "            \"command\": \"ls\",\n"
      "            \"dependency\" : []\n"
      "        },\n"
      "        {\n"
      "            \"No\" : 2,\n"
      "            \"command\": \"sh\",\n"
      "            \"dependency\":  []\n"
      "        },\n"
      "        {\n"
      "            \"No\" :3,\n"
      "            \"command\": \"sleep\",\n"
      "            \"dependency\":  [ 1, 2 ]\n"
      "        },\n"
      "        {\n"
      "            \"No\" : 4,\n"
      "            \"command\": \"sh\",\n"
      "            \"dependency\":  [ 2,3, 5 ]\n"
      "        },\n"
      "        {\n"
      "            \"No\" : 5,\n"
      "            \"command\": \"sh\",\n"
      "            \"dependency\":  [ 1 ]\n"
      "        }\n"
      "    ]\n"
      "}"
   );

   JSONReader reader(myJson);
   CommandList cList = reader.GetCommandList();
   assert(5 == cList.size());

   CommandGraph cmdGraph(cList);
   cmdGraph.printGraph();
   std::list<int> sortedCommands = cmdGraph.topologicalSort();
   for_each(sortedCommands.begin(), sortedCommands.end(), [](int i)
   {
      std::cout << i << " ";
   });
   cout << endl;

   CommandProcessor cmp;
   cmp.ExecuteCommands(cList);
}

void WriteChunk(struct mg_connection* conn, const char* buf)
{
   mg_printf(conn, "%lx\r\n", strlen(buf));
   mg_write(conn, buf, strlen(buf));
   mg_write(conn, "\r\n", 2);
}

void WriteHTTPHeader(struct mg_connection* conn)
{
   mg_printf(conn, "%s", "HTTP/1.1 200 OK\r\nTransfer-Encoding: chunked\r\n\r\n");
}

void WriteLastChunk(struct mg_connection* conn)
{
   static char endBuf[] = "0\r\n\r\n";
   mg_write(conn, endBuf, sizeof endBuf - 1);

}
static int HTTPCallBack(struct mg_connection* conn)
{
   static CommandProcessor gCmdProcessor;
   int nReturn = 0;
   const struct mg_request_info* request_info = mg_get_request_info(conn);

   string strURI = request_info->uri;

   if (0 == _strcmpi(request_info->request_method, "GET")) {
      static char buf[1024];

      CommandSummary cSummary = gCmdProcessor.getCommandSummary();
      WriteHTTPHeader(conn);
      sprintf_s(buf, "Total commands executed: %llu, passed = %llu, failed=%llu\n",
         cSummary.totalFailedCommands + cSummary.totalPassedCommands, cSummary.totalPassedCommands,
         cSummary.totalFailedCommands);
      WriteChunk(conn, buf);

      sprintf_s(buf, "Total commands in progress: %llu, Pending = %llu\n",
         cSummary.totalInProgressCommands, cSummary.totalPendingCommands);
      WriteChunk(conn, buf);

      WriteLastChunk(conn);
      nReturn = 1;
   }
   else if (0 == _strcmpi(request_info->request_method, "POST")) {
      int nElem = 0;
      static char buf[1024];
      string jsonData;
      while ((nElem = mg_read(conn, buf, sizeof(buf))) > 0) {
         jsonData.append(buf, nElem);
      }

      bool inValidInput = false;
      JSONReader reader(jsonData);
      CommandList cList = reader.GetCommandList();
      inValidInput = cList.empty();

      if (!inValidInput) {

         CommandGraph cmdGraph(cList);

         std::list<int> sortedCommands = cmdGraph.topologicalSort();
         inValidInput = sortedCommands.empty();
         gCmdProcessor.ExecuteCommands(cList);
      }

      WriteHTTPHeader(conn);
      if (inValidInput) {
         static char buf[] = "Invalid input provided";
         WriteChunk(conn, buf);
         WriteLastChunk(conn);
      }
      else {
         static char buf[] = "Successfully executed commands";
         WriteChunk(conn, buf);
         WriteLastChunk(conn);
      }
      nReturn = 1;
   }

   // Returning non-zero tells mongoose that our function has replied to
      // the client, and mongoose should not send client any more data.
   return nReturn;
}


struct mg_context* StartWebServer()
{
   struct mg_context* ctx = NULL;

   int arrSize = (1 * 2) + 1; // 1 for NULL
   const char** options = (const char**)malloc(arrSize * sizeof(char*));
   options[0] = "listening_ports";
   options[1] = "2710";
   options[2] = 0;

   struct mg_callbacks callbacks;
   // Prepare callbacks structure. We have only one callback, the rest are NULL.
   memset(&callbacks, 0, sizeof(callbacks));
   callbacks.begin_request = HTTPCallBack;
   ctx = mg_start(&callbacks, NULL, options);
   free(options);

   cout << "Command orchestrator listening on port 2710. Try http://localhost:2710 to connect" << endl;
   return ctx;
}


// Command Orchestrator is a webserver listening on port 2710.
// It prints the command execution status for HTTP GET requests
// To execute commands provide them as JSON input through a POST request
int main(int argc, char** argv)
{
   struct mg_context* ct = StartWebServer();
   cout << "Enter a character to stop the command orchestrator" << endl;
   int c;
   cin >> c;
   mg_stop(ct);
   return 0;
}