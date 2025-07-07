#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fcntl.h>

#define BUF_SIZE 1024

char webpage[] = 
            "HTTP/1.1 200 OK\r\n"
            "Server: Linux Web Server\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n\r\n"
            "<!DOCTYPE html>\r\n"
            "<html><head><title> My Web Page </title>\r\n"
            "<style>body {background-color: #FFFF00 }</style></head>\r\n"
            "<body><center><h1>Hello world!!</h1><br>\r\n"
            "<img src=\"/game.jpg\"></center></body></html>\r\n";

void handle_request(int client_sock);
void send_image(int client_sock);

int main(int argc, char *argv[]) {
    int server_sock, client_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        perror("socket");
        exit(1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(atoi(argv[1]));

    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        close(server_sock);
        exit(1);
    }

    if (listen(server_sock, 5) < 0) {
        perror("listen");
        close(server_sock);
        exit(1);
    }

    printf("Server running on port %d...\n", atoi(argv[1]));

    while (1) {
        client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        handle_request(client_sock);
    }

    close(server_sock);
    return 0;
}

void handle_request(int client_sock) {
    char buffer[BUF_SIZE];
    int bytes_read;

    bytes_read = recv(client_sock, buffer, sizeof(buffer) - 1, 0);
    if (bytes_read < 0) {
        perror("recv");
        close(client_sock);
        return;
    }
    buffer[bytes_read] = '\0';

    printf("Request:\n%s\n", buffer);

    if (strncmp(buffer, "GET /game.jpg", 13) == 0) {
        send_image(client_sock);
    } 
    else if (strncmp(buffer, "GET ", 4) == 0) {
        send(client_sock, webpage, strlen(webpage), 0);
    } 
    else if (strncmp(buffer, "POST ", 5) == 0) {
        const char *response =
            "HTTP/1.1 200 OK\r\n"
            "Server: Linux Web Server\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n\r\n"
            "<!DOCTYPE html>\r\n"
            "<html><head><title> POST Response </title></head><body>\r\n"
            "<h1>POST request received</h1>\r\n"
            "</body></html>\r\n";
        
        send(client_sock, response, strlen(response), 0);
    } 
    else {
        const char *error_response = 
            "HTTP/1.1 400 Bad Request\r\n"
            "Server: Linux Web Server\r\n"
            "Content-Type: text/html; charset=UTF-8\r\n\r\n"
            "<!DOCTYPE html>\r\n"
            "<html><head><title> Bad Request </title></head><body>\r\n"
            "<h1>400 Bad Request</h1>\r\n"
            "</body></html>\r\n";
        
        send(client_sock, error_response, strlen(error_response), 0);
    }

    close(client_sock);
}

void send_image(int client_sock) {
    int image_file = open("game.jpg", O_RDONLY);
    if (image_file < 0) {
        perror("open");
        return;
    }

    const char *header =
        "HTTP/1.1 200 OK\r\n"
        "Server: Linux Web Server\r\n"
        "Content-Type: image/jpeg\r\n\r\n";
    send(client_sock, header, strlen(header), 0);

    char buffer[BUF_SIZE];
    int bytes_read;
    while ((bytes_read = read(image_file, buffer, sizeof(buffer))) > 0) {
        send(client_sock, buffer, bytes_read, 0);
    }

    close(image_file);
}
