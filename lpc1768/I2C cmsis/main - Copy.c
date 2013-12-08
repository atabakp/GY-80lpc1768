
#include "lpc17xx_i2c.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"
#include <stdio.h>
#include "uart.h"


/************************** PRIVATE DEFINITIONS *************************/
/** Used I2C device as slave definition */
#define I2CDEV_M LPC_I2C0
/** Own Slave address in Slave I2C device */
#define ADXL345_ADDR	0x53




uint8_t RData[5];
uint8_t TData[5];
uint8_t x[5];
signed char lcd_buf[50];
uint8_t valueL;
uint8_t valueH;
int16_t value=0;

/************************** PRIVATE FUNCTIONS *************************/







void Delay(int delaydata)
	{
	uint32_t i,j,k;
	for(i=0;i<delaydata;i++)
		for(j=0;j<100;j++)
			for(k=0;k<100;k++)
			;
	}






/*-------------------------MAIN FUNCTION------------------------------*/
/*********************************************************************//**

 ******************************************************************/
int main(void)
{

	
	PINSEL_CFG_Type PinCfg;
	I2C_M_SETUP_Type transferMCfg;


	/* Initialize debug via UART0
	 * – 115200bps
	 * – 8 data bit
	 * – No parity
	 * – 1 stop bit
	 * – No flow control
	 */

	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
#if ((USEDI2CDEV_M == 0))
	PinCfg.Funcnum = 1;
	PinCfg.Pinnum = 27;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 28;
	PINSEL_ConfigPin(&PinCfg);
#endif
#if ((USEDI2CDEV_M == 2))
	PinCfg.Funcnum = 2;
	PinCfg.Pinnum = 10;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 11;
	PINSEL_ConfigPin(&PinCfg);
#endif

	// Initialize Slave I2C peripheral
	I2C_Init(I2CDEV_M, 400000);

	/* Enable Slave I2C operation */
	I2C_Cmd(I2CDEV_M, ENABLE);
	



	
	TData[0] = 0x31;
TData[1] = 0x0B;
	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = ADXL345_ADDR;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = RData;
	transferMCfg.rx_length = sizeof(RData);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);

	TData[0] = 0x2D;
TData[1] = 0x08;
	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = ADXL345_ADDR;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = RData;
	transferMCfg.rx_length = sizeof(RData);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);

		TData[0] = 0x2E;
TData[1] = 0x80;
	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = ADXL345_ADDR;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = RData;
	transferMCfg.rx_length = sizeof(RData);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	

	/* Initialize buffer */
TData[0] = 0x2C;
TData[1] = 0x0E;
	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = ADXL345_ADDR;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = RData;
	transferMCfg.rx_length = sizeof(RData);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
	
		/* Initialize Gyro */
