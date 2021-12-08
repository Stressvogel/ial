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
	printf("ial_init() called\n");

	// zie pagina 47 van de DE2-115 computer manual
	__ial_button_irq_init();
}

/**
 * @inheritDoc
 **/
void ial_de2_115::ial_poll() {
	if (__ial_button_pending) {
		printf("ial_poll() --- pending: %d\n", __ial_button_pending);

		while (__ial_button_pending > 0) {
			for (__callback *cb : this->callbacks) {
				// simuleer press en release
				cb->callback(true);
				cb->callback(false);
			}
			--__ial_button_pending;
		}
	}
}

/**
 * @inheritDoc
 **/
void ial_de2_115::ial_register_button_callback(uint8_t button_id, uint8_t priority, ial::ial_button_cb callback) {
	printf("ial_register_button_callback() called\n");

	__callback *cb = new __callback();
	cb->button_id = button_id;
	cb->priority = priority;
	cb->callback = callback;

	this->callbacks.push_back(cb);
}
