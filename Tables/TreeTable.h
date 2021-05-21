#include <iostream>

template<class TKey>
class TreeNode
{
public:
	TKey* keys;
	int t;
	TreeNode** C;
	int n;
	bool leaf;

	TreeNode(int temp, bool bool_leaf);
	void insertNonFull(TKey k);
	void splitChild(int i, TreeNode* y);
	void print();
	TreeNode* search(TKey k);
	void deletion(TKey k);
	void removeFromLeaf(int idx);
	void removeFromNonLeaf(int idx);
	TKey getPredecessor(int idx);
	TKey getSuccessor(int idx);
	void merge(int idx);
	void fill(int idx);
	void borrowFromPrev(int idx);
	void borrowFromNext(int idx);
	int findKey(TKey k);
};

template<class TKey>
TreeNode<TKey>::TreeNode(int t1, bool leaf1)
{
	t = t1;
	leaf = leaf1;

	keys = new TKey[2 * t - 1];
	C = new TreeNode * [2 * t];

	n = 0;
}

template<class TKey>
void TreeNode<TKey>::print()
{
	int i;
	for (i = 0; i < n; i++) {
		if (leaf == false)
			C[i]->print();
		std::cout << keys[i] << "\n";
	}

	if (leaf == false)
		C[i]->print();
}

template<class TKey>
TreeNode<TKey>* TreeNode<TKey>::search(TKey k)
{
	int i = 0;
	while (i < n && k > keys[i])
		i++;

	if (keys[i] == k)
		return this;

	if (leaf == true)
		return NULL;

	return C[i]->search(k);
}

template<class TKey>
void TreeNode<TKey>::fill(int idx) {
	if (idx != 0 && C[idx - 1]->n >= t)
		borrowFromPrev(idx);

	else if (idx != n && C[idx + 1]->n >= t)
		borrowFromNext(idx);

	else {
		if (idx != n)
			merge(idx);
		else
			merge(idx - 1);
	}
	return;
}

template<class TKey>
void TreeNode<TKey>::borrowFromPrev(int idx) {
	TreeNode<TKey>* child = C[idx];
	TreeNode<TKey>* sibling = C[idx - 1];

	for (int i = child->n - 1; i >= 0; --i)
		child->keys[i + 1] = child->keys[i];

	if (!child->leaf) {
		for (int i = child->n; i >= 0; --i)
			child->C[i + 1] = child->C[i];
	}

	child->keys[0] = keys[idx - 1];

	if (!child->leaf)
		child->C[0] = sibling->C[sibling->n];

	keys[idx - 1] = sibling->keys[sibling->n - 1];

	child->n += 1;
	sibling->n -= 1;

	return;
}

template <class TKey>
void TreeNode<TKey>::borrowFromNext(int idx) {
	TreeNode<TKey>* child = C[idx];
	TreeNode<TKey>* sibling = C[idx + 1];

	child->keys[(child->n)] = keys[idx];

	if (!(child->leaf))
		child->C[(child->n) + 1] = sibling->C[0];

	keys[idx] = sibling->keys[0];

	for (int i = 1; i < sibling->n; ++i)
		sibling->keys[i - 1] = sibling->keys[i];

	if (!sibling->leaf) {
		for (int i = 1; i <= sibling->n; ++i)
			sibling->C[i - 1] = sibling->C[i];
	}

	child->n += 1;
	sibling->n -= 1;

	return;
}

template<class TKey>
int TreeNode<TKey>::findKey(TKey k) {
	int idx = 0;
	while (idx < n && keys[idx] < k)
		++idx;
	return idx;
}

template<class TKey>
void TreeNode<TKey>::deletion(TKey k) {
	int idx = findKey(k);

	if (idx < n && keys[idx] == k) {
		if (leaf)
			removeFromLeaf(idx);
		else
			removeFromNonLeaf(idx);
	}
	else {
		if (leaf) {
			std::cout << "The key " << k << " is does not exist in the tree\n";
			return;
		}

		bool flag = ((idx == n) ? true : false);

		if (C[idx]->n < t)
			fill(idx);

		if (flag && idx > n)
			C[idx - 1]->deletion(k);
		else
			C[idx]->deletion(k);
	}
	return;
}

template<class TKey>
void TreeNode<TKey>::removeFromLeaf(int idx) {
	for (int i = idx + 1; i < n; ++i)
		keys[i - 1] = keys[i];

	n--;

	return;
}

