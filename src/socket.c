#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
// create a client connection  by clientPort and host name or IP address
int Socket(const char *host, int clientPort)
{
    int sock;
    unsigned long inaddr;
    struct sockaddr_in ad;
    struct hostent *hp;

    memset(&ad, 0, sizeof(ad));
    ad.sin_family = AF_INET;

//    The inet_addr() routine converts a string representing an IPv4 Internet address
//    (for example, "127.0.0.1") into a numeric Internet address.
//    To convert a hostname such as ftp.qnx.com, call gethostbyname().
    inaddr = inet_addr(host);
    if (inaddr != INADDR_NONE)
    	// copy converted ip address to ad.sin_add
        memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
    else
    {
    	// get ip address acording to host name
        hp = gethostbyname(host);
        if (hp == NULL)
            return -1;
        memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
    }
//    将主机的无符号短整形数转换成网络字节顺序。//将无符号短整型主机字节序转换为网络字节序
    ad.sin_port = htons(clientPort);
//    Returns 0 on success, -1 for errors.
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
        return sock;
    if (connect(sock, (struct sockaddr *)&ad, sizeof(ad)) < 0)
        return -1;
    return sock;
}
