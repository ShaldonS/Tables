#pragma once
#include <iostream>
const int TTabMaxSize = 6;

template<class TKey, class TVal>
class Table 
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