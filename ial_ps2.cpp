/*
 * ial_ps2.cpp
 *
 *  Created on: Dec 10, 2021
 *      Author: Matthijs Bakker
 */

#include "ial_ps2.h"

#include <cstdio>
#include <system.h>

#define SCAN_CODE_RANGE_START 0x29

ial_ps2::ial_ps2() : ial() {}

ial_ps2::~ial_ps2() {}

/**
 * @inheritDoc
 **/
void ial_ps2::ial_init() {
	this->usb_dev = alt_up_ps2_open_dev(PS2_PORT_NAME);
	alt_up_ps2_init(this->usb_dev);

	/**
	 * Er blijkt een bug in de IP Core te zitten waardoor interrupts niet werken,
	 * dus we moeten een polling based approach implementeren.
	 */
	alt_up_ps2_disable_read_interrupt(this->usb_dev);
}

/**
 * @inheritDoc
 **/
void ial_ps2::ial_poll() {
	unsigned char buf = 0;
	// check of (en hoe vaak) er een button ingedrukt is
	while (!alt_up_ps2_read_data_byte(this->usb_dev, &buf)) {
		for (__callback *cb : this->callbacks) {
			// als de callback deze button geregistreerd heeft, call dan de function
			if ((buf - SCAN_CODE_RANGE_START) == cb->button_id) {
				// simuleer press en release
				cb->function(true, cb->user_data);
				cb->function(false, cb->user_data);
			}
		}
	}
}

/**
 * @inheritDoc
 **/
void ial_ps2::ial_register_button_callback(uint8_t button_id, uint8_t, ial::ial_button_cb callback, void *cb_user_data) {
	__callback *cb = new __callback();
	cb->button_id = button_id;
	cb->function = callback;
	cb->user_data = cb_user_data;

	this->callbacks.push_back(cb);
}
