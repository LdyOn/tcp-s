#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <syslog.h>

#include "apue.h" //摘自《Unix环境高级编程 第3版》

#define QLEN 128   //listen函数接受的连接数
#define LISTEN_PORT 65911  //服务器监听端口
#define LISTEN_ADDR "0.0.0.0"  //服务器监听地址



/****************************函数声明**********************************/
int InitServer(int type, const struct sockaddr *addr, socklen_t alen,
  int qlen);
void serve(int sockfd);
void GetProcessNumber(int sockfd);
int RunServer();

