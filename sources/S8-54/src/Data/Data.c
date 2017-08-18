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
static void PrepareDataForDraw(StructDataDrawing *dataStruct);
static void FillDataP2P(StructDataDrawing *dataStruct, Channel ch);
static void FillDataNormal(StructDataDrawing *dataStruct, Channel ch);


static DataSettings dataSettings;   ///< ����� �������� ��������� ��� �������� ��������� �������


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_Clear(void)
{
    DS = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadFromRAM(int fromEnd, StructDataDrawing *dataStruct)
{
    Data_Clear();

    bool readed = false;                                                    // ������� ����, ��� ������ �������

    if ((IN_AVERAGING_MODE || (IN_RANDOM_MODE && NRST_NUM_AVE_FOR_RAND))    // ���� �������� ����������
        && fromEnd == 0)                                                    // � ����������� ��������� ��������� ������
    {
        dataSettings = *DS_DataSettingsFromEnd(0);
        DS = &dataSettings;
        if (ENABLED_DS_A)
        {
            memcpy(IN_A, DS_GetAverageData(A), BYTES_IN_CHANNEL(DS));
        }
        if (ENABLED_DS_B)
        {
            memcpy(IN_B, DS_GetAverageData(B), BYTES_IN_CHANNEL(DS));
        }
        readed = true;
    }
    else
    {
        DS_GetDataFromEnd(fromEnd, &dataSettings, IN_A, IN_B);
        readed = true;
    }

    if (readed)
    {
        if (ENUM_POINTS(&dataSettings) == FPGA_ENUM_POINTS) /** \todo ��� ��������. ����� ������� �������� � ������������� ����� ������ �
                                                            � ProcessingSignal_SetData(), ����� �� �������� �� ������. */
        {
            DS = &dataSettings;

            Processing_SetData();

            PrepareDataForDraw(dataStruct);
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadFromROM(StructDataDrawing *dataStruct)
{
    Data_Clear();

    if (FLASH_GetData(NUM_ROM_SIGNAL, &dataSettings, IN_A, IN_B))
    {
        DS = &dataSettings;

        Processing_SetData();

        PrepareDataForDraw(dataStruct);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void PrepareDataForDraw(StructDataDrawing *dataStruct)
{
    if (!dataStruct)
    {
        return;
    }

    if (!DS)
    {
        dataStruct->needDraw[A] = dataStruct->needDraw[B] = false;
        return;
    }

    dataStruct->needDraw[A] = ENABLED_DS_A && SET_ENABLED_A;
    dataStruct->needDraw[B] = ENABLED_DS_B && SET_ENABLED_B;

    if (IN_P2P_MODE && DS_NumPointsInLastFrameP2P() < 2)
    {
        dataStruct->needDraw[A] = dataStruct->needDraw[B] = false;
        return;
    }

    if (IN_P2P_MODE)
    {
        FillDataP2P(dataStruct, A);
        FillDataP2P(dataStruct, B);
    }
    else
    {
        FillDataNormal(dataStruct, A);
        FillDataNormal(dataStruct, B);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void FillDataP2P(StructDataDrawing *dataStruct, Channel ch)
{
    for (int i = 0; i < 281; i++)
    {
        dataStruct->data[ch][i] = 0;
    }
    
    if(!dataStruct->needDraw[ch])
    {
        return;
    }
    
    int allPoints = DS_NumPointsInLastFrameP2P();
    if (allPoints > 1)
    {
        int pointer = 0;                // ��������� �� ������ ������� ������
        int index = 0;                  // ��������� �� ������ ��������� ������, � ������� �� ������� 281 �����
        while (allPoints > BYTES_IN_CHANNEL(DS))
        {
            ++index;
            if (index > 280)
            {
                index = 0;
            }
            --allPoints;
        }
        while (allPoints > 0)
        {
            dataStruct->data[ch][index] = dataOUT[ch][pointer];
            index++;
            pointer++;
            allPoints--;
            if (index > 280)
            {
                index = 0;
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void FillDataNormal(StructDataDrawing *dataStruct, Channel ch)
{
    if (!dataStruct->needDraw[ch])
    {
        return;
    }

    BitSet64 points = sDisplay_BytesOnDisplay();

    uint8 *dest = dataStruct->data[ch];
    uint8 *src = &dataOUT[ch][points.word0];

    int numBytes = PEAKDET_DS ? 281 * 2 : 281;

    for(int i = 0; i < numBytes; i++)
    {
        *dest++ = *src++;
    }
}


/** @}  @}
 */
