// routes.c
#include <stdio.h>
#include <string.h>
#include "routes.h"
#include "handlers.h"

#define BUFFER_SIZE 4096

// Define the routing table
Route routes[] = {
    {"GET", "/", handle_home},
    {"GET", "/about", handle_about},
    {"GET", "/api/data", handle_api_data},
    {NULL, NULL, NULL}
};

void route_request(SOCKET client, const char *request) {
    char method[8], path[1024];
    sscanf(request, "%s %s", method, path); // Parse method and path from the request

    // Strip out any query string if present
    char *query_string = strchr(path, '?');
    if (query_string) {
        *query_string = '\0'; // Terminate path at the start of the query string
    }

    // Debugging output
    printf("Parsed Method: %s, Path: %s\n", method, path);

    // Match the path and method to routes
    for (int i = 0; routes[i].method != NULL; i++) {
        if (strcmp(routes[i].method, method) == 0 && strcmp(routes[i].path, path) == 0) {
            routes[i].handler(client); // Call the matched handler function
            return;
        }
    }

    // No matching route found, send a 404 response
    const char *not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
    send(client, not_found_response, strlen(not_found_response), 0);
}

// Function to handle client connections
void handle_client(SOCKET client) {
    char buffer[BUFFER_SIZE];
    int recv_size;

    // Receive the client's HTTP request
    recv_size = recv(client, buffer, sizeof(buffer), 0);
    if (recv_size == SOCKET_ERROR) {
        printf("Receive failed. Error Code: %d\n", WSAGetLastError());
    } else {
        buffer[recv_size] = '\0'; // Null-terminate the received data
        route_request(client, buffer); // Route the request to the appropriate handler
    }

    // Close the client socket after handling the request
    closesocket(client);
}
