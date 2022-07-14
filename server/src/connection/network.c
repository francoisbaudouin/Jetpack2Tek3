/*
** EPITECH PROJECT, 2022
** Jetpack2Tek3
** File description:
** network
*/

#include "server.h"

int network(char *port)
{
    int socketfd = socket(AF_INET, SOCK_STREAM, 
        getprotobyname("tcp")->p_proto);
    struct sockaddr_in sock;

    sock.sin_family = AF_INET;
    sock.sin_port = htons(atoi(port));
    sock.sin_addr.s_addr = htonl(INADDR_ANY);
    if (socketfd == -1) {
        printf("socket connexion failed\n");
        close(socketfd);
        return (-1);
    }
    if (bind(socketfd, (struct sockaddr *) &sock, sizeof(sock)) != 0) {
        printf("Error bind");
        close(socketfd);
        return (-1);
    }
    listen(socketfd, MAX_CONNECTION);
    accept_connexion(socketfd, sock);
    close(socketfd);
    return (0);
}

int main(int ac, char **argv)
{
    if (ac != 2)
        return(84);
    network(argv[1]);
    return (0);
}