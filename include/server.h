#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <syslog.h>

#include "apue.h"

#define QLEN 128
#define SERVER_PORT 63769

int initserver(int type, const struct sockaddr *addr, socklen_t alen,
  int qlen);
void serve(int sockfd);

