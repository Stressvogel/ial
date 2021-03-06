/*
 * ial_device_ps2.cpp
 *
 * Omschrijving:	PS/2 toetsenbord driver
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#include <cstdio>
#include <system.h>

#include "ial_device_ps2.h"

#define SCAN_CODE_RANGE_START	(0x29)
#define SCAN_CODE_KEY_RELEASED	(0xF0 - SCAN_CODE_RANGE_START) // 0xC7

// In ons computer systeem heet de PS/2 port "ps2_0"
// terwijl hij in de Media Computer "PS2_Port" heet
#ifdef PS2_0_NAME
#define __PS2_PORT_NAME		PS2_0_NAME
#else
#define __PS2_PORT_NAME		PS2_PORT_NAME
#endif

namespace ial {

device_ps2::device_ps2() : device() {}

device_ps2::~device_ps2() {}

/**
 * @inheritDoc
 **/
void device_ps2::init() {
	// Open het device
	this->usb_dev = alt_up_ps2_open_dev(__PS2_PORT_NAME);
	alt_up_ps2_init(this->usb_dev);

	// Er blijkt een bug in de IP Core te zitten waardoor interrupts
	// niet werken. We moeten dus een polling based approach gebruiken.
	alt_up_ps2_disable_read_interrupt(this->usb_dev);
}

/**
 * @inheritDoc
 **/
void device_ps2::poll() {
	unsigned char buf = 0;

	// check of (en hoe vaak) er een button ingedrukt is
	while (!alt_up_ps2_read_data_byte(this->usb_dev, &buf)) {
		bool br = false;

		// check of break code, zo ja, haal de key code op.
		if (buf == 0xF0) {
			br = true;
			alt_up_ps2_read_data_byte(this->usb_dev, &buf);
		}

		// check bij elke callback of hij deze button geregistreerd heeft
		for (__callback *cb : this->callbacks) {
			// als de callback deze button geregistreerd heeft, call dan de function
			if ((buf - SCAN_CODE_RANGE_START) == cb->button_id) {
				// als het een break code is, set is_pressed op 0
				if (br) {
					// update state machine naar released
					cb->is_pressed = false;
					// signaleer release
					cb->function(false, cb->user_data);
				} else {
					// skip als het een repeat code is
					if (cb->is_pressed) continue;

					// signaleer press
					cb->function(true, cb->user_data);
					// update state machine naar pressed
					cb->is_pressed = true;
				}
			}
		}
	}
}

/**
 * @inheritDoc
 **/
void device_ps2::register_button_callback(uint8_t button_id, uint8_t /*priority*/, ial::button_cb callback, void *cb_user_data) {
	__callback *cb = new __callback();
	cb->button_id = button_id;
	cb->function = callback;
	cb->user_data = cb_user_data;

	// voeg deze callback to aan de callbacks list
	this->callbacks.push_back(cb);
}

} // namespace ial

