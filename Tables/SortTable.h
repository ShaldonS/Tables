#pragma once
#include "ScanTable.h"

enum SortMethod { INSERT_SORT, MERGE_SORT, QUICK_SORT };

template <class TKey, class TVal>
class SortTable : public ArrayTable <TKey, TVal>
{
protected:
	SortMethod sortMethod;
	ArrayTable<TKey, TVal> pArr;
	void SortData(void);
public:
	SortTable(int Size = TTabMaxSize)  { }
	//SortTable(const ArrayTable<TKey, TVal>& tab) { *this = tab; }
};