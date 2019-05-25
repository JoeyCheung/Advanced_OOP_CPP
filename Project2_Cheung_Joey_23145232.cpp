#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std; 

//global variables
fstream inFile;
fstream outFile;

class ListNode
{
private:
    friend class linkedList; 
public:
    int coeff;
    int expon;
    ListNode* next;
    //regular constructor
    ListNode()
    {
        this->coeff = 0;
        this->expon = 0;
        this->next = nullptr;
    }

    //Deep copy constructor
    ListNode(const ListNode &source)
    {
        next = new ListNode();
        next = source.next;

        cout<<"Copy constructor- Deep - data copy: " << next <<endl;
    }

    //Move Constructor
    ListNode(ListNode &&source)
    {
        next = new ListNode();
        next = source.next; 
        source.next = nullptr;
    }
    
    ListNode &operator+(int &rhs){
        return *this + rhs;
    }

    ListNode &operator*(int &rhs){
        return *this * rhs; 
    }

    ListNode &operator-(int &rhs){
        return *this - rhs;
    }

    ListNode &operator>(ListNode &rhs)
    {
        if(this > &rhs)
        {
            return *this; 
        }
        else if(this < &rhs)
        {
             return rhs; 
        }
    }

    ListNode &operator<(ListNode &rhs)
    {
        if(this < &rhs)
        {
            return *this; 
        }
        else if(this > &rhs)
        {
            return rhs; 
        }
    }

    bool operator>=(ListNode &rhs)
    {
        return (*this >= rhs); 
    }

    bool operator<=(ListNode &rhs)
    {
        return (*this <= rhs);
    }
};

class linkedList
{
    public:
        ListNode *head;
        ListNode *tail; 

        linkedList()
        {
            head = nullptr;
            tail = nullptr;  
        }

        void addNode(int coeff, int expon)
        {
            ListNode *temp = new ListNode(); 
            temp->coeff = coeff;
            temp->expon = expon; 
            temp->next = nullptr;
            cout<<endl; 
            cout << temp->coeff <<endl;
            cout << temp->expon <<endl;
            if(head == nullptr) 
            {
                head = temp;
                tail = temp; 
            }
            else 
            {
                tail->next = temp;
                tail = tail->next; 
            }
        }

        void canonicalOrder()
        {

            cout<<"in canonicalOrder" <<endl; 
            ListNode *current = head;
            cout << current->coeff <<endl;


            while(current->next != nullptr)
            { 
                if(current->expon > current->next->expon)
                {
                    std::swap(current->coeff, current->next->coeff);  
                    std::swap(current->expon, current->next->expon); 
                }

                current = current->next;
            }

            ListNode *canonicalNode = head; 

            while(canonicalNode != nullptr)
            {
                outFile << canonicalNode->coeff << "x^" << canonicalNode->expon <<endl; 

                if(canonicalNode->next == nullptr)
                {
                    goto outofloop; 
                }  

                canonicalNode = canonicalNode->next;
            }

            outofloop:
            cout<<" " <<endl; 
        }  

        void substraction()
        {
            ListNode *temp = head;
            if(temp->expon == temp->next->expon)
            {
                outFile << "SUBTRACTION: " << temp->coeff - temp->next->coeff <<"x^"<< temp->expon << endl;
                outFile << temp->next->next->coeff - temp->next->next->next->coeff <<"x^"<<temp->next->next->expon<<endl;
            }
            else
            {
                outFile << "SUBTRACTION: " << temp->coeff <<"x^" <<temp->expon << " - "<<temp->next->coeff <<"x^" << temp->next->expon << endl;
               outFile << temp->next->next->coeff <<temp->next->next->expon << "-" << temp->next->next->next->coeff <<"x^"<< temp->next->next->next->expon <<endl;

            }
            
            
        }

        void multiplication()
        {
            ListNode *temp = head;

            outFile << "MULTIPLICATION: " << temp->coeff * temp->next->coeff <<"x^"<<temp->expon + temp->next->expon <<endl;
            
            outFile << temp->next->next->coeff * temp->next->next->next->coeff <<"x^"<<temp->next->next->expon + temp->next->next->next->expon <<endl;

        }

        void addition()
        {
            ListNode *temp = head;
            if(temp->expon == temp->next->expon)
            {
                outFile << "ADDITION: " << temp->coeff + temp->next->coeff << "x^" << temp->expon <<endl;
                outFile << temp->next->next->coeff + temp->next->next->next->coeff <<"x^"<<temp->next->next->expon<<endl;
            }
            else
            {
                outFile << "ADDITION: " << temp->coeff <<"x^" <<temp->expon << " + "<<temp->next->coeff <<"x^" << temp->next->expon << endl;
                outFile << temp->next->next->coeff <<temp->next->next->expon << "+" << temp->next->next->next->coeff <<"x^"<< temp->next->next->next->expon <<endl;

            }
            
        }
};

int main(int argc, char *argv[])
{
    linkedList obj;
    inFile.open(argv[1], ios::in);
    outFile.open(argv[2], ios::out);

    int coeff, expon; 
    string line; 

    if(inFile.is_open())
    {
        while (getline(inFile, line)) 
        {
            stringstream ss(line);
            while (ss >> coeff >> expon) 
            {
                cout << coeff << "," <<  expon << "   ";
                obj.addNode(coeff, expon); 
            }
            cout << endl;
        }
    }
    else
    {
        cerr<<"Could not open file" <<endl;
        return 1;
    }

    obj.canonicalOrder(); 
    obj.multiplication();
    obj.substraction();
    obj.addition();
    
    inFile.close(); 
    outFile.close();
}