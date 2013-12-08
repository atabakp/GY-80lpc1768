/**
 * @author Peter Swanson
 * A personal note from me: Jesus Christ has changed my life so much it blows my mind. I say this because
 *                  today, religion is thought of as something that you do or believe and has about as
 *                  little impact on a person as their political stance. But for me, God gives me daily
 *                  strength and has filled my life with the satisfaction that I could never find in any
 *                  of the other things that I once looked for it in. 
 * If your interested, heres verse that changed my life:
 *      Rom 8:1-3: "Therefore, there is now no condemnation for those who are in Christ Jesus,
 *                  because through Christ Jesus, the law of the Spirit who gives life has set
 *                  me free from the law of sin (which brings...) and death. For what the law 
 *                  was powerless to do in that it was weakened by the flesh, God did by sending
 *                  His own Son in the likeness of sinful flesh to be a sin offering. And so He
 *                  condemned sin in the flesh in order that the righteous requirements of the 
 *                  (God's) law might be fully met in us, who live not according to the flesh
 *                  but according to the Spirit."
 *
 *  A special thanks to Ewout van Bekkum for all his patient help in developing this library!
 *
 * @section LICENSE
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * ADXL345, triple axis, I2C interface, accelerometer.
 *
 * Datasheet:
 *
 * http://www.analog.com/static/imported-files/data_sheets/ADXL345.pdf
 */  



#ifndef ADXL345_I2C_H
#define ADXL345_I2C_H


/**
 * Defines
 */
//Registers.
#define ADXL345_DEVID_REG          0x00
#define ADXL345_THRESH_TAP_REG     0x1D
#define ADXL345_OFSX_REG           0x1E
#define ADXL345_OFSY_REG           0x1F
#define ADXL345_OFSZ_REG           0x20
#define ADXL345_DUR_REG            0x21
#define ADXL345_LATENT_REG         0x22
#define ADXL345_WINDOW_REG         0x23
#define ADXL345_THRESH_ACT_REG     0x24
#define ADXL345_THRESH_INACT_REG   0x25
#define ADXL345_TIME_INACT_REG     0x26
#define ADXL345_ACT_INACT_CTL_REG  0x27
#define ADXL345_THRESH_FF_REG      0x28
#define ADXL345_TIME_FF_REG        0x29
#define ADXL345_TAP_AXES_REG       0x2A
#define ADXL345_ACT_TAP_STATUS_REG 0x2B
#define ADXL345_BW_RATE_REG        0x2C
#define ADXL345_POWER_CTL_REG      0x2D
#define ADXL345_INT_ENABLE_REG     0x2E
#define ADXL345_INT_MAP_REG        0x2F
#define ADXL345_INT_SOURCE_REG     0x30
#define ADXL345_DATA_FORMAT_REG    0x31
#define ADXL345_DATAX0_REG         0x32
#define ADXL345_DATAX1_REG         0x33
#define ADXL345_DATAY0_REG         0x34
#define ADXL345_DATAY1_REG         0x35
#define ADXL345_DATAZ0_REG         0x36
#define ADXL345_DATAZ1_REG         0x37
#define ADXL345_FIFO_CTL           0x38
#define ADXL345_FIFO_STATUS        0x39

//Data rate codes.
#define ADXL345_3200HZ      0x0F
#define ADXL345_1600HZ      0x0E
#define ADXL345_800HZ       0x0D
#define ADXL345_400HZ       0x0C
#define ADXL345_200HZ       0x0B
#define ADXL345_100HZ       0x0A
#define ADXL345_50HZ        0x09
#define ADXL345_25HZ        0x08
#define ADXL345_12HZ5       0x07
#define ADXL345_6HZ25       0x06

// read or write bytes
#define ADXL345_I2C_READ    0xA7  
#define ADXL345_I2C_WRITE   0xA6 
#define ADXL345_I2C_ADDRESS 0x53   //the ADXL345 7-bit address is 0x53 when ALT ADDRESS is low as it is on the sparkfun chip: when ALT ADDRESS is high the address is 0x1D

/////////////when ALT ADDRESS pin is high:
//#define ADXL345_I2C_READ    0x3B   
//#define ADXL345_I2C_WRITE   0x3A
//#define ADXL345_I2C_ADDRESS 0x1D 

#define ADXL345_X           0x00
#define ADXL345_Y           0x01
#define ADXL345_Z           0x02



// modes
#define MeasurementMode     0x08


#endif /* ADXL345_I2C_H */
