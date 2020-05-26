// CMakeProject2.cpp: 定义应用程序的入口点。
//
#include "string.h"
#include "stdio.h"
#include "malloc.h"
#include "ParseUrl.h"


char* strbetween(char* _string, char* begin, char* end)
{
	char* result = NULL;
	char* _begin = strstr(_string, begin);
	if (_begin != NULL)
	{
		 
		char* _end = strstr(_begin + strlen(begin), end);
		long long size = _end - _begin;
		if (_end != NULL && size >0)
		{
			result = (char*)calloc(1, size);
			memcpy(result, _begin + strlen(begin), size- +strlen(begin));
		}
	}
	return  result;
}
int main()
{
	char* url = "mqtt://127.0.0.1/taos/";
	char* username = strstr(url,"@")!=NULL? strbetween(url, "//", ":"):NULL;
	char* password = strstr(url, "@") != NULL ? strbetween(strstr( url, username), ":", "@"):NULL;
	char* host = strstr(url, "@") != NULL ? strbetween(url, "@", ":"): (strstr(strstr( url,"://")+3, ":") != NULL? strbetween(url, "//", ":"): strbetween(url, "//", "/"));
	char* port = strstr( strstr(url, host), ":")!=NULL? strbetween(strstr(url,host), ":", "/"):strbetween("'1883'","'","'");
	char* path =  strbetween(strstr(url,  strstr(strstr(url, host), ":") != NULL?port:host), "/", "/");
	printf("mqtt://%s:%s@%s:%s/%s/",username, password,host,port,path);
	free(username);
	free(password);
	free(host);
	free(port);
	free(path);
	return 0;
}

