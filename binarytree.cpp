#include "tree.h"
#include <deque>
#include <vector>
#include <math.h>
#include <string>
#include <iomanip>
#include <string>

void tree::addNode(int data) {

	std::shared_ptr<node> p = std::make_shared<node>(data);

	if (!root) {
		root = std::move(p);
		return;
	}

	std::shared_ptr<node> tmp = root;
	while(tmp != nullptr) {
		if (tmp->data > data) {
			if (tmp->left == nullptr) {
				tmp->left = std::move(p);
				break;
			}

			tmp = tmp->left;
		} else {
			if (tmp->right == nullptr) {
				tmp->right = std::move(p);
				break;
			}

			tmp = tmp->right;
		}
	}
}


void tree::removeNode(int data) {
	std::shared_ptr<node> tmp = root;	
	std::shared_ptr<node> parent = nullptr;

	auto getParent = [&](shared_ptr<node> p) {
		shared_ptr<node> tmp = root;

		while (tmp != nullptr) {
			if ((tmp->left == p) ||
					(tmp->right == p)) {
				return tmp;
			} else {
				if (tmp->data > p->data) {
					tmp = tmp->left;
				} else {
					tmp = tmp->right;
				}
			}
		}
	};

	if (tmp->data != data) {
		while(tmp != nullptr) {
			if (tmp->data == data) {
				break;
			} else if (tmp->data > data) {			
				tmp = tmp->left;
			} else {
				tmp = tmp->right;
			}
		}
		parent = getParent(tmp);		
	}

	if (tmp == nullptr) {
		cout << "No node found with data " << data << endl;
		return;
 	}

 	// find the left most node in right subtree 
 	std::shared_ptr<node> replacement = findLeftMostNodeInRightSubtree(tmp);

 	if (replacement == nullptr) {
 		if (parent->left == tmp) {
 			parent->left = nullptr;
 		} else {
 			parent->right = nullptr;
 		}

 		return;
 	}

 	std::shared_ptr<node> replacementParent = getParent(replacement);
 	if (replacementParent->left == replacement) replacementParent->left = nullptr;
 	else replacementParent->right = nullptr;

 	if (parent != nullptr) {
 		if (parent->left == tmp) {
 			parent->left = replacement;
 		} else {
 			parent->right = replacement;
 		}
 	}

 	replacement->right = std::move(tmp->right);
 	replacement->left = std::move(tmp->left);

 	if (tmp == root) {
 		root = replacement;
 	}
}

shared_ptr<node> tree::findLeftMostNodeInRightSubtree(std::shared_ptr<node> p) {
	shared_ptr<node> start = p->right;

	while (start != nullptr) {
		if (start->left != nullptr) {
			start = start->left;
		} else {
			break;
		}
	}

	return start;
}

int tree::getHeight(std::shared_ptr<node> element) {
	if (element == nullptr) {
		return 0;
	}

	int lHeight = getHeight(element->left);
	int rHeight = getHeight(element->right);

	return (lHeight > rHeight)?++lHeight:++rHeight;
}

void tree::print() {
	printT(root);
	
}

void tree::printT(shared_ptr<node> node) {
	if (node == nullptr) 
		return;

	int treeHeight = getHeight(root);

	// BFS print
	std::deque<std::shared_ptr<__node>> que;
	que.push_front(root);

	std::deque<std::shared_ptr<__node>>::iterator it = que.begin();
	while (it != que.end()) {
		std::shared_ptr<__node> n = *it++;

		int toProcess = pow(2, treeHeight - getHeight(n));

		if (n != nullptr) {
			que.push_back(n->left);
			que.push_back(n->right);
		} else {
			// do not do anything ??
		}
	}

	it = que.begin();
	while(it != que.end()) {
		if (*it != nullptr) {
			cout << (*it)->data << " ";
		}

		it++;
	}

	cout << endl;


	// Printing 1 level at a time
	que.clear();
	que.push_front(root);
	int h = treeHeight;
	int nodesInCurLevel = 1;

	// There are 3 lengths to consider while printing the binary tree
	// branch len -- space between the left child and right child
	// nodeSpaceLen -- space between the left branch's right child and right branch's left child
	// indent -- space for the first element in a given level
	int branchLen = pow(2,h) - pow(2, h-1);
	int nodeSpace = 2 + (pow(2,h));
	int indent = 2 + branchLen;

	auto printBranches = [&]() {
	    std::deque<std::shared_ptr<__node>>::iterator iter = que.begin();
	    for (int i =1;i < nodesInCurLevel; i++) {
	        cout << ((i==0)?setw(indent):setw(nodeSpace)) << "" << ((*iter++) ? "/" : " ");
            cout << setw(branchLen) << "" << ((*iter++) ? "\\" : " ");
	    }

	    cout << endl;
	};

	auto printNodes = [&]() {
	    std::deque<std::shared_ptr<__node>>::iterator iter = que.begin();
	    for (int i =0;i < nodesInCurLevel; i++) {
	        cout << ((i==0)?setw(indent):setw(nodeSpace)) << "" << (((*iter) && (*iter)->left) ? setfill('_') : setfill(' '));
            cout << setw(branchLen) << ((*iter) ? std::to_string((*iter)->data) : "");
            cout << (((*iter) && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
	    }

	    cout << endl;
	};

	auto printLeaves = [&]() {
	    std::deque<std::shared_ptr<__node>>::iterator iter = que.begin();
	    for (int i =0;i < nodesInCurLevel; i++,iter++) {
		cout << ((i==0)?setw(indent):setw(2)) <<  ((*iter)? std::to_string((*iter)->data) : "");
	    }
	    cout << endl;
	};

    std::deque<std::shared_ptr<__node>>::iterator iter = que.begin();
	for (int i = 1; i < h; i++) {
        printBranches();
	    branchLen = pow(2,i) - pow(2, i-1);
	    nodeSpace = 2 + (pow(2,i));
	    indent = 2 + branchLen;
        printNodes();

        for (int j=0; j < nodesInCurLevel ; j++) {
            std::shared_ptr<__node> n = *iter++;
            if (n != nullptr) {
                que.push_back(n->left);
                que.push_back(n->right);
            } else {
                que.push_back(nullptr);
                que.push_back(nullptr);
            }
            nodesInCurLevel += 2;
        }
	}

    printLeaves();

/*

	for (it = que.begin(); (it != que.end() && (h < treeHeight)); h++) {
	    int elemes = pow(2, h);

	    std::cout << std::string( 1.5 * pow(2, treeHeight - h -1 ), ' ' );

	    for (int i=0; i < elemes; i++) {
		std::shared_ptr<__node> n = *it++;
		if (n != nullptr)  {
			cout << n->data;
		} else {
			cout << "-1";
		}

		if (i % 2)
			std::cout << std::string( pow(2, treeHeight - h) + 1, ' ' );
		else
			std::cout << std::string( pow(2, treeHeight - h) - 1, ' ' );

		if (n != nullptr) {
			que.push_back(n->left);
			que.push_back(n->right);
		} else {
			que.push_back(nullptr);
			que.push_back(nullptr);
		}
	    }
	    cout << endl;
	} */
}
