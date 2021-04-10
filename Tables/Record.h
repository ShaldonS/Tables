#pragma once
#include <iostream>
#include <string>
#include <vector>

#define TTabMaxSize 25

template <class TKey, class TVal>
class DatValue
{
protected:
	int Type;
	virtual void Print(std::ostream& os) = 0;
public:
	DatValue(int t = 0) { Type = t; }
	virtual ~DatValue() {}
	int GetType() { return Type; }
	virtual DatValue<TKey, TVal>* GetCopy() = 0;
	friend std::ostream& operator<<(std::ostream& os, DatValue& dv)
	{
		if (&dv != NULL)
			dv.Print(os);
		return os;
	}
};

typedef DatValue<TKey, TVal>* PDatValue;

template <class TKey, class TVal>
class TabRecord : public DatValue<TKey, TVal>
{
protected:
	TKey Key;
	PDatValue pValue;
	virtual void Print(std::ostream& os) { os << Key << " " << *pValue; }
public:
	TabRecord(TKey k = "", PDatValue pVal = NULL) { Key = k; pValue = pVal; }
	~TabRecord() {};
	void SetKey(TKey k) { Key = k; }
	TKey GetKey(void) { return Key; }
	void SetValuePtr(PDatValue p) { pValue = p; }
	PDatValue GetValuePtr(void) { return pValue; }
	virtual DatValue<TKey, TVal>* GetCopy() {}
	TabRecord& operator = (TabRecord& tr)
	{
		Key = tr.Key;
		pValue = tr.pValue;
		return *this;
	}
	virtual int operator==(const TabRecord& tr) { return Key == tr.Key; }
	virtual int operator>(const TabRecord& tr) { return Key > tr.Key; }
	virtual int operator<(const TabRecord& tr) { return Key < tr.Key; }
	
	friend class ArrayTable;
	friend class ScanTable;
	friend class SortTable;
	friend class TreeTable;
	friend class HashTable;
};

typedef TabRecord<class TKey, class TVal>* PTabRecord;
