#include "../include/server.h"


int server_run()
{
    int sockfd,err;
    char  hostname[128];
    struct  addrinfo *ailist,*aip;
    struct  addrinfo hint;
    struct sockaddr_in servaddr; //主机地址
    
    // 清零
    memset( &servaddr,0,sizeof(servaddr) );
    // 填充地址信息
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(SERVER_PORT);  
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);  
   
    if ((sockfd = initserver(SOCK_STREAM, (struct sockaddr *) &servaddr, 
        sizeof(servaddr), QLEN)) >= 0) {
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
int
initserver(int type, const struct sockaddr *addr, socklen_t alen,
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
int
set_cloexec(int fd)
{
	int		val;

	if ((val = fcntl(fd, F_GETFD, 0)) < 0)
		return(-1);

	val |= FD_CLOEXEC;		/* enable close-on-exec */

	return(fcntl(fd, F_SETFD, val));
}

void
serve(int sockfd)
{

	int		clfd;
	FILE	*fp;
	char	*buf;
    int sendbytes;
	set_cloexec(sockfd);
	for (;;) {
		if ((clfd = accept(sockfd, NULL, NULL)) < 0) {
			syslog(LOG_ERR, "accept error: %s",
			  strerror(errno));
			exit(1);
		}
		set_cloexec(clfd);

        buf = "hello,Mr.Lawrence";
        // 发送消息
		if((sendbytes = send(clfd, buf, 100, 0))<0){
            syslog(LOG_ERR, "send error: %s",
              strerror(errno));
            exit(1);
        }else{
            // printf("数据发送成功");
        }

		close(clfd);
	}
}



