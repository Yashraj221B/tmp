// Assignment 7: UDP Client (Linux)
// Sends a datagram to the UDP server and displays its processed reply.

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

int main() {
    // Create a UDP socket.
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;                 // IPv4.
    serverAddr.sin_port = htons(8081);               // Server's UDP port.
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Same computer.

    // Read the data to send to the server.
    string message;
    cout << "Enter data to send to server: ";
    getline(cin, message);

    // Send the message as one UDP datagram. No connection is established.
    ssize_t sent = sendto(clientSocket, message.data(), message.size(), 0,
                          (sockaddr*)&serverAddr, sizeof(serverAddr));
    if (sent < 0) {
        perror("sendto");
        close(clientSocket);
        return 1;
    }

    // Receive the server's processed reply.
    char buffer[1024] = {0};
    socklen_t serverLen = sizeof(serverAddr);
    ssize_t received = recvfrom(clientSocket, buffer, sizeof(buffer), 0,
                                (sockaddr*)&serverAddr, &serverLen);
    if (received < 0) {
        perror("recvfrom");
        close(clientSocket);
        return 1;
    }

    cout << "Processed reply from server: ";
    cout.write(buffer, received);
    cout << endl;

    close(clientSocket); // Close the UDP socket.
    return 0;
}
