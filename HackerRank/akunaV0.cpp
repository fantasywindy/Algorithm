#include <map>
#include <set>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <string>
#include <bitset>
#include <cstdio>
#include <limits>
#include <vector>
#include <climits>
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <numeric>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Transaction
{
	string order_id;
	int quantity;
	int price;
	string type; //IOC or GFD
	int order_time;
};

class Book
{
public:
	Book()
	{

	}

	typedef list<Transaction>::iterator ListIt;

	void buy(Transaction t)
	{
		addBuyOrder(t);
		match(t.order_id);
	}

	void sell(Transaction t)
	{
		addSellOrder(t);
		match(t.order_id);
	}

	void addBuyOrder(Transaction t)
	{
		t.order_time = getCurTime();
		buyings.push_back(t);
		ListIt it = buyings.end();
		--it;
		buyingsIts[t.order_id] = it;
	}

	void addSellOrder(Transaction t)
	{
		t.order_time = getCurTime();
		sellings.push_back(t);
		ListIt it = sellings.end();
		--it;
		sellingsIts[t.order_id] = it;
	}

	pair<int, ListIt> findOrder(string order_id)
	{
		//first ret means the find result
		//-1 cannot find in buy or sell
		//0 find it in buy
		//1 find it in sell
		//second ret means the find ListIt
		if(buyingsIts.find(order_id) != buyingsIts.end())
		{
			//find it in the buyings
			return make_pair(0, buyingsIts[order_id]);
		}
		else
		{
			//try to find it in the sellings
			if(sellingsIts.find(order_id) != sellingsIts.end())
			{
				return make_pair(1, sellingsIts[order_id]);
			}
			else
			{
				return make_pair(-1, sellings.end());
			}
		}
	}

	void removeBuyOrder(ListIt it)
	{
		auto order_id = it->order_id;
		buyingsIts.erase(order_id);
		buyings.erase(it);
	}

	void removeSellOrder(ListIt it)
	{
		auto order_id = it->order_id;
		sellingsIts.erase(order_id);
		sellings.erase(it);
	}

	void cancelOrder(string order_id)
	{
		auto find_ret = findOrder(order_id);
		if(find_ret.first == -1)
		{
			return;
		}
		else if(find_ret.first == 0)
		{
			//find in buy
			removeBuyOrder(find_ret.second);
		}
		else if(find_ret.first == 1)
		{
			removeSellOrder(find_ret.second);
		}
		else
		{
			//do nothing
		}
	}

	void modifyOrder(string order_id, string changeToType, int new_price, int new_quantity)
	{
		auto find_ret = findOrder(order_id);
		if(find_ret.first == -1)
		{
			return;
		}
		else if(find_ret.first == 0)
		{
			//find it in buy
			auto it = find_ret.second;
			Transaction order = *it;

			//first remove it
			removeBuyOrder(it);

			//then add the new order into the book
			if(changeToType == "SELL")
			{
				//add it to sellings
				order.price = new_price;
				order.quantity = new_quantity;
				addSellOrder(order);
			}
			else
			{
				//just update it
				order.price = new_price;
				order.quantity = new_quantity;
				addBuyOrder(order);
			}
		}
		else if(find_ret.first == 1)
		{
			//find it in sell
			auto it = find_ret.second;
			Transaction order = *it;

			//first remove it
			removeSellOrder(it);

			//then add the new order into the book
			if(changeToType == "BUY")
			{
				//add it to buy
				order.price = new_price;
				order.quantity = new_quantity;
				addBuyOrder(order);
			}
			else
			{
				//stay the same, just update price and quantity
				order.price = new_price;
				order.quantity = new_quantity;
				addSellOrder(order);
			}
		}
		match(order_id);
	}

	void print()
	{
		map<int, int> sellMap;
		map<int, int> buyMap;

		for(auto it = sellings.begin(); it != sellings.end(); ++it)
		{
			sellMap[it->price] += it->quantity;
		}

		for(auto it = buyings.begin(); it != buyings.end(); ++it)
		{
			buyMap[it->price] += it->quantity;
		}

		cout << "SELL:" << endl;
		for(auto it = sellMap.rbegin(); it != sellMap.rend(); ++it)
		{
			cout << it->first << " " << it->second << endl;
		}

		cout << "BUY:" << endl;
		for(auto it = buyMap.rbegin(); it != buyMap.rend(); ++it)
		{
			cout << it->first << " " << it->second << endl;
		}
	}

