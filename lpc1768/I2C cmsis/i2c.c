#include "lpc17xx_i2c.h"

#define I2CDEV_M LPC_I2C0
I2C_M_SETUP_Type transferMCfg;


void write_i2c(uint8_t s_addr,uint8_t reg_addr,uint8_t txdata)
	{
uint8_t data[2];
data[0]=reg_addr;
data[1]=txdata;

	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = s_addr;
	transferMCfg.tx_data = data ;
	transferMCfg.tx_length = sizeof(txdata);
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		

}
	

int read_i2c(uint8_t s_addr,uint8_t reg_addr,uint8_t txdata)
	{
		

uint8_t data[2];
data[0]=reg_addr;
data[1]=txdata;

	

	/* Start I2C slave device first */
	transferMCfg.sl_addr7bit = s_addr;
	transferMCfg.tx_data = data ;
	transferMCfg.tx_length = sizeof(txdata);
	transferMCfg.rx_data = *Master_Buf;
	transferMCfg.rx_length = sizeof(Master_Buf);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		
		return Master_Buf;

}
	
