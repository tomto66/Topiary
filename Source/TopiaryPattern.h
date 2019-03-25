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

class TopiaryPattern
{

public:
	TopiaryPattern();
	~TopiaryPattern();
	int numItems;

	void sortByID(); // sort by index n (order in which the variables are in the struct
	void del(int n);
	void add(int measure, beat, tick, note, length, velocity);

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

	static const int headerListItems = 8;
	static const int maxItems = 16000;
	header headerList[headerListItems];

	struct data // MUST match what has been defined in the headerlist data!!!
	{
		int ID;
		int measure;
		int beat;
		int tick;
		int note;
		String label;
		int length;
		int velocity;
		int timestamp; // not in header because not in the table !!!
	};

	data dataList[maxItems];

	void fillDataList(XmlElement* dList);
	void setIntByIndex(int row, int o, int newInt);
	void setStringByIndex(int row, int i, String newString);
	int getColumnIndexByName(String name);
	void renumber();


private:
	void swap(int from, int to)
	{
		int rememberN;
		String rememberS;

		rememberN = dataList[from].ID;
		dataList[from].ID = dataList[to].ID;
		dataList[to].ID = rememberN;

		rememberN = dataList[from].beat;
		dataList[from].beat = dataList[to].beat;
		dataList[to].beat = rememberN;
		
		rememberN = dataList[from].measure;
		dataList[from].measure = dataList[to].measure;
		dataList[to].measure = rememberN;
		
		rememberN = dataList[from].tick;
		dataList[from].tick = dataList[to].tick;
		dataList[to].tick = rememberN;

		rememberN = dataList[from].timestamp;
		dataList[from].timestamp = dataList[to].timestamp;
		dataList[to].timestamp = rememberN;
		
		rememberN = dataList[from].note;
		dataList[from].note = dataList[to].note;
		dataList[to].note = rememberN;

		rememberS = dataList[from].label;
		dataList[from].label = dataList[to].label;
		dataList[to].label = rememberS;

		rememberN = dataList[from].length;
		dataList[from].length = dataList[to].length;
		dataList[to].length = rememberN;
		
		rememberN = dataList[from].velocity;
		dataList[from].velocity = dataList[to].velocity;
		dataList[to].velocity = rememberN;

	} // swap

}; // TopiaryPattern

#undef TOPIARYLISTMODEL
#undef TOPIARYTABLE
#define TOPIARYLISTMODEL TopiaryPattern
#define TOPIARYTABLE PatternTable
#include "TopiaryTableList.h" // header for PatternTable

   //////////////////////////////////////////////////////////////////


