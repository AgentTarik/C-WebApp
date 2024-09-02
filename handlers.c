// handlers.c
#include <stdio.h>
#include <string.h>
#include "handlers.h"

#define BUFFER_SIZE 4096

void handle_home(SOCKET client) {
    serve_file(client, "./static/index.html");
}

void handle_about(SOCKET client) {
    serve_file(client, "./static/about.html");
}

void handle_api_data(SOCKET client) {
    const char *response = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n{\"message\": \"Hello, World!\"}";
    send(client, response, strlen(response), 0);
}

void serve_file(SOCKET client, const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (file == NULL) {
        const char *not_found_response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><body><h1>404 Not Found</h1></body></html>";
        send(client, not_found_response, strlen(not_found_response), 0);
        return;
    }

    const char *header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    send(client, header, strlen(header), 0);

    char buffer[BUFFER_SIZE];
    int bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        send(client, buffer, bytes_read, 0);
    }

    fclose(file);
}
