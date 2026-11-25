// Assignment 4: Stop-and-Wait ARQ
#include <iostream>
using namespace std;

int main() {
    int n, lost;
    cout<<"Total frames: "; cin>>n;
    cout<<"Frame to lose once (0 = none): "; cin>>lost;
    if(n<=0 || lost<0 || lost>n) { cout<<"Invalid input.\n"; return 0; }

    bool loss=false; // This makes the selected frame get lost only one time.
    for(int i=1;i<=n;i++) {
        int attempt=1, ack=0; // attempt counts transmissions; ack becomes 1 after ACK arrives.
        while(!ack) { // The sender waits and repeats until it receives the acknowledgement.
            cout<<"Sending Frame "<<i<<" (Attempt "<<attempt<<")... ";
            if(i==lost && !loss) {
                cout<<"Lost. Timeout!\n"; // No ACK arrives, so the sender tries again.
                loss=true; attempt++;
            } else {
                cout<<"ACK "<<i<<" received.\n";
                ack=1; // Stop retransmitting this frame after its ACK is received.
            }
        }
    }
    cout<<"All frames sent successfully.\n";
    return 0;
}
