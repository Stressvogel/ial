/*
 * ial.h
 *
 *  Created on: Dec 3, 2021
 *      Author: Matthijs Bakker
 */

#ifndef SOFTWARE_IAL_H
#define SOFTWARE_IAL_H

#include <cstdint>

/**
 * Een generic invoerapparaat
 **/
class ial {
public:
	typedef void (*ial_button_cb)(bool is_pressed);

	virtual ~ial();

	/**
	 * Init functie.
	 * Wordt aangeroepen zodra het invoerapparaat moet worden geinitialiseerd.
	 **/
    virtual void ial_init() = 0;

    /**
     * Registreer een callback die moet worden uitgevoerd wanneer een button ingedrukt wordt.
     *
     * @param button_id Implementatie-specifieke button ID (bijv. de FPGA implementatie zal voor waarde 0 de KEY[0] gebruiken)
     * @param priority  Interrupt priority. Een hogere waarde = een lagere prioriteit.
     * @param callback  De functie die zal worden aangeroepen wanneer de button ingedrukt/losgelaten wordt.
     **/
    virtual void ial_register_button_callback(uint8_t button_id = 0, uint8_t priority = 0, ial_button_cb callback = nullptr) = 0;

};

#endif //SOFTWARE_IAL_H
