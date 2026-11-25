// Assignment 4: Go-Back-N ARQ
#include <iostream>
using namespace std;

int main() {
    int n,w,lost;
    cout<<"Total frames: "; cin>>n;
    cout<<"Window size: "; cin>>w;
    cout<<"Frame to lose once (0 = none): "; cin>>lost;
    if(n<=0 || w<=0 || w>n || lost<0 || lost>n) { cout<<"Invalid input.\n"; return 0; }

    bool loss=false; // Simulate losing the selected frame once.
    for(int start=1;start<=n;start+=w) { // Process frames in groups equal to the window size.
        int end=start+w-1; if(end>n) end=n; // The last window may contain fewer frames.
        cout<<"\nWindow "<<start<<" to "<<end<<"\n";
        int firstLost=0; // Stores the first frame lost in the current window.
        for(int i=start;i<=end;i++) {
            cout<<"Sending Frame "<<i<<"... ";
            if(i==lost && !loss) {
                cout<<"Lost.\n"; loss=true; firstLost=i;
            } else if(firstLost) {
                // Go-Back-N receiver discards later frames because an earlier frame is missing.
                cout<<"Discarded (out of order).\n";
            } else cout<<"ACK received.\n";
        }
        // Retransmit the lost frame and every later frame from this window.
        if(firstLost) for(int i=firstLost;i<=end;i++) cout<<"Retransmitting Frame "<<i<<"... ACK received.\n";
    }
    cout<<"All frames sent successfully.\n";
    return 0;
}
