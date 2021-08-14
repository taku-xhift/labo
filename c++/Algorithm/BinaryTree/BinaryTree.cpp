

#include <cstdlib>
#include "BinaryTree.hpp"

namespace {
}


BinaryTree::BinaryTree(int value)
	: value_(value)
	, left_(NULL)
	, right_(NULL)
{
}

BinaryTree::~BinaryTree() {
	if (this->left_) {
		delete this->left_;
		this->left_ = NULL;
	}
	if (this->right_) {
		delete this->right_;
		this->right_ = NULL;
	}
}



/**
 * ツリーの中に新しいデータを挿入する
 *
 * @param value [description]
 */
BinaryTree::PushResult BinaryTree::Push(int value) {
	// 基本戦略
	// 1. まずは自分と比較をしてみる。
	//         一致していればすることが無いので何もしない
	// 2. 大小を比べて自分のどちらの子に託すかを決める
	// 3. 1, 2 を自分が末代になるまで繰り返す
	// 4. 末代であることがわかったら、自分より大きければ右へ、小さければ左へ。

	if (this->value_ == value) {
		return PUSH_EXIST;
	} else if (this->value_ > value) {
		if (this->left_ == NULL) {
			this->left_ = new BinaryTree(value);
			return PUSH_SUCCESS;
		} else {
			return this->left_->Push(value);
		}
	} else {
		if (this->right_ == NULL) {
			this->right_ = new BinaryTree(value);
			return PUSH_SUCCESS;
		} else {
			return this->right_->Push(value);
		}
	}
}

BinaryTree::PopResult BinaryTree::Pop(int value) {
	if (this->left_) {
		if (this->left_->value_ == value) {
			this->left_ = this->RemoveAndGetSwap(this->left_);
			return POP_SUCCESS;
		} else {
			const PopResult result = this->left_->Pop(value);
			if (result == POP_SUCCESS) {
				return result;
			}
		}
	}

	if (this->right_) {
		if (this->right_->value_ == value) {
			this->right_ = this->RemoveAndGetSwap(this->right_);
			return POP_SUCCESS;
		} else {
			const PopResult result = this->right_->Pop(value);
			if (result == POP_SUCCESS) {
				return result;
			}
		}
	}

	return POP_UNFOUND;
}

const BinaryTree* BinaryTree::Find(int value) const {
	if (this->value_ == value) {
		return this;
	} else if (this->left_) {
		return this->left_->Find(value);
	} else if (this->right_) {
		return this->right_->Find(value);
	} else {
		return NULL;
	}
}


int BinaryTree::GetValue() const {
	return this->value_;
}


BinaryTree* BinaryTree::GetMaxValueNode() {
	if (!this->right_) {
		return this;
	} else {
		return this->right_->GetMaxValueNode();
	}
}



void BinaryTree::UnRegisterChild() {
	this->left_ = NULL;
	this->right_ = NULL;
}

BinaryTree* BinaryTree::RemoveAndGetSwap(BinaryTree* tree) {
	BinaryTree* maxNode = tree->GetMaxValueNode();
	tree->UnRegisterChild();
	delete tree;

	if (tree == maxNode) {
		// 自分自身が末端だった場合なので
		return NULL;
	} else {
		return maxNode;
	}
}

