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

        if (received == 0) return false; // Client disconnected.
        if (received < 0) return false;  // Receive error.
        if (ch == '\n') break;           // End of this message.

        data += ch;
    }

    return true;
}

int main() {
    // Create a TCP socket. SOCK_STREAM means connection-oriented TCP.
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("socket");
        return 1;
    }

    // Allow the port to be reused immediately after restarting the server.
    int reuse = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse));

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;          // IPv4 address family.
    serverAddr.sin_port = htons(8080);        // TCP server port.
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Accept on all local interfaces.

    // Bind the socket to IP address and port.
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("bind");
        close(serverSocket);
        return 1;
    }

    // Start listening for incoming TCP connection requests.
    if (listen(serverSocket, 5) < 0) {
        perror("listen");
        close(serverSocket);
        return 1;
    }

    cout << "TCP server waiting on port 8080..." << endl;

    // Accept one client connection. This call waits until a client connects.
    int clientSocket = accept(serverSocket, NULL, NULL);
    if (clientSocket < 0) {
        perror("accept");
        close(serverSocket);
        return 1;
    }

    string clientData;
    if (receiveLine(clientSocket, clientData)) {
        cout << "Client sent: " << clientData << endl;

        // Process the received data on the server.
        string result = process(clientData);
        cout << "Processed data: " << result << endl;

        // Send the processed result back to the client.
        if (!sendAll(clientSocket, result + "\n")) {
            perror("send");
        }
    } else {
        cout << "Could not receive a complete message from the client." << endl;
    }

    close(clientSocket); // Close the connected client socket.
    close(serverSocket); // Close the listening socket.
    return 0;
}
