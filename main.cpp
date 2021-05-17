//#include "Table.h"
//#include "ArrayTable.h"
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <Windows.h>
#include <string>
#include <algorithm>
#include <iterator>
#include <queue>

const int TTabMaxSize = 6;
enum SortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

template <class TKey, class TVal>
class TabRecord
{
protected:
	//virtual void Print(std::ostream& os) { os << Key << " " << *pValue; }
public:
	TabRecord(TKey k = "", TVal* pVal = NULL) { Key = k; pValue = pVal; }
	~TabRecord() {};
	void SetKey(TKey k) { Key = k; }
	TKey GetKey(void) { return Key; }
	void SetValuePtr(TVal p) { pValue = p; }
	TVal GetValuePtr(void) { return pValue; }
	//virtual TVal* GetCopy() {}
	/*TabRecord& operator = (TabRecord& tr)
	{
		Key = tr.Key;
		pValue = tr.pValue;
		return *this;
	}*/
	virtual int operator==(const TabRecord& tr) { return Key == tr.Key; }
	virtual int operator>(const TabRecord& tr) { return Key > tr.Key; }
	virtual int operator<(const TabRecord& tr) { return Key < tr.Key; }
	TKey Key;
	TVal* pValue;
	//friend class ArrayTable;
	//friend class SortTable;
	//friend class TreeTable;
	//friend class HashTable;
};

template<class TKey, class TVal>
class Table : public TabRecord<TKey, TVal>
{
protected:
	int DataCount;
	int efficienty;
public:
	Table() :DataCount(0), efficienty(0) {}
	virtual ~Table() {};
	int GetDataCount() const { return DataCount; }
	int GetEfficienty() const { return efficienty; }
	bool IsEmpty() const { return DataCount == 0; }
	bool IsTabEnded() const { return DataCount == TTabMaxSize; }
	virtual bool IsFull() const = 0;
	virtual int FindRecord(TKey k) = 0;
	virtual void InsRecord(TKey k, TVal pVal) = 0;
	virtual void DelRecord(TKey k) = 0;
	virtual int Reset(void) = 0;
	// virtual int IsTabEnded(void) = 0;
	virtual int GoNext(void) = 0;
	virtual TKey GetKey(void) const = 0;
	virtual TVal GetValuePtr(void) const = 0;
	virtual void print(void) = 0;
	int SetRecCode(int k) { return k; }
	friend std::ostream& operator<<(std::ostream& os, Table& tb)
	{
		std::cout << "Table: \n";
		for (tb.Reset(); !tb.IsTabEnded(); tb.GoNext())
		{
			//os << "Key: " << tb.GetKey() << " Value: " << tb.GetValuePtr() << "\n";
		}
		return os;
	}
	virtual void InsertSort() = 0;
	virtual void MergeSort(int first, int last) = 0;
	virtual void QuickSort(int left, int right) = 0;
	const int TabOK{ 0 };
	const int TabEmpty{ -101 };
	const int TabFull{ -102 };
	const int TabNoRec{ -103 };
	const int TabRecObl{ -104 };
	const int TabNoMem{ -105 };
};

template<class TKey, class TVal>
class ArrayTable : public Table<TKey, TVal>
{
	using Table<TKey, TVal>::DataCount;
	using Table<TKey, TVal>::TabFull;
	using Table<TKey, TVal>::SetRecCode;
	using Table<TKey, TVal>::TabOK;
	using Table<TKey, TVal>::TabNoRec;
	using Table<TKey, TVal>::IsEmpty;
	using Table<TKey, TVal>::efficienty;
protected:
	TabRecord<TKey, TVal> rec;
	//int TabSize;
	int CurrPos;
	//std::vector<std::pair<TKey, TVal>> pRecs;
public:
	std::vector<std::pair<TKey, TVal>> pRecs;
	int TabSize;
	enum DataPos { FIRST_POS, CURRENT_POS, LAST_POS };
	ArrayTable(int Size = 6) : Table<TKey, TVal>()
	{
		TabSize = Size;
		CurrPos = 0;
	}
	virtual ~ArrayTable()
	{
		pRecs.clear();
	}