	void printTransaction(ListIt buyIt, ListIt sellIt)
	{
		int amount = min(buyIt->quantity, sellIt->quantity);
		stringstream ss;
		auto l = (buyIt->order_time < sellIt->order_time) ? buyIt : sellIt;
		auto r = (buyIt->order_time < sellIt->order_time) ? sellIt : buyIt;
		ss << "TRADE " << l->order_id << " " << l->price << " " << amount << " " << r->order_id << " " << r->price << " " << amount;
		cout << ss.str() << endl;
	}

	void updateTransaction(ListIt buyIt, ListIt sellIt)
	{
		int amount = min(buyIt->quantity, sellIt->quantity);

		buyIt->quantity -= amount;
		if(buyIt->quantity == 0)
		{
			removeBuyOrder(buyIt);
		}
		
		sellIt->quantity -= amount;
		if(sellIt->quantity == 0)
		{
			removeSellOrder(sellIt);
		}
	}

	void makeTransaction(ListIt buyIt, ListIt sellIt)
	{
		printTransaction(buyIt, sellIt);

		updateTransaction(buyIt, sellIt);
	}

	bool oneMatch()
	{
		//return true means we made a transaction
		//return false means we did not make any transaction
		if(sellings.empty())
		{
			return false;
		}

		auto sellIt = sellings.begin();

		auto buyIt = buyings.begin();

		while(buyIt != buyings.end())
		{
			if(buyIt->price >= sellIt->price)
			{
				makeTransaction(buyIt, sellIt);
				return true;
			}
			else
			{
				++buyIt;
			}
		}

		return false;
	}


	void match(string order_id)
	{
		while(oneMatch() == true)
		{

		}
	}

	int getCurTime()
	{
		return curTime++;
	}

	list<Transaction> buyings;
	list<Transaction> sellings;

	map<string, ListIt> buyingsIts;
	map<string, ListIt> sellingsIts;

	int curTime = 0;
};


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

	Book book;
    string line;
    while(getline(cin, line))
    {
    	stringstream ss(line);
    	vector<string> columns;
    	string col;
    	while(getline(ss, col, ' '))
    	{
    		columns.push_back(col);
    	}

    	if(columns[0] == "BUY" || columns[0] == "SELL")
    	{
    		Transaction t;
    		t.type = columns[1];
    		t.price = stoi(columns[2]);
    		if(t.price <= 0)
    		{
    			continue;
    		}
    		t.quantity = stoi(columns[3]);
    		if(t.quantity <= 0)
    		{
    			continue;
    		}
    		t.order_id = columns[4];
    		if(t.order_id == "")
    		{
    			continue;
    		}
    		if(columns[0] == "BUY")
    		{
    			book.buy(t);
    		}
    		else
    		{
    			book.sell(t);
    		}
    	}
    	else if(columns[0] == "CANCEL")
    	{
    		if(columns.size() == 1)
    		{
    			//do nothing
    		}
    		else
    		{
    			string order_id = columns[1];
    			if(order_id == "")
    			{
    				continue;
    			}
    			book.cancelOrder(order_id);
    		}
    	}
    	else if(columns[0] == "MODIFY")
    	{
    		if(columns.size() == 1)
    		{
    			//do nothing
    		}
    		else
    		{
    			string order_id = columns[1];
    			if(order_id == "")
    			{
    				continue;
    			}
    			string type = columns[2];
    			int new_price = stoi(columns[3]);
    			if(new_price <= 0)
    			{
    				continue;
    			}
    			int new_quantity = stoi(columns[4]);
    			if(new_quantity <= 0)
    			{
    				continue;
    			}
    			book.modifyOrder(order_id, type, new_price, new_quantity);
    		}
    	}
    	else if(columns[0] == "PRINT")
    	{
    		book.print();
    	}
    	else
    	{
    		//do nothing
    	}
    }

    return 0;
}