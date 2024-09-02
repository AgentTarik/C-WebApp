// server.h
#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>

// Function prototypes
void initialize_winsock();
SOCKET create_socket();
void bind_socket(SOCKET server, struct sockaddr_in *server_addr);
void listen_for_connections(SOCKET server);
SOCKET accept_connection(SOCKET server, struct sockaddr_in *client_addr);
void handle_client(SOCKET client);
void cleanup(SOCKET server);

#endif // SERVER_H
