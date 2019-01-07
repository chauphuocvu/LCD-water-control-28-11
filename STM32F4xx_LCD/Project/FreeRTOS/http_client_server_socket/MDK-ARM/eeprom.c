#include <stm32f4xx_rcc.h>

#include <eeprom.h>


// Unlocks the data memory and FLASH_PECR register
void EEPROM_Unlock(void) {
	 if((FLASH->CR & FLASH_CR_LOCK) != RESET)
  {
    /* Authorize the FLASH Registers access */
    FLASH->KEYR = FLASH_KEY1;
    FLASH->KEYR = FLASH_KEY2;
	}
}

// Lock the data memory and FLASH_PECR register
void EEPROM_Lock(void) {
 FLASH->CR |= FLASH_CR_LOCK;;
}

// Wait for a EEPROM operation complete or a timeout occur
// input:
//   Timeout - timeout interval
// return: EEPROM status: EEPROM_COMPLETE or EEPROM_TIMEOUT
EEPROM_Status EEPROM_WaitForLastOperation(uint32_t Timeout) {
	volatile EEPROM_Status status = EEPROM_COMPLETE;

	// Wait for a EEPROM operation to complete or a timeout occur
	while (FLASH->SR & FLASH_SR_BSY && Timeout) Timeout--;
	if (!Timeout) status = EEPROM_TIMEOUT;

	return status;
}

// Write long at specified address in data memory (32-bit)
// input:
//   Address - address of long to be written
//   Data - data to be written
// return: EEPROM status: EEPROM_COMPLETE or EEPROM_TIMEOUT
EEPROM_Status EEPROM_Write(uint32_t Address, uint32_t Data) {
	EEPROM_Status status = EEPROM_COMPLETE;

	// Wait for a EEPROM operation to complete or a timeout occur
	status = EEPROM_WaitForLastOperation(EEPROM_PRG_TIMEOUT);

	if (status == EEPROM_COMPLETE) {
		// Clear the FTDW bit (data will be erased before write if it non zero)
		FLASH->KEYR &= (uint32_t)(~(uint32_t)FLASH_PECR_FTDW);
		*(volatile uint32_t *)Address = Data; // Program the new data

		// Wait for a EEPROM operation to complete or a timeout occur
		status = EEPROM_WaitForLastOperation(EEPROM_PRG_TIMEOUT);
	}

	return status;
}

// Read 32-bit value from EEPROM data memory
// input:
//   Address - address in data memory
// return: value from EEPROM data memory
// note: Address must be between DATA_EEPROM_START_ADDR and DATA_EEPROM_END_ADDR
uint32_t EEPROM_Read(uint32_t Address) {
	return (*(volatile uint32_t*)Address);
}

// Read specified quantity of data from EEPROM to buffer
// input:
//   addr - start address in EEPROM data memory
//   buffer - pointer to buffer
//   len - length of buffer in bytes
// note: buffer must be 32-bit aligned
void ReadBuffer_EEPROM(uint32_t addr, volatile uint32_t *buffer, uint32_t len) {
	uint8_t i;

	for (i = 0; i < len; i += 4) *buffer++ = EEPROM_Read(addr + i);
}

// Save specified buffer to EEPROM
// input:
//   addr - start address in EEPROM data memory
//   buffer - pointer to buffer
//   len - length of buffer in bytes
// note: buffer must be 32-bit aligned
void SaveBuffer_EEPROM(uint32_t addr, volatile uint32_t *buffer, uint32_t len) {
	uint8_t i;
	volatile uint32_t data;

	EEPROM_Unlock();
	for (i = 0; i < len; i += 4) {
		data = *buffer++;
		if (data != EEPROM_Read(addr + i)) EEPROM_Write(addr + i,data);
	}
	EEPROM_Lock();
}
