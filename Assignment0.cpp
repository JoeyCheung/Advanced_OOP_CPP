#include <iostream>
using namespace std;

template<typename T>
int sum(T v) {
    return v;
}

template<typename T, typename... Types>
int sum(T v, Types&&... others) {
    return v + sum(others...);
}

int main() {
    
    cout << sum(1,2,3) << endl;
    cout << sum(10,20) << endl;
    cout << sum(1, 2, 3.4, 12) << endl;
        
    return 0;
}
