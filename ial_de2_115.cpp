/*
 * ial_de2_115.cpp
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#include "ial_de2_115.h"

#include <cstdio>
#include <system.h>

ial_de2_115::ial_de2_115() : ial() {}

ial_de2_115::~ial_de2_115() {}

/**
 * Counter die wordt verhoogd zodra de button losgelaten is
 **/
volatile int __ial_button_pending = 0;

/**
 * @inheritDoc
 **/
extern "C" void __ial_button_irq_init(void);

/**
 * @inheritDoc
 **/
void ial_de2_115::ial_init() {
	// zie pagina 47 van de DE2-115 computer manual
	__ial_button_irq_init();
}

/**
 * @inheritDoc
 **/
void ial_de2_115::ial_poll() {
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
void ial_de2_115::ial_register_button_callback(uint8_t, uint8_t, ial::ial_button_cb callback, void *cb_user_data) {
	__callback *cb = new __callback();
	cb->function = callback;
	cb->user_data = cb_user_data;

	this->callbacks.push_back(cb);
}