	virtual bool IsFull() const
	{
		return 0;
	}

	int GetTabSize() const
	{
		return TabSize;
	}

	virtual TKey GetKey(void) const
	{
		return GetKey(CURRENT_POS);
	}

	virtual int FindRecord(TKey k)
	{
		k += " ";
		int i = 7;
		for (i = 0; i < pRecs.size(); ++i)
			if (pRecs[i].first == k) 
			{
				std::cout << "Найдена запись: " << pRecs[i].first << " ";
				for (int n(0); n < pRecs[i].second.size(); ++n)
				{
					std::cout << pRecs[i].second[n] << " ";
				}
				std::cout << " под номером " << i << "\n";
				break;
			}
		return i;
				/*int i;
		SetRecCode(TabOK);
		for (i = 0; i < pRecs.size(); ++i)
			if (pRecs[i].first == k)
				break;
		efficienty = i + 1;
		if (i < DataCount)
		{
			CurrPos = i;
			return pRecs[i].second;
		}
		SetRecCode(TabNoRec);*/
		//return NULL;
	}

	virtual TKey GetKey(DataPos mode) const
	{
		int pos = -1;
		if (!IsEmpty())
		{
			switch (mode)
			{
			case FIRST_POS:
				pos = 0;
				break;
			case LAST_POS:
				pos = DataCount - 1;
				break;
			default:
				pos = CurrPos;
				break;
			}
		}
		return (pos == -1) ? std::string("") : pRecs[pos].first;
	}

	virtual TVal GetValuePtr() const
	{
		return GetValuePtr(CURRENT_POS);
	}

	virtual TVal GetValuePtr(DataPos mode) const
	{
		int pos = -1;
		if (!IsEmpty())
		{
			switch (mode)
			{
			case FIRST_POS:
				pos = 0;
				break;
			case LAST_POS:
				pos = DataCount - 1;
				break;
			default:
				pos = CurrPos;
				break;
			}
		}
		return (pos == -1) ? /*NULL*/pRecs[pos].second : pRecs[pos].second;
	}

	virtual void InsRecord(TKey k, TVal pVal)
	{
		if (IsFull())
			SetRecCode(TabFull);
		else
		{
			//pRecs[DataCount] = //new TAbRecord(k, pVal);
			//std::cout << pRecs.size();
			pRecs.reserve(++TabSize);
			pRecs.push_back(std::pair<TKey, TVal>(k, pVal));
			DataCount++;
			SetRecCode(TabOK);
		}
	}

	virtual void DelRecord(TKey k)
	{
		int temp = FindRecord(k);

		if (temp == 7)
		{
			std::cout << "Записи не существует";
			SetRecCode(TabNoRec);
		}
		else
		{
			SetRecCode(TabOK);
			pRecs.erase(pRecs.begin() + temp);
			std::cout << "Запись под номером " << temp << " удалена\n";
		}
	}

	virtual int Reset(void)
	{
		CurrPos = 0;
		return IsTabEnded();
	}

	virtual int IsTabEnded(void) const
	{
		return CurrPos >= DataCount;
	}

	virtual int GoNext(void)
	{
		if (!IsTabEnded()) CurrPos++;
		return IsTabEnded();
	}

	virtual int SetCurrentPos(int pos)
	{
		CurrPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
		return IsTabEnded();
	}

