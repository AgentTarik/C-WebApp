// handlers.h
#ifndef HANDLERS_H
#define HANDLERS_H

#include <winsock2.h>

// Function prototypes for request handlers
void handle_home(SOCKET client);
void handle_about(SOCKET client);
void handle_api_data(SOCKET client);
void serve_file(SOCKET client, const char *file_path);

#endif // HANDLERS_H
