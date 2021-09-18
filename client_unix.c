#include <stdio.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define SOCK_FILE "/tmp/.tfs_cfg"

int main()
{
	int sockfd;
	struct sockaddr_un ser_addr;

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	ser_addr.sun_family = AF_UNIX;
	strcpy(ser_addr.sun_path, SOCK_FILE);

	connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

	write(sockfd, "hello", sizeof("hello"));
	
	close(sockfd);	

	return 0;
}