	int GetCurrentPos(void) const
	{
		return CurrPos;
	}
	virtual void print(void)
	{
		for (int i(0); i < pRecs.size(); ++i)
		{
			std::cout << pRecs[i].first << " ";
			for (int n(0); n < pRecs[i].second.size(); ++n)
			{
				std::cout << pRecs[i].second[n] << " ";
			}
			std::cout << "\n";
		}
	}
	virtual void InsertSort()
	{
		char cur[30];
		TabSize /= 2;
		std::vector<std::pair<TKey, TVal>> tmp;
		for (int i = 0; i < TabSize; ++i)
			tmp.push_back(std::pair<TKey, TVal>(pRecs[i].first, pRecs[i].second));
		int j = 0;

		for (int i = 1; i < TabSize; ++i)
		{
			strcpy_s(cur, pRecs[i].first.c_str());
			for (j = i - 1; j >= 0 && strcmp(pRecs[j].first.c_str(), cur) > 0; --j)
			{
				{
					pRecs[j + 1].first = pRecs[j].first;
					//pRecs[j + 1].second = pRecs[j].second;
				}
			}
			pRecs[j + 1].first = cur;
		}

		int k;
		for (int i = 0; i < TabSize; ++i)
		{
			for (int j = 0; j < TabSize; ++j)
			{
				if (tmp[i].first == pRecs[j].first)
				{
					k = 0;
					for (int in : tmp[i].second)
					{
						pRecs[j].second[k] = in;
						k++;
					}
					k = 0;
				}
			}
		}
	}

	virtual void MergeSort(int low, int high)
	{
		int mid = 0;
		if (low < high)
		{
			mid = ((low + high) / 2);
			MergeSort(low, mid);
			MergeSort(mid + 1, high);
			MergeA(low, mid, high);
		}
	}
	void MergeA(int low, int mid, int high)
	{
		int i = low, j = mid + 1, k = low;
		std::string Temp[6];

		while (i <= mid && j <= high)
		{
			if (pRecs[i].first < pRecs[j].first)
			{
				Temp[k].assign(pRecs[i].first);
				i++;
			}
			else
			{
				Temp[k].assign(pRecs[j].first);
				j++;
			}
			k++;
		}
		if (i > mid)
		{
			for (int h = j; h <= high; h++)
			{
				Temp[k].assign(pRecs[h].first);
				k++;
			}
		}
		else
			for (int h = i; h <= mid; h++)
			{
				Temp[k].assign(pRecs[h].first);
				k++;
			}
		std::cout << "\nВывод: ";
		for (int i = 0; i <= Temp[i].size(); i++)
		{
			std::cout << Temp[i] << "\n";
		}
		std::cout << "\n";
		for (int i = 0; i <= high; i++)
		{
			pRecs[i].first.assign(Temp[i]);
		}
	}

	virtual void QuickSort(int left, int right)
	{
		int i, j, p;
		i = left;
		j = right;
		//char tmp[100];

		while (i != j) 
		{
			if ((strcmp(pRecs[i].first.c_str(), pRecs[j].first.c_str()) > 0) != (i < j))
			//if ( i <= j)
			{
				std::cout << i << " " << j << "\n";
				swap(pRecs[i], pRecs[j]);

				p = i;
				i = j;

				if (p < j)
					j = p + 1;
				else j = p - 1;
			}
			else
			{
				if (i < j) j--;
				else j++;
			}
		}

		if (left < i - 1)
			QuickSort(left, i);
		if (i + 1 < right)
			QuickSort(i + 1, right);
	}

};

template <class TKey, class TVal>
class SortTable : public ArrayTable <TKey, TVal>
{
protected:
	SortMethod sortMethod;
	ArrayTable<TKey, TVal> pArr;
	void SortData(void);
public:
	SortTable(int Size = TTabMaxSize) : ArrayTable<TKey, TVal>(Size) { }
	//SortTable(const ArrayTable<TKey, TVal>& tab) { *this = tab; }
};

