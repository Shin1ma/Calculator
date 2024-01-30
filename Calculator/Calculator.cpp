

#include <iostream>
#include "CalculatorEng.h"

void InputHandler(int choice, CalculatorEng ogg);       //handles input, creates new nodes ecc...
void CalculatorDisplay();       //""graphic"" interface
void Update();      //updates the display

CalculatorEng ogg;
int temp1 = 1;
int temp2 = 1;

int size = 0;



int main()
{
    

    
    Update();

    while (true) {
        
        CalculatorDisplay();

        int choice = 0;

        std::cout << "\nwelcome to calculator.cpp, please enter a choice:\n";
        std::cout << "1 new element\n2 replace element\n3 delete element\n4 resolve operation\n5 reset operation\n6 exit\n7 DEBUG MOLT\n\n";
        std::cin >> choice;
        
        InputHandler(choice, ogg);
    }
    return 0;
}

void CalculatorDisplay() {

    if (ogg.VNodes.size() > 0) {
       while (size < ogg.VNodes.size()) {
             while (temp1 >= 0) {                   //first line of * character based
                   std::cout << "*";
                   if (temp1 == 0) {
                       std::cout << "\n*";
                   }
                   temp1--;
             }
             std::cout << ogg.VNodes[size].v_char << " ";           //numbers/operators prints
             size++;
             if (size == ogg.VNodes.size()) {
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

void Update() {
    system("cls");

    temp1 = 1;
    temp2 = 1;

    if (ogg.VNodes.size() > 0) {
        for (auto& num : ogg.VNodes) {
            temp1 += num.v_char.length() + 1;
            temp2 += num.v_char.length() + 1;
        }
    }
    size = 0;
}

void InputHandler(int choice, CalculatorEng ogg) {
    Update();
    CalculatorDisplay();


    int type = 0;
    int subtype = 0;
    int value = 0;
    int result = 0;
    std::string inp;

    switch (choice) {
    case 1:
        std::cout << "\n\nchoose an option:\n";
        std::cout << "0  number\n1  operation\n";
        std::cin >> type; if (type != 0 && type != 1) { std::cout << "enter a valid number\n"; system("pause"); break; }
        if (type == 0) {
            std::cout << "please enter a value: ";
            std::cin >> value;
            subtype = NULL;
            ogg.addNode(type, subtype, value);
            system("pause");
        }
        if (type == 1) {
            std::cout << "\n\nchoose an option:\n";
            std::cout << "0  addition\n1  subtraction\n2  moltiplication\n3  division\n";
            std::cin >> subtype; if (subtype != 0 && subtype != 1 && subtype != 2 && subtype != 3) { std::cout << "enter a valid number\n"; system("pause"); break; }
            value = NULL;
            ogg.addNode(type, subtype, value);
            system("pause");
        }

        break;

    case 2:
        int posr;
        std::cout << "choose a position range: 0 - " << ogg.VNodes.size() - 1 << "\n";
        std::cin >> posr; if(posr > ogg.VNodes.size() - 1 || posr < 0){ std::cout << "enter a valid position\n"; system("pause"); break; }

        std::cout << "\n\nchoose an option:\n";
        std::cout << "0  number\n1  operation\n";
        std::cin >> type; if (type != 0 && type != 1) { std::cout << "enter a valid number\n"; system("pause"); break; }
        if (type == 0) {
            std::cout << "please enter a value: ";
            std::cin >> value;
            subtype = NULL;
            ogg.replaceNode(posr, type, subtype, value);
        }
        if (type == 1) {
            std::cout << "\n\nchoose an option:\n";
            std::cout << "0  addition\n1  subtraction\n2  moltiplication\n3  division\n";
            std::cin >> subtype; if (subtype != 0 && subtype != 1 && subtype != 2 && subtype != 3) { std::cout << "enter a valid number\n"; system("pause"); break; }
            value = NULL;
            ogg.replaceNode(posr, type, subtype, value);
        }
        break;

    case 3:
        int pos;
        std::cout << "\n\nchoose a position range: 0 - " << ogg.VNodes.size() - 1 << "\n";
        std::cin >> pos; if (pos > ogg.VNodes.size() - 1 || pos < 0) { std::cout << "enter a valid position\n"; system("pause"); break; }
        ogg.deleteNode(pos);
        break;

    case 4:
        result = ogg.resolveVect();
        if (result == 2147483647) {
            std::cout << "\n\nsyntax/math error\n";
            system("pause");
            break;
        }
        std::cout << "\n\nthe result is: " << result << " enter anything to continue\n";
        system("pause");
        break;

    case 5:
        ogg.resetVect();
        std::cout << "\n\nDone!\n";
        system("pause");
        break;

    case 6:
        exit(0);
        break;

    case 7:
        ogg.resolveVectMolt();
        break;

    default:
        std::cout << "\n please enter a valid number";
        system("pause");
        break;
    }
    Update();
}