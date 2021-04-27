#include "apue.h"


/*函数声明*/
void ParseArgs(int argc, char const *argv);
int RunServer();
void CreateLogDir();
FILE *OpenLogFile(char *filename);
