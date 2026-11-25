// Assignment 7: TCP Client (Linux)
// Sends a line to the TCP server and displays the processed reply.

#include <iostream>
#include <string>
#include <cerrno>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

using namespace std;

// Sends the complete string, even if send() transmits only part of it.
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

// Reads one newline-terminated message from the TCP connection.
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
    // Create a TCP socket.
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("socket");
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;                 // IPv4.
    serverAddr.sin_port = htons(8080);               // Server's TCP port.
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Same computer.

    // Connect to the TCP server.
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("connect");
        close(clientSocket);
        return 1;
    }

    // Read the message to send to the server.
    string message;
    cout << "Enter data to send to server: ";
    getline(cin, message);

    // Newline marks the end of the message for this simple TCP example.
    if (!sendAll(clientSocket, message + "\n")) {
        perror("send");
        close(clientSocket);
        return 1;
    }

    // Receive and display the server's processed result.
    string reply;
    if (receiveLine(clientSocket, reply)) {
        cout << "Processed reply from server: " << reply << endl;
    } else {
        cout << "Could not receive a reply from the server." << endl;
    }

    close(clientSocket); // Close the TCP connection.
    return 0;
}
