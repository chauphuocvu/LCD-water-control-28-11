#ifndef __RFID_READER__
#define __RFID_READER__
#include "lib_CR95HF.h"
#include "miscellaneous.h"
#include "lib_iso14443A.h"
#include "lib_iso14443B.h"
#include "lib_SRIX4k.h"
#include "hw_config.h"

void Rfid_SerialInterfaceInitialization (ReaderConfigStruct ReaderConfig);
int8_t User_IsCR95HF (void);
int8_t User_Get14443ATag (uint8_t* UIDout );
int8_t User_Get14443BTag (void);
int8_t User_Get14443SRTag (void);
#endif
