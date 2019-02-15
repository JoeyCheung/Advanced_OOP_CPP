#include <iostream>
using namespace std;

int main() {

    int n;
    int count = 0;
    cout << "Please enter a number and we'll return the number of 1's from 1 - n" << endl;
    cin >> n;

    for (int i = 0; i <= n; i++) {
        int k = 0;
        int j = i;
        while (j > 0) {
            if (j % 10 == 1) {
                k += 1; 
            }
            j = j / 10;
        }
        count += k;
    }
    cout << count;
}
