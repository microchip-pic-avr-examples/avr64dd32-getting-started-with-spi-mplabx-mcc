/**
  @Company
    Microchip Technology Inc.

  @Description
    This Source file provides APIs.
    Generation Information :
    Driver Version    :   2.0.0
*/
/*
© [2022] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef SPI0_BASIC_H_INCLUDED
#define SPI0_BASIC_H_INCLUDED

#include "../system/utils/compiler.h"
#include <stdbool.h>
#include "spi_interface.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
  SPI_INTERFACE object 

  @Summary
    SPI driver interface object.
 */                
extern const struct SPI_INTERFACE SPI0_s;

/** Function pointer to callback function called by SPI IRQ.
    NULL=default value: No callback function is to be used.
*/
typedef void (*spi0_TRANSFER_DONE_CB)(void);

typedef struct 
{
    // hardware stuff that controls SPI mode
    // hardware stuff that controls SPI baud rate
    uint8_t CTRLAvalue;
    uint8_t CTRLBvalue;
} SPI0_configuration_t; 

/** Specify whether the SPI transfer is to be uni- or bidirectional.
    A bidirectional transfer (=SPI_EXCHANGE) causes the received data
    to overwrite the buffer with the data to transmit.
*/
typedef enum spi0_transfer_type 
{
    SPI0_EXCHANGE, ///< SPI transfer is bidirectional
    SPI0_READ,     ///< SPI transfer reads, writes only 0s
    SPI0_WRITE     ///< SPI transfer writes, discards read data
} spi0_transfer_type_t;

/** Status of the SPI hardware and SPI bus.*/
typedef enum spi0_transfer_status 
{
    SPI0_FREE, ///< SPI hardware is not open, bus is free.
    SPI0_IDLE, ///< SPI hardware has been opened, no transfer ongoing.
    SPI0_BUSY, ///< SPI hardware has been opened, transfer ongoing.
    SPI0_DONE  ///< SPI hardware has been opened, transfer complete.
} spi0_transfer_status_t;

/** Enumeration of the different configurations supported by the driver.
    A configuration is specified as parameter to SPI0_Open(),
    and is used by the function to set SPI parameters as specified by the
    configuration. A user may specify a configuration, e.g. CLIENT_A, used when
    communication over SPI with CLIENT_A, and another configuration, CLIENT_B,
    used when communication with CLIENT_B. The configurations may use different
    SPI configuration such as polarity or SCK frequency.
*/
typedef enum 
{
    SPI0_DEFAULT
} SPI0_configuration_name_t;

/**
 * \brief Initialize SPI interface
 * If module is configured to disabled state, the clock to the SPI is disabled
 * if this is supported by the device's clock system.
 *
 * \return Nothing
 */
void SPI0_Initialize(void);

/**
 * \brief Enable SPI
 * 1. If supported by the clock system, enables the clock to the SPI
 * 2. Enables the SPI module by setting the enable-bit in the SPI control register
 *
 * \return Nothing
 */
void SPI0_Enable(void);

/**
 * \brief Disable SPI
 * 1. Disables the SPI module by clearing the enable-bit in the SPI control register
 * 2. If supported by the clock system, disables the clock to the SPI
 *
 * \return Nothing
 */
void SPI0_Disable(void);

/**
 * \brief Sets the index of Configuration to use in the transfer
 *
 * \param[in] spiConfigIndex The configuration index
 *
 * \return Initialization status.
 * \retval false The SPI open was successful
 * \retval true  The SPI open was successful
 */
bool SPI0_Open(uint8_t spiConfigIndex);

/**
 * \brief Close the SPI for communication
 *
 * \return Nothing
 */
void SPI0_Close(void);

/**
 * \brief Exchange one byte over SPI. Blocks until done.
 *
 * \param[in] byteData The byte to transfer
 *
 * \return Received data byte.
 */
uint8_t SPI0_ByteExchange(uint8_t byteData);

/**
 * \brief Exchange a buffer over SPI. Blocks if using polled driver.
 *
 * \param[inout] bufferData The buffer to transfer. Received data is returned here.
 * \param[in] bufferSize The size of buffer to transfer
 *
 * \return Nothing.
 */
void SPI0_BufferExchange(void * bufferData, size_t bufferSize);

/**
 * \brief Write a buffer over SPI. Blocks if using polled driver.
 *
 * \param[in] bufferData The buffer to transfer
 * \param[in] bufferSize The size of buffer to transfer
 *
 * \return Nothing.
 */
void SPI0_BufferWrite(void * bufferData, size_t bufferSize);

/**
 * \brief Read a buffer over SPI. Blocks if using polled driver.
 *
 * Zeros are transmitted out of the SPI.
 *
 * \param[out] bufferData Received data is written here.
 * \param[in] bufferSize The size of buffer to transfer
 *
 * \return Nothing.
 */
void SPI0_BufferRead(void * bufferData, size_t bufferSize);

/**
 * \brief Write data byte to SPI.
 *
 * \param[in] byteData The byte to transfer
 *
 * \return Nothing.
 */
void SPI0_ByteWrite(uint8_t byteData);

/**
 * \brief Get received data byte from SPI.
 *
 * \return Received data byte
 */
uint8_t SPI0_ByteRead(void);

/**
 * \brief Check if SPI CLIENT is selected, i.e. its SS has been asserted.
 *
 * \return SPI SS status
 * \retval true  SPI is selected
 * \retval false SPI is not selected
 */
bool SPI0_Selected(void);

/**
 * \brief Wait until SPI has recaived a data byte
 *
 * \return Nothing
 */
void SPI0_WaitDataready(void);

uint8_t __attribute__((deprecated)) SPI0_ExchangeByte(uint8_t data);
void __attribute__((deprecated)) SPI0_ExchangeBlock(void *block, size_t blockSize);
void __attribute__((deprecated)) SPI0_WriteBlock(void *block, size_t blockSize);
void __attribute__((deprecated)) SPI0_ReadBlock(void *block, size_t blockSize);
void __attribute__((deprecated)) SPI0_WriteByte(uint8_t byte);
uint8_t __attribute__((deprecated)) SPI0_ReadByte(void);

#ifdef __cplusplus
}
#endif

#endif /* SPI0_BASIC_H_INCLUDED */
