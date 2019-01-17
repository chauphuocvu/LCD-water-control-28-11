/*
			CHAU PHUOC VU
*/
#include "DisplayNumber.h"

////////////////////////////////////////////////////////////////////////
void DisplayNumber(void)
{
		switch(Screen)
		{
			case StartScreen_df:
				LCD_SetColors(WHITE,BLACK);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(20,130,(uint8_t *)"00:00:01");
// Chon man hinh de hien thi dc set tu Type of Probe
			switch(TypeofProbe)
			{
				case FREECHLORINE:
					LCD_SetColors(BLACK,VU_YELLOW);
					LCD_SetFont(&Font16x24);
					DisplayDoubleNumber(130, 100, RequireValueCLF_Display, 1, 1, None);
					LCD_SetFont(&Font12x12);
					DisplayDoubleNumber(80, 170, RequireValueCLF_Display, 1, 1, None);
					break;
				case REDOXPROBE:
					LCD_SetColors(BLACK,VU_YELLOW);
					LCD_SetFont(&Font16x24);
					DisplayIntegerNumber(130, 100, RequireValueRedoxpH_Redox_Display, 3, None);
					LCD_SetFont(&Font12x12);
					DisplayIntegerNumber(80, 135, RequireValueRedoxpH_Redox_Display, 3, mV);
					break;
				case MLPERHOUR:
					LCD_SetColors(BLACK,VU_YELLOW);
					LCD_SetFont(&Font16x24);
					DisplayIntegerNumber(130, 100, RequireValueDosepH_DoseHour_Display, 2, None);
					break;
				case MLPERDAY:
					LCD_SetColors(BLACK,VU_GRAY);
					LCD_SetFont(&Font16x24);
					DisplayIntegerNumber(130, 100, RequireValueDosepH_DoseDay_Display, 2, None);
					break;
				default:
					break;
			}
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(130, 330, RequireValuepH_Display, 1, 1, None);
				LCD_SetFont(&Font12x12);
				DisplayDoubleNumber(80, 400, RequireValuepH_Display, 1, 1, None);
				break;
/*****************************************************************************************/
			case DosingTestScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(120,85,150,3,ml);
				LCD_SetFont(&Font12x12);
				DisplayIntegerNumber(70,155,400,3,ml);
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(120,315,150,3,ml);
				LCD_SetFont(&Font12x12);
				DisplayIntegerNumber(70, 385, 200,3,ml);
			break;
/*****************************************************************************************/
			case ParametersPoolVolumeScreen_df:
			case ParametersFitrationPeriodScreen_df:
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(100,105,PoolVolume_Display,2,m3);
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(100, 315, FiltrationPeriod_Display,2,h);
			break;
/*****************************************************************************************/
			case WarningMaximalSafetyScreen_df:
				LCD_SetColors(WHITE,VU_GREEN);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(150,195,15,2,None);
			break;
/*****************************************************************************************/
			case WarningExtremeConditionScreen_df:
				LCD_SetColors(WHITE,VU_RED);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(150,195,20,2,None);
			break;
/*****************************************************************************************/
			case ParametersRequireValuepHScreen_df:
			case ParametersRequireValueCLFScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(100, 100, RequireValueCLF_Display, 1, 1, None);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,165,(uint8_t *)"mg/l");
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(100, 330, RequireValuepH_Display, 1, 1, None);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
			break;
/*****************************************************************************************/
			case CalibrationpHProbeScreen_df:
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(100, 330, Probe_pH_Display, 1, 1, None);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
			break;
/*****************************************************************************************/
			case CalibrationCLFProbeScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(100, 330, Probe_CLF_Display, 1, 1, None);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"mg/h");
			break;
/*****************************************************************************************/
			case ParametersRequireValueRedoxpH_RedoxScreen_df:
			case ParametersRequireValueRedoxpH_pHScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(100,100,RequireValueRedoxpH_Redox_Display,3,mV);
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(100, 330, RequireValuepH_Display, 1, 1, None);
//				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(100,395,(uint8_t *)"pH");
			break;
/*****************************************************************************************/
			case ParametersRequireValueDosepH_DoseHourScreen_df:
			case ParametersRequireValueDosepH_DoseHour_pHScreen_df:
				LCD_SetColors(BLACK,VU_YELLOW);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(100,100,5,2,None);
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(100, 330, RequireValuepH_Display, 1, 1, None);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
			break;
