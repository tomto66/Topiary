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

class TopiaryVariation
{ // there is never a table to edit this one, so no header either!!!

public:
	TopiaryVariation();
	~TopiaryVariation();
	int numItems;

	void sortByID(); // sort by index n (order in which the variables are in the struct
	void del(int n);
	void add(int timestamp note, length, velocity);
	
	//static const int headerListItems = 5;
	static const int maxItems = 16000;

	struct data 
	{
		int ID;
		int note;
		int length;
		int velocity;
		int timestamp;
	};

	data dataList[maxItems];	
	void renumber();


private:
	void swap(int from, int to)
	{
		int rememberN;
		String rememberS;

		rememberN = dataList[from].ID;
		dataList[from].ID = dataList[to].ID;
		dataList[to].ID = rememberN;

		rememberN = dataList[from].timestamp;
		dataList[from].timestamp = dataList[to].timestamp;
		dataList[to].timestamp = rememberN;
			
		rememberN = dataList[from].note;
		dataList[from].note = dataList[to].note;
		dataList[to].note = rememberN;
		
		rememberN = dataList[from].length;
		dataList[from].length = dataList[to].length;
		dataList[to].length = rememberN;
		
		rememberN = dataList[from].velocity;
		dataList[from].velocity = dataList[to].velocity;
		dataList[to].velocity = rememberN;

	} // swap

}; // TopiaryVariation




