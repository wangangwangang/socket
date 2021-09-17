#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

#define IP   "127.0.0.1"
#define PORT 8081

int main()
{
	int sockfd;
	struct sockaddr_in ser_addr;
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(PORT);
	inet_pton(AF_INET, IP, &ser_addr.sin_addr.s_addr);
	
	connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

	while(1) {
		sleep(3);
		write(sockfd, "hello", sizeof("hello"));
	}

	close(sockfd);
	
	return 0;
}
