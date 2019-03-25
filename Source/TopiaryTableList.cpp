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
// Needs TOPIARYLISTMODEL defined; that will actually be a datalist model!!!
// Needs TOPIARYTABLE defined; that will be the name of this table model
/////////////////////////////////////////////////////////////////////////////

#pragma once
//#include "TopiaryTable.h"

#if defined(BEATZ) || defined(CHORDZ)

TOPIARYTABLE::TOPIARYTABLE()
{
	tableComponent.setColour(ListBox::outlineColourId, Colours::grey);
	tableComponent.setOutlineThickness(1);
	model = nullptr;
	numRows = 0;
	tableData.reset(new XmlElement("TopiaryTable")); // make sure it's not a null pointer   
	dataList = new XmlElement("DataList");
	//columnList = new XmlElement("HeaderList");
	tableData->addChildElement(dataList);
	//tableData->addChildElement(columnList);
	addAndMakeVisible(tableComponent); // see if we do that here or in setModel
	
} // TOPIARYTABLE

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::setHeader()
{
	headerSet = true;
} // ~TOPIARYTABLE

//////////////////////////////////////////////////////////////////////////////////////

bool TOPIARYTABLE::isHeaderSet()
{
	return headerSet;
} // isHeaderSet

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::setModel(TOPIARYLISTMODEL *m)
{
/*
		columnList = h;
		dataList = d;
		if (dataList == nullptr)
			dataList = dummyDataList->getFirstChildElement(); // may happen at initialization - dummyDataList is just a temporary XmlElement

		if (dataList != nullptr)
			numRows = dataList->getNumChildElements();
		else
			jassert(false);
*/
		model = m;
		if (!headerSet) // if the column has already been set, we are probably loading a new preset; ignore 
		{
			for (int h =0; h< model->headerListItems; h++)
			{  
				// type is for internal use, not to show in the header
				tableComponent.getHeader().addColumn(m->headerList[h].name,
														m->headerList[h].columnID,
														m->headerList[h].width,
														10,
														400,
														//TableHeaderComponent::defaultFlags);
														TableHeaderComponent::visible + TableHeaderComponent::sortable);
				/*
				XmlElement *child = new XmlElement("Column");
				child->setAttribute("columnID", String(m->headerList->columnID));
				child->setAttribute("name", m->headerList->name);
				child->setAttribute("width", String(m->headerList->width));
				child->setAttribute("type", String(m->headerList->type));
				child->setAttribute("editable", (m->headerList->editable) ? "true" : "false");
				child->setAttribute("min", String(m->headerList->min));
				child->setAttribute("max", String(m->headerList->max));
				columnList->addChildElement(child);
					*/	
			}
			
			headerSet = true;
		}
		
		tableComponent.getHeader().setSortColumnId(1, true);
		
		tableComponent.setMultipleSelectionEnabled(false);
		if (numRows > 0) selectRow(1);
		tableComponent.getHeader().setStretchToFitActive(true);
		updateContent();
		
} // setModel


//////////////////////////////////////////////////////////////////////////////////////


int TOPIARYTABLE::getNumRows() 
{
		return numRows;
		
} //getNumRows

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::paintRowBackground(Graphics& g, int rowNumber, int /*width*/, int /*height*/, bool rowIsSelected) 
{
		auto alternateColour = getLookAndFeel().findColour(ListBox::backgroundColourId)
			.interpolatedWith(getLookAndFeel().findColour(ListBox::textColourId), 0.03f);
		if (rowIsSelected)
			g.fillAll(TopiaryColour::brightBlue);
		else if (rowNumber % 2)
			g.fillAll(alternateColour);
			
} // PaintRowBackground

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::paintCell(Graphics& g, int rowNumber, int columnId, int width, int height, bool rowIsSelected) 
{
	UNUSED(rowIsSelected)
	// below controls the cell text color; in the demo the ID gets a different color (dark blue - we've taken that out so rowIsSelected is no longer used really)
	// cell background is in paintRowBackground
	
	g.setColour(getLookAndFeel().findColour(ListBox::textColourId));
	g.setFont(font);

	if (auto* rowElement = dataList->getChildElement(rowNumber))
	{
		auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));
		g.drawText(text, 2, 0, width - 4, height, Justification::centredLeft, true);
	}

	g.setColour(getLookAndFeel().findColour(ListBox::backgroundColourId));
	g.fillRect(width - 1, 0, 1, height);
	
} // paintCell

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::sortOrderChanged(int newSortColumnId, bool isForwards) 
{

		if (newSortColumnId != 0)
		{
			DataSorter sorter(getAttributeNameForColumnId(newSortColumnId), isForwards);
			dataList->sortChildElements(sorter);

			tableComponent.updateContent();
		}
		
} // sortOrderChanged

//////////////////////////////////////////////////////////////////////////////////////

