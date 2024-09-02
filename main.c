// main.c
#include <stdio.h>
#include "server.h"

#pragma comment(lib, "ws2_32.lib") // Winsock Library

int main() {
    SOCKET server, client;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size = sizeof(client_addr);

    initialize_winsock();
    server = create_socket();

    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    bind_socket(server, &server_addr);
    listen_for_connections(server);

    printf("Server listening on port 8080...\n");

    client = accept_connection(server, &client_addr);
    if (client != INVALID_SOCKET) {
        handle_client(client);
    }

    cleanup(server);

    return 0;
}
