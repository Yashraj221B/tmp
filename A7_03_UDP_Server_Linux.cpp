// Assignment 7: UDP Server (Linux)
// Receives a datagram, processes it, and sends the result to the client.

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

int main() {
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serverAddr{};
    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8081);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSocket);
        return 1;
    }

    cout << "UDP server waiting on port 8081..." << endl;

    char buffer[1024] = {0};
    ssize_t received = recvfrom(serverSocket, buffer, sizeof(buffer), 0,
                                (sockaddr*)&clientAddr, &clientLen);
    if (received < 0) {
        perror("recvfrom");
        close(serverSocket);
        return 1;
    }

    string clientData(buffer, static_cast<size_t>(received));
    cout << "Client sent: " << clientData << endl;

    string result = process(clientData);
    cout << "Processed data: " << result << endl;

    ssize_t sent = sendto(serverSocket, result.data(), result.size(), 0,
                          (sockaddr*)&clientAddr, clientLen);
    if (sent < 0) {
        perror("sendto");
    }

    close(serverSocket);
    return 0;
}
