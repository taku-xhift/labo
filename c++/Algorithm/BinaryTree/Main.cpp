
#include <iostream>
#include <cassert>
#include "BinaryTree.hpp"


int main() {
	BinaryTree tree(10);
	tree.Push(3);
	const BinaryTree* found = tree.Find(3);

	assert(found);

	const BinaryTree* unfound = tree.Find(12);
	assert(!unfound);

	tree.Push(100);
	tree.Push(45);
	tree.Push(32);
	tree.Push(11);
	tree.Push(198);

	BinaryTree::PopResult popResult = tree.Pop(198);
	assert(popResult == BinaryTree::POP_SUCCESS);
	assert(!tree.Find(198));

	popResult = tree.Pop(111111111);
	assert(popResult == BinaryTree::POP_UNFOUND);
}
