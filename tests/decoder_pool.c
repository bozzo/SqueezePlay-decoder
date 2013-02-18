/*
 * decoder_pool.c
 *
 *  Created on: 14 févr. 2013
 *      Author: ljrh4054
 */
#include "../src/decoder.h"
#include "../src/hashmap.h"

void print_hashmap(char * key, void * value)
{
	fprintf(stdout,"%s ---> %s\n",key,(char *) value);
}

void  write_iteree( int s, const char * tamponE , size_t aenvoyer )
{
	const char * p ;
	ssize_t    nb ;

	p=tamponE ;
	do
	{
		nb=write(s,p,aenvoyer);
		if ( nb == -1 )
		{
			fprintf(stderr,"probleme write : ") ;
			perror(" --> ") ;
			exit(1) ;
		}
		p += nb ;
		aenvoyer -= nb ;
	}
	while ( aenvoyer != 0 ) ;

}

int main(int argc, char **argv)
{
	hashmap_t * map;

	int                  sC,port;
	struct  sockaddr_in     serveur;
	struct  hostent      *phote;


	if (argc != 3) {
		fprintf(stderr, "Usage: %s ip port\n",argv[0]);
		exit(EXIT_FAILURE);
	}

	if (  (phote = gethostbyname(argv[1])) == NULL )
	{
		fprintf(stderr,"%s : %s --> HOTE INCONNU\n",argv[0],argv[1]);
		return(1) ;
	}

	sscanf(argv[2],"%d",port);

	memset(&serveur,0,sizeof(serveur)) ;
	memcpy(&serveur.sin_addr, phote->h_addr , phote->h_length) ;
	serveur.sin_family = phote->h_addrtype ;
	serveur.sin_port = htons(port) ;

	if ( (sC = socket(AF_INET,SOCK_STREAM,0)) < 0 )
	{
		perror("socket CL_TCP ");
		return(1);
	}

	if ( connect(sC,(struct sockaddr *)&serveur,sizeof(serveur)) < 0 )
	{
		fprintf(stderr,"%s : connect --> ",argv[0]) ;
		perror(" ") ;
		return(1) ;
	}

	map = (hashmap_t *)malloc(sizeof(hashmap_t));

	hashmap_init(map);

	/* Call server to get infos */


	decode(argv[1], map);

	hashmap_iterate(map,print_hashmap);

	hashmap_delete_all(map);

	hashmap_free(map);
	free(map);

	shutdown(sC,2) ;
	close(sC) ;

	exit(0);
}

