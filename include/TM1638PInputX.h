/*
 Name:		TM1638PInputX.h
 Created:	12/19/2024 12:33:01 AM
 Author:	djneo
 Editor:	http://www.visualmicro.com
*/

#ifndef _TM1638PInputX_h
#define _TM1638PInputX_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
	
#else
	#include "WProgram.h"
#endif
#include "TM1638plus.h"

#ifndef DEBOUNCE_DLY
	#define DEBOUINCE_DLY	10
#endif

/// @brief function to call whenever a change in button status occurs. used in setButtonsChanged(cb). the first parameter is a uint8_t representing the buttons which have been pressed, and the second is the same but for released buttons.
typedef void (*ButtonsChangedCB)(uint8_t,uint8_t);
typedef void (*BtnPressedCB)(uint8_t);
typedef void (*BtnReleasedCB)(uint8_t);

/// @brief Expanded Input for the TM1638Plus Library
class TMInputX {
protected:
	TM1638plus* m_tm;
	uint32_t m_debounce_time = 0;
	bool m_debouncing = false;
	uint8_t m_buttonCurrent = 0x00;
	uint8_t m_buttonLast = 0x00;
	uint8_t m_buttonChanged = 0x00;
	uint8_t m_buttonJustPressed = 0x00;

	ButtonsChangedCB m_buttonsChangedCallback;
	bool m_isChangedCbEnabled = false;
	BtnPressedCB m_PressedCBs[8];
	uint8_t m_pressCbEnable = 0x00;
	BtnReleasedCB m_ReleasedCBs[8];
	uint8_t m_releaseCbEnable = 0x00;
	void m_runEvents();
public:
	/// @brief Constructor
	/// @param device the TM1638plus device for which to collect input
	TMInputX(TM1638plus* device);

	/// @brief Reads inputs and evaluates button state.
	/// @return If there is a change in any of the button states, readInputs will return True.
	bool readInputs();
	bool getButtonPressed(uint8_t btn);
	bool getButtonJustPressed(uint8_t btn);
	bool getButtonChanged(uint8_t btn);
	bool getButtonJustReleased(uint8_t btn);
	uint8_t getPressed() { return m_buttonCurrent; }
	uint8_t getChanged() { return m_buttonChanged; }
	uint8_t getJustPressed() { return m_buttonJustPressed; }
	uint8_t getJustRleased();
	bool isDebouncing() { return m_debouncing; }

	void setPressedCB(BtnPressedCB callback, uint8_t button);
	void setReleasedCB(BtnReleasedCB callback, uint8_t button);
	void setChangeCB(ButtonsChangedCB callback);

	//set and unset event callbacks

	/// @brief Sets the Buttons Changed event callback. 
	/// @param cb 
	void setChangedCallback(ButtonsChangedCB cb){
		m_buttonsChangedCallback = cb;
		m_isChangedCbEnabled = true;
	}
/*
	TODO:
	/// @brief Sets a Button Just Pressed event callback on a specific button.
	/// @param cb 
	/// @param button 
	void setBtnPressCb(BtnPressedCB cb, uint8_t button);
	
	/// @brief Sets a Button Just Released event callback on a specific button. 
	/// @param cb 
	/// @param button 
	void setBtnReleaseCb(BtnReleasedCB cb, uint8_t button);

	/// @brief Removes a pressed callback from a button.
	/// @param btn 
	void unsetPress(uint8_t btn);


	/// @brief Remopves a released callback from a button.
	/// @param btn 
	void unsetRelease(uint8_t btn);
	*/

	/// @brief Removes the buttons changed callback.
	void unsetChange(){m_isChangedCbEnabled = false;}

};

#endif

