#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h> // for close
#include <arpa/inet.h>

#include <netinet/in.h>

int main(void)
{

    int network_socket;
    int conn_status = 0;
    char srv_ans[256];
    struct sockaddr_in server_address;


    //creer un socket
    network_socket = socket(AF_INET,SOCK_STREAM,0);

    //Specifie l'adresse pour le socket

    server_address.sin_family = AF_INET; // Le type d'adresse
    server_address.sin_port = htons(9002); //htons convertis int -- to sin_port
    server_address.sin_addr.s_addr = inet_addr("192.168.1.38");



    

    conn_status = connect(network_socket,(struct sockaddr*) &server_address,sizeof(server_address));

    if(conn_status==-1)
        printf("Erreur de connexion\n");
    
    recv(network_socket,srv_ans,sizeof(srv_ans),0);
    printf("Server answer : %s\n",srv_ans);

    close(network_socket);


    return 0;
}