#pragma once
#include <iostream>
#include <string>
#include <stack>
#include <vector>

using std::cin;
using std::cout;
//enum TDataPos { FIRST_POS, CURRENT_POS, LAST_POS };

template  <class TKey, class TVal>
class TTable
{
protected:
	int DataCount; // ���������� ������� � �������
	int Efficiency; // ���������� ������������� ���������� ��������
public:
	TTable() { DataCount = 0; Efficiency = 0; } // �����������
	virtual ~TTable() {}; // ����������
	 // �������������� ������
	int GetDataCount() const { return DataCount; } // �-�� �������
	int GetEfficiency() const { return Efficiency; } // �������������
	int IsEmpty() const { return DataCount == 0; } //�����?
	virtual int IsFull() const = 0; // ���������?
	// ������
	virtual TKey GetKey(void) const = 0;
	virtual TVal GetValuePTR(void) const = 0;
	// �������� ������
	virtual TVal FindRecord(TKey k) = 0; // ����� ������
	virtual void InsRecord(TKey k, TVal pVal) = 0; // ��������
	virtual void DelRecord(TKey k) = 0; // ������� ������
	// ���������
	virtual int Reset(void) = 0; // ���������� �� ������ ������
	virtual int IsTabEnded(void) const = 0; // ������� ���������?
	virtual int GoNext(void) = 0; // ������� � ��������� ������
	// (=1 ����� ���������� ��� ��������� ������ �������)
};

//1
template <class TKey, class TVal>
class Record : public TTable<TKey, TVal>
{
protected: // ����
	TKey Key; // ���� ������
	TVal Value;
public: // ������
	Record(TKey key, TVal value)
	{
		Key = key;
		Value = value;
	};// �����������
	~Record() {};
	// ���������� �������� �����
	void SetRec(TKey k, TVal v)
	{
		cout << "\nName: ";
		cin >> k;
		cout << "\nMark: ";
		cin >> k;
	}
	TKey GetKey(void); // �������� �������� �����
	Record& operator = (Record& tr);// ������������
	virtual int operator == (const Record& tr); // ��������� =
	virtual int operator < (const Record& tr); // ��������� �<�
	virtual int operator > (const Record& tr); // ��������� �>�
   //������������� ������ ��� ��������� ����� ������, ��. �����
	friend class scanTable;
	friend class sortTable;
	friend class TTreeNode;
	friend class treeTable;
	friend class TArrayHash;
	friend class TListHash;
};

//2
template  <class TKey, class TVal>
class TArrayTable : public TTable<TKey, TVal>
{
protected:
	std::vector<Record<TKey, TVal>> pRecs; // ������ ��� ������� �������
	int TabSize; // ����. ����.���������� ������� � �������
	int CurrPos; // ����� ������� ������ (��������� � 0)
public:
	TArrayTable(int Size = 25) : TTable(0, 0)
	{
		TabSize = Size;
		CurrPos = 0;
		pRecs.reserve(Size);
	}
	~TArrayTable()
	{
		delete[] pRecs;
	};
	// �������������� ������
	virtual int IsFull() const;
	// �-�� �������
	int GetTabSize() const
	{
		return pRecs.size();
	}; 
	// ������
	virtual TKey GetKey(void) const
	{

	};
	// �������� ������
	// ����� ������
	virtual TVal FindRecord(TKey k)
	{
		std::string input;
		cout << "Input number of record for search: ";
		cin >> input;
		for (std::string find : pRecs)
			if (input == find) cout << find << "\n";
	}
	// ��������
	virtual void InsRecord(TKey k, TVal pVal)
	{
		int pos;
		cout << "In which position need to insert new record?: ";
		cin >> pos;
	}
	// ������� ������
	virtual void DelRecord(TKey k)
	{

	}
	// ���������
	// ���������� �� ������ ������
	virtual int Reset(void)
	{
		CurrPos = 0;
	}
	// ������� ���������?
	virtual int IsTabEnded(void) const; 
	// ������� � ��������� ������
	virtual int GoNext(void); 
	//(=1 ����� ���������� ��� ��������� ������ �������)
	// ���������� ������� ������
	virtual int SetCurrentPos(int pos);
	//�������� ����� ������� ������
	int GetCurrentPos(void) const
	{
		return CurrPos;
	}
};