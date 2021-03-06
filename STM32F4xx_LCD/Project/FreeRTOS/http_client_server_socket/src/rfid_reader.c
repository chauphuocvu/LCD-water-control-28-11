#include "rfid_reader.h"
extern CR95HF_INTERFACE		CR95HF_Interface;
extern uint8_t 	ReaderRecBuf[MAX_BUFFER_SIZE+3]; 	// buffer for SPI ou UART reception
/**  
* @brief 	this function intialiezes either UART or SPI serial interface of MCU to communication with CR95HF
* @param  	none 	
* @retval 	none
*/
void Rfid_SerialInterfaceInitialization (ReaderConfigStruct ReaderConfig)
{

	if (ReaderConfig.Interface == CR95HF_INTERFACE_UART)
	{
		CR95HF_Interface = CR95HF_INTERFACE_UART;
		UART_Initialization(BAUDRATE_DATARATE_DEFAULT );	 
	}
	else if (ReaderConfig.Interface == CR95HF_INTERFACE_SPI)
	{
		CR95HF_Interface = CR95HF_INTERFACE_SPI;
		ReaderConfig.Interface = CR95HF_INTERFACE_SPI;
		SPI_Initialization( );
		// -- EXTI configuration if the polling mode is not selected
		if (ReaderConfig.SpiMode == SPI_INTERRUPT) //SPI_POLLING_MODE 
		{	// -- An EXTI must be set to catch the IRQ (a edge on the UART RX pin) from the CR95HF
			EXTI_Config( );
		}	
	}
}

/**  
* @brief  	this function returns RESULTOK if an CR95HF is available
* @param  	none 	
* @retval 	status function
*/
int8_t User_IsCR95HF (void)
{
int8_t NbAttempt =0;

	do{
		delay_ms(50);
		CR95HF_Echo(ReaderRecBuf);
	}	while (ReaderRecBuf[0] !=ECHORESPONSE && NbAttempt++ <10);
	
	if (ReaderRecBuf[0] ==0x55)
		return RESULTOK;
	else	
		return ERRORCODE_GENERIC;	
}
/**  
* @brief 	this function read data block from tag
* @param  	pointer for data return
* @retval 	none
*/

int8_t Read_data(uint8_t *pResponse)
{
	uint8_t DataToSend[ISO14443A_CMD_MAXNBBYTE],NthByte=0;
	int8_t 	status;

	// add command code
	DataToSend[NthByte++] = ISO14443A_CMDCODE_READ;
	// append the command control byte 0x07 ( Number of significant bit = 7)
	DataToSend[NthByte++] = 0;
	
	// send command to contacless tag through CR95HF device and received its response
	errchk(CR95HF_SendRecv(NthByte,DataToSend,pResponse));
	return RESULTOK;

Error:
	return CR95HF_ERROR_CODE;
}
/**  
* @brief 	this function sends a REQA command, performs a Select Sequence and get UID 
* @param  	none 	
* @retval 	none
*/
int8_t User_Get14443ATag (uint8_t* UIDout )
{

	int8_t		status=0;
	uint8_t		SAKByte,NbUIDByte;//UIDout[ISO14443A_MAX_NBBYTE_UID]
	uint8_t i,CRC_check=0xFF;

	/* === Send REQA command to detect 14443_A contacless tag ===*/
	status = ISO14443A_IsPresent ();
	
	/* === Send Select sequence to a contacless tag ===*/
	if (status == RESULTOK)
		status = ISO14443A_SelectSequence ( &SAKByte );

   /* === Get UID to a contacless tag ===*/
   if (status == RESULTOK)
		status = ISO14443A_GetUID ( &SAKByte, &NbUIDByte, UIDout );
// 	 if(status == RESULTOK)
// 		 status = Read_data(ReaderRecBuf);
	return status;
}
/**  
* @brief 	this function sends a REQB command and display the result on LCD screen	
* @param  	none 	
* @retval 	none
*/
int8_t User_Get14443BTag (void)
{
int8_t		status=0;


	// send a ReqB command to detect a 14443_B contacless tag
		status = ISO14443B_IsPresent ();
		/* ===  Display "SR card detected " ===*/		   
		if (status == RESULTOK)
		{
		}
		return status;
}
/**  
* @brief 	this function handles a SR contacless tag and disply its UID.
* @param  	none 	
* @retval 	none
*/
int8_t User_Get14443SRTag (void)
{
int8_t		status=0;
uint8_t 	UIDfield[SRIX4K_SRIX4K_UID_NBBYTE];

	// send an initiate command to detect a SRi product
	status = SRIX4K_IsPresent ();	
	
	// If a SRI product detected, checks if it's a SRIX4k
	if (status == RESULTOK)
	{
		// Get UID of a tag  
		status = SRIX4K_GetUIDadvanced( UIDfield );
		/* ===  Display Contacless tag UID or No Reply === */
	}
	return status;
}

