#include <iostream>
using namespace std;

template <class T>
class ThreadedTree {
	struct Node {
		T data_;
		Node* left_;
		Node* right_;
		bool leftThread_;
		bool rightThread_;
		Node(const T& data = T{}, Node* left = nullptr, Node* right = nullptr)
		{
			data_ = data;
			left_ = left;
			right_ = right;
			leftThread_ = true;
			rightThread_ = true;
		}
	};
	Node* root_;
	Node* smallest_;
	Node* biggest_;
	size_t size_;
public:
	class const_iterator {
		friend class ThreadedTree;
	protected:
		Node* cur_;
		const ThreadedTree* tree_;

	public:
		const_iterator()
		{
			cur_ = nullptr;
			tree_ = nullptr;
		}
		const_iterator(Node* node, const ThreadedTree* tree)
		{
			cur_ = node;
			tree_ = tree;
		}
		//iterator advances to next biggest value in the tree if the iterator is not currently at end(). The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the increment.
		const_iterator operator++(int)
		{
			const_iterator old = *this;
			if (this->cur_ != nullptr)
			{
				if (this->cur_->rightThread_ == true)
				{
					this->cur_ = this->cur_->right_;
				}
				else
				{
					this->cur_ = this->cur_->right_;

					while (this->cur_->leftThread_ == false)
					{
						this->cur_ = this->cur_->left_;
					}
				}
			}
			return old;
		}
		//iterator goes to the next smallest node in the tree. The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the decrement.
		const_iterator operator--(int)
		{
			const_iterator old = *this;
			if (this->cur_ != nullptr)
			{
				if (this->cur_->leftThread_ == true)
				{
					this->cur_ = this->cur_->left_;
				}
				else
				{
					this->cur_ = this->cur_->left_;
					while (this->cur_->rightThread_ == false)
					{
						this->cur_ = this->cur_->right_;
					}
				}
			}
			else
			{
				this->cur_ = this->tree_->biggest_;
			}
			return old;
		}
		//iterator advances to next biggest value in the tree if the iterator is not currently at end(). The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the increment.
		const_iterator operator++()
		{
			if (this->cur_ != nullptr)
			{
				if (this->cur_->rightThread_ == true)
				{
					this->cur_ = this->cur_->right_;
				}
				else
				{
					this->cur_ = this->cur_->right_;

					while (this->cur_->leftThread_ == false)
					{
						this->cur_ = this->cur_->left_;
					}
				}
			}
			return *this;
		}
		//iterator goes to the next smallest node in the tree. The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the decrement.
		const_iterator operator--()
		{
			if (this->cur_ != nullptr)
			{
				if (this->cur_->leftThread_ == true)
				{
					this->cur_ = this->cur_->left_;
				}
				else
				{
					this->cur_ = this->cur_->left_;
					while (this->cur_->rightThread_ == false)
					{
						this->cur_ = this->cur_->right_;
					}
				}
			}
			else
			{
				this->cur_ = this->tree_->biggest_;
			}
			return *this;
		}
		//returns a const reference to data in the node referred to by the iterator.
		const T& operator*() const
		{
			return cur_->data_;
		}
		//function returns true if rhs and current object refer to the same node
		bool operator==(const const_iterator& rhs) const
		{

			if (rhs.cur_ == this->cur_)
			{
				return true;
			}

			return false;
		}
		//function returns true if rhs and current object does not refer to the same node
		bool operator!=(const const_iterator& rhs) const
		{
			if (rhs.cur_ != this->cur_)
			{
				return true;
			}
			return false;
		}
		friend class ThreadedTree;
	};
	class iterator :public const_iterator {
	public:
		iterator() :const_iterator() {}
		iterator(Node* node, const ThreadedTree* tree) : const_iterator(node, tree) {};
		//returns a const reference to data in the node referred to by the iterator.
		const T& operator*() const
		{
			return this->cur_->data_;
		}
		//returns a const reference to data in the node referred to by the iterator.
		T& operator*()
		{
			return this->cur_->data_;
		}
		//iterator advances to next biggest value in the tree if the iterator is not currently at end(). The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the increment.
		iterator operator++(int)
		{
			iterator old = *this;
			if (this->cur_ != nullptr)
			{
				if (this->cur_->rightThread_ == true)
				{
					this->cur_ = this->cur_->right_;
				}
				else
				{
					this->cur_ = this->cur_->right_;

					while (this->cur_->leftThread_ == false)
					{
						this->cur_ = this->cur_->left_;
					}
				}
			}
			return old;
		}
		//iterator goes to the next smallest node in the tree. The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the decrement.
		iterator operator--(int)
		{
			iterator old = *this;
			if (this->cur_ != nullptr)
			{
				if (this->cur_->leftThread_ == true)
				{
					this->cur_ = this->cur_->left_;
				}
				else
				{
					this->cur_ = this->cur_->left_;
					while (this->cur_->rightThread_ == false)
					{
						this->cur_ = this->cur_->right_;
					}
				}
			}
			else
			{
				this->cur_ = this->tree_->biggest_;
			}
			return old;
		}
		//iterator advances to next biggest value in the tree if the iterator is not currently at end(). The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the increment.
		iterator operator++()
		{
			if (this->cur_ != nullptr)
			{
				if (this->cur_->rightThread_ == true)
				{
					this->cur_ = this->cur_->right_;
				}
				else
				{
					this->cur_ = this->cur_->right_;

					while (this->cur_->leftThread_ == false)
					{
						this->cur_ = this->cur_->left_;
					}
				}
			}
			return *this;
		}
		//iterator goes to the next smallest node in the tree. The iterator returned depends if it is prefix or postfix. prefix operator returns iterator to current node. postfix operator returns iterator to node before the decrement.
		iterator operator--()
		{
			if (this->cur_ != nullptr)
			{
				if (this->cur_->leftThread_ == true)
				{
					this->cur_ = this->cur_->left_;
				}
				else
				{
					this->cur_ = this->cur_->left_;
					while (this->cur_->rightThread_ == false)
					{
						this->cur_ = this->cur_->right_;
					}
				}
			}
			else
			{
				this->cur_ = this->tree_->biggest_;
			}
			return *this;
		}

