#pragma once

#include <iostream>
#include <vector>
#include <string>


enum NodeType
{
    NUMBER,
    OPERATION,
    PRIORITYOP,
};

enum OperationType
{
    ADDITION,
    SUBTRACTION,
    MOLTIPLICATION,
    DIVISION,
    PRIORITYOPEN,
    PRIORITYCLOSE,
};


struct Node
{
    int Type; //number, operation
    int value; //if number
    int SubType; //operation only subtype (addition, subtraction ecc...)
    int Position; //position in Node vector
    std::string v_char; //init values (lookup init function)
    bool Init = false;
    int priority = 0;
};




class CalculatorEng //handles node vector
{
private:
	static int VecLenght;
    bool Prioritized = false;       //in a priority bracket

public:
    static std::vector<Node> VNodes;

    CalculatorEng();

    int getVecLenght();
    
    void initNode(Node *node);                      //initializes node, gives it a c_value (char_value)
    void addNode(int type, int subtype, int value);     //adds the node, also runs initnode and checknode
    void deleteNode(int pos);       //deletes a node
    void replaceNode(int pos, int type, int subtype, int value);     //replaces node   
    bool checkNode(Node node);      //checks for sintax errors
    void printVect();
    void resetVect();   //deletes the vector
    void recalculatePositions(); //when deleting nodes updates positions
    void normalizePriority(); //used in case of modification to make sure priority is normal
    int resolveVect(std::vector<Node>* nodesptr, bool priority);  //resolves the operations
    void resolveVectMolt(std::vector<Node> *nodesptr, std::vector<Node> nodes);     //resolves the moltiplication this is in order to do multiplication early 
    void resolvePriority(); //resolve prioritized nodes in brackets ()
    bool checkVect(std::vector<Node> nodes); //checks entire vector for errors
};

