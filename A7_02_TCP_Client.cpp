// Assignment 7: TCP Client (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Link with Winsock.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w);

    SOCKET s=socket(AF_INET,SOCK_STREAM,0);
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8080);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    connect(s,(sockaddr*)&addr,sizeof(addr));
    send(s,"Hello from TCP client",21,0);

    char msg[100]={0};
    recv(s,msg,99,0);
    cout<<"Server: "<<msg<<"\n";

    closesocket(s);
    WSACleanup();
    return 0;
}
