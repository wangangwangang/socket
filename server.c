#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main()
{
	int sockfd;
	int l_sockfd;
	int cli_len;
	struct sockaddr_in ser_addr;
	struct sockaddr_in cli_addr;
	char ip[128] = "127.0.0.1";
	int port = 8081;
	char buff[128];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &ser_addr.sin_addr.s_addr);

	bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(struct sockaddr_in));

	listen(sockfd, 5);

	l_sockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &cli_len);
	
	memset(buff, 0, sizeof(buff));

	read(l_sockfd, buff, sizeof(buff));

	printf("buff:%s\n", buff);
}

