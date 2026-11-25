// Assignment 3: CRC (Cyclic Redundancy Check) using modulo-2 division
#include <iostream>
#include <string>
using namespace std;

// Return the modulo-2 division remainder.
string divideBits(string a, string g) {
  for (int i = 0; i <= (int)a.length() - (int)g.length(); i++)
    if (a[i] == '1')
      for (int j = 0; j < (int)g.length(); j++)
        a[i + j] = (a[i + j] == g[j])
                       ? '0'
                       : '1';
  return a.substr(a.length() - g.length() + 1);
}

int main() {
  string data, gen, code, rec;
  cout << "Enter data bits: ";
  cin >> data;
  cout << "Enter generator bits: ";
  cin >> gen;
  if (gen.length() < 2 || data.length() == 0) {
    cout << "Invalid input.\n";
    return 0;
  }
  for (int i = 0; i < (int)data.length(); i++)
    if (data[i] != '0' && data[i] != '1') {
      cout << "Use binary bits.\n";
      return 0;
    }
  for (int i = 0; i < (int)gen.length(); i++)
    if (gen[i] != '0' && gen[i] != '1') {
      cout << "Use binary bits.\n";
      return 0;
    }

  code = data + string(gen.length() - 1, '0');
  string rem = divideBits(code, gen);
  code = data + rem;
  cout << "CRC remainder: " << rem << "\nCodeword: " << code
       << "\nEnter received codeword: ";
  cin >> rec;
  if (rec.length() != code.length()) {
    cout << "Wrong codeword length.\n";
    return 0;
  }

  rem = divideBits(rec, gen);
  if (rem.find('1') == string::npos)
    cout << "No error detected.\n";
  else {
    cout << "Error detected. Checking for one-bit correction...\n";
    int found = -1, count = 0;
    // CRC is intended for error detection; this only attempts single-bit fixes.
    for (int i = 0; i < (int)rec.length(); i++) {
      string t = rec;
      t[i] = (t[i] == '0') ? '1' : '0';
      if (divideBits(t, gen).find('1') == string::npos)
        found = i, count++;
    }
    if (count == 1) {
      rec[found] = (rec[found] == '0') ? '1' : '0';
      cout << "Single-bit error corrected at position " << found + 1
           << ".\nCorrected code: " << rec << "\n";
    } else
      cout << "Cannot uniquely correct this error. CRC is mainly for "
              "detection.\n";
  }
  return 0;
}
