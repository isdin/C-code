#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> // for close
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(void)
{
    char server_message[256] = " Server Reached !";
    int server_socket;
    int client_socket;
    //Creer le socket
    server_socket = socket(AF_INET,SOCK_STREAM,0);

    //L'adresse du serveur.

    struct sockaddr_in server_address;

    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(9002);
    //server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_addr.s_addr = inet_addr("192.168.1.38");
    //Bind le socket !

    bind(server_socket,(struct sockaddr *) &server_address,sizeof(server_address));

    listen(server_socket,5);

    client_socket = accept(server_socket,NULL,NULL);

    //Envoi le message
    send(client_socket,server_message,sizeof(server_message),0);

    close(server_socket);



    return 0;
}