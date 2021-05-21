#include <list>

template <class TKey, class TVal>
class HashTable
{
	std::vector<std::list<std::pair<TKey, TVal>>> pRecs;
	int size;
	int capacity;
	int m;
public:
	HashTable(int cap)
	{
		capacity = cap;
		size = 0;
		pRecs.reserve(6);
	}
	~HashTable()
	{
		pRecs.clear();
	}
	int HashIntKey(TKey key) const
	{
		return key.size();
	}
	virtual int FindRecord(TKey k)
	{
		int pos = 0;
		if (k[k.size() != ' ']) k += " ";
		int i = 0;
		m = 0;
		int cnt = 0;
		pos = HashIntKey(k) - 1;
		for (std::pair<TKey, TVal> p : pRecs[pos])
		{
			if (p.first == k)
			{
				if (cnt != 0)m++;
				std::cout << "Найдена запись: " << p.first;
				for (int j : p.second) std::cout << j << " ";
				std::cout << " в списке номер " << pos << "\n";
				continue;
			}
			cnt++;
		}
		//if(!(l.empty())) i++;
		return pos;
	}
	virtual void InsRecord(TKey k, TVal pVal)
	{
		std::pair<TKey, TVal> insPair(k, pVal);
		std::list<std::pair<TKey, TVal>> li;
		int pos = HashIntKey(k) - 1;
		std::cout << pos << "\n";
		pRecs.reserve(pos);
		for (int i(0); i <= pos; ++i)
			pRecs.push_back(li);
		pRecs[pos].push_back(insPair);
	}
	virtual void DelRecord(TKey k)
	{
		int pos = FindRecord(k);
		if (pos == 7)
		{
			std::cout << "Записи не существует";
		}
		else
		{
			std::list<std::pair<std::string, std::vector<int>>>::iterator it2;
			for (int i(0); i < pRecs.size(); ++i)
			{
				if (i == pos)
				{
					it2 = pRecs[i].begin();
					advance(it2, m);
					pRecs[i].erase(it2);
				}
			}
			std::cout << "Запись в списке номер " << pos << " удалена\n";
		}
	}
	virtual void print(void)
	{
		//std::sort(pRecs.begin(), pRecs.end(), [](const auto& l, const auto& r) {return l < r; });
		for (std::list<std::pair<TKey, TVal>> l : pRecs)
		{
			for (std::pair<TKey, TVal> p : l)
			{
				std::cout << p.first << " ";
				for (int i : p.second)
					std::cout << i << " ";
				std::cout << "\n";
			}
		}
	}
};