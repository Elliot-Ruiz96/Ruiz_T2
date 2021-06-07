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

#define ZERO		0x00u
#define ONE			0x01u
#define TWO			0x02u
#define THREE		0x03u

typedef enum{											// Variable ennumerada

	GREEN,
	BLUE,
	PURPLE,
	RED,
	YELLOW,
	WHITE,

} State_Color;

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

gpio_pin_config_t sw_config = {
       kGPIO_DigitalInput,
       0,
   };


const port_pin_config_t sw_in_config = {
	    kPORT_PullUp,
	    kPORT_FastSlewRate,
	    kPORT_PassiveFilterDisable,
	    kPORT_OpenDrainDisable,
	    kPORT_HighDriveStrength,
	    kPORT_MuxAsGpio,
	    kPORT_UnlockRegister
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

	GPIO_PinInit(GPIOB, PIN22, &led_config);						// Inicializar
	GPIO_PinInit(GPIOB, PIN21, &led_config);
	GPIO_PinInit(GPIOE, PIN26, &led_config);

	GPIO_PinInit(GPIOA, PIN4, &sw_config);
	GPIO_PinInit(GPIOC, PIN6, &sw_config);

	State_Color Current_State = GREEN;

	uint8_t Switch2;
	uint8_t Switch3;
	uint8_t i = 0, MAX = 4, MIN = 0;
	uint8_t SwitchTotal;

    while(1){

    	Switch2 = GPIO_PinRead(GPIOC, PIN6);
    	Switch3 = GPIO_PinRead(GPIOA, PIN4);

    	Switch2 = Switch2 << 1;										// Corrimiento 0001 -> 0010
    	SwitchTotal = Switch2 | Switch3;							// Bitwise OR

    	switch (Current_State){
    	case GREEN:
        	GPIO_PortClear(GPIOE, 1u << PIN26);
        	GPIO_PortSet(GPIOE, 1u << PIN26);
        	if(ZERO == Switch_Total){
        		Current_State = WHITE;
        	}
        	else if(ONE){
        		Current_State = BLUE;
        	}
        	else if(TWO){
        		Current_State = YELLOW;
        	}
        	else if(THREE){
        		Current_State;
        	}
        	else{
        		Current_State;
        	}
    		break;
    	case BLUE:
        	GPIO_PortClear(GPIOB, 1u << PIN21);
        	GPIO_PortSet(GPIOB, 1u << PIN21);
        	if(ZERO == Switch_Total){
        		Current_State = WHITE;
        	}
        	else if(ONE){
        		Current_State = PURPLE;
        	}
        	else if(TWO){
        		Current_State = GREEN;
        	}
        	else if(THREE){
        		Current_State;
        	}
        	else{
        		Current_State;
        	}
    		break;
    	case PURPLE:
        	GPIO_PortClear(GPIOB, 1u << PIN21);
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	GPIO_PortSet(GPIOB, 1u << PIN21);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	if(ZERO == Switch_Total){
        		Current_State = WHITE;
        	}
        	else if(ONE){
        		Current_State = RED;
        	}
        	else if(TWO){
        		Current_State = BLUE;
        	}
        	else if(THREE){
        		Current_State;
        	}
        	else{
        		Current_State;
        	}
    		break;
    	case RED:
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	if(ZERO == Switch_Total){
        		Current_State = WHITE;
        	}
        	else if(ONE){
        		Current_State = YELLOW;
        	}
        	else if(TWO){
        		Current_State = PURPLE;
        	}
        	else if(THREE){
        		Current_State;
        	}
        	else{
        		Current_State;
        	}
    		break;
    	case YELLOW:
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	GPIO_PortClear(GPIOE, 1u << PIN26);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	GPIO_PortSet(GPIOE, 1u << PIN26);
        	if(ZERO == Switch_Total){
        		Current_State = WHITE;
        	}
        	else if(ONE){
        		Current_State = GREEN;
        	}
        	else if(TWO){
        		Current_State = RED;
        	}
        	else if(THREE){
        		Current_State;
        	}
        	else{
        		Current_State;
        	}
    		break;
    	case WHITE:
        	GPIO_PortClear(GPIOB, 1u << PIN21);
        	GPIO_PortClear(GPIOB, 1u << PIN22);
        	GPIO_PortClear(GPIOE, 1u << PIN26);
        	GPIO_PortSet(GPIOB, 1u << PIN21);
        	GPIO_PortSet(GPIOB, 1u << PIN22);
        	GPIO_PortSet(GPIOE, 1u << PIN26);
    		break;
    	default:
    		break;
    	}


    	switch (SwitchTotal){
    	case 0:
    		break;
    	case 1:
    		break;
    	case 2:
    		break;
    	case 3:
    		break;
    	case 4:
    		break;
    	default:
    		break;

    	}

    }
    return 0 ;
}
