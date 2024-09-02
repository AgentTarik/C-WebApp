// server.c
#include <stdio.h>
#include <winsock2.h>
#include "server.h"

#pragma comment(lib, "ws2_32.lib") // Winsock Library

void initialize_winsock() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}

SOCKET create_socket() {
    SOCKET server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == INVALID_SOCKET) {
        printf("Could not create socket. Error Code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    return server_socket;
}

void bind_socket(SOCKET server, struct sockaddr_in *server_addr) {
    if (bind(server, (struct sockaddr *)server_addr, sizeof(*server_addr)) == SOCKET_ERROR) {
        printf("Bind failed. Error Code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}

void listen_for_connections(SOCKET server) {
    if (listen(server, 3) == SOCKET_ERROR) {
        printf("Listen failed. Error Code: %d\n", WSAGetLastError());
        exit(EXIT_FAILURE);
    }
}

SOCKET accept_connection(SOCKET server, struct sockaddr_in *client_addr) {
    int client_addr_size = sizeof(*client_addr);
    SOCKET client_socket = accept(server, (struct sockaddr *)client_addr, &client_addr_size);
    if (client_socket == INVALID_SOCKET) {
        printf("Accept failed. Error Code: %d\n", WSAGetLastError());
    }
    return client_socket;
}

void handle_client(SOCKET client) {
    char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nHello, World!";
    char buffer[1024];
    int recv_size;

    recv_size = recv(client, buffer, sizeof(buffer), 0);
    if (recv_size == SOCKET_ERROR) {
        printf("Receive failed. Error Code: %d\n", WSAGetLastError());
    } else {
        send(client, response, strlen(response), 0);
    }

    closesocket(client);
}

void cleanup(SOCKET server) {
    closesocket(server);
    WSACleanup();
}
