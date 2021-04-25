#include "../include/server.h"


extern const int LISTEN_PORT;
extern const int QLEN;
extern const char *LISTEN_ADDR;
extern const char *LOG_DIR;
/*
*运行服务器
*/
int RunServer()
{
    int sockfd;
    //主机地址
    struct sockaddr_in servaddr; 

    memset( &servaddr, 0, sizeof(servaddr) );
    // 选择协议
    servaddr.sin_family = AF_INET;  
    // 设置监听端口
    servaddr.sin_port = htons(LISTEN_PORT); 
    // 设置监听地址
    inet_pton(AF_INET, LISTEN_ADDR, &servaddr.sin_addr);  
   
    // 初始化一个套接字、绑定地址、设置监听端口
    if ((sockfd = InitServer(SOCK_STREAM, (struct sockaddr *) &servaddr, 
        sizeof(servaddr), QLEN)) >= 0) {
        /*如果成功返回一个监听套接字，则调用accept函数接受请求*/
        serve(sockfd);
        exit(0);
    }
    
	exit(1);

    return 0;
}

/**
 * 初始化一个监听套接字，成功返回一个可用的套接字
 *
 * @param int 套接字类型。取值SOCK_DGRAM,SOCK_RAM,SOCK_SEQPACKET,SOCK_STREAM
 * @param *scokaddr 地址
 * @param socklen_t  addr变量的长度
 * @param int 监听的队列长度
 *
 *
 * @author 代码摘自《Unix环境高级编程 第3版》
*/ 
int InitServer(int type, const struct sockaddr *addr, socklen_t alen,
  int qlen)
{
	int fd, err;
	int reuse = 1;

    // 初始化一个套接字
	if ((fd = socket(addr->sa_family, type, 0)) < 0)
		return(-1);
    // 设置套接字选项
	if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse,
	  sizeof(int)) < 0)
		goto errout;
    // 套接字绑定
	if (bind(fd, addr, alen) < 0)
		goto errout;
    // 如果套接字类型是SOCK_STREAM或者SOCK_SEQPACKET则调用监听函数
	if (type == SOCK_STREAM || type == SOCK_SEQPACKET)
		if (listen(fd, qlen) < 0)
			goto errout;
	return(fd);

errout:
	err = errno;
	close(fd);
	errno = err;
	return(-1);
}

// 对文件描述符设置执行时关闭
int SetCloexec(int fd){
	int		val;

	if ((val = fcntl(fd, F_GETFD, 0)) < 0)
		return(-1);

	val |= FD_CLOEXEC;		/* enable close-on-exec */

	return(fcntl(fd, F_SETFD, val));
}

void serve(int sockfd)
{

	int		clfd;
	char	*buf;
    int sendbytes;
	SetCloexec(sockfd);

	for (;;) {

		if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
			syslog(LOG_ERR, "accept error: %s",
			  strerror(errno));
			exit(1);
		}
		SetCloexec(clfd);

        buf = "hello,Mr.Lawrence.";
        // 发送消息
		if((sendbytes = send(clfd, buf, 17, 0))<0){
            syslog(LOG_ERR, "send error: %s",
              strerror(errno));
            exit(1);
        }else{
            printf("数据发送成功");
        }

		// close(clfd);
	}
}



