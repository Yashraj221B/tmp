// Assignment 7: TCP Client (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // In Dev-C++ also add -lws2_32 in Linker options.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w); // Start Windows socket support.

    SOCKET s=socket(AF_INET,SOCK_STREAM,0); // Create a TCP socket (reliable, connection-based).
    sockaddr_in addr;
    addr.sin_family=AF_INET;                       // Use IPv4.
    addr.sin_port=htons(8080);                     // Connect to the server's port 8080.
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");   // 127.0.0.1 means the same computer.

    connect(s,(sockaddr*)&addr,sizeof(addr)); // Request a connection to the TCP server.
    send(s,"Hello from TCP client",21,0);     // Send a message after connecting.

    char msg[100]={0};
    recv(s,msg,99,0);                           // Receive the server's reply.
    cout<<"Server: "<<msg<<"\n";

    closesocket(s); // Close the TCP connection.
    WSACleanup();   // Clean up Windows socket support.
    return 0;
}
