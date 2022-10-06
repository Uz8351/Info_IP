
/*
------------------------
Possunt quia posse videntur.
------------------------
Hilario Iglesias Martínez.
-------------------------
Info_Ip.c
*********
En este sencillo programa de ejemplo,
se explica la utilización de varias
funciones, con la finalidad de
dada una dirección IP, con la notación de 
punto, y mediante las estructura hostent, 
y otras,extraer de ella el nombre, o los 
nombres que haya de la máquina.
En el desarrollo del mismo se ponen
las estructuras implicadas con el fin
de identificar valores y llamadas a 
datos.

Este programa fue realizado en una plataforma
LINUX Ubuntu 20.04.4 LTS.
Bajo el standard ANSI-C,
bajo una consola Linux.

Compilar:
$ gcc -Wall -Werror -o Info_Ip Info_Ip.c

Ejemplo de ejecución:

./Info_Ip  62.117.224.138 

*/

#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include <stdlib.h>
#include <arpa/inet.h>
int main(int argc,  const char *argv[])
{
	
	unsigned long Direcion;
	struct hostent *HosP;
	char **puntero;

/*
#include <netdb.h>
------------------
struct hostent {
	char  *h_name;            Nombre oficial del host
	char **h_aliases;         Nombres alternativos para el host
	int    h_addrtype;        Tipo:en la práctica, su valor siempre es AF_INET o AF_INET6
	int    h_length;          Esta es la longitud, en bytes, de cada dirección. 
	char **h_addr_list;       Vector de direcciones para el host.
	                          Generalmente, el host puede tener varias direcciones IP.
}

*/

/*Defiinimos entrada por argumento de main*/
	if (argc !=2)
	{
		printf("Debe ser ejecutado :%s Dirección IP: \n",argv[0]);
		exit(1);
	}

if ((Direcion=inet_addr (argv[1]))== -1)
{
	printf("La dirección IP debe estar en notación de punto"
		   "por ejemplo: 182.123.67.89\n");
	       exit(2);
}

/*
#include <arpa/inet.h>
----------------------
uint32_t htonl(uint32_t hostlong);
uint16_t htons(uint16_t hostshort);
uint32_t ntohl(uint32_t netlong);
uint16_t ntohs(uint16_t netshort);
in_addr_t      inet_addr(const char *cp);
in_addr_t      inet_lnaof(struct in_addr in);
struct in_addr inet_makeaddr(in_addr_t net, in_addr_t lna);
in_addr_t      inet_netof(struct in_addr in);
in_addr_t      inet_network(const char *cp);
char          *inet_ntoa(struct in_addr in);
inet_addr, inet_network, inet_makeaddr, inet_lnaof, inet_netof, inet_ntoa - Para manipulación 
de direcciones IP.

in_addr_t inet_addr(const char *cp);
La función inet_addr() convierte la cadena a la que apunta cp,
en la notación de puntos estándar de Internet,
en un valor entero adecuado para usar como dirección de Internet.

*/
 HosP=gethostbyaddr((char *)&Direcion, sizeof(Direcion),AF_INET);
if (HosP==NULL)
{
printf("No se encuentra información sobre esta dirección de  HOST %s \n",argv[1] );

exit(3);
}

for (puntero=HosP->h_addr_list;*puntero!=0;puntero++)
{
	//struct sockaddr_in *pinto;
//struct iphdr *puntero=malloc(sizeof(puntero->tos));

struct in_addr P_in;

	memcpy(&P_in.s_addr,*puntero,sizeof(P_in.s_addr));
	printf("%s\t%s\n",inet_ntoa(P_in),HosP->h_name );
	
}

/*
struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};

struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};

*/
	/*
#include <socket.h>
#include <netdb.h>
struct hostent *gethostbyaddr_r(const char *host_addr,
 int len
 int type,
 struct hostent *result,
 char *buffer, int buflen,
 int *h_errnop);
Description
The gethostbyaddr_r function is the same as gethostbyaddr except that it is reentrant.
No static storage location is used. 

*/

exit(0);

}