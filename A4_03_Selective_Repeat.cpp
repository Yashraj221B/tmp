// Assignment 4: Selective Repeat ARQ
#include <iostream>
using namespace std;

int main() {
    int n,w,lost,ack[101]={0};
    cout<<"Total frames (max 100): "; cin>>n;
    cout<<"Window size: "; cin>>w;
    cout<<"Frame to lose once (0 = none): "; cin>>lost;
    if(n<=0 || n>100 || w<=0 || w>n || lost<0 || lost>n) { cout<<"Invalid input.\n"; return 0; }

    bool loss=false;
    for(int start=1;start<=n;start+=w) {
        int end=start+w-1; if(end>n) end=n;
        cout<<"\nWindow "<<start<<" to "<<end<<"\n";
        for(int i=start;i<=end;i++) {
            cout<<"Sending Frame "<<i<<"... ";
            if(i==lost && !loss) { cout<<"Lost. No ACK.\n"; loss=true; }
            else { cout<<"ACK "<<i<<" received.\n"; ack[i]=1; }
        }
        // Retransmit only frames that did not receive an ACK.
        for(int i=start;i<=end;i++) if(!ack[i]) {
            cout<<"Retransmitting only Frame "<<i<<"... ACK received.\n";
            ack[i]=1;
        }
    }
    cout<<"All frames sent successfully.\n";
    return 0;
}
