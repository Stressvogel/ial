/*
 * ial_device_de2_115.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_IAL_DEVICE_DE2_115_H_
#define SOFTWARE_IAL_DEVICE_DE2_115_H_

#include <vector>

#include "ial_device.h"

extern "C" {
void __interrupt_handler(void);
}

/**
 * Een interne struct die de info over een geregistreerde callback bijhoudt.
 **/
struct __callback {
	ial::button_cb function;
	void *user_data;
};

namespace ial {

/**
 * Een invoerapparaat dat gebruik maakt van de knoppen op het DE2_115 bord.
 **/
class device_de2_115 : public device {
private:
	/**
	 * Een lijst met alle geregistreerde callbacks.
	 **/
	std::vector<__callback *> callbacks;

public:
	device_de2_115();

	~device_de2_115();

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
     * Wij gebruiken <b>priority</b> en <b>button_id</b> niet
     **/
    void register_button_callback(uint8_t button_id, uint8_t priority, ial::button_cb callback, void *cb_user_data);

};

} // namespace ial

#endif /* SOFTWARE_IAL_DEVICE_DE2_115_H_ */