TData[0] = 0x20;
TData[1] = 0x0F;
	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = 0x69;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = RData;
	transferMCfg.rx_length = sizeof(RData);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	



							//	TData[0] = 0x1E;
							//TData[1] = 0xFD;
							//	

							//	/* Start I2C slave device first */
							//	transferMCfg.sl_addr7bit = ADXL345_ADDR;
							//	transferMCfg.tx_data = TData ;
							//	transferMCfg.tx_length = sizeof(TData);
							//	transferMCfg.rx_data = RData;
							//	transferMCfg.rx_length = sizeof(RData);
							//	transferMCfg.retransmissions_max = 3;
							//	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
							//		
							//	
							//		TData[0] = 0x1F;
							//TData[1] = 0x03;
							//	

							//	/* Start I2C slave device first */
							//	transferMCfg.sl_addr7bit = ADXL345_ADDR;
							//	transferMCfg.tx_data = TData ;
							//	transferMCfg.tx_length = sizeof(TData);
							//	transferMCfg.rx_data = RData;
							//	transferMCfg.rx_length = sizeof(RData);
							//	transferMCfg.retransmissions_max = 3;
							//	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);


							//		TData[0] = 0x20;
							//TData[1] = 0xFE;
							//	

							//	/* Start I2C slave device first */
							//	transferMCfg.sl_addr7bit = ADXL345_ADDR;
							//	transferMCfg.tx_data = TData ;
							//	transferMCfg.tx_length = sizeof(TData);
							//	transferMCfg.rx_data = RData;
							//	transferMCfg.rx_length = sizeof(RData);
							//	transferMCfg.retransmissions_max = 3;
							//	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);

	
	/* init pressure */
		TData[1] = 0xF4;
	TData[0] = 0x2E;
	
	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = 0x77;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = RData;
	transferMCfg.rx_length = sizeof(RData);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	


	while(1){
			/* Transmit -------------------------------------------------------- */

	//while (_DG != '1');

	TData[0] = 0x32;
	
 
	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = ADXL345_ADDR;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = RData;
	transferMCfg.rx_length = sizeof(RData);
	transferMCfg.retransmissions_max = 5;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		

		TData[0] = 0x33;
	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = ADXL345_ADDR;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = x;
	transferMCfg.rx_length = sizeof(x);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
	
		 value = (int)(x[0] << 8) | (int)RData[0]	;
		 
sprintf((signed char*)lcd_buf,"accX= %i\r\n\n",value);
		UART0_SendString((signed char *)lcd_buf);
		
		
		
		

		
//		TData[0] = 0x36;
	
//	/* Start I2C slave device first */
//	transferMCfg.sl_addr7bit = ADXL345_ADDR;
//	transferMCfg.tx_data = TData ;
//	transferMCfg.tx_length = sizeof(TData);
//	transferMCfg.rx_data = RData;
//	transferMCfg.rx_length = sizeof(RData);
//	transferMCfg.retransmissions_max = 3;
//	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
//		
//		//sgnint=RData[0];
//		sprintf(lcd_buf,"Z: %d\r\n\n",RData[0]);
//		UART0_SendString((signed char *)lcd_buf);
	
	

//TData[0] = 0x28;

//	/* Start I2C slave device first */
//	transferMCfg.sl_addr7bit = 0x69 ;
//	transferMCfg.tx_data = TData ;
//	transferMCfg.tx_length = sizeof(TData);
//	transferMCfg.rx_data = &valueL;
//	transferMCfg.rx_length = sizeof(valueL);
//	transferMCfg.retransmissions_max = 3;
//	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
//TData[0] = 0x29;

//	/* Start I2C slave device first */
//	transferMCfg.sl_addr7bit = 0x69 ;
//	transferMCfg.tx_data = TData ;
//	transferMCfg.tx_length = sizeof(TData);
//	transferMCfg.rx_data = &valueH;
//	transferMCfg.rx_length = sizeof(valueH);
//	transferMCfg.retransmissions_max = 3;
//	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
//	
//	value = (int) (valueH << 8) | (int) valueL ;
//	
//	sprintf((signed char*)lcd_buf, "X=%6d \r\n", value);

////sprintf(lcd_buf,"X= %d\r\n\n",(signed char)value);
//		UART0_SendString((signed char *)lcd_buf);
//	
	
	
	
	
	

	
TData[0] = 0xF6;

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = 0x77 ;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = &valueL;
	transferMCfg.rx_length = sizeof(valueL);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
TData[0] = 0xF7;

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = 0x77 ;
	transferMCfg.tx_data = TData ;
	transferMCfg.tx_length = sizeof(TData);
	transferMCfg.rx_data = &valueH;
	transferMCfg.rx_length = sizeof(valueH);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
	value = (int) (valueH << 8) | (int) valueL ;
	
	sprintf((signed char*)lcd_buf, "T=%6d \r\n", value);

//sprintf(lcd_buf,"X= %d\r\n\n",(signed char)value);
		UART0_SendString((signed char *)lcd_buf);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	Delay(2500);
		

 
		



//
 
	


		/* Loop forever */

}

/* With ARM and GHS toolsets, the entry point is main() - this will
	 allow the linker to generate wrapper code to setup stacks, allocate
	 heap area, and initialize and copy code and data segments. For GNU
	 toolsets, the entry point is through __start() in the crt0_gnu.asm
	 file, and that startup code will setup stacks and data */
//int main(void)
//{
//	while(1){
//		return c_entry();
//}
}


#ifdef	DEBUG
/*******************************************************************************
* @brief		Reports the name of the source file and the source line number
* 				where the CHECK_PARAM error has occurred.
* @param[in]	file Pointer to the source file name
* @param[in]		line assert_param error line source number
* @return		None
*******************************************************************************/
void check_failed(uint8_t *file, uint32_t line)
{
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while(1);
}
#endif

/*
 * @}
 */
