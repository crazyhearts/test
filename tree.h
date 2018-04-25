#include <iostream>
#include <memory>
using namespace std;


enum class Color { red, black};

typedef struct __node {
	int data;
	int height;
	Color color;
	std::shared_ptr<__node> left;
	std::shared_ptr<__node> right;

	__node(int data) {
		this->data = data;
		this->right = nullptr;
		this->left = nullptr;
	}
}node;

class tree {
public:
	std::shared_ptr<node> root;

	tree() { root = nullptr; }

	// rotate operations
	void rotateRight(node* p);
	void rotateLeft(node* p);

	// for delete operation
	void removeNode(int data);
	shared_ptr<node> findLeftMostNodeInRightSubtree(shared_ptr<node> p);

	// for adding a node
	void addNode(int data);
	void print();

	int getHeight(std::shared_ptr<node> element);

private:
	tree(const tree &p);
	void operator =(const tree &p);

	void printT(std::shared_ptr<node> r);
};