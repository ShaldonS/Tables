#pragma once
#include "Record.h"

#define TabOK 0
#define TabEmpty -101
#define TabFull -102
#define TabNoRec -103
#define TabRecObl -104
#define TabNoMem -105

template<class TKey, class TVal>
class Table
{
protected:
	int DataCount;
	int efficienty;
public:
	Table():DataCount(0), efficienty(0) {}
	virtual ~Table() {};
	int GetDataCount() const { return DataCount; }
	int GetEfficienty() const { return efficienty; }
	bool IsEmpty() const { return DataCount == 0; }
	virtual bool IsFull() const = 0;
	virtual PDatValue FindRecord(TKey k) = 0;
	virtual void InsRecord(TKey k, PDatValue pVal) = 0;
	virtual void DelRecord(TKey k) = 0;
	virtual int Reset(void) = 0;
	virtual int IsTabEnded(void) = 0;
	virtual int GoNext(void) = 0;
	virtual TKey GetKey(void) const = 0;
	virtual PDatValue GetValuePtr(void) const = 0;
	friend std::ostream& operator<<(std::ostream& os, Table& tb)
	{
		std::cout << "Table: \n";
		for (tb.Reset(); !tb.IsTabEnded(); tb.GoNext())
		{
			os << "Key: " << tb.GetKey() << " Value: " << tb.GetValuePtr() << "\n";
		}
		return os;
	}
};
