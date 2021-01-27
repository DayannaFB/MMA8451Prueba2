
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "sdk_hal_i2c0.h"
#include "fsl_i2c.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/


/*******************************************************************************
 * Private Prototypes
 ******************************************************************************/


/*******************************************************************************
 * External vars
 ******************************************************************************/


/*******************************************************************************
 * Local vars
 ******************************************************************************/


/*******************************************************************************
 * Private Source Code
 ******************************************************************************/


/*******************************************************************************
 * Public Source Code
 ******************************************************************************/
 /*--------------------------------------------*/
status_t i2c0MasterInit(uint32_t baud_rate) {
	i2c_master_config_t masterConfig;
//	status_t status;

	I2C_MasterGetDefaultConfig(&masterConfig);
    masterConfig.baudRate_Bps = baud_rate;

    I2C_MasterInit(I2C0, &masterConfig, CLOCK_GetFreq(I2C0_CLK_SRC));
	return(kStatus_Success);
}
/*--------------------------------------------*/
status_t i2c0MasterReadByte(uint16_t *data, uint8_t device_address, int8_t memory_address) {
	i2c_master_transfer_t masterXfer;
	uint8_t i2c_rx_buffer[1];

    masterXfer.slaveAddress = device_address;
    masterXfer.direction = kI2C_Read;
    masterXfer.subaddress = (uint32_t)memory_address;
    masterXfer.subaddressSize = 1;
    masterXfer.data = i2c_rx_buffer;
    masterXfer.dataSize = 1;
    masterXfer.flags = kI2C_TransferDefaultFlag;

    I2C_MasterTransferBlocking(I2C0, &masterXfer);

    *data=i2c_rx_buffer[0];

    return(kStatus_Success);
}

status_t i2c0MasterWriteByte(uint16_t *data, uint8_t direccion, uint8_t register_data, uint8_t value  ){
	i2c_master_transfer_t masterXfer;


	    masterXfer.slaveAddress = direccion;
	    masterXfer.direction = kI2C_Write;
	    masterXfer.subaddress = register_data;
	    masterXfer.subaddressSize = 1;
	    masterXfer.data = &value;
	    masterXfer.dataSize = 1;
	    masterXfer.flags = kI2C_TransferDefaultFlag;

	    I2C_MasterTransferBlocking(I2C0, &masterXfer);


	return(kStatus_Success);
}
