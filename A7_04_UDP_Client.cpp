// Assignment 7: UDP Client (Windows / Dev-C++)
#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib") // Link with Winsock.
using namespace std;

int main() {
    WSADATA w;
    WSAStartup(MAKEWORD(2,2),&w);
    SOCKET s=socket(AF_INET,SOCK_DGRAM,0);

    sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8081);
    addr.sin_addr.s_addr=inet_addr("127.0.0.1");

    sendto(s,"Hello from UDP client",21,0,(sockaddr*)&addr,sizeof(addr));
    char msg[100]={0};
    int len=sizeof(addr);
    recvfrom(s,msg,99,0,(sockaddr*)&addr,&len);
    cout<<"Server: "<<msg<<"\n";

    closesocket(s);
    WSACleanup();
    return 0;
}
