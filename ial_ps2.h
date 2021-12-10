/*
 * ial_ps2.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_IAL_PS2_H_
#define SOFTWARE_IAL_PS2_H_

#include <vector>
#include <altera_up_avalon_ps2.h>
#include <altera_up_ps2_keyboard.h>

#include "ial.h"

/**
 * Een interne struct die de info over een geregistreerde callback bijhoudt.
 **/
struct __callback {
	uint8_t button_id;
	ial::ial_button_cb function;
	void *user_data;
};

/**
 * Een invoerapparaat dat gebruik maakt van een PS2 toetsenbord. <br />
 * <br />
 * Omdat PS2 interrupts niet werken op deze versie van nios gebruiken wij polling.
 **/
class ial_ps2 : public ial {
private:
	/**
	 * Een lijst met alle geregistreerde callbacks.
	 **/
	std::vector<__callback *> callbacks;

	alt_up_ps2_dev *usb_dev;

public:
	ial_ps2();

	~ial_ps2();

	/**
	 * @inheritDoc
	 **/
    void ial_init();

    /**
     * @inheritDoc
     **/
    void ial_poll();

    /**
     * @inheritDoc
     *
     * De button ID is de scancode - 0x29<br />
     * <br />
     * Wij gebruiken <b>priority</b> niet
     **/
    void ial_register_button_callback(uint8_t button_id, uint8_t priority, ial_button_cb callback, void *cb_user_data);

};

#endif /* SOFTWARE_IAL_PS2_H_ */