template <class TKey, class TVal>
class HashTable 
{
	std::vector<std::list<std::pair<TKey, TVal>>> pRecs;
	int size;
	int capacity;
	int m;
public:
	HashTable(int cap)
	{
		capacity = cap;
		size = 0;
		pRecs.reserve(6);
	}
	~HashTable()
	{
		pRecs.clear();
	}
	int HashIntKey(TKey key) const
	{
		return key.size();
	}
	virtual int FindRecord(TKey k)
	{
		int pos = 0;
		k += " ";
		int i = 0;
		m = 0;
		int cnt = 0;
		for (std::list<std::pair<TKey, TVal>> l : pRecs)
		{
			pos = HashIntKey(k)-1;
			for (std::pair<TKey, TVal> p : l)
			{
				if (p.first == " ") std::cout << "hi ";
				if (p.first == k)
				{
					if(cnt!=0)m++;
					std::cout << "Найдена запись: " << p.first;
					for (int j : p.second) std::cout << j << " ";
					std::cout << " в списке номер " << pos << "\n";
					continue;
				}
				cnt++;
			}
			if(!(l.empty())) i++;
		}
		return pos;
	}
	virtual void InsRecord(TKey k, TVal pVal)
	{
		std::pair<TKey, TVal> insPair(k, pVal);
		std::list<std::pair<TKey, TVal>> li;
		int pos = HashIntKey(k) - 1;
		std::cout << pos << "\n";
		pRecs.reserve(pos);
		for(int i(0); i <= pos; ++i)
			pRecs.push_back(li);
		pRecs[pos].push_back(insPair);
	}
	virtual void DelRecord(TKey k)
	{
		int pos = FindRecord(k);
		if (pos == 7)
		{
			std::cout << "Записи не существует";
		}
		else
		{
			std::list<std::pair<std::string, std::vector<int>>>::iterator it2;
			std::cout << "m: " << m;
			for (int i(0); i < pRecs.size(); ++i)
			{
				if (i == pos)
				{
					it2 = pRecs[i].begin();
					advance(it2, m);
					pRecs[i].erase(it2);
				}
			}
			std::cout << "Запись в списке номер " << pos << " удалена\n";
		}
	}
	virtual void print(void)
	{
		//std::sort(pRecs.begin(), pRecs.end(), [](const auto& l, const auto& r) {return l < r; });
		for (std::list<std::pair<TKey, TVal>> l : pRecs)
		{
			for (std::pair<TKey, TVal> p : l)
			{
				std::cout << p.first << " ";
				for (int i : p.second)
					std::cout << i << " ";
				std::cout << "\n";
			}
		}
	}
};

template <class TKey, class TVal>
class TreeTable
{

};

class node {
public:
	node* left;
	node* right;
	int data;
};

node* root = NULL;// initilize empty tree

node* getNewnode(int newdata) {

	node* newNode = new node;
	newNode->data = newdata;
	newNode->left = NULL;
	newNode->right = NULL;

	return newNode;

}

void print(node* curr) {

	if (curr != NULL) {
		print(curr->left);
		std::cout << curr->data << " ";
		print(curr->right);

	}

	return;
}

bool search(node* curr, int data) {
	std::cout << " search: " << data;
	if (curr == NULL) return false;
	//else if (data <= curr->data) return search(curr->left, data);
	//else if (data > curr->data) return search(curr->right, data);
	else if (curr->data == data) return true;

}

node* insertNode(node* curr, int newdata) {

	if (curr == NULL) {
		curr = getNewnode(newdata);
	}
	else if (newdata <= curr->data) {
		curr->left = (insertNode(curr->left, newdata));
	}
	else if (newdata > curr->data) {
		curr->right = (insertNode(curr->right, newdata));
	}
	return curr;

}

//returns min of right sub-tree
node* findmin(node* curr) {

	while (curr->left != NULL) curr = curr->left;

	return curr;
}


//returns max of right sub-tree
node* findmax(node* curr) {

	while (curr->right != NULL) curr = curr->right;

	return curr;
}

