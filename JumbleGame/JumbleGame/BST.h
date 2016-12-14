#ifndef _BST_H_
#define _BST_H_

template<typename Type>
class BST
{
	struct Node
	{
		Type element;
		Node* left;
		Node* right;
	};
	Node* root;
	void preOrderAssign(Node* n);
	void postOrderDelete(Node* n);
	void inOrderPrint(Node* n) const;
	bool inOrderFind(Node* n, const Type& v, bool found) const;
	void case0Remove(Node* n, Node* parent);
	void case1Remove(Node* n, Node* parent);
public:
	BST();
	~BST();
	BST(const BST& obj);
	BST& operator=(const BST& obj);
	void insert(const Type& v);
	bool findAndRemove(const Type& v);
	bool find(const Type& v) const;
	void clear();
	void printInOrder() const;
};
template<typename Type>
void BST<Type>::preOrderAssign(Node* n)
{
	if (n != nullptr)
	{
		insert(n->element);
		preOrderAssign(n->left);
		preOrderAssign(n->right);
	}
}
template<typename Type>
void BST<Type>::postOrderDelete(Node* n)
{
	if (n != nullptr)
	{
		postOrderDelete(n->left);
		postOrderDelete(n->right);
		delete n;
	}
}
template<typename Type>
void BST<Type>::inOrderPrint(Node* n) const
{
	if (n != nullptr)
	{
		inOrderPrint(n->left);
		cout << n->element << ' ';
		inOrderPrint(n->right);
	}
}
template<typename Type>
bool BST<Type>::inOrderFind(Node* n, const Type& v, bool found) const
{
	//bool found = false;
	if (n != nullptr)
	{
		inOrderFind(n->left, v, found);
		if (n->element == v)
		{
			found = true;
		}
		inOrderFind(n->right, v, found);
		return found;
	}
	//return found;
}
template<typename Type>
void BST<Type>::case0Remove(Node* n, Node* parent)
{
	if (n == root)
	{
		delete root;
		root = nullptr;
	}
	else
	{
		if (n->element < parent->element)
		{
			parent->left = nullptr;
			delete n;
		}
		else
		{
			parent->right = nullptr;
			delete n;
		}
	}
}
template<typename Type>
void BST<Type>::case1Remove(Node* curr, Node* parent)
{
	// If Root
	if (curr == root)
	{
		// Root Left Child is Null
		if (curr->left == nullptr)
		{
			curr->element = curr->right->element;
			delete curr->right;
			curr->right = nullptr;
		}
		// Root Right Child is Null
		else
		{
			curr->element = curr->left->element;
			delete curr->left;
			curr->left = nullptr;
		}
	}
	// Non-Root
	else
	{
		// In Left Subtree
		if (curr->element < parent->element)
		{
			// Left-Left Case
			if (curr->right == nullptr)
			{
				parent->left = curr->left;
				delete curr;
			}
			// Left-Right Case
			else
			{
				parent->left = curr->right;
				delete curr;
			}
		}
		// In Right Subtree
		else
		{
			// Right-Left Case
			if (curr->right == nullptr)
			{
				parent->right = curr->left;
				delete curr;
			}
			// Right-Right Case
			{
				parent->right = curr->right;
				delete curr;
			}
		}
	}
}
template<typename Type>
BST<Type>::BST()
{
	root = nullptr;
}
template<typename Type>
BST<Type>::~BST()
{
	clear();
}
template<typename Type>
BST<Type>::BST(const BST& obj)
{
	root = nullptr;
	Node* tmp = obj.root;
	preOrderAssign(tmp);
}
template<typename Type>
BST<Type>& BST<Type>::operator=(const BST<Type>& obj)
{
	clear();
	if (this != &obj)
	{
		Node* tmp = obj.root;
		preOrderAssign(tmp);
	}
	return *this;
}
template<typename Type>
void BST<Type>::insert(const Type& v)
{
	Node* n = new Node;
	n->element = v;
	n->left = nullptr;
	n->right = nullptr;
	Node* curr = root;
	if (root == nullptr)
	{
		root = n;
		return;
	}
	else
	{
		while (true)
		{
			// Left Subtree Check
			if (n->element < curr->element)
			{
				if (curr->left == nullptr)
				{
					curr->left = n;
					return;
				}
				curr = curr->left;
			}
			// Right Subtree Check
			else if (n->element >= curr->element)
			{
				if (curr->right == nullptr)
				{
					curr->right = n;
					return;
				}
				curr = curr->right;
			}
		}
	}
}
template<typename Type>
bool BST<Type>::findAndRemove(const Type& v)
{
	if (root != nullptr)
	{
		if (!find(v))
			return false;
		else
		{
			Node* curr = root;
			Node* parent = curr;

			// Iterate to Requested Value
			if (root->element != v)
			{
				while (curr->element != v)
				{
					// Left Subtree Check
					if (v < curr->element)
					{
						parent = curr;
						curr = curr->left;
					}
					// Right Subtree Check
					else if (v >= curr->element)
					{
						parent = curr;
						curr = curr->right;
					}
				}
			}

			// If Root
			if (root->element == v)
			{
				// Case 0 Removal
				if (root->left == nullptr && root->right == nullptr)
				{
					case0Remove(curr, parent);
					return true;
				}
				// Case 1 Removal
				else if ((root->left == nullptr && root->right != nullptr) || (root->left != nullptr && root->right == nullptr))
				{
					case1Remove(curr, parent);
					return true;
				}
				// Case 2 Removal
				else
				{
					Node* tmp = curr;
					//tmp = tmp->right;
					curr = curr->right;
					while (curr->left != nullptr)
					{
						parent = curr;
						curr = curr->left;
						//tmp = tmp->left;
					}
					tmp->element = curr->element;
					if (curr->left == nullptr && curr->right == nullptr)
					{
						case0Remove(curr, parent);
						return true;
					}
					else
					{
						case1Remove(curr, parent);
						return true;
					}
				}
			}

			// Non-Root
			//// Left Subtree Check
			//if (v < curr->element)
			//{
			//	// Case 0 Removal
			//	if (curr->left == nullptr && curr->right == nullptr)
			//	{
			//		case0Remove(curr, parent);
			//		return true;
			//	}
			//	// Case 1 Removal
			//	else if ((curr->left == nullptr && curr->right != nullptr) || (curr->left != nullptr && curr->right == nullptr))
			//	{
			//		case1Remove(curr, parent);
			//		return true;
			//	}
			//	// Case 2 Removal
			//	else
			//	{
			//		Node* tmp = curr;
			//		tmp = tmp->right;
			//		while (tmp != nullptr)
			//			tmp = tmp->left;
			//		curr->element = tmp->element;
			//		if (tmp->left == nullptr && tmp->right == nullptr)
			//			case0Remove(curr, parent);
			//		else
			//			case1Remove(curr, parent);
			//	}
			//}
			//// Right Subtree Check

			// Non-Root Removal
			else
			{
				// Case 0 Removal
				if (curr->left == nullptr && curr->right == nullptr)
				{
					case0Remove(curr, parent);
					return true;
				}
				// Case 1 Removal
				else if ((curr->left == nullptr && curr->right != nullptr) || (curr->left != nullptr && curr->right == nullptr))
				{
					case1Remove(curr, parent);
					return true;
				}
				// Case 2 Removal
				else
				{
					Node* tmp = curr;
					//tmp = tmp->right;
					curr = curr->right;
					while (curr->left != nullptr)
					{
						parent = curr;
						curr = curr->left;
						//tmp = tmp->left;
					}
					tmp->element = curr->element;
					if (curr->left == nullptr && curr->right == nullptr)
					{
						case0Remove(curr, parent);
						return true;
					}
					else
					{
						case1Remove(curr, parent);
						return true;
					}
				}
			}
		}
	}
	return false;
}
template<typename Type>
bool BST<Type>::find(const Type& v) const
{
	if (root != nullptr)
	{
		Node* curr = root;
		while (true)
		{
			if (root->element == v)
				return true;
			// Left Subtree Check
			if (v < curr->element)
			{
				if (curr->left == nullptr)
					return false;
				if (curr->left->element == v)
				{
					return true;
				}
				curr = curr->left;
			}
			// Right Subtree Check
			else if (v >= curr->element)
			{
				if (curr->right == nullptr)
					return false;
				if (curr->right->element == v)
				{
					return true;
				}
				curr = curr->right;
			}
		}
	}
	return false;
	//bool found = false;
	//return inOrderFind(n, v, found); 
}
template<typename Type>
void BST<Type>::clear()
{
	Node* n = root;
	postOrderDelete(n);
	root = nullptr;
}
template<typename Type>
void BST<Type>::printInOrder() const
{
	Node* n = root;
	inOrderPrint(n);
	cout << '\n';
}
#endif