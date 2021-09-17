#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define IP   "127.0.0.1"
#define PORT 8081

int main()
{
	int sockfd;
	int l_sockfd;
	int cli_len;
	char buff[128];
	struct sockaddr_in ser_addr;
	struct sockaddr_in cli_addr;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &ser_addr.sin_addr.s_addr);

	bind(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

	listen(sockfd, 5);

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