node* deleteNode(node* curr, int data) {

	if (curr == NULL) return curr;
	else if (data < curr->data) curr->left = deleteNode(curr->left, data);
	else if (data > curr->data) curr->right = deleteNode(curr->right, data);
	else {
		//case 1  both childs are NULL
		if (curr->left == NULL && curr->right == NULL) {
			delete curr;
			curr = NULL;
		}//case 2 only one child
		else if (curr->left == NULL) {
			node* temp = curr;
			curr = curr->right;
			delete temp;
		}
		else if (curr->right == NULL) {
			node* temp = curr;
			curr = curr->left;
			delete temp;
		}//case 3 node has both childs
		else if (curr->left != NULL && curr->right != NULL) {

			node* temp = findmin(curr->right);
			curr->data = temp->data;
			curr->right = deleteNode(curr->right, temp->data);

		}
	}

	return curr;
}

void print_BFS(node* curr) {

	std::cout << "Inside BFS" << std::endl;
	//  print(curr);
	std::cout << "\n" << std::endl;

	if (curr == NULL) return;
	std::queue<node*> discovered;
	discovered.push(curr);

	while (!discovered.empty()) {

		node* temp = discovered.front();
		discovered.pop();
		if (temp != NULL) std::cout << temp->data << " " << std::endl;
		if (temp->left != NULL) discovered.push(temp->left);
		if (temp->right != NULL) discovered.push(temp->right);

	}

}

node* common_ancestor(node* curr, int a, int b) {

	if (curr->data < a && curr->data < b) {
		curr = common_ancestor(curr->right, a, b);
	}
	else if (curr->data > a && curr->data > b) {
		curr = common_ancestor(curr->left, a, b);
	}
	else
		return curr;
}

bool IsBST(node* curr, int max, int min) {

	if (curr == NULL) return true;

	if (curr->data < max && curr->data > min
		&& IsBST(curr->left, curr->data, min)
		&& IsBST(curr->right, max, curr->data))
		return true;
	else return false;
}

bool BST_check(node* root) {
	return IsBST(root, INT_MAX, INT_MIN);
}


bool Is_balanced(node* curr) {
	if (curr == NULL) return true;
}



void ASimpleTable();
void ASortTable();
void AHashTable();
void ATreeTable();

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int choose;
	std::cout << "Choose the table: \n1-ScanTable\n2-SortTable\n3-HashTable\n4-TreeTable\n";
	std::cin >> choose;
	switch (choose)
	{
	case 1:
		ASimpleTable();
		break;
	case 2:
		ASortTable();
		break;
	case 3:
		AHashTable();
		break;
	case 4:
		ATreeTable();
		break;
	default:
		break;
	}

	return 0;
}

