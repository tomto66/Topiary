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

#include "TopiaryPoolList.h"

TopiaryPoolList::TopiaryPoolList()
{
	// initialize the headerlist data

	// headerlist IDs start at 1;
	// datalist IDs start at 1;

	headerList[0].columnID = 1;
	headerList[0].name = "ID";
	headerList[0].width = 20;
	headerList[0].type = Topiary::HeaderType::Int;
	headerList[0].editable = false;

	headerList[1].columnID = 2;
	headerList[1].name = "Note";
	headerList[1].width = 50;
	headerList[1].type = Topiary::HeaderType::Int;
	headerList[1].editable = false;

	headerList[2].columnID = 3;
	headerList[2].name = "Label";
	headerList[2].width = 50;
	headerList[2].type = Topiary::HeaderType::NoteLabel;
	headerList[2].editable = true;

	headerList[3].columnID = 4;
	headerList[3].name = "Description";
	headerList[3].width = 110;
	headerList[3].type = Topiary::HeaderType::String;
	headerList[3].editable = true;

	headerList[4].columnID = 2;
	headerList[4].name = "Pool";
	headerList[4].width = 40;
	headerList[4].type = Topiary::HeaderType::Int;
	headerList[4].editable = false;
	headerList[4].min = 1;
	headerList[4].max = 4;

	numItems = 0; // empty list

} // TopiaryPoolList

/////////////////////////////////////////////////////////////////////////////

TopiaryPoolList::~TopiaryPoolList()
{
}

/////////////////////////////////////////////////////////////////////////////

void TopiaryPoolList::setIntByIndex(int row, int i, int newInt)
{

	jassert(row < numItems);
	jassert(i < headerListItems);
	if (i == 0)
		dataList[row].ID = newInt;
	else if (i == 2)
		dataList[row].note = newInt;
	else if (i == 5)
		dataList[row].pool = newInt;
	else
	{
		jassert(false); // wrong type
	}

} // setIntByID

/////////////////////////////////////////////////////////////////////////////

void TopiaryPoolList::setStringByIndex(int row, int i, String newString)
{

	jassert(row < numItems);
	jassert(i < headerListItems);
	if (i == 3)
		dataList[row].label = newString;
	else if (i == 4)
		dataList[row].description = newString;
	else
	{
		jassert(false); // wrong type
	}
}

/////////////////////////////////////////////////////////////////////////////

void TopiaryPoolList::del(int n)
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

void TopiaryPoolList::add()
{
	jassert(numItems < (maxItems + 1));

	// adds new empty one
	dataList[numItems].note = 1;
	dataList[numItems].label = MidiMessage::getMidiNoteName(1, true, true, 5);
	dataList[numItems].description = dataList[numItems].label;
	dataList[numItems].pool = 1;
	dataList[numItems].ID = numItems + 1;
	numItems++;

} // add

/////////////////////////////////////////////////////////////////////////////

void TopiaryPoolList::sortByID()
{
	// sorts and then renumbers by ID (one might have been deleted)
	// IDs to delete are set to Topiary::ToDeleteID

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

void TopiaryPoolList::renumber()
{
	for (int i = 0; i < numItems; i++)
		dataList[i].ID = i + 1;
} // renumber

/////////////////////////////////////////////////////////////////////////////

int TopiaryPoolList::isNoteInPool(int n)
{
	for (int i = 0; i < numItems; i++)
		if (dataList[i].note == n)
			return i;

	return -1;
}

/////////////////////////////////////////////////////////////////////////////

void TopiaryPoolList::fillDataList(XmlElement* dList)
{
	dList->deleteAllChildElements();
	for (int i = 0; i < numItems; i++)
	{
		XmlElement *child = new XmlElement("Pool");
		child->setAttribute("Note", dataList[i].note);
		child->setAttribute("ID", dataList[i].ID);
		child->setAttribute("Pool", dataList[i].pool);
		child->setAttribute("Label", dataList[i].label);
		child->setAttribute("Description", dataList[i].description);
		dList->addChildElement(child);
	}
}  // fillDataList

/////////////////////////////////////////////////////////////////////////////

int TopiaryPoolList::getColumnIndexByName(String name)
{
	for (int i = 0; i < headerListItems; i++)
		if (name.compare(headerList[i].name) == 0)
			return i;
	jassert(false); // column name not found
	return(-1);
}

/////////////////////////////////////////////
// Create the table model for this one
/////////////////////////////////////////////

#include "TopiaryTableList.cpp"
