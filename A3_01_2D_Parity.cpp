// Assignment 3: Two-dimensional parity (single-bit error correction)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string a[5], data;
    char p;
    cout << "Enter 16 data bits: "; cin >> data;

    if (data.length()!=16) { cout << "Enter exactly 16 bits.\n"; return 0; }
    for (int i=0;i<16;i++) if(data[i]!='0' && data[i]!='1') { cout<<"Use only 0 and 1.\n"; return 0; }

    cout << "Even or Odd parity (E/O): "; cin >> p;
    if(p!='E' && p!='e' && p!='O' && p!='o') { cout<<"Invalid choice.\n"; return 0; }
    int want = (p=='O' || p=='o') ? 1 : 0;

    // The last row and column hold parity bits.
    for(int i=0;i<5;i++) a[i]="00000";
    for(int i=0;i<16;i++) a[i/4][i%4]=data[i];

    for(int i=0;i<4;i++) {
        int n=0;
        for(int j=0;j<4;j++) if(a[i][j]=='1') n++;
        a[i][4]=char('0'+((n%2)^want));
    }

    for(int j=0;j<4;j++) {
        int n=0;
        for(int i=0;i<4;i++) if(a[i][j]=='1') n++;
        a[4][j]=char('0'+((n%2)^want));
    }

    int n=0;
    for(int i=0;i<4;i++) if(a[i][4]=='1') n++;
    a[4][4]=char('0'+((n%2)^want));

    cout << "Transmitted 5x5 codeword:\n";
    for(int i=0;i<5;i++) cout<<a[i]<<"\n";

    cout << "Enter received 5 rows (5 bits each):\n";
    for(int i=0;i<5;i++) {
        cin>>a[i];
        if(a[i].length()!=5) { cout<<"Each row must have 5 bits.\n"; return 0; }
        for(int j=0;j<5;j++) if(a[i][j]!='0' && a[i][j]!='1') { cout<<"Use only 0 and 1.\n"; return 0; }
    }

    int r=-1,c=-1,rc=0,cc=0;
    for(int i=0;i<5;i++) {
        n=0; for(int j=0;j<5;j++) if(a[i][j]=='1') n++;
        if(n%2!=want) r=i,rc++;
    }
    for(int j=0;j<5;j++) {
        n=0; for(int i=0;i<5;i++) if(a[i][j]=='1') n++;
        if(n%2!=want) c=j,cc++;
    }

    if(rc==0 && cc==0) cout<<"No error detected.\n";
    else if(rc==1 && cc==1) {
        // A single failed row and column identify the bit to flip.
        a[r][c]=(a[r][c]=='0')?'1':'0';
        cout<<"Single-bit error corrected at row "<<r+1<<", column "<<c+1<<".\n";
        cout<<"Corrected codeword:\n"; for(int i=0;i<5;i++) cout<<a[i]<<"\n";
        cout<<"Recovered data: ";
        for(int i=0;i<4;i++) cout<<a[i].substr(0,4);
        cout<<"\n";
    } else cout<<"Error detected, but it cannot be corrected uniquely.\n";
    return 0;
}