void ASimpleTable()
{
	int choose, Size = 6;
	int val;
	std::vector<int>value;
	bool wh = 1, check = 1;
	std::string key;
	int key_int[3];
	std::vector<std::string>vec_key;

	std::vector<std::vector<int>>vec_value;

	Table<std::string, std::vector<int>>* pTab = new ArrayTable<std::string, std::vector<int>>(Size);

	std::fstream file("table.txt", std::ios::in);
	if (!file) std::cout << "File was not opened";

	for (int i = 0; i < Size; ++i)
	{
		std::vector<int> temp;
		check = 1;
		//file >> key;
		std::getline(file, key);
		std::cout << key << "\n";
		int im = 0;
		for (char ch : key)
		{
			if ((int(ch)) >= 48 && (int(ch)) <= 57)
			{
				key_int[im] = ch - 48;
				temp.push_back(key_int[im]);
				im++;
			}
		}
		vec_value.push_back(temp);
		temp.clear();
		int ik;
		for (ik = 0; ik < key.size(); ++ik)
		{
			if (key[ik] == '|') break;
		}
		key.erase(ik, key.size());
		std::cout << "\n" << key << "\n";
		vec_key.push_back(key);
	}

	int j(0);
	for (int i(0); i < Size; ++i)
	{
		pTab->InsRecord(vec_key[i], vec_value[j]);
		j++;
	}
	/*
	for (std::string str : vec_key) std::cout << "key: " << str << " ";
	std::cout << "\n";

	for (std::vector<int> inn : vec_value)
	{
		for (int in : inn) std::cout << "v: " << in << " ";
		std::cout << "\n";
	}
	std::cout << "\n";
	*/
	while (wh)
	{
		std::cout << "\nWhat to do: \n1-Insert\n2-Find\n3-Delete\n4-Print\n5-Exit\n ";
		std::cin >> choose;
		switch (choose)
		{
		case 1:
			value.clear();
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			std::cout << "\nInput value: ";
			for (int i(0); i < 3; ++i)
			{
				std::cin >> val;
				value.push_back(val);
			}
			pTab->InsRecord(key, value);
			break;
		case 2:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			pTab->FindRecord(key);
			break;
		case 3:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			pTab->DelRecord(key);
			break;
		case 4:
			pTab->print();
			break;
		case 5:
			wh = 0;
			break;
		default:
			break;
		}
	}
}
void ASortTable() 
{
	int choose, Size = 6;
	int val;
	std::vector<int>value;
	bool wh = 1, check = 1;
	std::string key;
	int key_int[3];
	std::vector<std::string>vec_key;
	std::vector<std::vector<int>>vec_value;

	ArrayTable<std::string, std::vector<int>>* pTab1 = new SortTable<std::string, std::vector<int>>(Size);
	//Table<std::string, std::vector<int>>* pTab = new ArrayTable<std::string, std::vector<int>>(Size);

	std::fstream file("table.txt", std::ios::in);
	if (!file) std::cout << "File was not opened";

	for (int i = 0; i < Size; ++i)
	{
		std::vector<int> temp;
		check = 1;
		//file >> key;
		std::getline(file, key);
		int im = 0;
		for (char ch : key)
		{
			if ((int(ch)) >= 48 && (int(ch)) <= 57)
			{
				key_int[im] = ch - 48;
				temp.push_back(key_int[im]);
				im++;
			}
		}
		vec_value.push_back(temp);
		temp.clear();
		int ik;
		for (ik = 0; ik < key.size(); ++ik)
		{
			if (key[ik] == '|') break;
		}
		key.erase(ik, key.size());
		vec_key.push_back(key);
	}

	int j(0);
	for (int i(0); i < Size; ++i)
	{
		pTab1->InsRecord(vec_key[i], vec_value[j]);
		j++;
	}

	while (wh)
	{
		std::cout << "\nWhat to do: \n1-Insert\n2-Find\n3-Delete\n4-Print\n5-Sort\n6-Exit\n ";
		std::cin >> choose;
		switch (choose)
		{
		case 1:
			value.clear();
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			std::cout << "\nInput value: ";
			for (int i(0); i < 3; ++i)
			{
				std::cin >> val;
				value.push_back(val);
			}
			pTab1->InsRecord(key, value);
			break;
		case 2:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			pTab1->FindRecord(key);
			break;
		case 3:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			pTab1->DelRecord(key);
			break;
		case 4:
			pTab1->print();
			break;
		case 5:
		{
			SortMethod sortMethod;
			int choice;
			std::cout << "\Choose sort method: \n1-InsertSort\n2-MergeSort\n3-QuickSort\n";
			std::cin >> choice;
			switch (choice)
			{
			case 1:
				sortMethod = INSERT_SORT;
				pTab1->InsertSort();
				break;
			case 2:
				sortMethod = MERGE_SORT;
				pTab1->MergeSort( 0, 5);
				break;
			case 3:
				sortMethod = QUICK_SORT;
				pTab1->QuickSort(0, 5);
				break;
			default:
				break;
			}
		}
			break;
		case 6:
			wh = 0;
			break;
		default:
			break;
		}
	}

}
void AHashTable() 
{
	int choose, Size = 6;
	int val;
	std::vector<int>value;
	bool wh = 1, check = 1;
	std::string key;
	int key_int[3];
	std::vector<std::string>vec_key;

	std::vector<std::vector<int>>vec_value;

	//Table<std::string, std::vector<int>>* pTab = new HashTable<std::string, std::vector<int>>(Size);
	HashTable<std::string, std::vector<int>> pTab(Size);
	std::fstream file("table.txt", std::ios::in);
	if (!file) std::cout << "File was not opened";

	for (int i = 0; i < Size; ++i)
	{
		std::vector<int> temp;
		check = 1;
		//file >> key;
		std::getline(file, key);
		//std::cout << key << "\n";
		int im = 0;
		for (char ch : key)
		{
			if ((int(ch)) >= 48 && (int(ch)) <= 57)
			{
				key_int[im] = ch - 48;
				temp.push_back(key_int[im]);
				im++;
			}
		}
		vec_value.push_back(temp);
		temp.clear();
		int ik;
		for (ik = 0; ik < key.size(); ++ik)
		{
			if (key[ik] == '|') break;
		}
		key.erase(ik, key.size());
		//std::cout << "\n" << key << "\n";
		vec_key.push_back(key);
	}

	int j(0);
	for (int i(0); i < Size; ++i)
	{
		pTab.InsRecord(vec_key[i], vec_value[j]);
		j++;
	}

	while (wh)
	{
		std::cout << "\nWhat to do: \n1-Insert\n2-Find\n3-Delete\n4-Print\n5-Exit\n ";
		std::cin >> choose;
		switch (choose)
		{
		case 1:
			value.clear();
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			std::cout << "\nInput value: ";
			for (int i(0); i < 3; ++i)
			{
				std::cin >> val;
				value.push_back(val);
			}
			pTab.InsRecord(key, value);
			break;
		case 2:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			pTab.FindRecord(key);
			break;
		case 3:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			pTab.DelRecord(key);
			break;
		case 4:
			pTab.print();
			break;
		case 5:
			wh = 0;
			break;
		default:
			break;
		}
	}
}
void ATreeTable() 
{
	root = insertNode(root, 15);
	root = insertNode(root, 11);
	root = insertNode(root, 18);
	root = insertNode(root, 10);
	root = insertNode(root, 16);
	root = insertNode(root, 12);
	root = insertNode(root, 17);

	std::cout << "Inorder Tree" << std::endl;
	print(root);
	bool ch = search(root, 15);
	std::cout << "\n" << ch;

	std::cout << "\nBFS" << std::endl;
	print_BFS(root);
	root = deleteNode(root,18);

	std::cout << "After deleting" << std::endl;
	print(root);

	std::cout << "\nBFS" << std::endl;
	print_BFS(root);
	std::cout << "in commin " << std::endl;
	node* temp = common_ancestor(root, 17, 17);
	std::cout << "common_ancestor is : " << temp->data << std::endl;

	if (BST_check(root)) std::cout << "YES IT Is BST" << std::endl;
	else std::cout << "IT IS NOT BST" << std::endl;
}

/*std::cout << l << " " << r << "\n";
		char curr[30];
		strcpy_s(curr, pRecs[l].first.c_str());
		if (r == l)
			return;
		if (r - l == 1)
		{
			if (strcmp(pRecs[r].first.c_str() , curr) < 0)
				pRecs[r] = pRecs[l];
			return;
		}
		int m = (r + l) / 2;
		std::cout << "\n1: ";
		MergeSort(l, m);
		std::cout << "\n2: ";
		MergeSort(m + 1, r);
		char buf[6][30];
		int xl = l;
		int xr = m + 1;
		int cur = 0;
		char currr[30];
		strcpy_s(currr, pRecs[xr].first.c_str());

		while (r - l + 1 != cur)
		{
			if (xl > m)
				strcpy_s(buf[cur++], pRecs[xr++].first.c_str());
			else if (xr > r)
				strcpy_s(buf[cur++], pRecs[xl++].first.c_str());
			else if (strcmp(pRecs[r].first.c_str(), currr) > 0)
				strcpy_s(buf[cur++], pRecs[xr++].first.c_str());
			else strcpy_s(buf[cur++], pRecs[xl++].first.c_str());
		}
		for (int i = 0; i < cur; i++)
			pRecs[i + l].first = buf[i];*/