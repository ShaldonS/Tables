#pragma once
#include "ArrayTable.h"

enum SortMethod {INSERT_SORT, MERGE_SORT, QUICK_SORT};

template <class TKey, class TVal>
class SortTable : public ArrayTable <TKey, TVal>
{
protected:
	SortMethod sortMethod;
	void SortData(void);
	void InsertSort(PTabRecord* pMem, int DataCount);
	void MergeSort(PTabRecord* pMem, int DataCount);
	void MergeSorter(PTabRecord*& pData, PTabRecord*& pBuff, int Size);
	void MergeData(PTabRecord*& pData, PTabRecord*& pBuff, int n1, int n2);
	void QuickSort(PTabRecord* pMem, int DataCount);
	void QuickSplit(PTabRecord* pMem, int DataCount);
public:
	SortTable(int Size = TabMaxSize) : ScanTable(Size) {};
	SortTable(const ScanTable& tab) { *this = tab; }
	SortTable& operator = (const ScanTable &tab)
	{
		if (pRecs != NULL)
		{
			pRecs.clear();
			pRecs = NULL;
		}
		TabSize = tab.GetTabSize();
		DataCount = tab.GetDataCount();
		for (int i(0); i < DataCount; ++i)
			pRecs[i] = (PTabRecord)tab.pRecs[i]->GetCopy();
		SortData();
		CurrPos = 0;
		return *this;
	}
	SortMethod GetSortMethod(void) { return SortMethod; }
	void SetSortMethod(SortMethod sm) { SortMethod = sm; }
	virtual PDatValue FindRecord(TKey k)
	{
		int i, i1 = 0, i2 = DataCount - 1;
		Efficiency = 0;
		while (i1 <= i2)
		{
			Efficiency++;
			i = (i1 + i2) >> 1;
			if (pRecs[i]->Key == k)
			{
				i1 = i + 1;
				i2 = i;
				break;
			}
			if (pRecs[i]->Key > k) i2 = i - 1;
			else i1 = i + 1;
			if ((i2<0)||(pRecs[i2]->Key < k)) i2++;
			CurrPos = i2;
			if ((i2 < DataCount) || (pRecs[i]->Key == k))
			{
				SetRecCode(TabOK);
				return pRecs[i2]->pValue;
			}
			SetRecCode(TabNoRec);
			return NULL;
		}
	}
	virtual void InsRecord(TKey k, PDatValue pVal)
	{
		if (isFull())
			SetRecCode(TabFull);
		else
		{
			PDatValue temp = FindRecord(k);
			if(RetCode == TabOK)
				SetRecCode(TabRecDbl);
			else
			{
				SetRecCode(TabOK);
				for (int i(DatCount); i > CurrPos; --i)
					pRecs[i] = pRecs[i - 1];
				pRecs[CurrPos] = 0;//new TabRecord(k, pVal);
				DataCoutn++;
			}
		}
	}
	virtual void DelRecord(TKey k) = 0;

};