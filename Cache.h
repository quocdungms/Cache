#ifndef CACHE_H
#define CACHE_H

#include "main.h"

class AVL
{

public:
	class Node;

private:
	Node* root;
	int numOfNode;
public:
	AVL() {
		this->root = NULL;
		this->numOfNode = 0;
	}
	~AVL() {
		this->Clear(root);
	}
	//void run(string filename);
	int get_height_rec(Node* node);
	int get_balance_factor(Node* node);
	int size();
	Node* insert(Node*& node, Elem* element);
	void INSERT(Elem* element);
	Node* remove(Node*& node, int address);
	void REMOVE(int address);
	Node* search(int address);
	//void SEARCH(Elem &element);
	Node* get_root();
	Node* balance(Node* node);
	Node* ll_rotation(Node* parent);
	Node* rr_rotation(Node* parent);
	Node* lr_rotation(Node* parent);
	Node* rl_rotation(Node* parent);
	Node* max_node_rec(Node* node);
	Node* min_node_rec(Node* node);

	// preOrder
	void printNLR(Node* node);
	void PRINT_NLR();

	// inOrder
	void printLNR(Node* node);
	void PRINT_LNR();


	void display(Node* node, int level);
	void Clear(AVL::Node* node);

public: class Node
{

protected:

	Elem* element;
	Node* left;
	Node* right;
	friend class AVL;

public:
	Elem* getElement() {
		return this->element;
	}
	Node(int addr, Data* data, bool sync) {
		this->element = new Elem(addr, data, sync);
		this->left = this->right = NULL;
	}
};

};


class Cache {
		
	public:
		//class AVL;
		queue<int> myQueue;
		AVL* tree;
		int capacity;
	public:
		Cache(int capacity) {
			this->capacity = capacity;
			this->tree = new AVL();

		}
		~Cache() {
			this->capacity = 0;
			delete tree;
		}
		Data* read(int addr);
		Elem* put(int addr, Data* cont);
		Elem* write(int addr, Data* cont);
		void print();
		void preOrder();
		void inOrder();	
		bool isFull();
		
		//void printNLR(Node* node)

};






#endif