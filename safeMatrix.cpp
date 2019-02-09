#include<iostream>
#include<cstdlib> 
#include<cassert> 
using namespace std;

template<class T> class SA
{
private:
    int low, high;
    T* p;
public:
    // default constructor
    SA()
    {
        low = 0;
        high = -1;
        p = NULL;
    }
    // 2 parameter constructor lets us write 
    SA(int l, int h)
    {
        if ((h - l + 1) <= 0)
        {
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        p = new T[h - l + 1];
    }

    // single parameter constructor lets us
    // SA x(10); and getting an array x indexed from 0 to 9
    SA(int i)
    {
        low = 0;
        high = i - 1;
        p = new T[i];
    }

    // copy constructor for pass by value and 
    // initialization
    SA(const SA & s)
    {
        int size = s.high - s.low + 1;
        p = new T[size];

        for (int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
    }

    // destructor
    ~SA()
    {
        delete[] p;
    }

    //overloaded [] lets us write 
    //SA x(10,20); x[15]= 100;
    T& operator[](int i)
    {
        if (i < low || i > high)
        {
            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return p[i - low];
    }

    // overloaded assignment lets us assign one SA to another
    SA & operator=(const SA & s)
    {
        if (this == &s)
            return *this;
        delete[] p;
        int size = s.high - s.low + 1;
        p = new T[size];

        for (int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
        return *this;
    }
    // overloads << so we can directly print SAs 
    friend ostream& operator<<(ostream& os, SA s)
    {
        int size = s.high - s.low + 1;
        for (int i = 0; i < size; i++)
            cout << s.p[i] << endl;
        return os;
    };
    //end of ostream
};
//end class of safeArray 

//Matrix class
template<class T> class Matrix {

private:
        
    SA<SA<T>> matrx;
    
public:
    //2 param for 2D array
    Matrix(int r, int c) {
        matrx = SA<SA<T>>(0, r - 1);
        for (int i = 0; i < r; i++) {
            matrx[i] = SA<T>(0, c - 1);
        }
    }
    
    SA<T> operator[](int row) {
        return (matrx[row]);
    }
        
//     void multiplication() {
//         for(int i = 0; i < 3; i++) {
//             for (int j = 0; j < 3; j++) {
//                 ans[i][j] = 0;
//                 for(int k = 0; k < 3; k++)
//                     ans[i][j] += a[i][k] * b[k][j];
//                 cout << ans[i][j] << "\t";
//             }
//             cout << endl;
//         }
//     }
};

int main() {
    
    Matrix<int> A(2,2);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << A[i][j] << endl;
        }
    }

    return 0;
}
