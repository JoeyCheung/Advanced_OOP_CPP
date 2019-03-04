#include <iostream>
#include <climits>
#include <cstdlib>
#include <cassert>
using namespace std;

template <class T> class SA;

template <class T> //forward declaration
ostream& operator<<(ostream& os, SA<T> s);

template <class T> class SA {
private:
    int low, high;
    T* p;
public:
    // default constructor
    // allows for writing things like SA a;
    SA() {
        low = 0;
        high = -1;
        p = NULL;
    }
    // 2 parameter constructor lets us write
    // SA x(10,20);
    SA(int l, int h){
        if((h - l + 1) <= 0) {
            cout << "constructor error in bounds definition" << endl;
            exit(1);
        }
        low = l;
        high = h;
        p = new T[h - l + 1];
    }
    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9
    SA(int i) {
        low = 0;
        high = i-1;
        p = new T[i];
    }
    // copy constructor for pass by value and
    // initialization
    SA(const SA & s){
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
    }
    // destructor
    ~SA(){
        delete [] p;
    }
    //overloaded [] lets us write
    //SA x(10,20); x[15]= 100;
    T& operator[](int i){
        if(i < low || i > high){
            cout << "index " << i << " out of range" << endl;
            exit(1);
        }
        return p[i - low];
    }
    // overloaded assignment lets us assign
    // one SA to another
    SA & operator=(const SA & s){
        if(this == &s) return *this;
        delete [] p;
        int size = s.high - s.low + 1;
        p = new T[size];
        for(int i = 0; i < size; i++)
            p[i] = s.p[i];
        low = s.low;
        high = s.high;
        return *this;
    }
    // overloads << so we can directly print SAs
    friend ostream& operator<< <T>(ostream& os, SA<T> s);
};

template <class T>
ostream& operator<<(ostream& os, SA<T> s){
    int size = s.high-s.low+1;
    for(int i = 0; i < size; i++)
        cout << s.p[i] << endl;
    return os;
};

template<class T>
class VNT{
private:
    int row, col, rowL, colL;
    SA<SA<T>> vnt;
public:

    VNT(int x, int y){
        row = x;
        col = y;
        rowL = 0;
        colL = 0;
        vnt = SA<SA<T>>(row);
        for (int k = 0; k < row ; ++k) {
            vnt[k] = SA<T>(col);
        }//for k
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                vnt[i][j] = INT_MAX;
            }//for i
        }//for i
    }

    void add(int x) {
        if(rowL == row || colL == col){
            cout << "VNT is FULL...";
            return;
        }
        int temp = 0;
        int crow = rowL;
        int ccol = colL;
        vnt[crow][ccol] = x;
        int *current = &vnt[crow][ccol];
        int *top, *left;

        while(ccol >= 1 && crow >= 1) {
            top = &vnt[crow - 1][ccol];
            left = &vnt[crow][ccol - 1];
            if (*top > *current && *top > *left) {
                swap(*top, *current);
                crow = crow - 1;
                current = top;
            } else if (*left > *current && *left > *top) {
                swap(*left, *current);
                ccol = ccol - 1;
                current = left;
            } else if (*top < *current && *left == INT_MAX) {
                swap(*left, *current);
                ccol = ccol - 1;
                current = left;
            } else {
                break;
            }
        }//while

        if(crow >= 0){
            while(crow >= 1){
                top = &vnt[crow - 1][ccol];
                if(*top > x) {
                    swap(*top,*current);
                    crow -= 1;
                    current = top;
                }else{
                    break;
                }//else
            }//while
        }//if curr_row

        if(ccol > 0){
            while (ccol >= 1) {
                left = &vnt[crow][ccol - 1];
                if (*left > *current || *left == INT_MAX) {
                    swap(*left, *current);
                    ccol -= 1;
                    current = left;
                } else {
                    break;
                }//else
            }//while
        }//if curr_col
        
        if (colL + 1 == col) {
            colL = 0;
            rowL = rowL + 1;
        } else {
            colL = colL + 1;
        }
        
        return;
    }

    T getMin() {
        if (rowL == 0 && colL == 0) {
            cout << "VNT is Empty there is no min...";
            return 0;
        }
        
        if (rowL >= row) {
            rowL = row - 1;
            colL = col - 1;
        } else if (colL - 1 < 0) {
            rowL -= 1;
            colL = col - 1;
        } else {
            colL -= 1;
        }
        
        int min = vnt[0][0];
        vnt[0][0] = INT_MAX;
        swap(vnt[0][0], vnt[rowL][colL]);
        int crow = 0;
        int ccol = 0;
        int *current = &vnt[crow][ccol];
        int *right, *bottom;

        while (ccol <= col - 2 && crow <= row - 2) {
            right = &vnt[crow][ccol + 1];
            bottom = &vnt[crow + 1][ccol];

            if (*right < *current && *right < *bottom) {
                swap(*right, *current);
                current = right;
                ccol += 1;
            } else if (*bottom < *current && *bottom < *right) {
                swap(*bottom, *current);
                current = bottom;
                crow += 1;
            } else {
                break;
            }
        }
        if (ccol < col - 1) {
            while (ccol < col - 2) {
                right = &vnt[crow][ccol + 1];
                if (*right < *current) {
                    swap(*right, *current);
                    current = right;
                    ccol += 1;
                } else {
                    break;
                }
            }
        }
        return min;
    }

    void sort(int q[], int size){
        for (int i = 0; i < size; ++i) {
            this->add(q[i]);
        }
        return;
    }