Component* TOPIARYTABLE::refreshComponentForCell(int rowNumber, int columnId, bool /*isRowSelected*/,
		Component* existingComponentToUpdate) 
{
		if (columnId != 1)
		{
			const auto& columnName = tableComponent.getHeader().getColumnName(columnId);
			//see if this column is editable
			//auto columnDefinition = columnList->getChildByAttribute("name", columnName);
			//auto columnDefinition = model->headerList[columnId - 1].name;

			//auto editable = columnDefinition->getStringAttribute("editable");
			int colNumber = model->getColumnIndexByName(columnName);  
			auto editable = model->headerList[colNumber].editable;

			if (editable) {

				auto* textLabel = static_cast<EditableTextCustomComponent*> (existingComponentToUpdate);

				if (textLabel == nullptr) textLabel = new EditableTextCustomComponent(*this);

				textLabel->setRowAndColumn(rowNumber, columnId);
				return textLabel;
			}
			else return nullptr;
		}

		jassert(existingComponentToUpdate == nullptr);
		return nullptr;
		
} // refreshComponentForCell

//////////////////////////////////////////////////////////////////////////////////////

int TOPIARYTABLE::getColumnAutoSizeWidth(int columnId) 
{
		if (columnId == 9)
			return 50;

		int widest = 32;

		for (auto i = getNumRows(); --i >= 0;)
		{
			if (auto* rowElement = dataList->getChildElement(i))
			{
				auto text = rowElement->getStringAttribute(getAttributeNameForColumnId(columnId));

				widest = jmax(widest, font.getStringWidth(text));
			}
		}

		return widest + 8;
		
} // getColumnAutoSizeWidth

//////////////////////////////////////////////////////////////////////////////////////

int TOPIARYTABLE::getSelectedRow()
{
	return tableComponent.getSelectedRow(0);
	
} // getSelectedRow

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::selectRow(int i)
{
	tableComponent.selectRow(i);
	
} // selectRow

//////////////////////////////////////////////////////////////////////////////////////

int TOPIARYTABLE::getSelection(const int rowNumber) const
{  
		return dataList->getChildElement(rowNumber)->getIntAttribute("Select");
		
} // getSelection

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::setSelection(const int rowNumber, const int newSelection)
{
		dataList->getChildElement(rowNumber)->setAttribute("Select", newSelection);
		
} // setSelection

//////////////////////////////////////////////////////////////////////////////////////

String TOPIARYTABLE::getText(const int columnNumber, const int rowNumber) const
{
	return dataList->getChildElement(rowNumber)->getStringAttribute(getAttributeNameForColumnId(columnNumber));
	
} // getText

//////////////////////////////////////////////////////////////////////////////////////

String TOPIARYTABLE::setText(const int columnNumber, const int rowNumber, const String& newText)
{
	String validatedText;
	// check input, type etc here!!!
	const auto& columnName = tableComponent.getHeader().getColumnName(columnNumber);
	// find the column definition in columnList

	// columnId is index in the model
	int columnIndex = model->getColumnIndexByName(columnName);

	//auto columnDefinition = model->headerList[columnId - 1].name;
	//auto type = columnDefinition->getStringAttribute("type");
	auto type = model->headerList[columnIndex].type;

	if (type == Topiary::HeaderType::Int)
	{
		// see if valid integer; if not make it 1 or minimum
		int i = newText.getIntValue();

		// if valid integer, see if it's beween the bounds
		int min = model->headerList[columnIndex].min;
		int max = model->headerList[columnIndex].max;

		if (i >= min)
		{
			if (i > max) i = max;
		}
		else i = min;
		validatedText = String(i);
	}
	
	else if (type == Topiary::HeaderType::NoteLabel)
	{
		validatedText = validateNote(newText);
		model->setStringByIndex(rowNumber, columnIndex, validatedText);
		int noteNumber = validNoteNumber(validatedText);
		columnIndex = model->getColumnIndexByName("NoteNumber");
		dataList->getChildElement(rowNumber)->setAttribute("NoteNumber", noteNumber);
		model->setIntByIndex(rowNumber, columnIndex, noteNumber);
	}
	else
	{
		validatedText = newText;
		model->setStringByIndex(rowNumber, columnIndex, newText);
	}

	// below writes in the table; writing in the model is done above!
	dataList->getChildElement(rowNumber)->setAttribute(columnName, validatedText);

	//if (broadcaster != nullptr)
	//{
	//	broadcaster->sendActionMessage(broadcastMessage);
	//}

#ifdef TOPIARYMODEL
	if (model != nullptr) // i.e. we are editing a pattern or pool notes (otherwise model == nullptr)
	{
		//model->validateTableEdit(pattern, dataList->getChildElement(rowNumber), columnName);
		int remember = tableComponent.getSelectedRow(0);
		//setDataLists(columnList, dataList);  // force refresh
		selectRow(remember);
	}
#endif
	return validatedText;
} // setText

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::updateContent()
{
	numRows = model->numItems;
	model->fillDataList(dataList);
	
	tableComponent.updateContent();
} // updateContent

//////////////////////////////////////////////////////////////////////////////////////

void TOPIARYTABLE::resized() 
{
	tableComponent.setBoundsInset(BorderSize<int>(8));
} // resized

//////////////////////////////////////////////////////////////////////////////////////

//void TOPIARYTABLE::setBroadcaster(ActionBroadcaster *b, String msg) 
//{

	// broadcaster = b;
	// broadcastMessage = msg;
//}

//////////////////////////////////////////////////////////////////////////////////////


#endif // main #if defined