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

// ------------------------------------------------------------
// SERVER-SIDE PROCESSING FUNCTION
// Replace this example with your own processing logic.
// This example converts the received message to uppercase.
// ------------------------------------------------------------
string process(const string& data) {
    string result = data;

    for (size_t i = 0; i < result.length(); i++) {
        result[i] = static_cast<char>(toupper(static_cast<unsigned char>(result[i])));
    }

    return result;
}

int main() {
    // Create a UDP socket. SOCK_DGRAM means connectionless UDP.
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSocket < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serverAddr{};
    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    serverAddr.sin_family = AF_INET;          // IPv4.
    serverAddr.sin_port = htons(8081);        // UDP server port.
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Listen on all local interfaces.

    // Bind the UDP socket to port 8081.
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSocket);
        return 1;
    }

    cout << "UDP server waiting on port 8081..." << endl;

    // Receive one datagram and store the sender's address in clientAddr.
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

    // Process the received data on the server.
    string result = process(clientData);
    cout << "Processed data: " << result << endl;

    // Send the processed result back to the sender.
    ssize_t sent = sendto(serverSocket, result.data(), result.size(), 0,
                          (sockaddr*)&clientAddr, clientLen);
    if (sent < 0) {
        perror("sendto");
    }

    close(serverSocket); // Close the UDP socket.
    return 0;
}
