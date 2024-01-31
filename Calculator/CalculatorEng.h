#pragma once

#include <iostream>
#include <vector>
#include <string>


enum NodeType
{
    NUMBER,
    OPERATION,
};

enum OperationType
{
    ADDITION,
    SUBTRACTION,
    MOLTIPLICATION,
    DIVISION,
};


struct Node
{
    int Type; //number, operation
    int value; //if number
    int SubType; //operation only subtype (addition, subtraction ecc...)
    int Position; //position in Node vector
    std::string v_char; //init values (lookup init function)
    bool Init = false;
};




class CalculatorEng //handles node vector
{
private:
	static int VecLenght;


public:
    static std::vector<Node> VNodes;

    CalculatorEng();

    int getVecLenght();
    
    void initNode(Node *node);                      //initializes node, gives it a c_value (char_value)
    void addNode(int type, int subtype, int value);     //adds the node, also runs initnode and checknode
    void deleteNode(int pos);       
    void replaceNode(int pos, int type, int subtype, int value);        
    bool checkNode(Node node);      //checks for sintax errors
    void printVect();
    void resetVect();   //deletes the vector
    int resolveVect();  //resolves the operations
    void resolveVectMolt();     //resolves the moltiplication this is in order to do multiplication early 
    bool checkVect(); //checks entire vector for errors
};

