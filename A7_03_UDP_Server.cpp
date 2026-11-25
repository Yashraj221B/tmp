// Assignment 7: UDP Server (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Link with Winsock.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w);
    SOCKET s=socket(AF_INET,SOCK_DGRAM,0);

    sockaddr_in addr,client;
    int len=sizeof(client);
    char msg[100]={0};
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8081);
    addr.sin_addr.s_addr=INADDR_ANY;

    bind(s,(sockaddr*)&addr,sizeof(addr));
    cout<<"UDP server waiting...\n";
    recvfrom(s,msg,99,0,(sockaddr*)&client,&len);
    cout<<"Client: "<<msg<<"\n";
    sendto(s,"Hello from UDP server",21,0,(sockaddr*)&client,len);

    closesocket(s);
    WSACleanup();
    return 0;
}
