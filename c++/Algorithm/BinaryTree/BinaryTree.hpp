#ifndef BINARY_TREE_HPP_INCLUDED
#define BINARY_TREE_HPP_INCLUDED


class BinaryTree {
public:

	enum PushResult {
		PUSH_SUCCESS,
		PUSH_EXIST,
		PUSH_MAX,
	};

	enum PopResult {
		POP_SUCCESS,
		POP_UNFOUND,
		POP_MAX,
	};


	explicit BinaryTree(int value);
	~BinaryTree();


	PushResult Push(int value);
	PopResult Pop(int value);
	const BinaryTree* Find(int value) const;

	int GetValue() const;

private:

	
	BinaryTree* GetMaxValueNode();

	void UnRegisterChild();
	BinaryTree* RemoveAndGetSwap(BinaryTree* tree);


	int value_;             //!< 要素

	// binary なので子供は２つだけ持つ
	BinaryTree* left_;      //!< 子供の１つめ
	BinaryTree* right_;     //!< 子供の２つめ
};


#endif
