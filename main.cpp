
#include "tree.h"

int main() {

	tree a;
	a.addNode(20);
	a.addNode(10);
	a.addNode(40);
	a.addNode(15);
	a.addNode(5);
	a.addNode(30);
	a.addNode(60);
	a.addNode(59);
	a.addNode(61);
	a.addNode(25);
	a.addNode(35);


	a.print();

	/*a.removeNode(5);
	a.print();*/
	return 1;
}