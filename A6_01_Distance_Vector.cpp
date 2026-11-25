// Assignment 6: Distance Vector Routing (Bellman-Ford style updates)
#include <iostream>
using namespace std;

int main() {
    int n,c[10][10],d[10][10],hop[10][10],INF=999;
    cout<<"Number of routers (2-10): "; cin>>n;
    if(n<2 || n>10) return 0;
    cout<<"Enter cost matrix (0 = no direct link):\n";
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) {
        cin>>c[i][j];
        if(i!=j && c[i][j]==0) c[i][j]=INF;
        d[i][j]=c[i][j];
        hop[i][j]=(i!=j && c[i][j]!=INF)?j:-1;
    }

    bool change=true;
    while(change) {
        change=false;
        for(int i=0;i<n;i++) for(int k=0;k<n;k++) for(int j=0;j<n;j++)
            if(d[i][k]!=INF && d[k][j]!=INF && d[i][k]+d[k][j]<d[i][j]) {
                d[i][j]=d[i][k]+d[k][j];
                hop[i][j]=hop[i][k];
                change=true;
            }
    }

    cout<<"\nFinal routing tables (cost, next hop):\n";
    for(int i=0;i<n;i++) {
        cout<<"Router "<<char('A'+i)<<"\n";
        for(int j=0;j<n;j++) {
            cout<<char('A'+j)<<": ";
            if(d[i][j]==INF) cout<<"No route\n";
            else cout<<d[i][j]<<", ";
            if(d[i][j]!=INF) cout<<char('A'+(hop[i][j]<0?i:hop[i][j]))<<"\n";
        }
    }
    return 0;
}
