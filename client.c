#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
	int sockfd;
	struct sockaddr_in seraddr;
	char ip[128] = "127.0.0.1";
	int port = 8081;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(port);
	inet_pton(AF_INET, ip, &seraddr.sin_addr);
	
	connect(sockfd, (struct sockaddr *)&seraddr, sizeof(struct sockaddr_in));

	write(sockfd, "hello", sizeof("hello"));

	return 0;
}
