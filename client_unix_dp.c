#include <stdio.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define SOCK_FILE "/tmp/.tfs_cfg"

struct tfs_cfg_head {
	int   length;		//本数据包大小。包括本包头和全部数据
};

struct tfs_config {
	struct tfs_cfg_head   header;     //本数据包大小。包括本包头和全部数据
	char  body[0];
};


char str[128] = "{\"module\": \"tfs_physic_interfaces_config\", \"action\": \"showone\", \"name\": \"ens33\"}";

int main()
{
	int sockfd;
	int ret;
	char str2[4096];
	struct sockaddr_un ser_addr;

	sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	ser_addr.sun_family = AF_UNIX;
	strcpy(ser_addr.sun_path, SOCK_FILE);

	connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

	struct tfs_config *p = (struct tfs_config *)malloc(sizeof(struct tfs_config) + strlen(str) +1);
	p->header.length = htonl(sizeof(struct tfs_config) + strlen(str) +1);
	strncpy(p->body, str, strlen(str));
	p->body[strlen(str)] = '\0';

	ret = write(sockfd, (void *)p, p->header.length);

	struct tfs_config *p1 = (struct tfs_config *)malloc(sizeof(struct tfs_config));
	read(sockfd, (void *)p1, sizeof(struct tfs_config));
	read(sockfd, (void *)str2, sizeof(str2));

	printf("%s:%s\n",str, str2);
	
	close(sockfd);	

	return 0;
}
