// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#define _INCLUDE_DATA_
#include "Data.h"
#undef _INCLUDE_DATA_
#include "DataBuffer.h"
#include "Globals.h"
#include "Log.h"
#include "Hardware/FLASH.h"
#include "Hardware/FSMC.h"
#include "Settings/SettingsMemory.h"
#include "Utils/GlobalFunctions.h"
#include "Utils/ProcessingSignal.h"


/** @addtogroup FPGA
 *  @{
 *  @addtogroup Data
 *  @{
 */


/// ��������� ��������� dataStruct ������� ��� ���������
static void PrepareDataForDraw(DataStruct *dataStruct);


static DataSettings dataSettings;   ///< ����� �������� ��������� ��� �������� ��������� �������


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_Clear(void)
{
    pDS = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadFromRAM(int fromEnd, DataStruct *dataStruct)
{
    Data_Clear();

    bool readed = false;                // ������� ����, ��� ������ �������

    if (IN_AVERAGING_MODE               // ���� �������� ����������
        && fromEnd == 0)                // � ����������� ��������� ��������� ������
    {
        dataSettings = *DS_DataSettingsFromEnd(0);
        pDS = &dataSettings;
        if (ENABLED_DS_A)
        {
            memcpy(inA, DS_GetAverageData(A), BYTES_IN_CHANNEL(DS));
        }
        if (ENABLED_DS_B)
        {
            memcpy(inB, DS_GetAverageData(B), BYTES_IN_CHANNEL(DS));
        }
        readed = true;
    }
    else
    {
        DS_GetDataFromEnd(fromEnd, &dataSettings, inA, inB);
        readed = true;
    }

    if (readed)
    {
        if (ENUM_POINTS(&dataSettings) == FPGA_ENUM_POINTS) /** \todo ��� ��������. ����� ������� �������� � ������������� ����� ������ �
                                                            � ProcessingSignal_SetData(), ����� �� �������� �� ������. */
        {
            pDS = &dataSettings;

            Processing_SetData();

            PrepareDataForDraw(dataStruct);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadFromROM(DataStruct *dataStruct)
{
    Data_Clear();

    if (FLASH_GetData(NUM_ROM_SIGNAL, &dataSettings, inA, inB))
    {
        pDS = &dataSettings;

        Processing_SetData();

        PrepareDataForDraw(dataStruct);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void PrepareDataForDraw(DataStruct *dataStruct)
{
    if (!dataStruct)
    {
        return;
    }

    dataStruct->peackDet = PEACKDET_DS;  // ������������ ����� ���� � ��� ������, ���� ������ �������� ��������� �� ���������
}


/** @}  @}
 */
