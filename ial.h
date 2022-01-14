/*
 * ial.h
 *
 * Omschrijving:	Diverse type definities
 * Hoofdauteur:		Matthijs Bakker
 *
 * Project Stressvogel
 * Computer Engineering
 * Windesheim, 2021-2022
 */

#ifndef SOFTWARE_IAL_IAL_H_
#define SOFTWARE_IAL_IAL_H_

namespace ial {

/**
 * Een template voor een functie die button callback data kan accepteren.
 **/
typedef void (*button_cb)(bool is_pressed, void *user_data);

} // namespace ial

#endif /* SOFTWARE_IAL_IAL_H_ */

