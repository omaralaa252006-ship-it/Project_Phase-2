#include "Component.h"

Component::Component(const GraphicsInfo &r_GfxInfo)
{
	m_GfxInfo = r_GfxInfo;	
	m_Label = "";
	m_Selected = false;
}

Component::Component() {
	m_Label = "";
	m_Selected = false;
}

void Component::SetSelected(bool s) {
	m_Selected = s;
}

bool Component::IsSelected() const {
	return m_Selected;
}

void Component::ToggleSelected() {
	m_Selected = !m_Selected;
}

GraphicsInfo* Component::GetGraphicsInfo() {
	return &m_GfxInfo;
}

void Component::SetLabel(const string& label) {
	m_Label = label;
}

string Component::GetLabel()const {
	return m_Label;
}

void Component::Edit() {

}


Component::~Component()
{}


