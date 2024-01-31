#include "CalculatorEng.h"



int CalculatorEng::VecLenght;
std::vector<Node>CalculatorEng::VNodes;		//Vector of nodes (operation)

CalculatorEng::CalculatorEng() {

	VecLenght = -1 ;			//sloppy gets the job done, too much of the code of this shiz is based off on this
}

int CalculatorEng::getVecLenght() { return VecLenght; }

void CalculatorEng::initNode(Node *node) {			 //initialization, dependant on type and subtype or value assigns a char value to print
	if (node->Type == OPERATION) {
		switch (node->SubType)
		{
		case ADDITION:
			node->v_char = '+';
			break;

		case SUBTRACTION:
			node->v_char = '-';
			break;

		case MOLTIPLICATION:
			node->v_char = '*';
			break;

		case DIVISION:
			node->v_char = '/';
			break;

		default:
			break;
		}
		node->Init = true;
	}
	if (node->Type == NUMBER) {
		node->v_char = std::to_string(node->value);
		node->Init = true;
	}
}

bool CalculatorEng::checkNode(Node node) {
	
	if (!(node.Init)) return false;
	if (node.Position == 0) { //if node is at pos 0 there is nothing to check for, it doesnt have any nodes nex to it
		if (node.Type == NUMBER) {		//only if its a number tho, in an operation an operator cannot be the first element (no negative numbers in this yet)
			return true;
		}
		else return false;
	}


	else {
		if (VNodes[node.Position - 1].Type == node.Type) {		//if node type equals the one behind him its a sintax error
			return false;
		}
		else { return true; }
	}
}

void CalculatorEng::replaceNode(int pos, int type, int subtype, int value) {	//practically creates a temporary node and inserts it at pos
	if (pos > VecLenght || pos < 0) {
		std::cout << "invalid position\n";
		return;
	}
	
	Node node;
	node.Type = type;
	node.SubType = subtype;
	node.value = value;
	node.Position = pos;

	initNode(&node);
		VNodes[pos] = node;
}

void CalculatorEng::addNode(int type, int subtype, int value) {		//adds a node in the vector
	
	Node node;			//node to slide into the vector
	node.Type = type;
	node.SubType = subtype;
	node.value = value;
	node.Position = VecLenght + 1;

	initNode(&node);			//initializes node (gives it a c_value)
	if (checkNode(node)) {			//checks it for syntax errors and if nothing is wrong pushes it back
		VNodes.push_back(node);
		VecLenght += 1;
	}
	else
	{
		std::cout << "sintax/init error\n";
		return;
	}
}

void CalculatorEng::deleteNode(int pos) {		//deletes a node at pos
	VNodes.erase(VNodes.begin() + pos);
	VecLenght -= 1;
}

void CalculatorEng::printVect() {			//prints vector, useless function was made during early stages to debug when there wasnt a display
	int temp = 0;
	if (VecLenght < 1) {
		return;
	}
	while (temp < VecLenght + 1) {
		std::cout << VNodes[temp].v_char;
		temp++;
	}
}

void CalculatorEng::resolveVectMolt() {				//this function is called in resolvevect() before resolving sums to give priority. Pretty much works by resolving the moltiplication, deleting and replacing.
	int temp;			//handles while statement
	Node resultnode;	//node to be placed
	resultnode.Type = NUMBER;
	temp = 0;

	while(temp < VNodes.size() - 1) {
		
		if (VNodes[temp].Type == OPERATION) {
			if (VNodes[temp].SubType == MOLTIPLICATION) {
				resultnode.value = VNodes[temp - 1].value * VNodes[temp + 1].value;		// A*B, in this case your at the operator position so you multiply the values of position pos - 1 and pos + 1
				resultnode.Position = temp - 1;		//resulting node will be place in the position of the first moltiplication number
				initNode(&resultnode);		//initializes node
				VNodes.erase(VNodes.begin() + temp);	//replacing and simplifing the nodes
				VNodes.erase(VNodes.begin() + temp);
				VNodes[temp - 1] = resultnode;
				temp =- 1;			//now if temp goes +1 it wont be in the correct place anymore because we deleted two nodes, so we slow down
				VecLenght -= 2;
			}
			else if (VNodes[temp].SubType == DIVISION) {		//same thing
				resultnode.value = VNodes[temp - 1].value / VNodes[temp + 1].value;
				resultnode.Position = temp - 1;
				initNode(&resultnode);
				VNodes.erase(VNodes.begin() + temp);
				VNodes.erase(VNodes.begin() + temp);
				VNodes[temp - 1] = resultnode;
				temp = -1;
				VecLenght -= 2;
			}
		}
		temp += 1;
	}
}


int CalculatorEng::resolveVect() {

	if (!(checkVect())) {		//checks whole vector for errors
		return 2147483647;		//gonna process this as an error in main, pretty sloppy but gets the job done
	}

	if (VecLenght < 2 || VNodes[VecLenght].Type == OPERATION ) {
		return 2147483647;		//gonna process this as an error in main, pretty sloppy but gets the job done
	}

	resolveVectMolt();		//moltiplication semplification

	int ResVal = VNodes[0].value;
	int temp = 0;
	while (temp < VecLenght) {		//simple algorithm adding/subtracting all the values in a sums only operation
		if (VNodes[temp].SubType == ADDITION) {
			ResVal += VNodes[temp + 1].value;
		}
		if (VNodes[temp].SubType == SUBTRACTION) {
			ResVal -= VNodes[temp + 1].value;
		}
		temp++;
	}
	return ResVal;
}

void CalculatorEng::resetVect() {		//clears vect
	VNodes.clear();
	VecLenght = -1;
}

bool CalculatorEng::checkVect() {		//checks whole vector before resolving it for syntattic errors
	int temp = 0;
	int size = VNodes.size() - 1;
	while (temp < size) {
		if (VNodes[temp].Type == VNodes[temp + 1].Type) {
				return false;
		}
		temp++;
	}
	return true;
}
