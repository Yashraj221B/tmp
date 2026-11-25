// Assignment 7: TCP Server (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Link with Winsock.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w);

    SOCKET s=socket(AF_INET,SOCK_STREAM,0), client;
    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8080);
    addr.sin_addr.s_addr=INADDR_ANY;

    bind(s,(sockaddr*)&addr,sizeof(addr));
    listen(s,1);
    cout<<"TCP server waiting...\n";
    client=accept(s,NULL,NULL);

    char msg[100]={0};
    recv(client,msg,99,0);
    cout<<"Client: "<<msg<<"\n";
    send(client,"Hello from TCP server",21,0);

    closesocket(client);
    closesocket(s);
    WSACleanup();
    return 0;
}
