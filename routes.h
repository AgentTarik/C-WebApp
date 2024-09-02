// routes.h
#ifndef ROUTES_H
#define ROUTES_H

#include <winsock2.h>

// Route structure
typedef struct {
    const char *method;     // HTTP method, e.g., "GET"
    const char *path;       // URL path, e.g., "/about"
    void (*handler)(SOCKET client); // Function pointer to the handler function
} Route;

// Function prototypes
void route_request(SOCKET client, const char *request);

void handle_client(SOCKET client);

#endif // ROUTES_H