template<class TKey>
void TreeNode<TKey>::removeFromNonLeaf(int idx) {
	TKey k = keys[idx];

	if (C[idx]->n >= t) {
		TKey pred = getPredecessor(idx);
		keys[idx] = pred;
		C[idx]->deletion(pred);
	}

	else if (C[idx + 1]->n >= t) {
		TKey succ = getSuccessor(idx);
		keys[idx] = succ;
		C[idx + 1]->deletion(succ);
	}

	else {
		merge(idx);
		C[idx]->deletion(k);
	}
	return;
}

template<class TKey>
TKey TreeNode<TKey>::getPredecessor(int idx) {
	TreeNode<TKey>* cur = C[idx];
	while (!cur->leaf)
		cur = cur->C[cur->n];

	return cur->keys[cur->n - 1];
}

template<class TKey>
TKey TreeNode<TKey>::getSuccessor(int idx) {
	TreeNode<TKey>* cur = C[idx + 1];
	while (!cur->leaf)
		cur = cur->C[0];

	return cur->keys[0];
}

template<class TKey>
void TreeNode<TKey> ::merge(int idx) {
	TreeNode<TKey>* child = C[idx];
	TreeNode<TKey>* sibling = C[idx + 1];

	child->keys[t - 1] = keys[idx];

	for (int i = 0; i < sibling->n; ++i)
		child->keys[i + t] = sibling->keys[i];

	if (!child->leaf) {
		for (int i = 0; i <= sibling->n; ++i)
			child->C[i + t] = sibling->C[i];
	}

	for (int i = idx + 1; i < n; ++i)
		keys[i - 1] = keys[i];

	for (int i = idx + 2; i <= n; ++i)
		C[i - 1] = C[i];

	child->n += sibling->n + 1;
	n--;

	delete (sibling);
	return;
}

template<class TKey>
void TreeNode<TKey>::insertNonFull(TKey k)
{
	int i = n - 1;

	if (leaf == true) {
		while (i >= 0 && keys[i] > k)
		{
			keys[i + 1] = keys[i];
			i--;
		}

		keys[i + 1] = k;
		n = n + 1;
	}
	else {
		while (i >= 0 && keys[i] > k)
			i--;

		if (C[i + 1]->n == 2 * t - 1) {
			splitChild(i + 1, C[i + 1]);

			if (keys[i + 1] < k)
				i++;
		}
		C[i + 1]->insertNonFull(k);
	}
}

template<class TKey>
void TreeNode<TKey>::splitChild(int i, TreeNode<TKey>* y)
{
	TreeNode* z = new TreeNode(y->t, y->leaf);
	z->n = t - 1;

	for (int j = 0; j < t - 1; j++)
		z->keys[j] = y->keys[j + t];

	if (y->leaf == false) {
		for (int j = 0; j < t; j++)
			z->C[j] = y->C[j + t];
	}

	y->n = t - 1;
	for (int j = n; j >= i + 1; j--)
		C[j + 1] = C[j];

	C[i + 1] = z;

	for (int j = n - 1; j >= i; j--)
		keys[j + 1] = keys[j];

	keys[i] = y->keys[t - 1];
	n = n + 1;
}

template<class TKey>
class BTree
{
	TreeNode<TKey>* root;
	int t; //count of nodes При построении B-дерева применяется фактор t, 
	//который называется минимальной степенью. Каждый узел, кроме корневого, должен иметь, как 
	//минимум t – 1, и не более 2t – 1 ключей.
public:
	BTree(int temp)
	{
		root = NULL;
		t = temp;
	}

	void print()
	{
		if (root != NULL)
			root->print();
	}

	TreeNode<TKey>* search(TKey k)
	{
		return (root == NULL) ? NULL : root->search(k);
	}

	void insert(TKey k)
	{
		if (root == NULL)
		{
			root = new TreeNode<TKey>(t, true);
			root->keys[0] = k;
			root->n = 1;
		}
		else {
			if (root->n == 2 * t - 1)
			{
				TreeNode<TKey>* s = new TreeNode<TKey>(t, false);

				s->C[0] = root;

				s->splitChild(0, root);

				int i = 0;
				if (s->keys[0] < k)
					i++;
				s->C[i]->insertNonFull(k);

				root = s;
			}
			else
				root->insertNonFull(k);
		}
	}

	void deletion(TKey k) {
		if (!root) {
			std::cout << "The tree is empty\n";
			return;
		}
		root->deletion(k);
		if (root->n == 0) {
			TreeNode<TKey>* tmp = root;
			if (root->leaf)
				root = NULL;
			else
				root = root->C[0];

			delete tmp;
		}
		return;
	}
};