//     bool find(int x) {
//         bool found = false;
//         if (rowL == 0 && colL == 0) {
//             cout<<"VNT is empty x not found...\n";
//             return found;
//         }//if
// 
//         int crow = 0, ccol = col - 1;
//         int *current = &vnt[crow][ccol];
//         int *left, *bottom;
//         while (crow < row - 1 && ccol > 0) {
//             left = &vnt[crow][ccol - 1];
//             bottom = &vnt[crow + 1][ccol];
//             if (*current == x) {
//                 found = true;
//                 cout << x <<" found at: (" << crow << "," << ccol << ")\n";
//                 return found;
//             }else if (x > *current) {
//                 crow += 1;
//                 current = bottom;
// 
//             } else if (x < *current) {
//                 ccol -= 1;
//                 current = left;
//             }
//         }//while
//         while (ccol > 0) {
//             left = &vnt[crow][ccol - 1];
//             if (x < *current) {
//                 current = left;
//                 ccol -= 1;
//             } else if (x == *current) {
//                 found = true;
//                 cout << x <<" found at: (" << crow << "," << ccol << ")\n";
//                 return found;
//             }
//         }//while
//         while (crow < row - 1) {
//             bottom = &vnt[crow + 1][ccol];
//             if (x > *current) {
//                 current = bottom;
//                 crow += 1;
//             } else if (x == *current) {
//                 found = true;
//                 cout << x <<" found at: (" << crow << "," << ccol << ")\n";
//                 return found;
//             }//else if
//         }//while
//         if (*current == x) {
//             found = true;
//             cout << x <<" found at: (" << crow << "," << ccol << ")\n";
//             return found;
//         }//if
//         if (!found) {
//             cout << x <<" is not in the matrix...\n";
//         }//if
//         return found;
//     }
    
    void printMatrix(){
        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; ++j) {
                if(vnt[i][j] == INT_MAX){
                    cout << " #" << " ";
                }else{
                    cout << vnt[i][j] << " ";
                }//else
            }//for j
            cout << "\n";
        }//for i
        cout << "\n";
    }//printMatrix
    
    SA<T>& operator[](int i) {
        if(i < row || i < col){
            return vnt[i];
        }else{
            cout<<"Index "<< i << " out of bounds";
            exit(1);
        }
    }
};

int main() {
    cout << "NOTE: # symbol represents INT_MAX.....\n\n";
    VNT<int> a(5,7);
    cout << "VNT A(empty): \n";
    a.printMatrix();

    int q[15] = {17,12,1,99,81,-2,100, 59,0, 66, 210 ,-55, -1, 3, 5};
    a.sort(q, (sizeof(q)/sizeof(*q)));

    cout << "VNT A after sort() of q[15]: \n";
    a.printMatrix();

    a.add(25);
    
    a.printMatrix();
    
    cout << "Calling find() on VNT A: \n";
//     a.find(-55);
    cout << "\n";
    
    cout << a.getMin() << endl;
    cout << a.getMin() << endl;

    return 0;
}
