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
	int DataCount; // êîëè÷åñòâî çàïèñåé â òàáëèöå
	int Efficiency; // ïîêàçàòåëü ýôôåêòèâíîñòè âûïîëíåíèÿ îïåðàöèè
public:
	TTable() { DataCount = 0; Efficiency = 0; } // êîíñòðóêòîð
	virtual ~TTable() {}; // äåñòðóêòîð
	 // èíôîðìàöèîííûå ìåòîäû
	int GetDataCount() const { return DataCount; } // ê-âî çàïèñåé
	int GetEfficiency() const { return Efficiency; } // ýôôåêòèâíîñòü
	int IsEmpty() const { return DataCount == 0; } //ïóñòà?
	virtual int IsFull() const = 0; // çàïîëíåíà?
	// äîñòóï
	virtual TKey GetKey(void) const = 0;
	virtual TVal GetValuePTR(void) const = 0;
	// îñíîâíûå ìåòîäû
	virtual TVal FindRecord(TKey k) = 0; // íàéòè çàïèñü
	virtual void InsRecord(TKey k, TVal pVal) = 0; // âñòàâèòü
	virtual void DelRecord(TKey k) = 0; // óäàëèòü çàïèñü
	// íàâèãàöèÿ
	virtual int Reset(void) = 0; // óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int IsTabEnded(void) const = 0; // òàáëèöà çàâåðøåíà?
	virtual int GoNext(void) = 0; // ïåðåõîä ê ñëåäóþùåé çàïèñè
	// (=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
};

//1
template <class TKey, class TVal>
class Record : public TTable<TKey, TVal>
{
protected: // ïîëÿ
	TKey Key; // êëþ÷ çàïèñè
	TVal Value;
public: // ìåòîäû
	Record(TKey key, TVal value)
	{
		Key = key;
		Value = value;
	};// êîíñòðóêòîð
	~Record() {};
	// óñòàíîâèòü çíà÷åíèå êëþ÷à
	void SetRec(TKey k, TVal v)
	{
		cout << "\nName: ";
		cin >> k;
		cout << "\nMark: ";
		cin >> k;
	}
	TKey GetKey(void); // ïîëó÷èòü çíà÷åíèå êëþ÷à
	Record& operator = (Record& tr);// ïðèñâàèâàíèå
	virtual int operator == (const Record& tr); // ñðàâíåíèå =
	virtual int operator < (const Record& tr); // ñðàâíåíèå «<»
	virtual int operator > (const Record& tr); // ñðàâíåíèå «>»
   //äðóæåñòâåííûå êëàññû äëÿ ðàçëè÷íûõ òèïîâ òàáëèö, ñì. äàëåå
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
	std::vector<Record<TKey, TVal>> pRecs; // ïàìÿòü äëÿ çàïèñåé òàáëèöû
	int TabSize; // ìàêñ. âîçì.êîëè÷åñòâî çàïèñåé â òàáëèöå
	int CurrPos; // íîìåð òåêóùåé çàïèñè (íóìåðàöèÿ ñ 0)
	Record<TKey, TVal> rec;
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
	}
	// èíôîðìàöèîííûå ìåòîäû
	virtual int IsFull() const;
	// ê-âî çàïèñåé
	int GetTabSize() const
	{
		return pRecs.size();
	}; 
	// äîñòóï
	virtual TKey GetKey(void) const
	{

	};
	// îñíîâíûå ìåòîäû
	// íàéòè çàïèñü
	virtual TVal FindRecord(TKey k)
	{
		std::string input;
		cout << "Input number of record for search: ";
		cin >> input;
		for (std::string find : pRecs)
			if (input == find) cout << find << "\n";
	}
	// âñòàâèòü
	virtual void InsRecord(TKey k, TVal pVal)
	{
		int pos;
		cout << "In which position need to insert new record?: ";
		cin >> pos;
		rec.SetRec();
	}
	// óäàëèòü çàïèñü
	virtual void DelRecord(TKey k)
	{

	}
	// íàâèãàöèÿ
	// óñòàíîâèòü íà ïåðâóþ çàïèñü
	virtual int Reset(void)
	{
		CurrPos = 0;
	}
	// òàáëèöà çàâåðøåíà?
	virtual int IsTabEnded(void) const; 
	// ïåðåõîä ê ñëåäóþùåé çàïèñè
	virtual int GoNext(void); 
	//(=1 ïîñëå ïðèìåíåíèÿ äëÿ ïîñëåäíåé çàïèñè òàáëèöû)
	// óñòàíîâèòü òåêóùóþ çàïèñü
	virtual int SetCurrentPos(int pos);
	//ïîëó÷èòü íîìåð òåêóùåé çàïèñè
	int GetCurrentPos(void) const
	{
		return CurrPos;
	}
};
