#include "bsp_gpio.h"
#include "PinMap.h"

void pinPeripheral(uint8_t pin, uint32_t ulPeripheral){
	
	if ( g_APinDescription[pin].ulPin & 1 ) // is pin odd?
	{
		uint32_t temp ;

		// Get whole current setup for both odd and even pins and remove odd one
		temp = (PORT->Group[g_APinDescription[pin].ulPort].PMUX[g_APinDescription[pin].ulPin >> 1].reg) & PORT_PMUX_PMUXE( 0xF ) ;
		// Set new muxing
		PORT->Group[g_APinDescription[pin].ulPort].PMUX[g_APinDescription[pin].ulPin >> 1].reg = temp|PORT_PMUX_PMUXO( ulPeripheral ) ;
		// Enable port mux
		PORT->Group[g_APinDescription[pin].ulPort].PINCFG[g_APinDescription[pin].ulPin].reg |= PORT_PINCFG_PMUXEN ;
	}
	else // even pin
	{
		uint32_t temp ;

		temp = (PORT->Group[g_APinDescription[pin].ulPort].PMUX[g_APinDescription[pin].ulPin >> 1].reg) & PORT_PMUX_PMUXO( 0xF ) ;
		PORT->Group[g_APinDescription[pin].ulPort].PMUX[g_APinDescription[pin].ulPin >> 1].reg = temp|PORT_PMUX_PMUXE( ulPeripheral ) ;
		PORT->Group[g_APinDescription[pin].ulPort].PINCFG[g_APinDescription[pin].ulPin].reg |= PORT_PINCFG_PMUXEN ; // Enable port mux
	}
}