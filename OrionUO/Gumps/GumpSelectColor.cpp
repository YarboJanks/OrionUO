﻿/***********************************************************************************
**
** GumpSelectColor.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GumpSelectColor.h"
#include "../Managers/ColorManager.h"
#include "../Managers/GumpManager.h"
#include "GumpOptions.h"
//----------------------------------------------------------------------------------
CGumpSelectColor::CGumpSelectColor(uint serial, short x, short y, SELECT_COLOR_GUMP_STATE state)
: CGump(GT_SELECT_COLOR, serial, x, y), m_State(state), m_ColorRef(1),
m_SelectedIndex(10), m_Slider(NULL), m_DataBox(NULL)
{
}
//----------------------------------------------------------------------------------
CGumpSelectColor::~CGumpSelectColor()
{
}
//----------------------------------------------------------------------------------
void CGumpSelectColor::UpdateContent()
{
	WISPFUN_DEBUG("c121_f1");
	if (m_Items == NULL)
	{
		Add(new CGUIGumppic(0x0906, 0, 0));

		Add(new CGUIButton(ID_GSC_BUTTON_OKAY, 0x0907, 0x0909, 0x0908, 208, 138));

		m_Slider = (CGUISlider*)Add(new CGUISlider(ID_GSC_SLIDER, 0x0845, 0x0846, 0x0846, 0, false, false, 39, 142, 145, 0, 4, m_ColorRef));

		m_DataBox = (CGUIDataBox*)Add(new CGUIDataBox());
	}
	else
		m_DataBox->Clear();

	const int cellWidthX = 8;
	const int cellWidthY = 8;
	m_SelectedIndex = 10;

	ushort startColor = m_ColorRef + 1;

	puchar huesData = (puchar)g_ColorManager.GetHuesRangePointer() + 32 + 4;
	const int colorOffsetDivider = sizeof(HUES_GROUP) - 4;
	bool focused = true;

	IFOR(y, 0, 10)
	{
		IFOR(x, 0, 20)
		{
			int colorIndex = (startColor + ((startColor + (startColor << 2)) << 1)) << 3;

			colorIndex += (colorIndex / colorOffsetDivider) << 2;
			ushort color = *(pushort)(huesData + colorIndex);

			uint clr = g_ColorManager.Color16To32(color);

			CGUIColoredPolygone *polygone = (CGUIColoredPolygone*)m_DataBox->Add(new CGUIColoredPolygone(ID_GSC_COLORS + (x * 30 + y), startColor, 34 + (x * cellWidthX), 34 + (y * cellWidthY), cellWidthX, cellWidthY, clr));
			polygone->CallOnMouseUp = true;
			polygone->Focused = focused;
			focused = false;

			startColor += 5;
		}
	}
}
//----------------------------------------------------------------------------------
void CGumpSelectColor::GUMP_BUTTON_EVENT_C
{
	WISPFUN_DEBUG("c121_f2");
	if (serial == ID_GSC_BUTTON_OKAY && m_DataBox != NULL)
	{
		ushort color = 0;

		QFOR(item, m_DataBox->m_Items, CBaseGUI*)
		{
			if (item->Serial == m_SelectedIndex)
			{
				OnSelectColor(item->Color);

				break;
			}
		}
	}
	else if (serial >= ID_GSC_COLORS)
	{
		m_SelectedIndex = serial;
		m_WantRedraw = true;

		QFOR(item, m_DataBox->m_Items, CBaseGUI*)
			((CGUIColoredPolygone*)item)->Focused = (item->Serial == m_SelectedIndex);
	}
}
//----------------------------------------------------------------------------------
void CGumpSelectColor::GUMP_SLIDER_CLICK_EVENT_C
{
	WISPFUN_DEBUG("c121_f3");
	OnSliderMove(serial);
}
//----------------------------------------------------------------------------------
void CGumpSelectColor::GUMP_SLIDER_MOVE_EVENT_C
{
	WISPFUN_DEBUG("c121_f4");
	if (m_Slider != NULL && m_ColorRef != m_Slider->Value)
	{
		m_ColorRef = m_Slider->Value;
		m_WantUpdateContent = true;
	}
}
//----------------------------------------------------------------------------------
void CGumpSelectColor::OnSelectColor(const ushort &color)
{
	WISPFUN_DEBUG("c121_f5");
	CGumpOptions *gump = (CGumpOptions*)g_GumpManager.UpdateGump(g_PlayerSerial, 0, GT_OPTIONS);

	if (gump != NULL)
		gump->UpdateColor(m_State, color);

	m_RemoveMark = true;
}
//----------------------------------------------------------------------------------
