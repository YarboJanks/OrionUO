﻿/***********************************************************************************
**
** SelectedObject.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "SelectedObject.h"
//----------------------------------------------------------------------------------
CSelectedObject g_SelectedObject;
CSelectedObject g_LastSelectedObject;
//----------------------------------------------------------------------------------
CSelectedObject::CSelectedObject()
: m_Object(NULL), m_Gump(NULL), m_Serial(0)
{
}
//----------------------------------------------------------------------------------
CSelectedObject::~CSelectedObject()
{
}
//----------------------------------------------------------------------------------
void CSelectedObject::Clear()
{
	WISPFUN_DEBUG("c205_f1");
	m_Object = NULL;
	m_Gump = NULL;
	m_Serial = 0;
}
//----------------------------------------------------------------------------------
void CSelectedObject::Clear(CRenderObject *obj)
{
	WISPFUN_DEBUG("c205_f2");
	if (obj == m_Object)
	{
		m_Object = NULL;
		m_Gump = NULL;
		m_Serial = 0;
	}
}
//----------------------------------------------------------------------------------
void CSelectedObject::Init(CRenderObject *obj, CGump *gump)
{
	WISPFUN_DEBUG("c205_f3");
	m_Object = obj;
	m_Gump = gump;
	m_Serial = (obj != NULL ? obj->Serial : 0);
}
//----------------------------------------------------------------------------------
void CSelectedObject::Init(const CSelectedObject &obj)
{
	WISPFUN_DEBUG("c205_f4");
	m_Object = obj.Object();
	m_Gump = obj.Gump();
	m_Serial = (obj.Object() != NULL ? obj.Object()->Serial : 0);
}
//----------------------------------------------------------------------------------
