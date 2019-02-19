#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
using namespace std;

class Polynomial {
public:
    map<int, int> polynomial;
    
public:

    //Checks to see if it was already indexed and if not then adds the coefficient to the value
    bool indexed(int coefficient, int power) {
        map<int, int>::iterator iterator = polynomial.find(power);
        if (iterator != polynomial.end()) {
            iterator>second += coefficient;
            return true;
        }
        return false;
    }

    // Checks if the variables have been mapped
    void mapVariables(int coefficient, int power) {
        if (!(indexed(coefficient, power))) {
            polynomial[power] = {coefficient};
        }
    }

    //
    Polynomial &operator+(const Polynomial &other) {
        Polynomial *temp = new Polynomial();
        for (auto i: this->polynomial) {
            temp->mapVariables(i.second, i.first);
        }
        for (auto k: other.polynomial) {
            temp->mapVariables(j.second, j.first);
        }
        return *temp;
    }

    Polynomial &operator-(const Polynomial &other) {
        Polynomial *temp = new Polynomial();
        for (auto i: this->polynomial) {
            temp->mapVariables(i.second, i.first);
        }
        for (auto j: other.polynomial) {
            temp->mapVariables((-1 * j.second), j.first);
        }
        return *temp;
    }

    Polynomial &operator*(const Polynomial &other) {
        Polynomial *temp = new Polynomial();
        for (auto i: this->polynomial) {
            for (auto j: other.polynomial) {
                temp->mapVariables((i.second * j.second), (i.first + j.first));
            }
        }
        return *temp;
    }
};

int main() {
    
    Polynomial polynomials[2], sum, difference, product;
    ifstream in("input.txt");
    string line;
    int count = 0, coefficient, power;
    while (getline(in, line)) {
        stringstream ss(line);
        while (ss >> coefficient >> power) {
            cout << coefficient << "," <<  power << "   ";
            polynomials[count].mapVariables(coefficient,power);
        }
        cout << "\n";
        count++;
    }
    in.close();
    
    ofstream myFile;
    myFile.open("output.txt");
    myFile << "First polynomial: \n\n";   
    
    map<int, int>::reverse_iterator rit;
    for (rit = polynomials[0].polynomial.rbegin(); rit != polynomials[0].polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == polynomials[0].polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    myFile << "\n\nSecond polynomial: \n\n";
    
    for (rit = polynomials[1].polynomial.rbegin(); rit != polynomials[1].polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == polynomials[1].polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    sum=polynomials[0]+polynomials[1];
    myFile << "\n\nSum: \n\n";
    
    for (rit = sum.polynomial.rbegin(); rit != sum.polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == sum.polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    myFile << "\n\nDifference: \n\n";
    difference=polynomials[0]-polynomials[1];

    for (rit = difference.polynomial.rbegin(); rit != difference.polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == difference.polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    myFile << "\n\nProduct: \n\n";
    product=polynomials[0]*polynomials[1];
    
    for (rit = product.polynomial.rbegin(); rit != product.polynomial.rend(); ++rit) {
        if (rit->second != 0) {
            if (rit == product.polynomial.rbegin()) {
                myFile << rit->second << "^" << rit->first;
            } else if (rit->second < 0) {
                myFile << " - " << (rit->second * -1) << "^" << rit->first;
            } else {
                myFile << " + " << rit->second << "^" << rit->first;
            }
        }
    }
    
    return 0;
}
