/*
 * ial_de2_115.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#include <cstdio>
#include <system.h>
#include "ial_device_de2_115.h"

/**
 * Counter die wordt verhoogd zodra de button losgelaten is
 **/
volatile int __ial_button_pending = 0;

/**
 * @inheritDoc
 **/
extern "C" void __ial_button_irq_init(void);

namespace ial {

device_de2_115::device_de2_115() : device() {}

device_de2_115::~device_de2_115() {}

/**
 * @inheritDoc
 **/
void device_de2_115::init() {
	// zie pagina 47 van de DE2-115 computer manual
	__ial_button_irq_init();
}

/**
 * @inheritDoc
 **/
void device_de2_115::poll() {
	if (__ial_button_pending) {
		while (__ial_button_pending > 0) {
			for (__callback *cb : this->callbacks) {
				// simuleer press en release
				cb->function(true, cb->user_data);
				cb->function(false, cb->user_data);
			}
			--__ial_button_pending;
		}
	}
}

/**
 * @inheritDoc
 **/
void device_de2_115::register_button_callback(uint8_t, uint8_t, ial::button_cb callback, void *cb_user_data) {
	__callback *cb = new __callback();
	cb->function = callback;
	cb->user_data = cb_user_data;

	// voeg deze callback to aan de callbacks list
	this->callbacks.push_back(cb);
}

} // namespace ial
