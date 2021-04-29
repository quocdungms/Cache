#include "Cache.h"

/*
* Class Cache
*/


Data* Cache::read(int addr) {
	if (tree->search(addr) != NULL)
		return tree->search(addr)->getElement()->data;
	else {
		return NULL;
	}
    
}
Elem* Cache::put(int addr, Data* data) {
	if (this->isFull())
	{
		Elem* temp = new Elem(addr, data, true);
		int del_pos = myQueue.front();
		Elem* DEATH = tree->search(del_pos)->getElement();
		myQueue.pop();
		tree->REMOVE(del_pos);
		myQueue.push(temp->addr);
		tree->INSERT(temp);
		return DEATH;
	}
	else {
		Elem* temp = new Elem(addr, data, true);
		tree->INSERT(temp);
		myQueue.push(temp->addr);
		return NULL;
	}
    
}
Elem* Cache::write(int addr, Data* data) {
    
	if (tree->search(addr) != NULL)
	{
		tree->search(addr)->getElement()->data = data;
		tree->search(addr)->getElement()->sync = false;
		return NULL;
	}
	else {
		if (this->isFull())
		{
			Elem* temp = new Elem(addr, data, false);
			int del_pos = myQueue.front();
			Elem* DEATH = tree->search(del_pos)->getElement();
			myQueue.pop();
			tree->REMOVE(del_pos);
			myQueue.push(temp->addr);
			tree->INSERT(temp);
			return DEATH;
		}
		else {
			Elem* temp = new Elem(addr, data, false);
			tree->INSERT(temp);
			myQueue.push(temp->addr);
			return NULL;
		}
	}
  
}
void Cache::print() {
	Elem* current = NULL;
	int pos = -1;
	while (!myQueue.empty())
	{
		pos = myQueue.front();
		myQueue.pop();
		current = tree->search(pos)->getElement();
		current->print();
	}
}



void Cache::preOrder() {

	tree->PRINT_NLR();
}
void Cache::inOrder() {
    // LNR
	tree->PRINT_LNR();
}

bool Cache::isFull() {
	return (int)myQueue.size() == capacity;
}




/*
* Class AVL
*/





int AVL::size() {
	return this->numOfNode;
}
void AVL::Clear(Node* node) {
	if (node != NULL) {
		Clear(node->left);
		Clear(node->right);
		delete node;
	}
	node = NULL;
	numOfNode = 0;
}


int AVL::get_height_rec(Node* node) {
	if (node == NULL)
		return 0;
	int left_height = get_height_rec(node->left);
	int right_height = get_height_rec(node->right);

	return left_height > right_height ? left_height + 1 : right_height + 1;
}


int AVL::get_balance_factor(Node* node) {
	int left_height = get_height_rec(node->left);
	int right_height = get_height_rec(node->right);
	return left_height - right_height;
}



typename AVL::Node* AVL::balance(Node* node) {
	int balance_factor = get_balance_factor(node);

	if (balance_factor > 1) {
		if (get_balance_factor(node->left) > 0) {
			node = ll_rotation(node);
		}
		else {
			node = lr_rotation(node);
		}
	}
	else if (balance_factor < -1) {
		if (get_balance_factor(node->right) > 0) {
			node = rl_rotation(node);
		}
		else {
			node = rr_rotation(node);
		}
	}
	return node;
}


typename AVL::Node* AVL::ll_rotation(Node* parent) {
	Node* current;
	current = parent->left;
	parent->left = current->right;
	current->right = parent;

	return current;
}


typename AVL::Node* AVL::rr_rotation(Node* parent) {
	Node* current;
	current = parent->right;
	parent->right = current->left;
	current->left = parent;
	return current;
}



typename AVL::Node* AVL::lr_rotation(Node* parent) {
	Node* current;
	current = parent->left;
	parent->left = this->rr_rotation(current);
	return this->ll_rotation(parent);
}

typename AVL::Node* AVL::rl_rotation(Node* parent) {
	Node* current;
	current = parent->right;
	parent->right = this->ll_rotation(current);
	return this->rr_rotation(parent);
}


typename AVL::Node* AVL::search(int address) {
	Node* current = root;
	while (current != NULL)
	{
		if (current->element->addr == address) {
			break;
		}
		address > current->element->addr ? current = current->right : current = current->left;
	}
	return current;
}
//template <class T>
//void AVL<T>::SEARCH(Elem &element) {
//	this->search(element) != NULL ? std::cout << "\n" << element << " was found\n" : std::cout << "\n" << element << " was not found\n";
//}


typename AVL::Node* AVL::insert(Node*& node, Elem* element) {
	if (node == NULL) {
		Node* temp = new Node(element->addr, element->data, element->sync);
		numOfNode++;
		node = temp;
		node->left = NULL;
		node->right = NULL;
		return node;
	}
	else if (node->element->addr > element->addr) {
		node->left = insert(node->left, element);
		node = balance(node);
	}
	else if (node->element->addr <= element->addr) {
		node->right = insert(node->right, element);
		node = balance(node);
	}

	return node;
}


void AVL::INSERT(Elem* element) {
	this->insert(root, element);
}



typename AVL::Node* AVL::remove(Node*& node, int address) {
	Node* temp = NULL;
	if (node == NULL) return NULL;
	else if (address > node->element->addr) node->right = remove(node->right, address);
	else if (address < node->element->addr) node->left = remove(node->left, address);
	// element found and has 2 children
	else if (node->left != NULL && node->right != NULL)
	{
		// get min node of right sub-tree
		temp = this->min_node_rec(node->right);
		// assign data of current node to min
		node->element->addr = temp->element->addr;
		node->element->data = temp->element->data;
		node->element->sync = temp->element->sync;
		node->right = remove(node->right, address);
	}
	else
	{
		temp = node;
		if (node->left == NULL) node = node->right;
		else if (node->right == NULL) node = node->left;
		delete temp;
		numOfNode--;
	}
	if (node == NULL) return node;
	node = this->balance(node);
	
	return node;
}


void AVL::REMOVE(int address) {
	if (this->search(address) != NULL) {
		this->remove(root, address);
	}
}

void AVL::printNLR(Node* node)
{
	if (node == NULL) return;
	node->getElement()->print();
	printNLR(node->left);
	printNLR(node->right);

}
void AVL::PRINT_NLR() {
	this->printNLR(this->root);
}

// inOrder
void AVL::printLNR(Node* node)
{
	if (node == NULL) return;

	printLNR(node->left);
	node->getElement()->print();
	printLNR(node->right);
	

}

void AVL::PRINT_LNR()
{
	printLNR(this->root);
}



typename AVL::Node* AVL::get_root() {
	return this->root;
}



void AVL::display(Node* node, int level) {

	int i;
	if (node != NULL)
	{
		display(node->right, level + 1);
		printf("\n");
		if (node == root)
			std::cout << "Root -> ";
		for (i = 0; i < level && node != root; i++)
			std::cout << "      ";
		std::cout << node->element->addr;
		display(node->left, level + 1);
	}
}



typename AVL::Node* AVL::max_node_rec(Node* node) {
	if (node == NULL) {
		return NULL;
	}
	else if (node->right == NULL) {
		return node;
	}
	else {
		return max_node_rec(node->right);
	}
}



typename AVL::Node* AVL::min_node_rec(Node* node) {
	if (node == NULL) {
		return NULL;
	}
	else if (node->left == NULL) {
		return node;
	}
	else {
		return min_node_rec(node->left);
	}
}


