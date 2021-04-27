#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include  <sys/stat.h>


extern char *LOG_DIR;
/*以追加写的方式打开一个日志文件，返回文件指针；若文件不存在则创建*/
FILE *OpenLogFile(char *filename)
{
	int len;
	char filepath[512]; 
	FILE  *fp = NULL;

	len = strlen(LOG_DIR);
    strncpy(filepath, LOG_DIR, 512);
    
    if(*(LOG_DIR+len -1) !='/'){
    	strcat(filepath, "/");
    }
    strcat(filepath, filename);
	
	// 在文件尾追加
	fp = fopen(filepath, "a+");

	return fp;
}

/*判断日志目录是否存在。如果不存在则创建*/
void CreateLogDir()
{
	int i,len;
    char str[512];    
    strncpy(str, LOG_DIR, 512);
    len = strlen(str);
    for( i=0; i<len; i++ )
    {
        if( str[i]=='/' )
        {
            str[i] = '\0';
            if( access(str, F_OK)!=0 )
            {
                mkdir( str, 0777 );
            }
            str[i]='/';
        }
    }
    if( len>0 && access(str, F_OK)!=0 )
    {
        mkdir( str, 0777 );
    }
    return;

}





