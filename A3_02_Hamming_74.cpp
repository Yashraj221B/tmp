// Assignment 3: Hamming code (7,4), using even parity
#include <iostream>
#include <string>
using namespace std;

int main() {
    string d, c="0000000", r;
    cout<<"Enter 4 data bits: "; cin>>d;
    if(d.length()!=4) { cout<<"Enter exactly 4 bits.\n"; return 0; }
    for(int i=0;i<4;i++) if(d[i]!='0' && d[i]!='1') { cout<<"Use only 0 and 1.\n"; return 0; }

    // Data goes in positions 3, 5, 6, and 7; the other positions hold parity bits.
    c[2]=d[0]; c[4]=d[1]; c[5]=d[2]; c[6]=d[3];

    c[0]=char('0'+((c[2]-'0')^(c[4]-'0')^(c[6]-'0')));
    c[1]=char('0'+((c[2]-'0')^(c[5]-'0')^(c[6]-'0')));
    c[3]=char('0'+((c[4]-'0')^(c[5]-'0')^(c[6]-'0')));

    cout<<"Hamming code: "<<c<<"\nEnter received 7 bits: "; cin>>r;
    if(r.length()!=7) { cout<<"Enter exactly 7 bits.\n"; return 0; }
    for(int i=0;i<7;i++) if(r[i]!='0' && r[i]!='1') { cout<<"Use only 0 and 1.\n"; return 0; }

    int s1=(r[0]-'0')^(r[2]-'0')^(r[4]-'0')^(r[6]-'0');
    int s2=(r[1]-'0')^(r[2]-'0')^(r[5]-'0')^(r[6]-'0');
    int s4=(r[3]-'0')^(r[4]-'0')^(r[5]-'0')^(r[6]-'0');
    int pos=s1+2*s2+4*s4;

    if(pos==0) cout<<"No error detected.\n";
    else {
        r[pos-1]=(r[pos-1]=='0')?'1':'0';
        cout<<"Error at bit "<<pos<<" corrected.\n";
    }
    cout<<"Corrected code: "<<r<<"\n";
    cout<<"Recovered data: "<<r[2]<<r[4]<<r[5]<<r[6]<<"\n";
    return 0;
}
