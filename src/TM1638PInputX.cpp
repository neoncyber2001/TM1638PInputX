/*
 Name:		TM1638PInputX.cpp
 Created:	12/19/2024 12:33:01 AM
 Author:	djneo
 Editor:	http://www.visualmicro.com
*/

#include "TM1638PInputX.h"

void TMInputX::m_runEvents()
{
	if(m_buttonChanged>0&&m_isChangedCbEnabled){
		m_buttonsChangedCallback(m_buttonJustPressed,this->getJustRleased());
	}
	uint8_t selector = 0x01;
	for(int i=0; i<8; i++){
		uint8_t prs = m_buttonJustPressed & (selector<<i);
		uint8_t rel = this->getJustRleased() & (selector<<i);

		if(prs>0 && (m_pressCbEnable &(0x01<<i))>0){
			m_PressedCBs[i](i);
		}

		if(rel>0 && (m_releaseCbEnable &(0x01<<i))>0){
			m_ReleasedCBs[i](i);
		}
	}
}

TMInputX::TMInputX(TM1638plus *device)
{
	m_tm = device;
}

bool TMInputX::readInputs()
{
	if (!m_debouncing) {
		m_buttonLast = m_buttonCurrent;
		m_buttonCurrent = m_tm->readButtons();
		m_buttonChanged = m_buttonLast ^ m_buttonCurrent;
		if(m_buttonChanged > 0){
			m_debounce_time = millis() + DEBOUINCE_DLY;
			m_debouncing = true;
			m_buttonJustPressed = (uint8_t)(m_buttonChanged & m_buttonCurrent);
			this->m_runEvents();
			return true;
		}
	}
	else {
		if (m_debounce_time > millis()) {
			m_debouncing = false;
		}
	}
	return false;
}

bool TMInputX::getButtonPressed(uint8_t btn)
{
	if ((m_buttonCurrent & (0x01 << btn))>0) {
		return true;
	}
	else {
		return false;
	}
}

bool TMInputX::getButtonJustPressed(uint8_t btn)
{
	if ((m_buttonJustPressed & (0x01 << btn)) > 0) {
		return true;
	}
	return false;
}

bool TMInputX::getButtonChanged(uint8_t btn)
{
	if ((m_buttonChanged & (0x01 << btn)) > 0) {
		return true;
	}
	return false;
}

bool TMInputX::getButtonJustReleased(uint8_t btn)
{
	if ((this->getJustRleased() & (0x01 << btn)) > 0) {
		return true;
	}
	return false;
}

uint8_t TMInputX::getJustRleased()
{
	return (~m_buttonJustPressed & m_buttonChanged);
}

void TMInputX::setPressedCB(BtnPressedCB callback, uint8_t button)
{
	m_PressedCBs[button] = callback;
	m_pressCbEnable = m_pressCbEnable | (0x01<<button);
}


void TMInputX::setReleasedCB(BtnReleasedCB callback, uint8_t button)
{
	m_ReleasedCBs[button] = callback;
	m_releaseCbEnable = m_releaseCbEnable | (0x01<<button);
}

void TMInputX::setChangeCB(ButtonsChangedCB callback)
{
	//todo
}