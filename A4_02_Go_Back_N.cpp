// Assignment 4: Go-Back-N ARQ
#include <iostream>
using namespace std;

int main() {
    int n,w,lost;
    cout<<"Total frames: "; cin>>n;
    cout<<"Window size: "; cin>>w;
    cout<<"Frame to lose once (0 = none): "; cin>>lost;
    if(n<=0 || w<=0 || w>n || lost<0 || lost>n) { cout<<"Invalid input.\n"; return 0; }

    bool loss=false;
    for(int start=1;start<=n;start+=w) {
        int end=start+w-1; if(end>n) end=n;
        cout<<"\nWindow "<<start<<" to "<<end<<"\n";
        int firstLost=0;
        for(int i=start;i<=end;i++) {
            cout<<"Sending Frame "<<i<<"... ";
            if(i==lost && !loss) {
                cout<<"Lost.\n"; loss=true; firstLost=i;
            } else if(firstLost) {
                // The receiver discards frames that arrive after a missing frame.
                cout<<"Discarded (out of order).\n";
            } else cout<<"ACK received.\n";
        }
        // Go-Back-N retransmits from the first lost frame to the end of the window.
        if(firstLost) for(int i=firstLost;i<=end;i++) cout<<"Retransmitting Frame "<<i<<"... ACK received.\n";
    }
    cout<<"All frames sent successfully.\n";
    return 0;
}
