/*
			CHAU PHUOC VU
*/
#include "DisplayNumber.h"
#include <stdint.h>
////////////////////////////////////////////////////////////////////////
void DisplayNumber(void)
{
		//UARTprintf("co chay Switch case\r\n");
		switch(Screen)
		{
			case StartScreen_df:
				LCD_SetColors(WHITE,BLACK);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(20,130,(uint8_t *)"00:00:01");
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(130,100,(uint8_t *)"0.5");//hien thi Chlorine
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,170,(uint8_t *)"0.5");	
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(130,330,(uint8_t *)"0.5");//hien thi pH
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(80,400,(uint8_t *)"0.5");		
				break;
			case SettingsScreen_df:
				break;
			case DosingTestStartStartScreen_df:
			case DosingTestStopStartScreen_df:
			case DosingTestStopStopScreen_df:
			case DosingTestStartStopScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(120,100,(uint8_t *)"150");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(70,170,(uint8_t *)"400ml");	
				LCD_DisplayStringLine(127,155,(uint8_t *)"ml");
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(120,330,(uint8_t *)"150");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(70,400,(uint8_t *)"200ml");
				LCD_DisplayStringLine(127,385,(uint8_t *)"ml");
				break;
			case ParametersScreen_df:
				break;
			case ParametersPoolVolumeScreen_df:
			case ParametersFitrationPeriodScreen_df:
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,100,(uint8_t *)"15 m3");
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"06 h");
				break;
			case ParametersWaterScreen_df:
				break;
			case WarningMaximalSafetyScreen_df:
				LCD_SetColors(WHITE,VU_GREEN);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(150,195,(uint8_t *)"15");
				break;
			case WarningExtremeConditionScreen_df:
				LCD_SetColors(WHITE,VU_RED);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(150,195,(uint8_t *)"15");
				break;
			case ParametersRequireValuepHScreen_df:
			case ParametersRequireValueCLFScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,100,(uint8_t *)"0,2");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,165,(uint8_t *)"mg/l");
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"7,0");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
				break;
			case CalibrationpHProbeScreen_df:
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"7,0");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
				break;
			case CalibrationCLFProbeScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"7,0");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"mg/h");
				break;
			case ParametersRequireValueRedoxpH_RedoxScreen_df:
			case ParametersRequireValueRedoxpH_pHScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,100,(uint8_t *)"650");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,165,(uint8_t *)"mV");
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"7,0");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
				break;
			case ParametersRequireValueDosepH_DoseHourScreen_df:
			case ParametersRequireValueDosepH_DoseHour_pHScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,120,(uint8_t *)"5");
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"6,8");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
				break;
			case ParametersRequireValueDosepH_DoseDayScreen_df:
			case ParametersRequireValueDosepH_DoseDay_pHScreen_df:
				LCD_SetColors(BLACK,VU_GRAY);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,120,(uint8_t *)"5");
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"6,8");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
				break;
			case CalibrationWaterScreen_df:
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"28");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"oC");
				break;
			case CalibrationAirScreen_df:
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				LCD_DisplayStringLine(100,330,(uint8_t *)"30");
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"oC");
				break;
			case CalibrationScreen_df:
			case TypeOfProbeScreen_df:
			case WarningWaterHardnessScreen_df:
			case WarningProbeCalibration62_78Screen_df:
			case WarningProbeCalibrationScreen_df:
			case WarningProbeCalibration70Screen_df:
			case WarningProbeCalibrationRequiredValueScreen_df:
			case WarningProbeCalibrationRequiredValueRedScreen_df:
			case WarningProbeCalibrationRequiredValueImpossibleScreen_df:
			case WarningTooRapidChangeScreen_df:
				break;
			default :
				break;
		}
}


void DisplayIntegerNumber(uint16_t line, uint16_t column, uint16_t value, uint8_t quantity, uint8_t unit)
{
	switch(unit)
	{
		case pH:
			char a[quantity];
			break;
	}
	LCD_DisplayStringLine(line,column,(uint8_t *)"15");
}
