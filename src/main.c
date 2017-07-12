//
// CANable firmware - a fork of CANtact by Eric Evenchick
//


#include "stm32f0xx_hal.h"
#include "usb_device.h"
#include "usbd_cdc_if.h"
#include "can.h"
#include "slcan.h"
#include "system.h"
#include "led.h"

uint32_t last_msg_num = 0;
uint32_t msg_per_second = 0;

int main(void)
{
    HAL_Init();

    system_init();
    can_init();
    led_init();
    usb_init();

    led_green_on();
    led_blue_blink(3);

    uint32_t last_blinkgreen = 0;

    while(1)
    {

        if(HAL_GetTick() - last_blinkgreen > 1000)
        { 
            HAL_GPIO_TogglePin(LED_GREEN);
            last_blinkgreen = HAL_GetTick();
						msg_per_second = can_msg_receive- last_msg_num;
						last_msg_num = can_msg_receive;
        }

		led_process();
        can_process();
        usb_process();
    }
}

