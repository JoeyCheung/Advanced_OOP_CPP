#include <iostream>
#include <fstream>
#include <string> 
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <memory>


using namespace std; 

//global variables
ifstream in_File;
ofstream outFile;

class ListNode
{
private:
    friend class linkedList; 
public:
    int coeff;
    int expon;
    string variable;
    char op;
    ListNode* next;
    //overload operator = uses l-values
    ListNode& operator=(const ListNode &rhs) = default;
    //regular constructor
    ListNode()
    {
        this->coeff = 0;
        this->expon = 0;
        this->variable = " ";
        this->op = ' ';
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

};

class linkedList
{
public:
    ListNode *front = new ListNode();

    //regular constructor
linkedList()
{
    front->next = nullptr;
}

//Deep copy constructor
linkedList(const linkedList &source)
{
    front = new ListNode; //allocate storage
    *front = *source.front;

    cout << "Copy constructor-Deep- data copy: " << front->next <<endl; 
}
/*
//Move Constructor
linkedList::linkedList(linkedList &&source):front{source.front}
{
    source.front = nullptr;
}
//Destructor
~linkedList()
{
    if(front != nullptr)
    {
        cout<<"Destructor freeing data for: " << front->str <<endl;
    }
    else
    {
        cout<<"Destructor freeing data for nullptr" <<endl;
    }

    delete front; 
}
*/

void calculate_Poly()
{
    ListNode *curr = this->front;
    ListNode *prev = this->front; 

	while (curr != nullptr)
    {
        prev = curr;
        curr = curr->next;//so it skips the dummy
        if (curr->next == nullptr)break; 
        if (curr->expon == curr->next->expon && curr->variable == curr->next->variable)
        {
            ListNode *temp;
            temp = curr->next;
            curr->coeff = curr->coeff + curr->next->coeff;
            prev->next = curr;
            curr->next = curr->next->next;
            delete temp;
        }
    }
    output();
}

//method for calculation

void output()
{   ListNode *curr;
    curr = this->front;
    while(curr->next != nullptr)
    {
        outFile <<curr->next->coeff << curr->next->variable << "^" <<
        curr->next->expon<<endl;
        curr = curr->next;
    }
}

void buildList(int coeff, char variable, char exponent, char op)
{
    ListNode *curr = this->front; 
    ListNode* newNode = new ListNode; 

    if (coeff == 0)
    {
        coeff = 1; 
    }
    if(op == '-')
    {
        coeff = -(coeff);
    }
    if(op == '+')
    {
        coeff = +(coeff);
    }

    newNode->coeff = coeff;
    newNode->variable = variable;
    newNode->expon = exponent;
    newNode->op = op; 

    if(curr->next == nullptr)
    {
        curr->next = newNode;
        newNode->next = nullptr; 
        return;
    }
    else
    {
        while(curr->next != nullptr)
        {
            if(newNode->expon >= curr->next->expon)
            {
                ListNode* temp;
                temp = curr->next;
                curr->next = newNode;
                newNode->next = temp; 
                break;
            }
            else if(curr->next == nullptr)
            {
                curr->next = newNode;
                newNode->next = nullptr; 
                break;
            }
            
            curr = curr->next;// pointing to the next one
        }
    }
    return;
}

void loadList(int n)
{
    char* arr = new char[n]; 
    char a;

    for(int i = 0; i < n; i++)
    {
        in_File >> a;
        arr[i] = a;  
    }

    separate_Polynomial(arr, n);
}

void separate_Polynomial(char* arr, int n)
{
    int counter {0};
    
    char op {' '};
    int coeff {0};
    char variable {' '};
    char exponent {' '};

    for(int i = 0; i < n; counter = i)
    {
         op = ' ';
         coeff = 0;
         variable = ' ';
         exponent = ' ';

        if(arr[i] == '+' || arr[i] == '-')
        {
            op = arr[i];
            counter++;
        }

        switch(arr[i])
        {
            case '+':
                for(counter; counter < n; counter++)
                {
                    switch(arr[counter])
                    {
                        case '^':
                            exponent = arr[counter + 1] - '0';
                            counter++;
                            break;
                        case 'x':
                            variable = arr[counter];
                            break; 
                        case '+':
                            goto add_node;
                            break;
                        case '-':
                            goto add_node;
                            break;
                        default:
                            if(isdigit(arr[counter]))
                            {   
                                int result = 0; 
                                for(counter; arr[counter] != '\0'; counter++)
                                {
                                    if(arr[counter] == '+' || arr[counter] == '-' || arr[counter] == 'x')break; 
                                    result +=  atoi(&arr[counter]);
                                }
                                if(arr[counter] == 'x' && arr[counter + 1] == '^')
                                {
                                    variable = arr[counter]; 
                                }
                                else if(arr[counter] == 'x' && arr[counter + 1] != '^')
                                {
                                    variable = arr[counter];
                                    exponent = 1; 
                                }
                                else if(arr[counter] != 'x')
                                {
                                    variable = 0;
                                    exponent = 0;
                                }

                                coeff = result;
                                if(arr[counter] == '+' || arr[counter] == '-')goto add_node;
                            }  
                            break;
                    }
                }
            case '-':
                for(counter; counter < n; counter++)
                {
                    switch(arr[counter])
                    {   
                        case '^':
                            exponent = arr[counter + 1] - '0';
                            counter++;
                            break;

                        case 'x':
                            variable = arr[counter];
                            break; 

                        case '+':
                            goto add_node;
                            break;
                        
                        case '-':
                            goto add_node;
                            break;

                        default:
                            if(isdigit(arr[counter]))
                            {
                                int result = 0; 

                                for(counter; arr[counter] != '\0'; counter++)
                                {
                                    if(arr[counter] == '+' || arr[counter] == '-' || arr[counter] == 'x')break;
                                    result += atoi(&arr[counter]); 
                                }
                                if(arr[counter] == 'x' && arr[counter + 1] == '^')
                                {
                                    variable = arr[counter]; 
                                }
                                else if(arr[counter] == 'x' && arr[counter + 1] != '^')
                                {
                                    variable = arr[counter];
                                    exponent = 1; 
                                }
                                else if(arr[counter] != 'x')
                                {
                                    variable = 0;
                                    exponent = 0;
                                }

                                coeff = result;
                                if(arr[counter] == '+' || arr[counter] == '-')goto add_node;
                            }
                            break; 
                    }
                }
            default:
                cout<<"Not the correct input: " << arr[counter] <<endl;
                break;
        }
        add_node:
        buildList(coeff, variable, exponent, op);
        i = counter; 
        cout << "counter: " << counter <<endl; 
    }
        //send list
        calculate_Poly();
    }
};

int main(int argc, char *argv[])
{
    linkedList obj;
    int n = 32;//length of poly
    in_File.open(argv[1]);
    outFile.open(argv[2]);

    if(in_File.is_open())
    {
        obj.loadList(n);
    }
    else
    {
        cerr<<"Could not open file" <<endl;
        return 1;
    }
    
    in_File.close(); 
    outFile.close();
}