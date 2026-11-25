// Assignment 5: VLSM calculator for the network 192.168.0.0/16
#include <algorithm>
#include <iostream>
using namespace std;

struct Req {
  int batch, hosts, block, prefix;
};

void printIP(unsigned long x) {
  cout << (x >> 24 & 255) << "." << (x >> 16 & 255) << "." << (x >> 8 & 255)
       << "." << (x & 255);
}

bool bigger(Req a, Req b) { return a.block > b.block; }

int main() {
  Req r[500];
  int n = 0, groups, batch = 0;
  while (true) {
    cout << "Number of groups (0 to finish): ";
    cin >> groups;
    if (groups == 0)
      break;
    if (groups < 0 || n + groups > 500) {
      cout << "Invalid number of groups.\n";
      return 0;
    }
    batch++;
    int hosts;
    cout << "Usable IPs required by each group: ";
    cin >> hosts;
    if (hosts < 1) {
      cout << "Hosts must be positive.\n";
      return 0;
    }

    int block = 1;
    while (block - 2 < hosts)
      block *= 2;
    int prefix = 32;
    for (int t = block; t > 1; t /= 2)
      prefix--;
    for (int i = 0; i < groups; i++)
      r[n++] = {batch, hosts, block, prefix};
  }
  if (n == 0) {
    cout << "No groups entered.\n";
    return 0;
  }

  sort(r, r + n, bigger);
  unsigned long start = 3232235520UL, end = start + 65536, cur = start,
                used = 0;
  cout << "\nVLSM allocation for 192.168.0.0/16\n";
  for (int i = 0; i < n; i++) {
    unsigned long b = r[i].block;
    cur = ((cur + b - 1) / b) * b;
    if (cur + b > end) {
      cout << "Requested subnets do not fit in /16.\n";
      return 0;
    }
    cout << "Batch " << r[i].batch << " | Hosts " << r[i].hosts << " | ";
    printIP(cur);
    cout << "/" << r[i].prefix << " | Usable ";
    printIP(cur + 1);
    cout << " - ";
    printIP(cur + b - 2);
    cout << " | Broadcast ";
    printIP(cur + b - 1);
    cout << "\n";
    cur += b;
    used += b;
  }
  cout << "Total subnets: " << n << "\nAllocated addresses: " << used
       << "\nRemaining addresses: " << (65536 - used) << "\n";
  return 0;
}
