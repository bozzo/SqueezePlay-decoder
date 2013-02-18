#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 

#include "../src/decoder.h"
#include "../src/hashmap.h"

void print_hashmap(char * key, void * value)
{
	fprintf(stdout,"%s ---> %s\n",key,(char *) value);
}

int squeeze_connect(char * ip, int port)
{
	int sockfd = 0;
	struct sockaddr_in serv_addr;

	/*memset(RETOUR, '0',sizeof(RETOUR));
		memset(CMD, '0',sizeof(CMD));*/
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("\n Error : Could not create socket \n");
		return -1;
	}

	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0)
	{
		printf("\n inet_pton error occured\n");
		return -1;
	}

	if( connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		printf("\n Error : Connect Failed \n");
		return -1;
	}
	return sockfd;
}

int main(int argc, char *argv[])
{
	int sockfd = 0, n = 0, i=0;
	char RECEIVE[2048];
	char SEND[512];

	hashmap_t * map;


	if(argc != 4)
	{
		printf("\n Usage: %s <ip of server> <Target> <Command>\n",argv[0]);
		return 1;
	}

	/*strcat(SEND,CIBLE);
	strcat(SEND," ");
	strcat(SEND,CMD);
	strcat(SEND,"\n");*/
	sprintf(SEND,"%s %s\n",argv[2],argv[3]);

	map = (hashmap_t *)malloc(sizeof(hashmap_t));

	hashmap_init(map);

	if((sockfd = squeeze_connect(argv[1],9090)) < 0)
	{
		printf("\n Error : Couldn't connect to SqueezePlay.\n");
		return 1;
	}

	while (1)
	{
		n=send(sockfd,SEND, strlen(SEND),0);
		n=recv(sockfd,RECEIVE,sizeof RECEIVE -1,0);
		RECEIVE[n]='\0';
		/*printf("%s",str_replace(str_replace(str_replace(RECEIVE,"%3A",":")," ","\n"),"%20"," "));*/
		decode(RECEIVE, map);

		hashmap_iterate(map,print_hashmap);

		printf("Duree : %s\n",(char *)hashmap_get(map,"playlist_tracks"));
		sleep(2);
		printf("FOIS :%d\n",i++);
	}
	hashmap_delete_all(map);

	hashmap_free(map);
	free(map);

	shutdown(sockfd,2) ;
	close(sockfd);

	return 0;
}

