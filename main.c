#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define PIN4      	4u
#define	PIN6		6u
#define PIN21      	21u
#define	PIN22		22u
#define PIN26		26u

#define CORE_FREQ	21000000u
#define DELAY		1000000u

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

gpio_pin_config_t sw_config = {
       kGPIO_DigitalInput,
       0,
   };


const port_pin_config_t sw_in_config = {
	    kPORT_PullUp,                                            /* Internal pull-up resistor is enabled */
	    kPORT_FastSlewRate,                                      /* Fast slew rate is configured */
	    kPORT_PassiveFilterDisable,                              /* Passive filter is disabled */
	    kPORT_OpenDrainDisable,                                  /* Open drain is disabled */
	    kPORT_HighDriveStrength,                                 /* High drive strength is configured */
	    kPORT_MuxAsGpio,                                         /* Pin is configured as PTA4 */
	    kPORT_UnlockRegister                                     /* Pin Control Register fields [15:0] are not locked */
	  };

int main(void) {

	// Habilitamos los relojes de los Puertos a usar

	CLOCK_EnableClock(kCLOCK_PortA);								// Switch 3
	CLOCK_EnableClock(kCLOCK_PortB);								// Red and Blue LED
	CLOCK_EnableClock(kCLOCK_PortC);								// Switch 2
	CLOCK_EnableClock(kCLOCK_PortE);								// Green LED

	// Funcion de GPIO

	PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio); 					// Blue LED GPIO
	PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio); 					// Red LED GPIO
	PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio); 					// Green LED GPIO

	PORT_SetPinConfig(PORTA, PIN4, &sw_in_config);					// Activacion de Switch 3
	PORT_SetPinConfig(PORTC, PIN6, &sw_in_config);					// Activacion de Switch 2

	GPIO_PinInit(GPIOB, PIN22, &led_config);
	GPIO_PinInit(GPIOB, PIN21, &led_config);
	GPIO_PinInit(GPIOE, PIN26, &led_config);

	GPIO_PinInit(GPIOA, PIN4, &sw_config);
	GPIO_PinInit(GPIOC, PIN6, &sw_config);

	uint8_t Switch2 = 0;											//
	uint8_t Switch3 = 0;											//

    while(1){

    	Switch2 = GPIO_PinRead(GPIOC, PIN4);
    	Switch3 = GPIO_PinRead(GPIOA, PIN6);

    	int i = 0;

    	if(!Switch2)
    	{

    		i = i + 1 ;

    		if(i > 4){

    			i = 0;
    		}
    	}

    	else if(!Switch3)
    	{
    		i = i - 1;

    		if(i <0 ){

    			i = 4;
    		}
    	}

    	else if((!Switch2) && (Switch3)){
    		i = 6;
    	}

    	switch (i){

    	case 0:
        	GPIO_PortClear(GPIOE, 1u << PIN26);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
        	GPIO_PortSet(GPIOE, 1u << PIN26);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;

    	case 1:
        	GPIO_PortClear(GPIOB, 1u << PIN21);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
        	GPIO_PortSet(GPIOB, 1u << PIN21);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;

    	case 2:
        	GPIO_PortClear(GPIOB, 1u << PIN21);
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
        	GPIO_PortSet(GPIOB, 1u << PIN21);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;

    	case 3:
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;

    	case 4:
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	GPIO_PortClear(GPIOE, 1u << PIN26);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	GPIO_PortSet(GPIOE, 1u << PIN26);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;

    	case 6:
        	GPIO_PortClear(GPIOB, 1u << PIN21);
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	GPIO_PortClear(GPIOE, 1u << PIN26);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
        	GPIO_PortSet(GPIOB, 1u << PIN21);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	GPIO_PortSet(GPIOE, 1u << PIN26);
        	SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;

    	}

    }
    return 0 ;
}
