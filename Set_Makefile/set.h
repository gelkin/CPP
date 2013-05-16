#ifndef SET_H
#define SET_H


#ifndef nullptr
#include <cstddef>
#define nullptr NULL
#endif

struct set {

private:
	struct node;

public:
	struct iterator {
		friend struct set;

		iterator();
		// ~iterator();

		iterator& operator++();
		iterator operator++(int);
		iterator& operator--();
		iterator operator--(int);
		int& operator*() const;
		bool operator==(iterator const&) const;
		bool operator!=(iterator const&) const;

	private:
		iterator(node*);
		node* data;
	};

	set();
	set(set const&);
	~set();
	set& operator =(set const&);
	void insert(int);
	iterator find(int);
	void erase(iterator);

	iterator begin();
	iterator end();

private:
	struct node {
		node();
		node(node*, node*, node*, int);
		~node();

		node* minimum();
		node* maximum();
		node* next();
		node* prev();
		node* get_first();
		node* get_last();
		void replaceByChild(node*);

		void insertHelper(int);
		node* findHelper(int);
		void eraseHelper(node*);
		node* copyHelper(const node*);

		node* left;
		node* right;
		node* parent;
		int key;
	};

	node* root;
};

#endif // SET_H
