/*
 * ial_device.h
 *
 * Omschrijving:	Een interface voor een invoerapparaat
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_IAL_DEVICE_H
#define SOFTWARE_IAL_DEVICE_H

#include <cstdint>

#include "ial.h"

namespace ial {

/**
 * Een generic invoerapparaat
 **/
class device {
public:
	device() = default;

	virtual ~device() = default;

	/**
	 * Initialisatie functie.<br />
	 * <br />
	 * Moet worden aangeroepen voordat je andere functies gebruikt.
	 **/
	virtual void init() = 0;

	/**
	 * Check of het device nieuwe informatie heeft.<br />
	 * <br />
	 * Is alleen nodig als het device niet met interrupts werkt.<br />
	 * Als het device met interrupts werkt is het aanroepen van deze functie een NOOP.
	 **/
	virtual void poll() = 0;

	/**
	 * Registreer een callback die moet worden uitgevoerd wanneer een button ingedrukt wordt.
	 *
	 * @param button_id	Implementatie-specifieke button ID (bijv. de FPGA implementatie zal voor waarde 0 de KEY[0] gebruiken)
	 * @param priority	Interrupt priority. Een hogere waarde = een lagere prioriteit.
	 * @param callback	De functie die zal worden aangeroepen wanneer de button ingedrukt/losgelaten wordt.
	 * @param cb_user_data	Een willekeurige data pointer die de user kan meegeven naar de callback
	 **/
	virtual void register_button_callback(uint8_t button_id = 0, uint8_t priority = 0, ial::button_cb callback = nullptr, void *cb_user_data = nullptr) = 0;

};

} // namespace ial

#endif //SOFTWARE_IAL_DEVICE_H

