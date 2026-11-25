// Assignment 5: VLSM calculator for the network 192.168.0.0/16
#include <algorithm>
#include <iostream>
using namespace std;

// Store the details needed for one subnet request.
struct Req {
  int batch, hosts, block, prefix;
};

// Display a 32-bit IP address as four decimal octets.
void printIP(unsigned long x) {
  cout << (x >> 24 & 255) << "." << (x >> 16 & 255) << "." << (x >> 8 & 255)
       << "." << (x & 255);
}

// Sorting function: larger subnet blocks must be allocated first in VLSM.
bool bigger(Req a, Req b) { return a.block > b.block; }

int main() {
  Req r[500];
  int n = 0, groups, batch = 0; // Keep a maximum of 500 subnet requests.
  while (true) {
    cout << "Number of groups (0 to finish): ";
    cin >> groups;
    if (groups == 0)
      break; // Enter 0 when all group requirements are provided.
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

    // Find the smallest power-of-two block that provides the requested usable
    // host IPs. Two addresses are reserved: network address and broadcast
    // address.
    int block = 1;
    while (block - 2 < hosts)
      block *= 2;
    int prefix = 32;
    for (int t = block; t > 1; t /= 2)
      prefix--; // Convert block size into /prefix notation.
    for (int i = 0; i < groups; i++)
      r[n++] = {batch, hosts, block, prefix};
  }
  if (n == 0) {
    cout << "No groups entered.\n";
    return 0;
  }

  sort(r, r + n, bigger); // VLSM rule: assign biggest subnet first to avoid
                          // wasting address space.
  unsigned long start = 3232235520UL, end = start + 65536, cur = start,
                used = 0; // 192.168.0.0/16 range.
  cout << "\nVLSM allocation for 192.168.0.0/16\n";
  for (int i = 0; i < n; i++) {
    unsigned long b = r[i].block;
    cur = ((cur + b - 1) / b) *
          b; // Move to the next valid block boundary (network address).
    if (cur + b > end) {
      cout << "Requested subnets do not fit in /16.\n";
      return 0;
    }
    cout << "Batch " << r[i].batch << " | Hosts " << r[i].hosts << " | ";
    printIP(cur);
    cout << "/" << r[i].prefix << " | Usable ";
    printIP(cur + 1);
    cout << " - ";
    printIP(cur + b - 2); // First and last usable host addresses.
    cout << " | Broadcast ";
    printIP(cur + b - 1);
    cout << "\n"; // Last address in the block.
    cur += b;
    used += b; // Move to the next free address block.
  }
  cout << "Total subnets: " << n << "\nAllocated addresses: " << used
       << "\nRemaining addresses: " << (65536 - used) << "\n";
  return 0;
}
