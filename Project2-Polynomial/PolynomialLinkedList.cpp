#include <iostream>
using namespace std;

class Polynomial {
private:
    int coefficient, power;
    Polynomial* next;
    
public:
    Polynomial() {
        coefficient = 0;
        power = 0;
        next = nullptr;
    }
    
    Polynomial(int c, int p) {
        coefficient = c;
        power = p;
    }
    
    Polynomial(int c, int p, Polynomial* n) {
        coefficient = c;
        power = p;
        next = n;
    }
    
    ~Polynomial() {
        delete next;
    }
    
    int getCoefficient() {
        return coefficient;
    }
    
    int getPower() {
        return power;
    }
    
    Polynomial* getNext() {
        return next;
    }
    
    void setCoefficient(int c) {
        coefficient = c;
    }
    
    void setPower(int p) {
        power = p;
    }
    
    void setNext(Polynomial* n) {
        next = n;
    }
    
    void addToRear(Polynomial* head, Polynomial* p) {
        if (head == nullptr) {
            head = p;
            return;
        }
        Polynomial* current = head;
        while (current->getNext() != nullptr) {
            current = current->getNext();
        }
            current->setNext(p);
    }
    
    Polynomial* insert(Polynomial* list, Polynomial* node) {
        if (list == nullptr) {
            list = new Polynomial(node->getCoefficient(), node->getPower());
            
        } 
        else {
            Polynomial* current = list;
            Polynomial* cursor = list;
            
            while(current != nullptr) {
                if (node->getPower() > current->getPower() && current == cursor) {
                    node->setNext(current);
                    list = node;
                }
                if (node->getPower() < cursor->getPower() && node->getPower() > current->getPower()) {
                    cursor->setNext(node);
                    node->setNext(current);
                }
                if (node->getPower() == current->getPower()) {
                    current->setCoefficient(node->getCoefficient() + current->getCoefficient());
                }
                cursor = current;
                current = current->getNext();
            }
            if (current == nullptr) {
                cursor->setNext(node);
            }
        }
        return list;
    }
    
    Polynomial &operator+(const Polynomial &other) {
        Polynomial* sum = this;
        while(other != nullptr) {
            if (sum->getPower() == other->getPower()) {
                sum.setCoefficient(sum.getCoefficient() + other.getCoefficient());
            }
            else {
                addToRear(sum, other);
            }
            other = other->getNext();
        }    
        return *sum;
    }
};
    
int main() {
    
    Polynomial* p = new Polynomial(5,7);
    Polynomial* c = new Polynomial(5,6);
    Polynomial sum = *p + *c;
    
    return 0;
}
