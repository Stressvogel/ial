/*
 * ial_de2_115.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_IAL_DE2_115_H_
#define SOFTWARE_IAL_DE2_115_H_

#include <vector>

#include "ial.h"

extern "C" {
void __interrupt_handler(void);
}

struct __callback {
	uint8_t button_id, priority;
	ial::ial_button_cb callback;
};

/**
 * Een invoerapparaat dat gebruik maakt van de knoppen op het DE2_115 bord.
 **/
class ial_de2_115 : public ial {
private:
	std::vector<__callback *> callbacks;

public:
	ial_de2_115();

	~ial_de2_115();

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
     **/
    void ial_register_button_callback(uint8_t button_id, uint8_t priority, ial_button_cb callback);

};

#endif /* SOFTWARE_IAL_DE2_115_H_ */
