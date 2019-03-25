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

#include "TopiaryPattern.h"

TopiaryPattern::TopiaryPattern()
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
	headerList[1].name = "Measure";
	headerList[1].width = 70;
	headerList[1].type = Topiary::HeaderType::Int;
	headerList[1].editable = true;
	headerList[1].min = 0;
	headerList[1].max = 32;
	
	headerList[2].columnID = 3;
	headerList[2].name = "Beat";
	headerList[2].width = 40;
	headerList[2].type = Topiary::HeaderType::Int;
	headerList[2].editable = true;
	headerList[2].min = 0;
	headerList[2].max = 3;   // careful - needs to be re-set if meter changes!!!

	headerList[3].columnID = 4;
	headerList[3].name = "Tick";
	headerList[3].width = 40;
	headerList[3].type = Topiary::HeaderType::Int;
	headerList[3].editable = true;
	headerList[3].min = 0;
	headerList[3].max = Topiary::TICKS_PER_QUARTER - 1;
	
	headerList[4].columnID = 5;
	headerList[4].name = "Note";
	headerList[4].width = 40;
	headerList[4].type = Topiary::HeaderType::Int;
	headerList[4].editable = false;
	headerList[4].min = 0;
	headerList[4].max = 127;
	
	headerList[5].columnID = 6;
	headerList[5].name = "Label";
	headerList[5].width = 40;
	headerList[5].type = Topiary::HeaderType::NoteLabel;
	headerList[5].editable = true;

	headerList[6].columnID = 7;
	headerList[6].name = "Length";
	headerList[6].width = 50;
	headerList[6].type = Topiary::HeaderType::Int;
	headerList[6].editable = true;
	headerList[6].min = 1;
	headerList[6].max = 10000;

	headerList[7].columnID = 8;
	headerList[7].name = "Velocity";
	headerList[7].width = 50;
	headerList[7].type = Topiary::HeaderType::Int;
	headerList[7].editable = true;
	headerList[7].min = 0;
	headerList[7].max = 127;
	
	// timstamp not defined here because not in the table!!!
	
	numItems = 0; // empty list

} // TopiaryPattern

/////////////////////////////////////////////////////////////////////////////

TopiaryPattern::~TopiaryPattern()
{
}

/////////////////////////////////////////////////////////////////////////////

void TopiaryPattern::setIntByIndex(int row, int i, int newInt)
{

	jassert(row < numItems);
	jassert(i < headerListItems);
	switch(i)
	{
		case 0:
			dataList[row].ID = newInt;
			break;
		case 1:
			dataList[row].measure = newInt;
			break;
		case 2:
			dataList[row].beat = newInt;
			break;
		case 3:
			dataList[row].tick = newInt;
			break;
		case 4:
			dataList[row].note = newInt;
			break;
		case 6:
			dataList[row].length = newInt;
			break;
		case 7:
			dataList[row].velocity = newInt;
			break;
		default:
			jassert(false); // wrong type
	}
	

} // setIntByID

/////////////////////////////////////////////////////////////////////////////

void TopiaryPattern::setStringByIndex(int row, int i, String newString)
{

	jassert(row < numItems);
	jassert(i < headerListItems);
	if (i == 4)
		dataList[row].label = newString;
	else
	{
		jassert(false); // wrong type
	}
}

/////////////////////////////////////////////////////////////////////////////

void TopiaryPattern::del(int n)
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

void TopiaryPattern::add(int measure, beat, tick, note, length, velocity)
{
	jassert(numItems < (maxItems + 1));

	// adds new one
	dataList[numItems].note = note;
	dataList[numItems].label = MidiMessage::getMidiNoteName(1, true, true, 5);
	dataList[numItems].ID = numItems + 1;
	dataList[numItems].measure = measure;
	dataList[numItems].beat = beat;
	dataList[numItems].tick = tick;
	dataList[numItems].velocity = velocity;
	dataList[numItems].length = length;
	numItems++;

} // add

/////////////////////////////////////////////////////////////////////////////

void TopiaryPattern::sortByID()
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

void TopiaryPattern::renumber()
{
	for (int i = 0; i < numItems; i++)
		dataList[i].ID = i + 1;
} // renumber

/////////////////////////////////////////////////////////////////////////////



void TopiaryPattern::fillDataList(XmlElement* dList)
{
	dList->deleteAllChildElements();
	for (int i = 0; i < numItems; i++)
	{
		XmlElement *child = new XmlElement("Note");
		child->setAttribute("Note", dataList[i].note);
		child->setAttribute("ID", dataList[i].ID);
		child->setAttribute("Measure", dataList[i].measure);
		child->setAttribute("Beat", dataList[i].beat);
		child->setAttribute("Tick", dataList[i].tick);
		child->setAttribute("Velocity", dataList[i].velocity);
		child->setAttribute("Length", dataList[i].length);
		child->setAttribute("Label", dataList[i].label);

		dList->addChildElement(child);
	}
}  // fillDataList

/////////////////////////////////////////////////////////////////////////////

int TopiaryPattern::getColumnIndexByName(String name)
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

