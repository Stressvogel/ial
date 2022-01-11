/*
 * ial.h
 *
 *  Created on: Jan 11, 2022
 *      Author: Matthijs Bakker
 */

#ifndef LIBRARY_IAL_IAL_H_
#define LIBRARY_IAL_IAL_H_

namespace ial {

/**
 * Een template voor een functie die button callback data kan accepteren.
 **/
typedef void (*button_cb)(bool is_pressed, void *user_data);

} // namespace ial

#endif /* LIBRARY_IAL_IAL_H_ */
