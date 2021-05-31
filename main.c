#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define	PIN4		4u
#define	PIN6		6u
#define	PIN21		21u
#define PIN22      	22u
#define PIN26		26u

uint8_t Sw1 = 0;
uint8_t Sw2 = 0;

gpio_pin_config_t sw_config = {
        kGPIO_DigitalInput,
        0,
    };

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };


int main(void) {

	const port_pin_config_t porta_pin4_config = {
		    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
		    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
		    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
		    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
		    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
		    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
		    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	const port_pin_config_t portc_pin6_config = {
			kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
			kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
			kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
			kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
			kPORT_HighDriveStrength,                                 /* High drive strength is configured */
			kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
			kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
			  };

	CLOCK_EnableClock(kCLOCK_PortA);
	CLOCK_EnableClock(kCLOCK_PortB);
	CLOCK_EnableClock(kCLOCK_PortC);
	CLOCK_EnableClock(kCLOCK_PortE);

	PORT_SetPinConfig(PORTA, PIN4, &porta_pin4_config);
	PORT_SetPinConfig(PORTC, PIN6, &portc_pin6_config);

	PORT_SetPinMux(PORTA, PIN4, kPORT_MuxAsGpio);					// Switch 3
	PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAsGpio);					// Switch 2

	PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio);			 		// Blue LED
	PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio); 					// Red LED
	PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio); 					// Green LED

	GPIO_PinInit(GPIOA, PIN4, &sw_config);
	GPIO_PinInit(GPIOC, PIN6, &sw_config);

	GPIO_PinInit(GPIOB, PIN21, &led_config);
	GPIO_PinInit(GPIOB, PIN22, &led_config);
	GPIO_PinInit(GPIOE, PIN26, &led_config);

    while(1) {

    	GPIO_PortClear(GPIOB, 1u << PIN21);
    	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    	GPIO_PortSet(GPIOB, 1u << PIN21);
    	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
     	GPIO_PortClear(GPIOB, 1u << PIN22);
     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
     	GPIO_PortSet(GPIOB, 1u << PIN22);
     	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    	GPIO_PortClear(GPIOE, 1u << PIN26);
    	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    	GPIO_PortSet(GPIOE, 1u << PIN26);
    	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

    }
    return 0 ;
}
