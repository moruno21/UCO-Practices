#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>



int main(int argc, char **argv) {
        struct hostent *hp;
	char ip[20];
        char *host = "google.es";
        int i;

        hp = gethostbyname(host);
        if (hp == NULL) {
                fprintf(stderr, "Problema con la dirección del dominio: %s\n", host);
                return 0;
        }
        for (i=0; hp->h_addr_list[i] != 0; i++){
   		inet_ntop(AF_INET, &hp->h_addr_list[i], ip, sizeof(ip));
		printf("Direccion: %s\n",ip);

	}
        
	return 0;
}


