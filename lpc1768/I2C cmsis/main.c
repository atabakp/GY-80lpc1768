
#include "lpc17xx_i2c.h"
#include "lpc17xx_libcfg.h"
#include "lpc17xx_pinsel.h"
#include "debug_frmwrk.h"
#include <stdio.h>
#include "uart.h"
#include "ADXL345_I2C.h"
#include "l3g4200d_driver.h"
#include "BMP085_driver.h"
#include "math.h"

/* Initialize debug via UART0
	 * – 115200bps
	 * – 8 data bit
	 * – No parity
	 * – 1 stop bit
	 * – No flow control
	 */
	 
/************************** PRIVATE DEFINITIONS *************************/
#define I2CDEV_M LPC_I2C0
uint8_t Rx[2];
uint8_t Tx[2];


uint8_t dataX[2];	
uint8_t dataY[2];
uint8_t dataZ[2]; 


uint8_t cal_param[3];

int ac1;
int ac2; 
int ac3; 
unsigned int ac4;
unsigned int ac5;
unsigned int ac6;
int b1; 
int b2;
int mb;
int mc;
int md;

long b5; 

short temperature;
long pressure;

// Use these for altitude conversions

float altitude;


signed char lcd_buf[50];
uint8_t valueL[2];
uint8_t valueH[2];
int16_t value;
I2C_M_SETUP_Type transferMCfg;





/************************** PRIVATE FUNCTIONS *************************/
void Delay(int delaydata){
	uint32_t i,j,k;
	for(i=0;i<delaydata;i++)
		for(j=0;j<100;j++)
			for(k=0;k<100;k++)
			;
	}	




	//////ADXL345/////
void ADXL345_init(){
	
	transferMCfg.sl_addr7bit = ADXL345_I2C_ADDRESS;
	transferMCfg.tx_length = 2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 2;
	
	
///////////DATA_FORMAT/////////
	
	Tx[0] = ADXL345_DATA_FORMAT_REG;
  Tx[1] = 0x0B;
	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
///////////POWER_CTL/////////
	
	Tx[0] = ADXL345_POWER_CTL_REG ;
	Tx[1] = 0x08;
	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
///////////INT_ENABLE/////////

	Tx[0] = ADXL345_INT_ENABLE_REG ;
	Tx[1] = 0x80;
	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
///////////BW_RATE//////////
	
	Tx[0] = ADXL345_BW_RATE_REG ;
	Tx[1] = ADXL345_1600HZ;
	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	

	
}
void ADXL345_ofs(){
	
	
	transferMCfg.sl_addr7bit = ADXL345_I2C_ADDRESS;
	transferMCfg.tx_length = sizeof(Tx);
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 2;
	
	
///////////OFSX/////////
	
	Tx[0] = ADXL345_OFSX_REG ;
	Tx[1] = 0x0;
	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
								
///////////OFSY/////////					
	Tx[0] = ADXL345_OFSY_REG ;
	Tx[1] = 0x6;
	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);				
    
///////////OFSZ/////////

  Tx[0] = ADXL345_OFSZ_REG ;
  Tx[1] = 0x6;
	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
	
	
}
int16_t ADXL345_X_out(){
	


transferMCfg.sl_addr7bit = ADXL345_I2C_ADDRESS;
	
	
	Tx[0] = ADXL345_DATAX0_REG ;
	
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = dataX;
	transferMCfg.rx_length = sizeof(dataX);
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		
	
  return ((dataX[1] << 8) | dataX[0])	;
}


int16_t ADXL345_Y_out(){
	


transferMCfg.sl_addr7bit = ADXL345_I2C_ADDRESS;
	
	
	Tx[0] = ADXL345_DATAY0_REG ;
	
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = dataY;
	transferMCfg.rx_length = sizeof(dataY);
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		
	
	return ((dataY[1] << 8) | dataY[0])	;
}




int16_t ADXL345_Z_out(){
	


transferMCfg.sl_addr7bit = ADXL345_I2C_ADDRESS;
	
	
	Tx[0] = ADXL345_DATAZ0_REG ;
	
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = dataZ;
	transferMCfg.rx_length = sizeof(dataZ);
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		
	return ((dataZ[1] << 8) | dataZ[0])	;

}




	

