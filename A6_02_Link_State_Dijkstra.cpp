// Assignment 6: Link State Routing using Dijkstra's shortest-path algorithm
#include <iostream>
using namespace std;

int main() {
    int n,c[10][10],d[10],used[10]={0},first[10],INF=999,src;
    cout<<"Number of routers (2-10): "; cin>>n;
    if(n<2 || n>10) return 0;
    cout<<"Enter cost matrix (0 = no direct link):\n";
    for(int i=0;i<n;i++) for(int j=0;j<n;j++) {
        cin>>c[i][j];
        if(i!=j && c[i][j]==0)c[i][j]=INF;
    }
    cout<<"Source router (0 for A, 1 for B, ...): "; cin>>src;
    if(src<0 || src>=n) return 0;

    for(int i=0;i<n;i++) d[i]=c[src][i],first[i]=(i==src?src:i);
    d[src]=0;

    for(int k=0;k<n;k++) {
        int u=-1;
        for(int i=0;i<n;i++) if(!used[i] && (u==-1 || d[i]<d[u])) u=i;
        if(u==-1 || d[u]==INF) break;
        used[u]=1;

        for(int v=0;v<n;v++) if(!used[v] && c[u][v]!=INF && d[u]+c[u][v]<d[v]) {
            d[v]=d[u]+c[u][v];
            first[v]=first[u];
        }
    }

    cout<<"\nShortest paths from Router "<<char('A'+src)<<":\n";
    for(int i=0;i<n;i++) {
        cout<<char('A'+i)<<": ";
        if(d[i]==INF) cout<<"No route\n";
        else cout<<"Cost = "<<d[i]<<", Next hop = "<<char('A'+first[i])<<"\n";
    }
    return 0;
}
