
/**
*=========================================================
* tcp服务器
*
* @author ldy
* @date 2021/4/22
*
*=========================================================
*/ 
#include  "../include/main.h"

const int LISTEN_PORT = 7911; //监听端口
const int QLEN = 128;	//套接字接受的连接数
const char *LISTEN_ADDR = "0.0.0.0";  //监听地址
const char *LOG_DIR = "/vagrant/qserver/logs";//日志目录


int main(int argc, char const *argv[])
{
	FILE *fp = NULL;
	// 创建日志目录
	CreateLogDir();
	fp = OpenLogFile("test.logs");
	fputs("Hello,World\n",fp);
	return 0;
	// 解析参数
	// 运行服务器
	RunServer();
}

// 解析参数
void ParseArgs(int argc, char const *argv)
{
	
}
