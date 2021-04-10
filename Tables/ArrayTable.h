#pragma once
#include "Table.h"

enum DataPos {FIRST_POS, CURRENT_POS, LAST_POS};

template  <class TKey, class TVal>
class TArrayTable : public Table<TKey, TVal>
{
	using Table<TKey, TVal>::DataCount;
	using Table<TKey, TVal>::efficienty;
	using Table<TKey, TVal>::IsEmpty;
	using Table<TKey, TVal>::IsFull;
protected:
	std::vector<TabRecord<TKey, TVal>> pRecs;
	int TabSize;
	int CurrPos;
	TabRecord<TKey, TVal> rec;
public:
	TArrayTable(int Size = 25) : Table()
	{
		TabSize = Size;
		CurrPos = 0;
		pRecs.reserve(Size);
	}
	virtual ~TArrayTable()
	{
		pRecs.clear();
	}

	//virtual int IsFull() const;

	int GetTabSize() const
	{
		return TabSize;
	}

	virtual TKey GetKey(void) const
	{
		return GetKey(CURRENT_POS);
	}

	virtual TVal FindRecord(TKey k)
	{
		int i;
		SetRecCode(TabOK);
		for (i(0); i < DataCount; ++i)
			if (pRecs[i]->Key == k)
				break;
		efficienty = i + 1;
		if (i < DataCount)
		{
			CurrPos = i;
			return pRecs[i]->pValue;
		}
		SetRecCode(TabNoRec);
		return NULL;
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
		return (pos == -1) ? std::string("") : pRecs[pos]->Key;
	}

	virtual PDatValue GetValuePtr(void) const
	{
		return GetValuePtr(CURRENT_POS);
	}

	virtual PDatValue GetValuePtr(DataPos mode) const
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
		return (pos == -1) ? NULL : pRecs[pos]->pValue;
	}

	virtual void InsRecord(TKey k, PDatValue pVal)
	{
		if (IsFull())
			SetRecCode(TabFull);
		else
		{
			pRecs[DataCount] = 0;//new TAbRecord(k, pVal);
			DataCount++;
			SetRecCode(TabOK);
		}
	}
	void print()
	{
		
	}

	virtual void DelRecord(TKey k)
	{
		PDatValue temp = FindRecord(k);
		if (temp == NULL)
			SetRecCode(TabNoRec);
		else
		{
			SetRecCode(TabOK);
			pRecs[CurrPos] = pRecs[DataCount - 1];
			pRecs[--DataCount] = NULL;
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
};