﻿#include "GAction.h"

GAction::GAction()
{
	m_Target = NULL;
	memset(&m_Action, 0, sizeof(m_Action));
	m_Obj = NULL;
}


GAction::~GAction()
{
	GO::release(m_Target);
	GO::release(m_Obj);
}

void GAction::set(GObject* target, GX::Selector sel, GObject* obj)
{
	GO::retain(target);
	GO::release(m_Target);
	m_Target = target;
	m_Action.sel = sel;
	GO::retain(obj);
	GO::release(m_Obj);
	m_Obj = obj;
}
void GAction::set(GX::Callback cbk, GObject* obj)
{
	GO::release(m_Target);
	m_Target = NULL;
	m_Action.cbk = cbk;
	GO::retain(obj);
	GO::release(m_Obj);
	m_Obj = obj;
}
void GAction::run()
{
	if (m_Target) {
		(m_Target->*m_Action.sel)(m_Obj);
	}
	else {
		m_Action.cbk(m_Obj);
	}
}
