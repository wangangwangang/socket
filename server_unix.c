#include <stdio.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

#define SOCK_FILE "/tmp/socket"

int main()
{
	int sockfd;
	int l_sockfd;
	int cli_len;
	char buff[128];
	struct sockaddr_un ser_addr;
	struct sockaddr_un cli_addr;

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	ser_addr.sun_family = AF_UNIX;
	strcpy(ser_addr.sun_path, SOCK_FILE);
	unlink(SOCK_FILE);

	bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

	listen(sockfd, 2);

	l_sockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);

	while(1) {
		memset(buff, 0, sizeof(buff));

		read(l_sockfd, buff, sizeof(buff));

		printf("buff:%s\n", buff);
	}
	
	close(l_sockfd);
	close(sockfd);

	return 0;
}
