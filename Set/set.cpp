#include "set.h"


	/********************* ______________________________**********************
	**********************|                              |*********************
	**********************|  START_OF_ITERATOR-METHODS   |*********************
	**********************|______________________________|*********************
	**********************                                *********************/

	set::iterator::iterator() {
		this->data = nullptr;
	}

	set::iterator::iterator(node* x) {
		this->data = x;
	}

	set::iterator& set::iterator::operator ++() {
		if (this->data->left == nullptr && this->data->right == nullptr
				&& this->data->parent == nullptr && this->data->key == 0) {
			return *this;
		}
		if (this->data->next()->parent == nullptr) {
			this->data = this->data->right;
		} else {
			this->data = this->data->next();
		}
		return *this;
	}

	set::iterator set::iterator::operator ++(int) {
		if (this->data->left == nullptr && this->data->right == nullptr
				&& this->data->parent == nullptr && this->data->key == 0) {
			return *this;
		}
		iterator* it = new iterator(this->data->copyHelper(this->data));
		if (this->data->next()->parent == nullptr) {
			this->data = this->data->right;
		} else {
			this->data = this->data->next();
		}
		return *(it);
	}

	set::iterator& set::iterator::operator --() {
		if (this->data->left == nullptr && this->data->right == nullptr
				&& this->data->parent == nullptr && this->data->key == 0) {
			return *this;
		}
		if (this->data->prev()->parent == nullptr) {
			this->data = this->data->left;
		} else {
			this->data = this->data->prev();
		}
		return *this;
	}

	set::iterator set::iterator::operator --(int) {
		if (this->data->left == nullptr && this->data->right == nullptr
				&& this->data->parent == nullptr && this->data->key == 0) {
			return *this;
		}
		iterator* it = new iterator(this->data->copyHelper(this->data));
		if (this->data->prev()->parent == nullptr) {
			this->data = this->data->left;
		} else {
			this->data = this->data->prev();
			}
		return *it;
	}

	int& set::iterator::operator *() const {
		return (this->data->key);
	}

	bool set::iterator::operator ==(iterator const& it) const {
		return (this->data == it.data)? true: false;
	}

	bool set::iterator::operator !=(iterator const& it) const {
		return (this->data != it.data)? true: false;
	}



	/********************* ______________________________**********************
	**********************|                              |*********************
	**********************|  END_OF_ITERATOR-METHODS     |*********************
	**********************|______________________________|*********************
	**********************                                *********************/


	/*********************  _________________________**********************
	**********************|                          |*********************
	**********************|  START_OF_NODE-METHODS   |*********************
	**********************|__________________________|*********************
	**********************                            *********************/

	set::node::node() {
		this->left = nullptr;
		this->right = nullptr;
		this->parent = nullptr;
		this->key = 0;
	}

	set::node::node(node* left, node* right, node* parent, int key) {
		this->left = left;
		this->right = right;
		this->parent = parent;
		this->key = key;
	}

	set::node::~node() {
		if (this->left != nullptr) {
			delete this->left;
		}
		if (this->right != nullptr) {
			delete this->right;
		}
	}

	set::node* set::node::minimum() {
		if (this->left == nullptr) {
			return this;
		}
		return this->left->minimum();
	}

	set::node* set::node::maximum() {
		if (this->right == nullptr) {
			return this;
		}
		return this->right->maximum();
	}

	set::node* set::node::next() {
		if (this->right != nullptr) {
			return this->right->minimum();
		}
		node* curparent = this->parent;
		node* cur = this;
		while (curparent != nullptr && cur == curparent->right) {
			cur = curparent;
			curparent = curparent->parent;
		}
		return curparent;
	}

	set::node* set::node::prev() {
		if (this->left != nullptr) {
			return this->left->maximum();
		}
		node* curparent = this->parent;
		node* cur = this;
		while (curparent != nullptr && cur == curparent->left) {
			cur = curparent;
			curparent = curparent->parent;
		}
		return curparent;
	}

	set::node* set::node::get_first() {
		while (this->left != nullptr) {
			return this->left->get_first();
		}
		return this;
	}

	set::node* set::node::get_last() {
		while (this->right != nullptr) {
			return this->right->get_last();
		}
		return this;
	}

	void set::node::replaceByChild(node* child) {
		if (this->left != child && this->right != child) {
			return;
		}

		child->parent = this->parent;
		if (this->parent->left == this) {
			this->parent->left = child;
		} else {
			this->parent->right = child;
		}

		// Set "this"'s children as "nullptr" (needed for destructor, details of implemention)
		this->left = nullptr;
		this->right = nullptr;
	}

	// @param: toCopy, A constant pointer to a node.
	// Function, that makes a real copy of the given node and its "children".
	set::node* set::node::copyHelper(const node *toCopy){
		if (toCopy == nullptr) {
			return nullptr;
		}
		node* copyNode = new node(nullptr, nullptr, nullptr, toCopy->key);
		if (toCopy->left != nullptr) {
			copyNode->left = copyHelper(toCopy->left);
			copyNode->left->parent = copyNode;
		}
		if (toCopy->right != nullptr) {
			copyNode->right = copyHelper(toCopy->right);
			copyNode->right->parent = copyNode;
		}
		return copyNode;
	}

	void set::node::insertHelper(int k) {
		if (k > this->key) {
			if (this->right != nullptr) {
				this->right->insertHelper(k);
			} else {
				this->right = new node(nullptr, nullptr, this, k);
				}
		} else if (k < this->key){
			if (this->left != nullptr) {
				this->left->insertHelper(k);
			} else {
				this->left = new node(nullptr, nullptr, this, k);
			}
		} else {
			return;
		}
	}

	set::node* set::node::findHelper(int k) {
		if (k == this->key) {
			return this;
		}
		if (k < this->key) {
			if (this->left != nullptr) {
				return this->left->findHelper(k);
			}
			return nullptr;
		} else {
			if (this->right != nullptr) {
				return this->right->findHelper(k);
			}
			return nullptr;
		}
	}

	void set::node::eraseHelper(node* cur) {
		if (cur->left != nullptr && cur->right != nullptr) {
			node* next = cur->next();
			cur->key = next->key;
			next->replaceByChild(next->right);
			delete next;
		} else {
			if (cur->left != nullptr) {
				cur->replaceByChild(cur->left);
				delete cur;
			} else if (cur->right != nullptr) {
				cur->replaceByChild(cur->right);
				delete cur;
			} else {
				if (cur->parent->left == cur) {
					cur->parent->left = nullptr;
				} else {
					cur->parent->right = nullptr;
				}
			}
		}
	}

	/********************** ________________________************************
	 **********************|                        |***********************
	 **********************|  END_OF_NODE-METHODS   |***********************
	 **********************|________________________|***********************
	 **********************                         ************************/


	/********************* ______________________________**********************
	**********************|                              |*********************
	**********************|  START_OF_SET-METHODS        |*********************
	**********************|______________________________|*********************
	**********************                                *********************/


	// nullptr-constructor
	set::set() {
		this->root = new node;
	}

	// @param: toCopy, A constant link of a set.
	// Copy-constructor, that makes a real copy of the fiven set.
	set::set(set const& toCopy) {
		root = root->copyHelper(toCopy.root);
	}

	// @param: x, A constant link to a set->
	// Assignment operator, makes a link of the given constant set->
	set& set::operator =(set const& x) {
		this->root = x.root;
		return *this;
	}

	set::~set() {
		if (this->root != nullptr) {
			delete root;
		}
	}

	void set::insert(int k) {
		if (this->root->left != nullptr) {
			this->root->left->insertHelper(k);
		} else {
			this->root->left = new node(nullptr, nullptr, this->root, k);
		}
	}

	set::iterator set::find(int k) {
		iterator* it;
		if (this->root->left != nullptr) {
			it = new iterator(this->root->left->findHelper(k));
			return *it;
		}
		it = new iterator();
		return *it;

	}

	void set::erase(iterator it) {
		if (this->root->left != nullptr) {
			this->root->left->eraseHelper(it.data);
		}
	}


	set::iterator set::begin() {
		iterator* it;
		if (this->root->left != nullptr) {
			it = new iterator(this->root->left->get_first());
		} else {
			it = new iterator();

		}
		return *it;
	}

	set::iterator set::end() {
		iterator* it;
		if (this->root->left != nullptr) {
			it = new iterator(this->root->left->get_last()->right);
		} else {
			it = new iterator();
		}
		return *it;
	}

	/********************* ______________________________**********************
	**********************|                              |*********************
	**********************|  END_OF_SET-METHODS          |*********************
	**********************|______________________________|*********************
	**********************                                *********************/

