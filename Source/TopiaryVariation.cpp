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

#include "TopiaryVariation.h"

TopiaryVariation::TopiaryVariation()
{
	numItems = 0; // empty list

} // TopiaryVariation

/////////////////////////////////////////////////////////////////////////////

TopiaryVariation::~TopiaryVariation()
{
}

/////////////////////////////////////////////////////////////////////////////

void TopiaryVariation::del(int n)
{
	jassert(n >= 0);
	jassert(n < numItems);
	for (int i = n; i < (numItems - 1); i++)
	{
		swap(i, i + 1);
	}

	numItems--;

} // del

/////////////////////////////////////////////////////////////////////////////

void TopiaryVariation::add(int timestamp, note, length, velocity)
{
	jassert(numItems < (maxItems + 1));

	// adds new one
	dataList[numItems].note = note;
	dataList[numItems].ID = numItems + 1;
	dataList[numItems].velocity = velocity;
	dataList[numItems].length = length;
	dataList[numItems].timestamp = timestamp;
	numItems++;

} // add

/////////////////////////////////////////////////////////////////////////////

void TopiaryVariation::sortByID()
{
	// sorts and then renumbers by ID 

	for (int i = 0; i <= numItems; i++)
	{
		for (int j = i + 1; j < numItems; j++)
		{
			if (dataList[i].ID > dataList[j].ID)
			{
				swap(i, j);
			}
		}
	};

	renumber();

} // sortByID

/////////////////////////////////////////////////////////////////////////////

void TopiaryVariation::renumber()
{
	for (int i = 0; i < numItems; i++)
		dataList[i].ID = i + 1;
} // renumber

/////////////////////////////////////////////////////////////////////////////



