#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class person {
public:  
    string name;
    double moneyPaid;
    double moneyOwed;
    person(string newName = "", double newMoneyP = 0.0, double newMoneyO = 0.0){
        this->name = newName;
        this->moneyPaid = newMoneyP;
        this->moneyOwed = newMoneyO;
    }
};

template<class T>
class node {
public:
    node<T> *prev;
    node<T> *next;
    person val;
    node(person val){
        this->prev=this->next=nullptr;
        this->val=val;
    }
};

template<class T>
class list{
public:
    node<T>* head;
    node<T>* tail;
    int size;
    list(){
        head = NULL;
        tail = NULL;
        size = 0;
    }
    list(node<T>* input){
        this->head=input;
        this->tail=input;
        this->size=1;
    }
    void addend(node<T>* end){
        if (size == 0){
            head = end;
            tail = end;
        } else {
            this->tail->next=end;
            end->prev=this->tail;
            this->tail=end;
        }
        this->size++;
    }

    void print(){
        if(this->size==0){cout<<"List is empty"<<endl;return;}

        node<T>* on=this->head;
        while(on!=nullptr){
            cout<<(on->val).moneyOwed<<" ";
            on=on->next;
        }
        cout<<endl;
    }

    bool isBalanced(){
        node<T>* on=this->head;
        while(on!=nullptr){
            if (on->val.moneyOwed >= 0.01 || on->val.moneyOwed <= -0.01){
                return false;
            }
            on=on->next;
        }
        return true;
    }
};


double readFile(ifstream& inFile, string fileName, list<person>* friendList);
void assignOwe(list<person>* friendList, double avg);
void balancePmt(list<person>* friendList);

int main(){
    string fileName;
    list<person>* friends = new list<person>();
    ifstream inFile;

    double avg = readFile(inFile, fileName, friends);
    assignOwe(friends, avg);
    balancePmt(friends);
    cout << "In the end, you should all have spent around $" << avg << endl;

    delete friends;
    return 0;
}


double readFile(ifstream& inFile, string fileName, list<person>* friendList){
    cout << "Enter the filename:";
    cin >> fileName;
    inFile.open(fileName);
    
    while (!inFile){
        cout << "Invalid file name. Please enter again:" << endl;
        cin >> fileName;
        inFile.clear();
        inFile.open(fileName);
    }

    double moneyP;
    string nameP;

    double moneyTotal = 0;

    while (inFile >> moneyP){
        moneyTotal += moneyP;
        inFile.ignore(9999, ' ');
        getline(inFile, nameP);
        person newP(nameP, moneyP, 0);

        node<person>* newFriend = new node<person> (newP);

        friendList->addend(newFriend);
    }

    double avg = moneyTotal / (friendList->size);    
    
    inFile.close();
    return avg;

}

void assignOwe(list<person>* friendList, double avg){
    node<person>* on = friendList->head;
    while (on != NULL){
        on->val.moneyOwed = avg - on->val.moneyPaid;
        if (on->val.moneyOwed == 0){
            cout << on->val.name << ", you don't need to do anything" << endl;
        }
        on = on -> next;
    }
}

void balancePmt(list<person>* friendList){
    double exchange;
    node<person>* frd1;
    node<person>* frd2;
    bool stop = false;

    while (!stop){
        frd1 = friendList->head;
        while (frd1->val.moneyOwed == 0) {
            frd1 = frd1->next;
        }
        
        if (frd1->val.moneyOwed < 0){
            frd2 = frd1->next;
            while (frd2->val.moneyOwed <= 0){
                frd2 = frd2->next;
            }
            exchange = min(-(frd1->val.moneyOwed), frd2->val.moneyOwed);
            frd1->val.moneyOwed += exchange;
            frd2->val.moneyOwed -= exchange;
            cout << frd2->val.name << ", you give " << frd1->val.name << " $" << exchange << endl;

        } else if (frd1->val.moneyOwed > 0) {
            frd2 = frd1->next;
            while (frd2->val.moneyOwed >= 0){
                frd2 = frd2->next;
            }
            exchange = min(frd1->val.moneyOwed, -(frd2->val.moneyOwed));
            frd1->val.moneyOwed -= exchange;
            frd2->val.moneyOwed += exchange;
            cout << frd1->val.name << ", you give " << frd2->val.name << " $" << exchange << endl;

        } 
        stop = friendList->isBalanced();
    }
    
}