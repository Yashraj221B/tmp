// Assignment 3: Two-dimensional parity (single-bit error correction)
#include <iostream>
#include <string>
using namespace std;

int main() {
    string a[5], data;              // 5 strings store the 5 rows of the 5x5 bit table.
    char p;
    cout << "Enter 16 data bits: "; cin >> data;

    // The original data must contain exactly 16 binary digits.
    if (data.length()!=16) { cout << "Enter exactly 16 bits.\n"; return 0; }
    for (int i=0;i<16;i++) if(data[i]!='0' && data[i]!='1') { cout<<"Use only 0 and 1.\n"; return 0; }

    cout << "Even or Odd parity (E/O): "; cin >> p;
    if(p!='E' && p!='e' && p!='O' && p!='o') { cout<<"Invalid choice.\n"; return 0; }
    int want = (p=='O' || p=='o') ? 1 : 0; // 0 means even parity; 1 means odd parity.

    // Fill the first 4x4 cells with the 16 input bits. The last row/column hold parity bits.
    for(int i=0;i<5;i++) a[i]="00000";
    for(int i=0;i<16;i++) a[i/4][i%4]=data[i];

    // Calculate one parity bit at the end of every data row.
    for(int i=0;i<4;i++) {
        int n=0;
        for(int j=0;j<4;j++) if(a[i][j]=='1') n++; // Count the 1s in this row.
        a[i][4]=char('0'+((n%2)^want));
    }

    // Calculate one parity bit at the bottom of every data column.
    for(int j=0;j<4;j++) {
        int n=0;
        for(int i=0;i<4;i++) if(a[i][j]=='1') n++; // Count the 1s in this column.
        a[4][j]=char('0'+((n%2)^want));
    }

    // The bottom-right bit checks the parity bits in the last row/column.
    int n=0;
    for(int i=0;i<4;i++) if(a[i][4]=='1') n++;
    a[4][4]=char('0'+((n%2)^want));

    cout << "Transmitted 5x5 codeword:\n";
    for(int i=0;i<5;i++) cout<<a[i]<<"\n";

    // Read the 5x5 codeword as it was received, because a bit may have changed in transmission.
    cout << "Enter received 5 rows (5 bits each):\n";
    for(int i=0;i<5;i++) {
        cin>>a[i];
        if(a[i].length()!=5) { cout<<"Each row must have 5 bits.\n"; return 0; }
        for(int j=0;j<5;j++) if(a[i][j]!='0' && a[i][j]!='1') { cout<<"Use only 0 and 1.\n"; return 0; }
    }

    // Find rows and columns whose parity does not match the selected even/odd rule.
    int r=-1,c=-1,rc=0,cc=0;
    for(int i=0;i<5;i++) {
        n=0; for(int j=0;j<5;j++) if(a[i][j]=='1') n++;
        if(n%2!=want) r=i,rc++; // Remember the row with incorrect parity.
    }
    for(int j=0;j<5;j++) {
        n=0; for(int i=0;i<5;i++) if(a[i][j]=='1') n++;
        if(n%2!=want) c=j,cc++; // Remember the column with incorrect parity.
    }

    if(rc==0 && cc==0) cout<<"No error detected.\n";
    else if(rc==1 && cc==1) {
        // The incorrect row and column meet at the changed bit. Flip that bit to correct it.
        a[r][c]=(a[r][c]=='0')?'1':'0';
        cout<<"Single-bit error corrected at row "<<r+1<<", column "<<c+1<<".\n";
        cout<<"Corrected codeword:\n"; for(int i=0;i<5;i++) cout<<a[i]<<"\n";
        cout<<"Recovered data: ";
        for(int i=0;i<4;i++) cout<<a[i].substr(0,4); // Print only the original 4x4 data bits.
        cout<<"\n";
    } else cout<<"Error detected, but it cannot be corrected uniquely.\n";
    return 0;
}
