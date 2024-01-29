#include "CalculatorEng.h"



int CalculatorEng::VecLenght;
std::vector<Node>CalculatorEng::VNodes;

CalculatorEng::CalculatorEng() {

	VecLenght = -1 ;
}

int CalculatorEng::getVecLenght() { return VecLenght; }

void CalculatorEng::initNode(Node *node) {
	if (node->Type == OPERATION) {
		switch (node->SubType)
		{
		case ADDITION:
			node->v_char = '+';
			break;

		case SUBTRACTION:
			node->v_char = '-';
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
	if (node.Position == 0) { //if vector lenght is 0 there is nothing to check for
		if (node.Type == NUMBER) {		//only if its a number tho
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

void CalculatorEng::replaceNode(int pos, int type, int subtype, int value) {
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

void CalculatorEng::addNode(int type, int subtype, int value) {
	
	Node node;
	node.Type = type;
	node.SubType = subtype;
	node.value = value;
	node.Position = VecLenght + 1;

	initNode(&node);
	if (checkNode(node)) {
		VNodes.push_back(node);
		VecLenght += 1;
	}
	else
	{
		std::cout << "sintax/init error\n";
		return;
	}
}

void CalculatorEng::deleteNode(int pos) {
	VNodes.erase(VNodes.begin() + pos);
	VecLenght -= 1;
}

void CalculatorEng::printVect() {
	int temp = 0;
	if (VecLenght < 1) {
		return;
	}
	while (temp < VecLenght + 1) {
		std::cout << VNodes[temp].v_char;
		temp++;
	}
}

int CalculatorEng::resolveVect() {

	if (!(checkVect())) {
		return 2147483647;		//gonna process this as an error in main, pretty sloppy but gets the job done
	}

	if (VecLenght < 2 || VNodes[VecLenght].Type == OPERATION ) {
		return 2147483647;		//gonna process this as an error in main, pretty sloppy but gets the job done
	}



	int ResVal = VNodes[0].value;
	int temp = 0;
	while (temp < VecLenght) {
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

void CalculatorEng::resetVect() {
	VNodes.clear();
	VecLenght = -1;
}

bool CalculatorEng::checkVect() {
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