//////L3G4200D FFUNCTIONS/////
void L3G_init(){		/* Initialize Gyro */	
	
	
	transferMCfg.sl_addr7bit = L3G4200D_I2C_ADDRESS;
	transferMCfg.tx_length = 2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 2;
	
///////////L3G4200D_CTRL_REG1//////////
	
	Tx[0] = L3G4200D_CTRL_REG1;
  Tx[1] = L3G4200D_ODR_760Hz_BW_110;

	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
		Tx[0] = L3G4200D_CTRL_REG2;
  Tx[1] = 0x00;

	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
		Tx[0] = L3G4200D_CTRL_REG3;
  Tx[1] = 0x8;

	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
			Tx[0] = L3G4200D_CTRL_REG4;
  Tx[1] = 0x0;

	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
				Tx[0] = L3G4200D_FIFO_CTRL_REG;
  Tx[1] = 0x0;

	transferMCfg.tx_data = Tx ;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
}




int16_t L3G_X(){
	transferMCfg.sl_addr7bit = L3G4200D_I2C_ADDRESS;
	
	
	Tx[0] = 0x2C ;
	
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = dataX;
	transferMCfg.rx_length = sizeof(dataX);
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		
	
  return ((dataX[1] << 8) | dataX[0])	;
	
}

///////BMP085///////
short BMP085ReadInt(uint32_t address){
	
transferMCfg.sl_addr7bit = BMP085_ADDRESS;
	
	
	Tx[0] = address ;
	
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = cal_param;
	transferMCfg.rx_length = sizeof(cal_param);
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
		
	
  	return ((cal_param[0] << 8) | cal_param[1])	;
	
}

void  BMP085Calibration(){
  ac1 = BMP085ReadInt(0xAA);
  ac2 = BMP085ReadInt(0xAC);
  ac3 = BMP085ReadInt(0xAE);
  ac4 = BMP085ReadInt(0xB0);
  ac5 = BMP085ReadInt(0xB2);
  ac6 = BMP085ReadInt(0xB4);
  b1 = BMP085ReadInt(0xB6);
  b2 = BMP085ReadInt(0xB8);
  mb = BMP085ReadInt(0xBA);
  mc = BMP085ReadInt(0xBC);
  md = BMP085ReadInt(0xBE);
}
uint16_t BMP085ReadUT(){
  uint16_t ut=0;
  
  // Write 0x2E into Register 0xF4
	Tx[1] = 0xF4;
	Tx[0] = 0x2E;
	

	transferMCfg.sl_addr7bit = BMP085_ADDRESS;
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
  // Wait at least 4.5ms
  Delay(2000);
  
  // Read two bytes from registers 0xF6 and 0xF7
  ut = BMP085ReadInt(0xF6);
  return ut;
}
// Read the uncompensated pressure value
long BMP085ReadUP(){

  long up = 0;
  
  // Write 0x34+(OSS<<6) into register 0xF4
  // Request a pressure reading w/ oversampling setting

  Tx[1] = 0xF4;
	Tx[0] = 0x34 + (OSS<<6);
	
	transferMCfg.sl_addr7bit = BMP085_ADDRESS;
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 2;
	transferMCfg.rx_data = NULL;
	transferMCfg.rx_length = 0;
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
  // Wait for conversion, delay time dependent on OSS
  Delay(200 + (3<<OSS));
  
  // Read register 0xF6 (MSB), 0xF7 (LSB), and 0xF8 (XLSB)
	Tx[0] = 0xF6 ;
	
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = cal_param;
	transferMCfg.rx_length = sizeof(cal_param);
	transferMCfg.retransmissions_max = 3;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
  
  up = (((unsigned long) cal_param[0] << 16) | ((unsigned long) cal_param[1] << 8) | (unsigned long) cal_param[2]) >> (8-OSS);
  
  return up;
}
short BMP085GetTemperature( unsigned long ut){
  long x1, x2;
  
	x1 = ( (long)ut - (long) ac6) * ((long) ac5 /pow(2,15));
	x2 = ((long) mc *pow(2,11)) / (x1 + md);
	b5 = x1 + x2;
    

  return ((b5 + 8) /pow(2,4)); 
}
long BMP085GetPressure(unsigned long up){
  long x1, x2, x3, b3, b6, p;
  unsigned long b4, b7;
  
  b6 = b5 - 4000;
  // Calculate B3
  x1 = (b2 * (b6 * b6)>>12)>>11;
  x2 = (ac2 * b6)>>11;
  x3 = x1 + x2;
  b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
  
  // Calculate B4
  x1 = (ac3 * b6)>>13;
  x2 = (b1 * ((b6 * b6)>>12))>>16;
  x3 = ((x1 + x2) + 2)>>2;
  b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
  
  b7 = ((unsigned long)(up - b3) * (50000>>OSS));
  if (b7 < 0x80000000)
    p = (b7<<1)/b4;
  else
    p = (b7/b4)<<1;
    
  x1 = (p>>8) * (p>>8);
  x1 = (x1 * 3038)>>16;
  x2 = (-7357 * p)>>16;
  p += (x1 + x2 + 3791)>>4;
  
  return p;
}


