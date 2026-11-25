// Assignment 7: UDP Client (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // In Dev-C++ also add -lws2_32 in Linker options.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w); // Start Windows socket support.
    SOCKET s=socket(AF_INET,SOCK_DGRAM,0); // Create a UDP socket (connectionless).

    sockaddr_in addr;
    addr.sin_family=AF_INET;                     // Use IPv4.
    addr.sin_port=htons(8081);                   // Send to the server's UDP port 8081.
    addr.sin_addr.s_addr=inet_addr("127.0.0.1"); // The server is running on this computer.

    sendto(s,"Hello from UDP client",21,0,(sockaddr*)&addr,sizeof(addr)); // Send without a connection.
    char msg[100]={0};
    int len=sizeof(addr);
    recvfrom(s,msg,99,0,(sockaddr*)&addr,&len); // Wait for the server's reply.
    cout<<"Server: "<<msg<<"\n";

    closesocket(s); // Close the UDP socket.
    WSACleanup();   // Clean up Windows socket support.
    return 0;
}
