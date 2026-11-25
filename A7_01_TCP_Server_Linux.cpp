// Assignment 7: TCP Server (Linux)
// Receives a line from the client, processes it, and sends the result back.

#include <iostream>
#include <string>
#include <cctype>
#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

using namespace std;

// Example processing: convert the message to uppercase.
string process(const string& data) {
    string result = data;

    for (size_t i = 0; i < result.length(); i++) {
        result[i] = static_cast<char>(toupper(static_cast<unsigned char>(result[i])));
    }

    return result;
}

// Send the full string, including when send() writes only part of it.
bool sendAll(int sock, const string& data) {
    size_t totalSent = 0;

    while (totalSent < data.length()) {
        ssize_t sent = send(sock, data.c_str() + totalSent,
                            data.length() - totalSent, MSG_NOSIGNAL);
        if (sent <= 0) {
            return false;
        }
        totalSent += static_cast<size_t>(sent);
    }

    return true;
}

// Read one newline-terminated message.
bool receiveLine(int sock, string& data) {
    data.clear();
    char ch;

    while (true) {
        ssize_t received = recv(sock, &ch, 1, 0);

        if (received <= 0) return false;
        if (ch == '\n') break;

        data += ch;
    }

    return true;
}

int main() {
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("socket");
        return 1;
    }

    int reuse = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSocket);
        return 1;
    }

    if (listen(serverSocket, 5) < 0) {
        perror("listen");
        close(serverSocket);
        return 1;
    }

    cout << "TCP server waiting on port 8080..." << endl;

    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket < 0) {
        perror("accept");
        close(serverSocket);
        return 1;
    }

    string clientData;
    if (receiveLine(clientSocket, clientData)) {
        cout << "Client sent: " << clientData << endl;

        string result = process(clientData);
        cout << "Processed data: " << result << endl;

        if (!sendAll(clientSocket, result + "\n")) {
            perror("send");
        }
    } else {
        cout << "Could not receive a complete message from the client." << endl;
    }

    close(clientSocket);
    close(serverSocket);
    return 0;
}
