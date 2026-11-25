// Assignment 7: TCP Server (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h> // Windows socket functions.
#pragma comment(lib, "ws2_32.lib") // Visual C++ linker instruction; in Dev-C++ add -lws2_32 in Linker options.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w); // Start the Windows socket service before using sockets.

    SOCKET s=socket(AF_INET,SOCK_STREAM,0), client; // SOCK_STREAM creates a TCP socket.
    sockaddr_in addr;
    addr.sin_family=AF_INET;          // Use IPv4 addresses.
    addr.sin_port=htons(8080);        // Server listens on port 8080 (htons converts byte order).
    addr.sin_addr.s_addr=INADDR_ANY;  // Accept connections through any local network interface.

    bind(s,(sockaddr*)&addr,sizeof(addr)); // Attach the socket to this IP/port.
    listen(s,1);                           // Wait for a client connection; queue size is 1.
    cout<<"TCP server waiting...\n";
    client=accept(s,NULL,NULL);            // Accept a client; this waits until one connects.

    char msg[100]={0};
    recv(client,msg,99,0);                 // Receive the client's message.
    cout<<"Client: "<<msg<<"\n";
    send(client,"Hello from TCP server",21,0); // Send a reply through the connected TCP socket.

    closesocket(client); // Close the client connection.
    closesocket(s);      // Close the listening socket.
    WSACleanup();        // Stop the Windows socket service.
    return 0;
}
