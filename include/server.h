#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <syslog.h>

#include "apue.h" //摘自《Unix环境高级编程 第3版》


/****************************函数声明********************************/
int  InitServer(int type, const struct sockaddr *addr, socklen_t alen,
  int qlen);
void serve(int sockfd);
void GetProcessNumber(int sockfd);
int  RunServer();

