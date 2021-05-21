#include "Table.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "HashTable.h"
#include "TreeTable.h"
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>

/*
template <class TKey, class TVal>
class node
{
public:
	node* left;
	node* right;
	std::pair<TKey, TVal> key;
};

template <class TKey, class TVal>
class TreeTable : public node<TKey, TVal>
{
public:
	node<TKey, TVal>* root = NULL;

	node<TKey, TVal>* getNewnode(std::pair<TKey, TVal> key)
	{
		node<TKey, TVal>* newNode = new node<TKey, TVal>;
		newNode->key = key;
		newNode->left = NULL;
		newNode->right = NULL;
		return newNode;
	}

	void print(node<TKey, TVal>* curr)
	{
		if (curr != NULL) 
		{
			print(curr->left);
			std::cout << curr->key.first << " ";
			for (int i(0); i < 3; ++i) std::cout << curr->key.second[i] << " ";
			std::cout << "\n";
			print(curr->right);
		}
	}

	bool FindRecord(node<TKey, TVal>* curr, TKey key)
	{
		if (curr == NULL) return false;
		else
		{
			if (curr->key.first == key)
			{
				std::cout << "������� ������: " << curr->key.first << " ";
				for (int j : curr->key.second) std::cout << j << " ";
			}
			else if (key <= curr->key.first)
			{
				return FindRecord(curr->left, key);
			}
			else if (key > curr->key.first) 
			{
				return FindRecord(curr->right, key);
			}
		}
	}

	node<TKey, TVal>* InsRecord(node<TKey, TVal>* curr, std::pair<TKey, TVal> key)
	{

		if (curr == NULL) 
		{
			curr = getNewnode(key);
		}
		else if (key.first <= curr->key.first) 
		{
			curr->left = (InsRecord(curr->left, key));
		}
		else if (key.first > curr->key.first) 
		{
			curr->right = (InsRecord(curr->right, key));
		}
		return curr;
	}

	node<TKey, TVal>* findmin(node<TKey, TVal>* curr)
	{
		while (curr->left != NULL) curr = curr->left;
		return curr;
	}


	node<TKey, TVal>* findmax(node<TKey, TVal>* curr)
	{
		while (curr->right != NULL) curr = curr->right;
		return curr;
	}

	node<TKey, TVal>* DelRecord(node<TKey, TVal>* curr, TKey key)
	{
		if (curr == NULL) return curr;
		else if (key < curr->key.first) curr->left = DelRecord(curr->left, key);
		else if (key > curr->key.first) curr->right = DelRecord(curr->right, key);
		else 
		{
			if (curr->left == NULL && curr->right == NULL) {
				delete curr;
				curr = NULL;
			}
			else if (curr->left == NULL) 
			{
				node<TKey, TVal>* temp = curr;
				curr = curr->right;
				delete temp;
			}
			else if (curr->right == NULL) 
			{
				node<TKey, TVal>* temp = curr;
				curr = curr->left;
				delete temp;
			}
			else if (curr->left != NULL && curr->right != NULL) 
			{
				node<TKey, TVal>* temp = findmin(curr->right);
				curr->key = temp->key;
				curr->right = DelRecord(curr->right, temp->key.first);
			}
		}
		return curr;
	}

	void print_BFS(node<TKey, TVal>* curr)
	{
		if (curr == NULL) return;
		std::queue<node<TKey, TVal>*> discovered;
		discovered.push(curr);

		while (!discovered.empty()) 
		{
			node<TKey, TVal>* temp = discovered.front();
			discovered.pop();
			if (temp != NULL)
			{
				std::cout << temp->key.first << " ";
				for (int i(0); i < 3; ++i) std::cout << temp->key.second[i] << " ";
				std::cout << "\n";
			}
			if (temp->left != NULL) discovered.push(temp->left);
			if (temp->right != NULL) discovered.push(temp->right);
		}
	}

	node<TKey, TVal>* common_ancestor(node<TKey, TVal>* curr, int a, int b)
	{
		if (curr->data < a && curr->data < b) {
			curr = common_ancestor(curr->right, a, b);
		}
		else if (curr->data > a && curr->data > b) {
			curr = common_ancestor(curr->left, a, b);
		}
		else
			return curr;
	}
	bool Is_balanced(node<TKey, TVal>* curr)
	{
		if (curr == NULL) return true;
	}
};
*/

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
		pTab->InsRecord(vec_key[i], vec_value[j]);
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
	int choose, Size = 6;
	int val;
	std::vector<int>value;
	bool wh = 1, check = 1;
	std::string key;
	int key_int[3];
	std::vector<std::string>vec_key;

	std::vector<std::vector<int>>vec_value;

	//TreeTable<std::string, std::vector<int>> pTab;
	BTree<std::string> pTab(3);
	std::fstream file("table.txt", std::ios::in);
	if (!file) std::cout << "File was not opened";

	for (int i = 0; i < Size; ++i)
	{
		std::vector<int> temp;
		check = 1;
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

	std::pair<std::string, std::vector<int>> my_pair();
	/*
	node<std::string, std::vector<int>>* root;
	root = pTab.root;
	*/

	int j(0);
	for (int i(0); i < Size; ++i)
	{
		std::pair<std::string, std::vector<int>> my_pair(vec_key[i], vec_value[j]);
		//root = pTab.InsRecord(root, my_pair);
		pTab.insert(vec_key[i]);
		j++;
	}

	std::pair<std::string, std::vector<int>> my_pair1;

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
			my_pair1.first = key;
			my_pair1.second = value;
			pTab.insert(key);
			break;
		case 2:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			my_pair1.first = key;
			if (pTab.search(key) != NULL) std::cout << "������ " << key << "�������";
			break;
		case 3:
			std::cout << "Input key: ";
			while (std::cin.get() != '\n');
			std::getline(std::cin, key);
			pTab.deletion(key);
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