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

class TopiaryPatternList
{

public:
	TopiaryPatternList();
	~TopiaryPatternList();
	int numItems;
	
	void sortByID(); // sort by index n (order in which the variables are in the struct
	void del(int n);
	void add();
	void duplicate(int i);

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

	static const int headerListItems = 3;
	static const int maxItems = 8;
	header headerList[headerListItems];
	
	struct data // MUST match what has been defined in the headerlist data!!!
	{
		int ID;
		String name;
		int measures;
	};
	
	data dataList[maxItems];
	 
	void fillDataList(XmlElement* dList);
	
	//int getIntByID(int row, int ID);
	void setIntByIndex(int row, int o, int newInt);
	
	//String getStringByID(int row, int ID);
	void setStringByIndex(int row, int i, String newString);

	int getColumnIndexByName(String name);

private:
	void swap(int from, int to)
	{
		int rememberN;
		String rememberS;
		
		rememberN = dataList[from].ID;
		dataList[from].ID = dataList[to].ID;
		dataList[to].ID = rememberN;
		
		rememberN = dataList[from].measures;
		dataList[from].measures = dataList[to].measures;
		dataList[to].measures = rememberN;
		
		rememberS = dataList[from].name;
		dataList[from].name = dataList[to].name;
		dataList[to].name = rememberS;
	} // swap
	
}; // TopiaryPatternList

#undef TOPIARYLISTMODEL
#undef TOPIARYTABLE
#define TOPIARYLISTMODEL TopiaryPatternList
#define TOPIARYTABLE PatternListTable
#include "TopiaryTableList.h" // header for PatternListTable

   //////////////////////////////////////////////////////////////////

