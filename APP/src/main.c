#include "main.h"
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	bsp_init();
	led_init();
	uart_init();
	uart_rx_t.status = 0;
	static float float_num = 0.00f;
	while(1)
	{
		LED_G_ON();
		DEBUG_PRINT("LED_G_ON\r\n");
		float_num += 1.01f;
		printf("float_num: %f\r\n", float_num);
		delay_ms(500);

		LED_G_OFF();
		DEBUG_PRINT("LED_G_OFF\r\n");
		float_num += 1.01f;
		printf("float_num: %f\r\n", float_num);
		delay_ms(500);

	}
}


void UART_COM_CPLT_Callback(UART_RXD_TypeDef *uart)
{
	uint8_t len = uart->status & RX_BUF_LEN_MASK;
	// printf("Input:\r\n");
	// printf("%.*s\r\n", len, uart->buffer);
	//HAL_UART_Transmit(&uart_com_t,uart->buffer,len,1000);
}




