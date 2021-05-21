#pragma once
#include <string>
#include <vector>
#include "ArrayTable.h"


#define TTabMaxSize 25

template <class TKey, class TVal>
class TabRecord
{
protected:
	TKey Key;
	TVal* pValue;
	virtual void Print(std::ostream& os) { os << Key << " " << *pValue; }
public:
	TabRecord(TKey k = "", TVal * pVal = NULL) { Key = k; pValue = pVal; }
	~TabRecord() {};
	void SetKey(TKey k) { Key = k; }
	TKey GetKey(void) { return Key; }
	void SetValuePtr(TVal p) { pValue = p; }
	TVal GetValuePtr(void) { return pValue; }
	//virtual TVal* GetCopy() {}
	TabRecord& operator = (TabRecord& tr)
	{
		Key = tr.Key;
		pValue = tr.pValue;
		return *this;
	}
	virtual int operator==(const TabRecord& tr) { return Key == tr.Key; }
	virtual int operator>(const TabRecord& tr) { return Key > tr.Key; }
	virtual int operator<(const TabRecord& tr) { return Key < tr.Key; }

	//friend class ArrayTable;
	//friend class SortTable;
	//friend class TreeTable;
	//friend class HashTable;
};