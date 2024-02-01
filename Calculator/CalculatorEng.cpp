#include "CalculatorEng.h"



int CalculatorEng::VecLenght;
std::vector<Node>CalculatorEng::VNodes;		//Vector of nodes (operation)

CalculatorEng::CalculatorEng() {

	VecLenght = -1 ;			//sloppy gets the job done, too much of the code of this shiz is based off on this
}

int CalculatorEng::getVecLenght() { return VecLenght; }

void CalculatorEng::initNode(Node *node) {			 //initialization, dependant on type and subtype or value assigns a char value to print
	if (node->Type == OPERATION || node->Type == PRIORITYOP) {
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

		case PRIORITYOPEN:
			node->v_char = '(';
			break;

		case PRIORITYCLOSE:
			node->v_char = ')';
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
	if (Prioritized && node->Type != PRIORITYOP) {
		node->priority = 1;
	}
}

bool CalculatorEng::checkNode(Node node) {
	
	if (!(node.Init)) return false;
	if (node.Position == 0) { //if node is at pos 0 there is nothing to check for, it doesnt have any nodes nex to it
		if (node.Type == NUMBER || node.Type == PRIORITYOP) {		//only if its a number tho, in an operation an operator cannot be the first element (no negative numbers in this yet)
			return true;
		}
		else return false;
	}


	else {
		if (node.Type == PRIORITYOP) {
			if (Prioritized && node.SubType == PRIORITYOPEN) return false;
			if (VNodes[node.Position - 1].Type == OPERATION) return true;
		}
		else if (VNodes[node.Position - 1].Type == node.Type) {		//if node type equals the one behind him its a sintax error
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
	

	if (subtype == PRIORITYCLOSE) {
		Prioritized = false;
		type = PRIORITYOP;
	}
	if (subtype == PRIORITYOPEN) {
		Prioritized = true;
		type = PRIORITYOP;
	}

	Node node;
	node.Type = type;
	node.SubType = subtype;
	node.value = value;
	node.Position = pos;

	initNode(&node);
	VNodes[pos] = node;
	normalizePriority();
}

void CalculatorEng::addNode(int type, int subtype, int value) {		//adds a node in the vector
	
	

	Node node;			//node to slide into the vector
	node.Type = type;
	node.SubType = subtype;
	node.value = value;
	node.Position = VecLenght + 1;

	initNode(&node);			//initializes node (gives it a c_value)
	if (checkNode(node)) {      //checks it for syntax errors and if nothing is wrong pushes it back
		if (subtype == PRIORITYCLOSE) {
			Prioritized = false;
		}
		if (subtype == PRIORITYOPEN) {
			Prioritized = true;
		}
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

void CalculatorEng::resolveVectMolt(std::vector<Node> *nodesptr, std::vector<Node> nodes) {				//this function is called in resolvevect() before resolving sums to give priority. Pretty much works by resolving the moltiplication, deleting and replacing.
	int temp;			//handles while statement
	Node resultnode;	//node to be placed
	resultnode.Type = NUMBER;
	temp = 0;

	while(temp < nodes.size() - 1) {
		
		if (nodes[temp].Type == OPERATION) {
			if (nodes[temp].SubType == MOLTIPLICATION) {

				resultnode.value = nodes[temp - 1].value * nodes[temp + 1].value;		// A*B, in this case your at the operator position so you multiply the values of position pos - 1 and pos + 1
				resultnode.Position = temp - 1;		//resulting node will be place in the position of the first moltiplication number
				initNode(&resultnode);	//initializes node

				nodesptr->at(temp - 1) = resultnode;
				nodesptr->erase(nodesptr->begin() + temp + 1);//replacing and simplifing the nodes
				nodesptr->erase(nodesptr->begin() + temp);

				temp =- 1;			//now if temp goes +1 it wont be in the correct place anymore because we deleted two nodes, so we slow down
				VecLenght -= 2;
				nodes = *nodesptr;
				recalculatePositions();
			}
			else if (nodes[temp].SubType == DIVISION) {		//same thing

				resultnode.value = nodes[temp - 1].value / nodes[temp + 1].value;		// A*B, in this case your at the operator position so you multiply the values of position pos - 1 and pos + 1
				resultnode.Position = temp - 1;		//resulting node will be place in the position of the first moltiplication number
				initNode(&resultnode);	//initializes node

				nodesptr->at(temp - 1) = resultnode;
				nodesptr->erase(nodesptr->begin() + temp + 1);//replacing and simplifing the nodes
				nodesptr->erase(nodesptr->begin() + temp);

				temp = -1;			//now if temp goes +1 it wont be in the correct place anymore because we deleted two nodes, so we slow down
				VecLenght -= 2;
				nodes = *nodesptr;
				recalculatePositions();
			}
		}
		temp += 1;
	}
}


int CalculatorEng::resolveVect(std::vector<Node> *nodesptr, bool priority) {

	normalizePriority();

	if (!(checkVect(*nodesptr))) {		//checks whole vector for errors
		return 2147483647;		//gonna process this as an error in main, pretty sloppy but gets the job done
	}

	if (VecLenght < 2 || nodesptr->at(nodesptr->size() - 1).Type == OPERATION) {
		return 2147483647;		//gonna process this as an error in main, pretty sloppy but gets the job done
	}

	if (!priority) {
		resolvePriority();
	}

	resolveVectMolt(nodesptr, *nodesptr);		//moltiplication semplification

	int ResVal = nodesptr->at(0).value;
	int temp = 0;
	while (temp < nodesptr->size() - 1) {		//simple algorithm adding/subtracting all the values in a sums only operation
		if (nodesptr->at(temp).SubType == ADDITION) {
			ResVal += nodesptr->at(temp + 1).value;
		}
		if (nodesptr->at(temp).SubType == SUBTRACTION) {
			ResVal -= nodesptr->at(temp + 1).value;
		}
		temp++;
	}
	return ResVal;
}


void CalculatorEng::normalizePriority() {
	int temp = 0;; //used in while statement
	bool normalizing = false;

	while (temp <= VecLenght) {		//resets priority
		VNodes[temp].priority = 0;
		temp++;
	}
	temp = 0;

	while (temp <= VecLenght) {		//normalizes priority

		if (VNodes[temp].SubType == PRIORITYOPEN) {
			normalizing = true;
		}
		if (VNodes[temp].SubType == PRIORITYCLOSE) {
			normalizing = false;
		}
		if (normalizing && VNodes[temp].SubType != PRIORITYCLOSE && VNodes[temp].SubType != PRIORITYOPEN) {
			VNodes[temp].priority = 1;
		}
		temp++;
	}
}


void CalculatorEng::resolvePriority() {
	int temp = 0; //handles while
	int result; //result of the prioritized operation
	std::vector<Node> TemporaryVect;
	int pos0;	//start of priority
	int pos1;	//end of priority
	bool inpriority = false; //handles when youre inside () a little like prioritized

	while (temp <= VecLenght) {
		if (VNodes[temp].SubType == PRIORITYOPEN) { pos0 = VNodes[temp].Position; inpriority = true; }	//setting up position of the first bracket now we are inside a prority section so priory = true

		if (VNodes[temp].SubType == PRIORITYCLOSE) {
			pos1 = VNodes[temp].Position; inpriority = false;	//setting pos and priority section	
			result = resolveVect(&TemporaryVect, true);			//resolves vector created to hold operation
			TemporaryVect.clear();

			while (pos1 > pos0) {							//erase parts we dont need anymore
				VNodes.erase(VNodes.begin() + pos1);
				pos1--;
				VecLenght--;
				temp--;
			}

			if (pos0 != 0) {										//code to handle negatives
				if (result < 0) {
					if (VNodes[pos0 - 1].SubType == ADDITION) {
						VNodes[pos0 - 1].SubType = SUBTRACTION;
						initNode(&VNodes[pos0 - 1]);
					}
					else {
						VNodes[pos0 - 1].SubType = ADDITION;
						initNode(&VNodes[pos0 - 1]);
					}
				}
			}

			VNodes[pos0].Type = NUMBER;					//setting up new node and clearing all up
			VNodes[pos0].SubType = 0;
			VNodes[pos0].value = abs(result);
			VNodes[pos0].priority = 0;
			initNode(&VNodes[pos0]);
			recalculatePositions();
		}

		if (VNodes[temp].priority == 1 && inpriority && VNodes[temp].Type != PRIORITYOP) {			//if node prioritized add it to new vector
			TemporaryVect.push_back(VNodes[temp]);
		}
		temp++;
	}

}

void CalculatorEng::resetVect() {		//clears vect
	VNodes.clear();
	VecLenght = -1;
	Prioritized = false;
}

bool CalculatorEng::checkVect(std::vector<Node> nodes) {		//checks whole vector before resolving it for syntattic errors
	int temp = 0;
	int checkprioritybrackets; //an int used in checks for open brackets without a close and viceversa
	bool unclosedbrackets = false; //are there unclosed brackets
	bool loop; //used to break out of loops
	int size = nodes.size() - 1;

	if (nodes[size].SubType == PRIORITYOPEN) {		//cant be ( at the end of a operation
		return false;
	}

	while (temp <= size) {

		if (temp != size) {									//i hate vector out of bounds errors HATE
			if (nodes[temp].Type == nodes[temp + 1].Type) {		//checks if there are any equal types next togeter ++, -+ (( ecc
				return false;
			}
		}
		if (nodes[temp].Type == PRIORITYOP) {	//algorithm to check if there is an unlclosed/unopened bracket

			if(nodes[temp].SubType == PRIORITYOPEN){
				loop = true;
				checkprioritybrackets = nodes[temp].Position;					//while variable to check against
				while (checkprioritybrackets <= nodes.size() - 1 && loop) {			//iterate trough all the operation if you dont find a closing bracket sintax error

					if (nodes[checkprioritybrackets].SubType == PRIORITYCLOSE) {
						loop = false;
					}
					if (checkprioritybrackets == nodes.size() - 1 && loop) {
						return false;
					}
					checkprioritybrackets++;
				}

				if (temp != 0) {
					if (nodes[temp - 1].Type == NUMBER) return false;		//brackets cant be after numbers
				}
			}
			else if (nodes[temp].SubType == PRIORITYCLOSE) {			//same thing as above but searchs for a closing bracket

				checkprioritybrackets = nodes[temp].Position;
				loop = true;

				while (checkprioritybrackets >= 0 && loop) {

					if (nodes[checkprioritybrackets].SubType == PRIORITYOPEN) {
						loop = false;
					}
					if (checkprioritybrackets == 0 && loop) {
						return false;
					}

					checkprioritybrackets--;
				}
				if (temp != nodes.size() - 1) {							//there cant be a a braket after a number
					if (nodes[temp + 1].Type == NUMBER) return false;
				}
			}
		}
		temp++;
	}
	return true;
}

void CalculatorEng::recalculatePositions() {
	int temp = 0; //used for while
	while (temp <= VNodes.size() - 1) {
		VNodes[temp].Position = temp;
		temp++;
	}
}