/*-------------------------MAIN FUNCTION------------------------------*/

int main(void)
{


	PINSEL_CFG_Type PinCfg;
	debug_frmwrk_init();

	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode = 0;
	PinCfg.Funcnum = 1;
	PinCfg.Pinnum = 27;
	PinCfg.Portnum = 0;
	PINSEL_ConfigPin(&PinCfg);
	PinCfg.Pinnum = 28;
	PINSEL_ConfigPin(&PinCfg);


	// Initialize Slave I2C peripheral
	I2C_Init(I2CDEV_M, 400000);

	/* Enable Slave I2C operation */
	I2C_Cmd(I2CDEV_M, ENABLE);
	
	// ADXL345//
	ADXL345_init();
	ADXL345_ofs();


/* init pressure */
	
	
BMP085Calibration();
	



						
	
	
	
	L3G_init();


	
	

	while(1){
//	BMP085Calibration();
//	sprintf((signed char*)lcd_buf, "X=%6i Y=%6i Z=%6i \r", ADXL345_X_out(),ADXL345_Y_out(),ADXL345_Z_out());
//	UART0_SendString((signed char*)lcd_buf);	
//		
//	temperature = BMP085GetTemperature(BMP085ReadUT());
//  pressure = BMP085GetPressure(BMP085ReadUP());
//	sprintf((signed char*)lcd_buf, "T=%i P=%i \r", temperature, pressure);
//	UART0_SendString((signed char*)lcd_buf);	
//	altitude = (float)44330 * (1 - pow(((float) pressure/p0), 0.190295));

//	sprintf((signed char*)lcd_buf, "Altitude=%i \r", altitude);
//	UART0_SendString((signed char*)lcd_buf);	

	
	transferMCfg.sl_addr7bit = BMP085_ADDRESS;
	
	
	Tx[0] = 0xBC ;
	
	transferMCfg.tx_data = Tx ;
	transferMCfg.tx_length = 1;
	transferMCfg.rx_data = cal_param;
	transferMCfg.rx_length = sizeof(cal_param);
	transferMCfg.retransmissions_max = 2;
	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);
	
//	
//sprintf((signed char*)lcd_buf, "ut=%d \r", ((cal_param[0] << 8) | cal_param[1]));
//	UART0_SendString((signed char*)lcd_buf);


//	

	
	sprintf((signed char*)lcd_buf, "gyro=%6d \r\n", L3G_X());


		UART0_SendString((signed char *)lcd_buf);
//	
	
	
	
	
	

//	
// Tx[0] = 0xAA;

//	/* Start I2C slave device first */
//	transferMCfg.sl_addr7bit = 0x77 ;
//	transferMCfg.tx_data = Tx ;
//	transferMCfg.tx_length = sizeof(Tx);
//	transferMCfg.rx_data = valueL;
//	transferMCfg.rx_length = sizeof(valueL);
//	transferMCfg.retransmissions_max = 3;
//	I2C_MasterTransferData(I2CDEV_M, &transferMCfg, I2C_TRANSFER_POLLING);

//	
//	value = (valueL[1] << 8) |  valueL[0] ;
//	
//	sprintf((signed char*)lcd_buf, "T=%6d \r\n", value);

////sprintf(lcd_buf,"X= %d\r\n\n",(signed char)value);
//		UART0_SendString((signed char *)lcd_buf);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
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
