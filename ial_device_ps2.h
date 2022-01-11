/*
 * ial_ps2.h
 *
 *  Created on: Dec 10, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_IAL_DEVICE_PS2_H_
#define SOFTWARE_IAL_DEVICE_PS2_H_

#include <vector>
#include <altera_up_avalon_ps2.h>
#include <altera_up_ps2_keyboard.h>

#include "ial_device.h"

/**
 * Een interne struct die de info over een geregistreerde callback bijhoudt.
 **/
struct __callback {
	uint8_t button_id;
	ial::button_cb function;
	void *user_data;
	bool is_pressed;
};

namespace ial {

/**
 * Een invoerapparaat dat gebruik maakt van een PS2 toetsenbord. <br />
 * <br />
 * Omdat PS2 interrupts niet werken op deze versie van nios gebruiken wij polling.
 **/
class device_ps2 : public device {
private:
	/**
	 * Een lijst met alle geregistreerde callbacks.
	 **/
	std::vector<__callback *> callbacks;

	alt_up_ps2_dev *usb_dev;

public:
	device_ps2();

	~device_ps2();

	/**
	 * @inheritDoc
	 **/
    void init();

    /**
     * @inheritDoc
     **/
    void poll();

    /**
     * @inheritDoc
     *
     * De button ID is de scancode - 0x29<br />
     * <br />
     * Wij gebruiken <b>priority</b> niet
     **/
    void register_button_callback(uint8_t button_id, uint8_t priority, ial::button_cb callback, void *cb_user_data);

};

} // namespace ial

#endif /* SOFTWARE_IAL_DEVICE_PS2_H_ */