		friend class ThreadedTree;
	};

	//constructor, creates empty ThreadedTree
	ThreadedTree()
	{
		root_ = nullptr;
		smallest_ = nullptr;
		biggest_ = nullptr;
		size_ = 0;
	}
	////The function inserts the data into the tree.
	void insert(const T& data)
	{

		if (root_ == nullptr) //if tree is empty
		{
			Node* newNode = new Node(data);
			root_ = newNode;
			size_++;
			smallest_ = root_;
			biggest_ = root_;
		}
		else //if is not empty
		{
			Node* cur = root_;
			Node* biggest = cur;
			Node* smallest = cur;

			while (true)
			{
				if (cur->data_ < data) //go right
				{
					smallest = cur;//update smallest thread

					if (cur->rightThread_ == false)
					{
						cur = cur->right_;//go right if right node is not a thread
					}
					else //add new node if right is a thread
					{
						if (biggest->data_ < data) //if this data is the biggest in a tree, make it right nullptr
						{
							biggest = nullptr;
						}
						Node* newNode = new Node(data, smallest, biggest);
						cur->right_ = newNode;
						cur->rightThread_ = false;
						size_++;
						if (biggest_->data_ < newNode->data_)//if this data is the biggest in a tree, assign it to biggest
						{
							biggest_ = newNode;
						}
						break;
					}
				}
				else //go left
				{
					biggest = cur;//update biggest thread

					if (cur->leftThread_ == false)
					{
						cur = cur->left_; //go left if left node is not a thread
					}

					else  //add new node if left is a thread
					{
						if (data < smallest->data_)//if this data is the smallest in a tree, make it right nullptr
						{
							smallest = nullptr;
						}
						Node* newNode = new Node(data, smallest, biggest);
						cur->left_ = newNode;
						cur->leftThread_ = false;
						size_++;
						if (newNode->data_ < smallest_->data_)//if this data is the smallest in a tree,assign it to smallest
						{
							smallest_ = newNode;
						}
						break;
					}
				}
			}
		}
	}
	
	//this function accepts a value, key and returns an iteratorr to the node containing that value. If key is not found, function returns end();
	iterator find(const T& key)
	{
		ThreadedTree<T>::iterator it;
		for (it = this->begin(); it != this->end(); it++)//iterate over tree untill the end of tree or until data is found
		{
			if (it.cur_->data_ == key)
			{
				return it;
			}
		}

		return it;

	}
	//this function accepts a value, key and returns an const_iterator to the node containing that value. If key is not found, function returns cend();
	const_iterator find(const T& key) const
	{
		ThreadedTree<T>::const_iterator it;
		for (it = this->cbegin(); it != this->cend(); it++)//iterate over tree untill the end of tree or until data is found
		{
			if (it.cur_->data_ == key)
			{
				return it;
			}
		}

		return it;
	}
	//returns the iterator to the smallest node in the tree
	iterator begin()
	{
		return iterator(this->smallest_, this);
	}
	//returns the iterator to the node after the largest node in the tree.
	iterator end()
	{
		return iterator(nullptr, this);
	}
	//returns the const iterator to the smallest node in the tree
	const_iterator cbegin()const
	{
		return const_iterator(this->smallest_, this);
	}
	//returns the const_iterator to the node after the largest node in the tree.
	const_iterator cend() const
	{
		return const_iterator(nullptr, this);
	}
	//This function returns the number of values stored in the tree
	int size() const
	{
		return size_;
	}
	//This function returns true if the tree has no values stored, false otherwise
	bool empty() const
	{
		if (size_ == 0)
		{
			return true;
		}
		return false;
	}

	//function for destructor
	void destructor(Node* node)
	{
		if (node->leftThread_ == false && node->left_ != nullptr)
		{
			destructor(node->left_);
		}
		if (node->rightThread_ == false && node->right_ != nullptr)
		{
			destructor(node->right_);
		}

		delete node;
		node = nullptr;

	}
	//make tree empty
	~ThreadedTree()
	{
		if (root_ != nullptr)
		{
			destructor(root_);
		}
	}
};
