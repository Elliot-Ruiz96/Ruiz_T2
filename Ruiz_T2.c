
#include <stdio.h>
#include "fsl_clock.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

gpio_pin_config_t led_config = {
        kGPIO_DigitalOutput,
        1,
    };

#define PIN22      	22u
#define	PIN21		21u
#define PIN26		26u
#define CORE_FREQ	21000000u
#define DELAY		1000000u

int main(void) {

	 CLOCK_EnableClock(kCLOCK_PortB);
	 CLOCK_EnableClock(kCLOCK_PortE);

	 PORT_SetPinMux(PORTB, PIN22, kPORT_MuxAsGpio); // Red LED
	 PORT_SetPinMux(PORTB, PIN21, kPORT_MuxAsGpio); // Blue LED
	 PORT_SetPinMux(PORTE, PIN26, kPORT_MuxAsGpio); // Green LED

	 GPIO_PinInit(GPIOB, PIN22, &led_config);
	 GPIO_PinInit(GPIOB, PIN21, &led_config);
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
