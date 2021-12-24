/*
 * ial_de2_115_irq.c
 *
 * We hebben deze code gescheiden gehouden van ial_de2_115.cpp
 * omdat het anders onoverzichtelijk werd
 * en we dan "extern 'C' {}" enzo moesten gebruiken.
 *
 *  Created on: Dec 8, 2021
 *      Author: Matthijs Bakker
 */

#include "altera_avalon_pio_regs.h"
#include "sys/alt_irq.h"
#include "system.h"

/**
 * Registreert de interrupt
 **/
void				__ial_button_irq_init(void);
/**
 * Interrupt handler die aangeroepen wordt op de falling flank van de button
 **/
static void			__ial_button_irq_handler(void * isr_context, alt_u32 id);

/**
 * @inheritDoc
 **/
extern volatile int	__ial_button_pending;

/**
 * We hoeven geen variabelen aan de ISR te geven dus deze gebruiken we niet.
 **/
static unsigned int	__isr_context;

void __ial_button_irq_init(void) {
	// zie pagina 47 van de DE2-115 computer manual !!!!!!!!
	// daar gebruiken ze niet alt_irq_* maar doen ze alles handmatig.
	// nogsteeds handig om ff te lezen wat daar staat

	// we gebruiken geen context maar ok.
	void * isr_context_ptr = (void *) &__isr_context;

	// schakel interrupt in voor button 1
	IOWR_ALTERA_AVALON_PIO_IRQ_MASK(PUSHBUTTONS_BASE, 1);
	// clear alle 'pending' interrupts
	IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 1);

	// registreer de interrupt service handler
	alt_irq_register(PUSHBUTTONS_IRQ, isr_context_ptr, __ial_button_irq_handler);

	// enable de interrupt
	alt_irq_enable(PUSHBUTTONS_IRQ);
}

/**
 * De interrupt service routine waarin we de pending count verhogen.
 * De pending count wordt dan in de IAL implementatie afgelezen zodra de game pollt.
 **/
static void __ial_button_irq_handler(void *isr_context, alt_u32 id) {
   IOWR_ALTERA_AVALON_PIO_EDGE_CAP(PUSHBUTTONS_BASE, 1);

   ++__ial_button_pending;
}

