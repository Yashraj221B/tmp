// Assignment 7: UDP Server (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // In Dev-C++ also add -lws2_32 in Linker options.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w); // Start Windows socket support.
    SOCKET s=socket(AF_INET,SOCK_DGRAM,0); // SOCK_DGRAM creates a UDP socket.

    sockaddr_in addr,client;
    int len=sizeof(client);
    char msg[100]={0};
    addr.sin_family=AF_INET;         // Use IPv4.
    addr.sin_port=htons(8081);       // UDP server uses port 8081.
    addr.sin_addr.s_addr=INADDR_ANY; // Listen on all local interfaces.

    bind(s,(sockaddr*)&addr,sizeof(addr)); // Attach the socket to port 8081.
    cout<<"UDP server waiting...\n";
    recvfrom(s,msg,99,0,(sockaddr*)&client,&len); // Receive a message and learn the client's address.
    cout<<"Client: "<<msg<<"\n";
    sendto(s,"Hello from UDP server",21,0,(sockaddr*)&client,len); // Send reply to that client address.

    closesocket(s); // Close the UDP socket.
    WSACleanup();   // Clean up Windows socket support.
    return 0;
}