/*****************************************************************************************/
			case ParametersRequireValueDosepH_DoseDayScreen_df:
			case ParametersRequireValueDosepH_DoseDay_pHScreen_df:
				LCD_SetColors(BLACK,VU_GRAY);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(100,100,5,2,None);
				LCD_SetColors(BLACK,VU_BLUE);
				LCD_SetFont(&Font16x24);
				DisplayDoubleNumber(100, 330, RequireValuepH_Display, 1, 1, None);
				LCD_SetFont(&Font12x12);
				LCD_DisplayStringLine(110,395,(uint8_t *)"pH");
			break;
/*****************************************************************************************/
			case CalibrationWaterScreen_df:
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(100,330,CalibrationWater_Display,2,oC);
			break;
/*****************************************************************************************/
			case CalibrationAirScreen_df:
				LCD_SetColors(WHITE,VU_GRAY);
				LCD_SetFont(&Font16x24);
				DisplayIntegerNumber(100,330,CalibrationAir_Display,2,oC);
			break;
/*****************************************************************************************/
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
			case SettingsScreen_df:
			case ParametersScreen_df:
			case ParametersWaterScreen_df:
			break;
			default :
			break;
		}
}

/*****************hien thi so interger va don vi di kem********************************/
void DisplayIntegerNumber(uint16_t line, uint16_t column, uint16_t value, uint8_t quantity, uint8_t unit)
{
	int j;
	switch(unit)
	{
		case ml:
		case m3:
		case oC:
		case mV:
			j = 4;
		break;
		case mgl:
		case mgh:
			j = 6;
		break;
		case h:
			j = 3;
		break;
		case None:
			j = 1;
		break;
		default:
		break;
	}
	char string[quantity + j];
	string[quantity + j - 1] = 0;
	switch(unit)
	{
		case ml:
			string[quantity + j - 2] = 'l';
			string[quantity + j - 3] = 'm';
			string[quantity + j - 4] = ' ';
		break;
		case m3:
			string[quantity + j - 2] = '3';
			string[quantity + j - 3] = 'm';
			string[quantity + j - 4] = ' ';
		break;
		case oC:
			string[quantity + j - 2] = 'C';
			string[quantity + j - 3] = 'o';
			string[quantity + j - 4] = ' ';
		break;
		case mV:
			string[quantity + j - 2] = 'V';
			string[quantity + j - 3] = 'm';
			string[quantity + j - 4] = ' ';
		break;
		case mgl:
			string[quantity + j - 2] = 'l';
			string[quantity + j - 3] = '/';
			string[quantity + j - 4] = 'g';
			string[quantity + j - 5] = 'm';
			string[quantity + j - 6] = ' ';
		break;
		case mgh:
			string[quantity + j - 2] = 'h';
			string[quantity + j - 3] = '/';
			string[quantity + j - 4] = 'g';
			string[quantity + j - 5] = 'm';
			string[quantity + j - 6] = ' ';
		break;
		case h:
			string[quantity + j - 2] = 'h';
			string[quantity + j - 3] = ' ';
		break;
		case None:
		break;
		default:
		break;
	}
	for (int j = 0; j < quantity; j++)
	{
		string[j] = (value%power(10,(quantity - j)))/power(10,(quantity - j - 1)) + 48;
	}
	LCD_DisplayStringLine(line,column,(uint8_t *)string);
}





/*****************hien thi so interger va don vi di kem********************************/
void DisplayDoubleNumber(uint16_t line, uint16_t column, double value, uint8_t natural, uint8_t decimal, uint8_t unit)
{
	int j;
	switch(unit)
	{
		case pH:
			j = 4;
		break;
		case None:
			j = 1;
		break;
		default:
		break;
	}
	char string[natural + decimal + 1 + j];
	switch(unit)
	{
		case pH:
			sprintf((char *)string,"%1.1f pH",value);
		break;
		case None:
			sprintf((char *)string,"%1.1f",value);
		break;
		default:
		break;
	}
	LCD_DisplayStringLine(line,column,(uint8_t *)string);
}





uint16_t power(uint16_t number, uint16_t n)
{
	uint16_t val = 1;
	if ( n == 0)
	{
	}
	else 
	{
		for (int16_t i = 0;i < n ;i++)
		{
			val *=number;
		}
	}
	return val;
}

