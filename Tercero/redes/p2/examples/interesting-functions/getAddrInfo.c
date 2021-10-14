#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(void)
{
    struct addrinfo *result;
    struct addrinfo *res;
    int error;
    char ip[30];
    
    
    /* resolve the domain name into a list of addresses */
    error = getaddrinfo("google.es", NULL, NULL, &result);
    if (error != 0)
    {
        fprintf(stderr, "error in getaddrinfo: %s\n", gai_strerror(error));
        return -1;
    }
    
    
    /* loop over all returned results and do inverse lookup */
    for (res = result; res != NULL; res = res->ai_next)
    {
       inet_ntop(AF_INET, &res->ai_addr, ip, sizeof(ip));
            printf("hostname: %s\n", ip);
    }
    
    
    freeaddrinfo(result);
    return 0;
}
