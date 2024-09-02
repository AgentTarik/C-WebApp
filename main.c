// main.c
#include <stdio.h>
#include "server.h"
#include "routes.h"
#include "tools.h"



#pragma comment(lib, "ws2_32.lib") // Winsock Library




int main() {

    print_working_directory();

    SOCKET server, client;
    struct sockaddr_in server_addr, client_addr;
    int client_addr_size = sizeof(client_addr);

    // Initialize Winsock library
    initialize_winsock();

    // Create a socket for the server
    server = create_socket();

    // Prepare the sockaddr_in structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on any available network interface
    server_addr.sin_port = htons(8080); // Bind to port 8080

    // Bind the socket to the specified address and port
    bind_socket(server, &server_addr);

    // Start listening for incoming connections
    listen_for_connections(server);

    printf("Server listening on port 8080...\n");

    // Main loop to accept and handle client connections
    while (1) {
        client = accept_connection(server, &client_addr); // Accept an incoming connection
        if (client != INVALID_SOCKET) {
            handle_client(client); // Handle the client request
        }
    }

    // Clean up server resources
    cleanup(server);

    return 0;
}


