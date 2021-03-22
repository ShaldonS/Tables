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
	int DataCount; // количество записей в таблице
	int Efficiency; // показатель эффективности выполнения операции
public:
	TTable() { DataCount = 0; Efficiency = 0; } // конструктор
	virtual ~TTable() {}; // деструктор
	 // информационные методы
	int GetDataCount() const { return DataCount; } // к-во записей
	int GetEfficiency() const { return Efficiency; } // эффективность
	int IsEmpty() const { return DataCount == 0; } //пуста?
	virtual int IsFull() const = 0; // заполнена?
	// доступ
	virtual TKey GetKey(void) const = 0;
	virtual TVal GetValuePTR(void) const = 0;
	// основные методы
	virtual TVal FindRecord(TKey k) = 0; // найти запись
	virtual void InsRecord(TKey k, TVal pVal) = 0; // вставить
	virtual void DelRecord(TKey k) = 0; // удалить запись
	// навигация
	virtual int Reset(void) = 0; // установить на первую запись
	virtual int IsTabEnded(void) const = 0; // таблица завершена?
	virtual int GoNext(void) = 0; // переход к следующей записи
	// (=1 после применения для последней записи таблицы)
};

//1
template <class TKey, class TVal>
class Record : public TTable<TKey, TVal>
{
protected: // поля
	TKey Key; // ключ записи
	TVal Value;
public: // методы
	Record(TKey key, TVal value)
	{
		Key = key;
		Value = value;
	};// конструктор
	~Record() {};
	// установить значение ключа
	void SetRec(TKey k, TVal v)
	{
		cout << "\nName: ";
		cin >> k;
		cout << "\nMark: ";
		cin >> k;
	}
	TKey GetKey(void); // получить значение ключа
	Record& operator = (Record& tr);// присваивание
	virtual int operator == (const Record& tr); // сравнение =
	virtual int operator < (const Record& tr); // сравнение «<»
	virtual int operator > (const Record& tr); // сравнение «>»
   //дружественные классы для различных типов таблиц, см. далее
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
	std::vector<Record<TKey, TVal>> pRecs; // память для записей таблицы
	int TabSize; // макс. возм.количество записей в таблице
	int CurrPos; // номер текущей записи (нумерация с 0)
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
	// информационные методы
	virtual int IsFull() const;
	// к-во записей
	int GetTabSize() const
	{
		return pRecs.size();
	}; 
	// доступ
	virtual TKey GetKey(void) const
	{

	};
	// основные методы
	// найти запись
	virtual TVal FindRecord(TKey k)
	{
		std::string input;
		cout << "Input number of record for search: ";
		cin >> input;
		for (std::string find : pRecs)
			if (input == find) cout << find << "\n";
	}
	// вставить
	virtual void InsRecord(TKey k, TVal pVal)
	{
		int pos;
		cout << "In which position need to insert new record?: ";
		cin >> pos;
	}
	// удалить запись
	virtual void DelRecord(TKey k)
	{

	}
	// навигация
	// установить на первую запись
	virtual int Reset(void)
	{
		CurrPos = 0;
	}
	// таблица завершена?
	virtual int IsTabEnded(void) const; 
	// переход к следующей записи
	virtual int GoNext(void); 
	//(=1 после применения для последней записи таблицы)
	// установить текущую запись
	virtual int SetCurrentPos(int pos);
	//получить номер текущей записи
	int GetCurrentPos(void) const
	{
		return CurrPos;
	}
};