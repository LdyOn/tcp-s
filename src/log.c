#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include  <sys/stat.h>


extern char *LOG_DIR;
/*打开一个日志文件，返回文件指针；若文件不存在则创建*/
FILE *OpenLogFile(char *filename)
{
	FILE  *fp = NULL;
	printf("%s", LOG_DIR);
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
            if( access(str,0)!=0 )
            {
                mkdir( str, 0777 );
            }
            str[i]='/';
        }
    }
    if( len>0 && access(str,0)!=0 )
    {
        mkdir( str, 0777 );
    }
    return;

}





