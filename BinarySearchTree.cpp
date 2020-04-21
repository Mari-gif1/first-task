/******************************************************************************

							  Online C++ Compiler.
			   Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <iostream>
#include <stack>
#include <queue>
using namespace std;
template<class T>
struct node
{
	T key;
	node* left;
	node* right;
	node(T k) :key(k), left(nullptr), right(nullptr) {}
};
template<class T>
class BST
{
public:
	BST() :root(nullptr) {}
	BST(const T& k) :root(new node(k)) {}
	BST(const BST&);
	BST& operator=(const BST&);
	BST(BST&&);
	BST& operator=(BST&&);
	void insert(const T&);
	node<T>* search(const T&);
	node<T>* minItem();
	node<T>* maxItem();
	void level_order_traversal();
	void displaybst();
	void remove(const T&);
	void spiral_traversal();
	~BST()
	{
		makeEmpty(root);
		root = nullptr;
	};

private:
	node<T>* insertItem(const T&, node<T>*);
	node<T>* searchItem(const T&, node<T>*);
	void makeEmpty(node<T>*);
	node<T>* findMin(node<T>*);
	node<T>* findMax(node<T>*);
	void inorder(node<T>*);
	node<T>* removeItem(const T&, node<T>*);
	node<T>* root;
};

template<class T>
BST<T>::BST(const BST& obj)
{
	queue<node<T>*> q1;
	queue<node<T>*> q2;
	q1.emplace(obj.root);
	root = new node<T>(obj.root->key);
	q2.emplace(root);
	node<T>* p1, *p2;
	while (!q1.empty())
	{
		p1 = q1.front();
		p2 = q2.front();
		q1.pop();
		q2.pop();
		if (p1->left)
		{
			q1.emplace(p1->left);
			p2->left = new node<T>(p1->left->key);
			q2.emplace(p2->left);
		}
		if (p1->right)
		{
			q1.emplace(p1->right);
			p2->right = new node<T>(p1->right->key);
			q2.emplace(p2->right);
		}
	}
}

template<class T>
BST<T>& BST<T>::operator=(const BST& obj)
{
	if (this == &obj)
		return *this;
	makeEmpty(root);
	queue<node<T>*> q1;
	queue<node<T>*> q2;
	q1.emplace(obj.root);
	root = new node<T>(obj.root->key);
	q2.emplace(root);
	node<T>* p1, *p2;
	while (!q1.empty())
	{
		p1 = q1.front();
		p2 = q2.front();
		q1.pop();
		q2.pop();
		if (p1->left)
		{
			q1.emplace(p1->left);
			p2->left = new node<T>(p1->left->key);
			q2.emplace(p2->left);
		}
		if (p1->right)
		{
			q1.emplace(p1->right);
			p2->right = new node<T>(p1->right->key);
			q2.emplace(p2->right);
		}
	}
	return *this;
}

template<class T>
BST<T>::BST(BST&& obj)
{
	root = obj.root;
	obj.root = nullptr;
}

template<class T>
BST<T>& BST<T>::operator=(BST&& obj)
{
	if (this == &obj)
		return *this;
	makeEmpty(root);
	root = obj.root;
	obj.root = nullptr;
	return *this;
}

template<class T>
node<T>* BST<T>::insertItem(const T& k, node<T>* n)
{
	if (n == nullptr)
	{
		n = new node<T>(k);
		return n;
	}
	if (k <= n->key)
	{
		n->left = insertItem(k, n->left);
	}
	else
	{
		n->right = insertItem(k, n->right);
	}
	return n;
}

template<class T>
void BST<T>::insert(const T& key)
{
	root = insertItem(key, root);
}

template<class T>
node<T>* BST<T>::removeItem(const T& value, node<T>* n) {
	node<T>* p;
	if (n == nullptr)
		return n;
	else if (value < n->key)
		n->left = removeItem(value, n->left);
	else if (value > n->key)
		n->right = removeItem(value, n->right);
	else if (n->left && n->right)
	{
		p = findMin(n->right);
		n->key = p->key;
		n->right = removeItem(n->key, n->right);
	}
	else
	{
		p = n;
		if (n->left == nullptr)
			n = n->right;
		else if (n->right == nullptr)
			n = n->left;
		delete p;
	}

	return n;
}

template<class T>
void BST<T>::remove(const T& el)
{
	root = removeItem(el, root);
}

template<class T>
node<T>* BST<T>::searchItem(const T& key, node<T>* n)
{
	if (n == nullptr || n->key == key)
		return n;
	if (key <= n->key)
		return searchItem(key, n->left);
	else
		return searchItem(key, n->right);
}

template<class T>
node<T>* BST<T>::search(const T& key)
{
	return searchItem(key, root);
}

template<class T>
void BST<T>::makeEmpty(node<T>* n)
{
	if (n)
	{
		makeEmpty(n->left);
		makeEmpty(n->right);
		delete n;
	}
}

template<class T>
node<T>* BST<T>::findMin(node<T>* n)
{
	if (n == nullptr) return n;
	while (n->left)
	{
		n = n->left;
	}
	return n;
}

template<class T>
node<T>* BST<T>::minItem()
{
	return findMin(root);
}

template<class T>
node<T>* BST<T>::findMax(node<T>* n)
{
	if (n == nullptr) return n;
	while (n->right)
	{
		n = n->right;
	}
	return n;
}

template<class T>
node<T>* BST<T>::maxItem()
{
	return findMax(root);
}

template<class T>
void BST<T>::inorder(node<T>* n)
{
	if (root)
	{
		inorder(n->left);
		cout << n->key << " ";
		inorder(n->right);
	}
}

template<class T>
void BST<T>::displaybst()
{
	inorder(root);
}

template<class T>
void BST<T>::level_order_traversal()
{
	queue<node<T>*> q;
	q.emplace(root);
	while (!q.empty())
	{
		node<T>* p = q.front();
		cout << p->key << " ";
		q.pop();
		if (p->left)
			q.emplace(p->left);
		if (p->right)
			q.emplace(p->right);
	}
}

template<class T>
void BST<T>::spiral_traversal()
{
	stack<node<T>*> s1;
	stack<node<T>*> s2;
	bool b = false;
	s1.push(root);
	node<T>* p = nullptr;
	while (true)
	{
		while (!s1.empty() && (!b))
		{
			p = s1.top();
			s1.pop();
			cout << p->key << " ";
			if (p->left)
				s2.push(p->left);
			if (p->right)
				s2.push(p->right);
		}
		if (s1.empty() && s2.empty())
			break;
		if (!b)
		{
			b = true;
			cout << '\n';
			continue;
		}
		while (!s2.empty() && b)
		{
			p = s2.top();
			s2.pop();
			cout << p->key << " ";
			if (p->right)
				s1.push(p->right);
			if (p->left)
				s1.push(p->left);
		}
		if (s1.empty() && s2.empty())
			break;
		if (b)
		{
			b = false;
			cout << '\n';
		}
	}
}
int main()
{
	BST<int> t;
	t.insert(8);
	t.insert(6);
	t.insert(9);
	t.insert(4);
	t.insert(7);
	t.insert(11);
	t.insert(2);
	t.insert(8);
	t.insert(10);
	t.insert(13);
	t.insert(12);
	t.spiral_traversal();
	cout << '\n';
	t.level_order_traversal();
	cout << '\n';
	BST<int> b(t);
	b.level_order_traversal();
	cout << '\n';
	node<int>* p = b.maxItem();
	if (p)
		cout << p->key << '\n';
	BST<int> b1;
	b1 = t;
	b1.level_order_traversal();
	cout << '\n';
	t.remove(8);
	t.level_order_traversal();
	cout << '\n';
}
