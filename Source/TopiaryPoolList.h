/////////////////////////////////////////////////////////////////////////////
/*
This file is part of Topiary, Copyright Tom Tollenaere 2018-19.

Topiary is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Topiary is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Topiary. If not, see <https://www.gnu.org/licenses/>.
*/
/////////////////////////////////////////////////////////////////////////////

#pragma once
#include "Topiary.h"

class TopiaryPoolList
{

public:
	TopiaryPoolList();
	~TopiaryPoolList();
	int numItems;

	void sortByID(); // sort by index n (order in which the variables are in the struct
	void del(int n);
	void add();

	struct header
	{
		int columnID;
		String name;
		int width;
		int type;  // define the type values !!
		bool editable;
		int min = 0;
		int max = 0;
	};

	static const int headerListItems = 5;
	static const int maxItems = 128;
	header headerList[headerListItems];

	struct data // MUST match what has been defined in the headerlist data!!!
	{
		int ID;
		int note;
		String label;
		String description;
		int pool;
	};

	data dataList[maxItems];

	void fillDataList(XmlElement* dList);

	void setIntByIndex(int row, int o, int newInt);

	void setStringByIndex(int row, int i, String newString);

	int getColumnIndexByName(String name);

	void renumber();

	int isNoteInPool(int n);

private:
	void swap(int from, int to)
	{
		int rememberN;
		String rememberS;

		rememberN = dataList[from].ID;
		dataList[from].ID = dataList[to].ID;
		dataList[to].ID = rememberN;

		rememberN = dataList[from].pool;
		dataList[from].pool = dataList[to].pool;
		dataList[to].pool = rememberN;

		rememberN = dataList[from].note;
		dataList[from].note = dataList[to].note;
		dataList[to].note = rememberN;

		rememberS = dataList[from].label;
		dataList[from].label = dataList[to].label;
		dataList[to].label = rememberS;

		rememberS = dataList[from].description;
		dataList[from].description = dataList[to].description;
		dataList[to].description = rememberS;

	} // swap

}; // TopiaryPoolList

#undef TOPIARYLISTMODEL
#undef TOPIARYTABLE
#define TOPIARYLISTMODEL TopiaryPoolList
#define TOPIARYTABLE PoolListTable
#include "TopiaryTableList.h" // header for PoolListTable

   //////////////////////////////////////////////////////////////////


