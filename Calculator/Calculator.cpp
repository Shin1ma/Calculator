

#include <iostream>
#include "CalculatorEng.h"


//Questo progetto è dedicato alla sgnra Barbara, Grazia frizzi pazzi e marinella perchè no


void InputHandler(int choice, CalculatorEng instance);       //handles input, creates new nodes ecc...
void CalculatorDisplay();       //a simple text display for the calculator
void UpdateDisplay();      //updates the display

//function taking and handling input
void InputAddNode();
void InputReplaceNode();
void InputDeleteNode();
void InputResolveVect();
void InputResetVect();

//object instance
CalculatorEng instance;

//temporary values to measure out border(* contorn) on the display
int temp1 = 1;
int temp2 = 1;


int size = 0;   //variable to compare to vector size



int main()
{
    

    
    UpdateDisplay();

    while (true) {
        
        CalculatorDisplay();

        int choice = 0;

        std::cout << "\nwelcome to calculator.cpp, please enter a choice:\n";
        std::cout << "1 new element\n2 replace element\n3 delete element\n4 resolve operation\n5 reset operation\n6 exit\n\n";
        std::cin >> choice;
        
        InputHandler(choice, instance);
    }
    return 0;
}


void CalculatorDisplay() {

    if (instance.VNodes.size() > 0) {
       while (size < instance.VNodes.size()) {
             while (temp1 >= 0) {                   //first line of * character based
                   std::cout << "*";
                   if (temp1 == 0) {
                       std::cout << "\n*";
                   }
                   temp1--;
             }
             std::cout << instance.VNodes[size].v_char << " ";           //numbers/operators prints
             size++;
             if (size == instance.VNodes.size()) {
                 std::cout << "*";
                 std::cout << "\n*";
                }
             }
       
       while (temp2 > 0) {          //second line of *
           std::cout << "*";
           if (temp2 == 0) {
               std::cout << "\n";
           }
           temp2--;
       }
      
    }
    
    
}


void UpdateDisplay() {  //resets values to clean up the display and update it
    system("cls");

    temp1 = 1;
    temp2 = 1;

    if (instance.VNodes.size() > 0) {
        for (auto& num : instance.VNodes) {
            temp1 += num.v_char.length() + 1;
            temp2 += num.v_char.length() + 1;
        }
    }
    size = 0;
}


void InputHandler(int choice, CalculatorEng instance) {
    UpdateDisplay();
    CalculatorDisplay();

    switch (choice) {
    case 1:

        InputAddNode();    //adds node
        break;

    case 2:
        
        InputReplaceNode(); //replaces a node
        break;

    case 3:
        
        InputDeleteNode();  //deletes a node
        break;

    case 4:
        
        InputResolveVect(); //resolves vector
        break;

    case 5:

        InputResetVect();   //resets vector
        break;

    case 6:
        exit(0);
        break;

    default:
        std::cout << "\n please enter a valid number\n";
        system("pause");
        break;
    }
    UpdateDisplay();
}


void InputAddNode() {
    int type = 0;       //input values used to create nodes
    int subtype = 0;
    int value = 0;

    std::cout << "\n\nchoose an option:\n";
    std::cout << "0  number\n1  operation\n";
    std::cin >> type; if (type != 0 && type != 1) { std::cout << "enter a valid number\n"; system("pause"); return;; }

    if (type == 0) {            //if node is a number it only needs a value
        std::cout << "please enter a value: ";
        std::cin >> value;
        subtype = NULL;
        instance.addNode(type, subtype, value);
        system("pause");
    }
    if (type == 1) {        //if node is an operation input subtype
        std::cout << "\n\nchoose an option:\n";
        std::cout << "0  addition\n1  subtraction                   4 open bracket\n2  moltiplication                5 close bracket\n3  division\n\n";
        std::cin >> subtype; if (subtype != 0 && subtype != 1 && subtype != 2 && subtype != 3 && subtype != 4 && subtype != 5) { std::cout << "enter a valid number\n"; system("pause"); return; }
        if (subtype == PRIORITYCLOSE || subtype == PRIORITYOPEN) type = PRIORITYOP;
        value = NULL;
        instance.addNode(type, subtype, value);
        system("pause");
    }
}


void InputReplaceNode() {
    int type = 0;       //input values used to create nodes
    int subtype = 0;
    int value = 0;
    int pos; 

    //basically the same as InputAddNodes(), only difference is that it takes a position to replace

    std::cout << "choose a position range: 0 - " << instance.VNodes.size() - 1 << "\n";
    std::cin >> pos; if (pos > instance.VNodes.size() - 1 || pos < 0) { std::cout << "enter a valid position\n"; system("pause"); return; }

    std::cout << "\n\nchoose an option:\n";
    std::cout << "0  number\n1  operation\n";
    std::cin >> type; if (type != 0 && type != 1) { std::cout << "enter a valid number\n"; system("pause"); return; }

    if (type == 0) {
        std::cout << "please enter a value: ";
        std::cin >> value;
        subtype = NULL;
        instance.replaceNode(pos, type, subtype, value);
    }
    if (type == 1) {
        std::cout << "\n\nchoose an option:\n";
        std::cout << "0  addition\n1  subtraction                   4 open bracket\n2  moltiplication                               5 close bracket\n3  division\n\n";
        std::cin >> subtype; if (subtype != 0 && subtype != 1 && subtype != 2 && subtype != 3 && subtype != 4 && subtype != 5) { std::cout << "enter a valid number\n"; system("pause"); return; }
        value = NULL;
        instance.replaceNode(pos, type, subtype, value);
    }
}


void InputDeleteNode() {        //takes a position for node deletion
    int pos;
    std::cout << "\n\nchoose a position range: 0 - " << instance.VNodes.size() - 1 << "\n";
    std::cin >> pos; if (pos > instance.VNodes.size() - 1 || pos < 0) { std::cout << "enter a valid position\n"; system("pause"); return;; }
    instance.deleteNode(pos);
}


void InputResolveVect() {                   //resolves vector and catches the error
    int result = instance.resolveVect(&instance.VNodes, false);
    if (result == 2147483647) {                     //sloppy way of handling errors
        std::cout << "\n\nsyntax/math error\n";
        system("pause");
    }
    std::cout << "\n\nthe result is: " << result << " enter anything to continue\n";
    system("pause");
}


void InputResetVect() {     //clears vect
    instance.resetVect();
    std::cout << "\n\nDone!\n";
    system("pause");
}