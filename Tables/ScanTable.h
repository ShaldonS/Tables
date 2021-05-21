#pragma once
#include "Table.h"
#include <vector>

template<class TKey, class TVal>
class ArrayTable : public Table<TKey, TVal>
{
	using Table<TKey, TVal>::DataCount;
	using Table<TKey, TVal>::TabFull;
	using Table<TKey, TVal>::SetRecCode;
	using Table<TKey, TVal>::TabOK;
	using Table<TKey, TVal>::TabNoRec;
	using Table<TKey, TVal>::IsEmpty;
	using Table<TKey, TVal>::efficienty;
protected:
	//TabRecord<TKey, TVal> rec;
	//int TabSize;
	int CurrPos;
	//std::vector<std::pair<TKey, TVal>> pRecs;
public:
	std::vector<std::pair<TKey, TVal>> pRecs;
	int TabSize;
	enum DataPos { FIRST_POS, CURRENT_POS, LAST_POS };
	ArrayTable(int Size = 6) : Table<TKey, TVal>()
	{
		TabSize = Size;
		CurrPos = 0;
	}
	virtual ~ArrayTable()
	{
		pRecs.clear();
	}

	virtual bool IsFull() const
	{
		return 0;
	}

	int GetTabSize() const
	{
		return TabSize;
	}

	virtual TKey GetKey(void) const
	{
		return GetKey(CURRENT_POS);
	}

	virtual int FindRecord(TKey k)
	{
		k += " ";
		int i = 7;
		for (i = 0; i < pRecs.size(); ++i)
			if (pRecs[i].first == k)
			{
				std::cout << "Найдена запись: " << pRecs[i].first << " ";
				for (int n(0); n < pRecs[i].second.size(); ++n)
				{
					std::cout << pRecs[i].second[n] << " ";
				}
				std::cout << " под номером " << i << "\n";
				break;
			}
		return i;
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
		return (pos == -1) ? std::string("") : pRecs[pos].first;
	}

	virtual TVal GetValuePtr() const
	{
		return GetValuePtr(CURRENT_POS);
	}

	virtual TVal GetValuePtr(DataPos mode) const
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
		return (pos == -1) ? /*NULL*/pRecs[pos].second : pRecs[pos].second;
	}

	virtual void InsRecord(TKey k, TVal pVal)
	{
		if (IsFull())
			SetRecCode(TabFull);
		else
		{
			//pRecs[DataCount] = //new TAbRecord(k, pVal);
			//std::cout << pRecs.size();
			pRecs.reserve(++TabSize);
			pRecs.push_back(std::pair<TKey, TVal>(k, pVal));
			DataCount++;
			SetRecCode(TabOK);
		}
	}

	virtual void DelRecord(TKey k)
	{
		int temp = FindRecord(k);

		if (temp == 7)
		{
			std::cout << "Записи не существует";
			SetRecCode(TabNoRec);
		}
		else
		{
			SetRecCode(TabOK);
			pRecs.erase(pRecs.begin() + temp);
			std::cout << "Запись под номером " << temp << " удалена\n";
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
	virtual void print(void)
	{
		for (int i(0); i < pRecs.size(); ++i)
		{
			std::cout << pRecs[i].first << " ";
			for (int n(0); n < pRecs[i].second.size(); ++n)
			{
				std::cout << pRecs[i].second[n] << " ";
			}
			std::cout << "\n";
		}
	}
	virtual void InsertSort()
	{
		char cur[30];
		TabSize /= 2;
		std::vector<std::pair<TKey, TVal>> tmp;
		for (int i = 0; i < TabSize; ++i)
			tmp.push_back(std::pair<TKey, TVal>(pRecs[i].first, pRecs[i].second));
		int j = 0;

		for (int i = 1; i < TabSize; ++i)
		{
			strcpy_s(cur, pRecs[i].first.c_str());
			for (j = i - 1; j >= 0 && strcmp(pRecs[j].first.c_str(), cur) > 0; --j)
			{
				{
					pRecs[j + 1].first = pRecs[j].first;
					//pRecs[j + 1].second = pRecs[j].second;
				}
			}
			pRecs[j + 1].first = cur;
		}

		int k;
		for (int i = 0; i < TabSize; ++i)
		{
			for (int j = 0; j < TabSize; ++j)
			{
				if (tmp[i].first == pRecs[j].first)
				{
					k = 0;
					for (int in : tmp[i].second)
					{
						pRecs[j].second[k] = in;
						k++;
					}
					k = 0;
				}
			}
		}
	}

	virtual void MergeSort(int low, int high)
	{
		int mid = 0;
		if (low < high)
		{
			mid = ((low + high) / 2);
			MergeSort(low, mid);
			MergeSort(mid + 1, high);
			MergeA(low, mid, high);
		}
	}
	void MergeA(int low, int mid, int high)
	{
		int i = low, j = mid + 1, k = low;
		std::string Temp[6];

		while (i <= mid && j <= high)
		{
			if (pRecs[i].first < pRecs[j].first)
			{
				Temp[k].assign(pRecs[i].first);
				i++;
			}
			else
			{
				Temp[k].assign(pRecs[j].first);
				j++;
			}
			k++;
		}
		if (i > mid)
		{
			for (int h = j; h <= high; h++)
			{
				Temp[k].assign(pRecs[h].first);
				k++;
			}
		}
		else
			for (int h = i; h <= mid; h++)
			{
				Temp[k].assign(pRecs[h].first);
				k++;
			}
		std::cout << "\nВывод: ";
		for (int i = 0; i <= Temp[i].size(); i++)
		{
			std::cout << Temp[i] << "\n";
		}
		std::cout << "\n";
		for (int i = 0; i <= high; i++)
		{
			pRecs[i].first.assign(Temp[i]);
		}
	}

	virtual void QuickSort(int left, int right)
	{
		int i, j, p;
		i = left;
		j = right;
		//char tmp[100];

		while (i != j)
		{
			if ((strcmp(pRecs[i].first.c_str(), pRecs[j].first.c_str()) > 0) != (i < j))
				//if ( i <= j)
			{
				std::cout << i << " " << j << "\n";
				swap(pRecs[i], pRecs[j]);

				p = i;
				i = j;

				if (p < j)
					j = p + 1;
				else j = p - 1;
			}
			else
			{
				if (i < j) j--;
				else j++;
			}
		}

		if (left < i - 1)
			QuickSort(left, i);
		if (i + 1 < right)
			QuickSort(i + 1, right);
	}

};