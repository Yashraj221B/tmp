// Assignment 4: Stop-and-Wait ARQ
#include <iostream>
using namespace std;

int main() {
    int n, lost;
    cout << "Total frames: ";
    cin >> n;
    cout << "Frame to lose once (0 = none): ";
    cin >> lost;

    if (n <= 0 || lost < 0 || lost > n) {
        cout << "Invalid input.\n";
        return 0;
    }

    // Drop the selected frame once.
    bool lossSimulated = false;
    for (int frame = 1; frame <= n; ++frame) {
        int attempt = 1;
        bool ack = false;

        // Retry until this frame is acknowledged.
        while (!ack) {
            cout << "Sending Frame " << frame << " (Attempt " << attempt << ")... ";
            if (frame == lost && !lossSimulated) {
                cout << "Lost. Timeout!\n";
                lossSimulated = true;
                ++attempt;
            } else {
                cout << "ACK " << frame << " received.\n";
                ack = true;
            }
        }
    }

    cout << "All frames sent successfully.\n";
    return 0;
}
