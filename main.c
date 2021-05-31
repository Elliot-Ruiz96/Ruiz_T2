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

uint8_t Sw2 = 0;
uint8_t Sw3 = 0;

gpio_pin_config_t sw2_config = {
        kGPIO_DigitalInput,
        0,
    };

gpio_pin_config_t sw3_config = {
        kGPIO_DigitalInput,
        0,
    };

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        0,
    };


int main(void) {

	const port_pin_config_t sw3_config = {
		    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
		    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
		    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
		    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
		    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
		    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
		    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
		  };

	const port_pin_config_t sw2_config = {
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

	PORT_SetPinConfig(PORTA, PIN4, &sw3_config);
	PORT_SetPinConfig(PORTC, PIN6, &sw2_config);

	PORT_SetPinMux(PORTA, PIN4, kPORT_MuxAsGpio);					// Switch 3
	PORT_SetPinMux(PORTC, PIN6, kPORT_MuxAsGpio);					// Switch 2

	PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio);			 		// Blue LED
	PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio); 					// Red LED
	PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio); 					// Green LED

	GPIO_PinInit(GPIOA, PIN4, &sw3_config);
	GPIO_PinInit(GPIOC, PIN6, &sw2_config);

	GPIO_PinInit(GPIOB, PIN21, &led_config);
	GPIO_PinInit(GPIOB, PIN22, &led_config);
	GPIO_PinInit(GPIOE, PIN26, &led_config);

    while(1){

    	int i=0;

    	if(Sw2){

    		i++;

    		if(i == 5){
    			i = 0;
    		}

    	}

    	else if(Sw3){

    		i--;

    		if(i == -1){
    			i = 4;
    		}

    	}

    	else if(Sw2 && Sw3){

    		i = 6;

    	}

    	switch(i){

    	case 0:
    		GPIO_PortClear(GPIOB, 1u << PIN21);
    		GPIO_PortClear(GPIOB, 1u << PIN22);

    		GPIO_PortSet(GPIOE, 1u << PIN26);
    		break;
    	case 1:
    		GPIO_PortClear(GPIOB, 1u << PIN22);
    		GPIO_PortClear(GPIOE, 1u << PIN26);

    		GPIO_PortSet(GPIOB, 1u << PIN21);
    		break;
    	case 2:
    		GPIO_PortSet(GPIOB, 1u << PIN21);
    		GPIO_PortSet(GPIOB, 1u << PIN22);
    		break;
    	case 3:
    		GPIO_PortClear(GPIOB, 1u << PIN21);
    		GPIO_PortClear(GPIOE, 1u << PIN26);

    		GPIO_PortSet(GPIOB, 1u << PIN22);
    	    break;
    	case 4:
    		GPIO_PortSet(GPIOB, 1u << PIN22);
    		GPIO_PortSet(GPIOE, 1u << PIN26);
    		break;
    	case 6:
    		GPIO_PortSet(GPIOB, 1u << PIN21);
    		GPIO_PortSet(GPIOB, 1u << PIN22);
    		GPIO_PortSet(GPIOE, 1u << PIN26);
    		break;

    	}

    }
    return 0 ;
}
