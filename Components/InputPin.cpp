#include "InputPin.h"

InputPin::InputPin()
{
	pComp = NULL;
	m_IsConnected = false;
}

void InputPin::setComponent(Component *pCmp)
{
	this->pComp = pCmp;
}

Component* InputPin::getComponent()
{
	return pComp;
}

void InputPin::setConnected(bool s)
{
	m_IsConnected = s;
}

bool InputPin::isConnected()
{
	return m_IsConnected;
}
