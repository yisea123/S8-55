// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#define _INCLUDE_DATA_
#include "Data.h"
#undef _INCLUDE_DATA_
#include "DataBuffer.h"
#include "Globals.h"
#include "Hardware/FLASH.h"
#include "Hardware/FSMC.h"
#include "Settings/SettingsMemory.h"
#include "Utils/ProcessingSignal.h"


/** @addtogroup FPGA
 *  @{
 *  @addtogroup Data
 *  @{
 */


static DataSettings dataSettings;   ///< ����� �������� ��������� ��� �������� ��������� �������


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool readedRAM = false;      ///< ���� true, �� � inA(B) �������� ������, ��������� �� ���.
static bool fromEndRAM = 0;         ///< ����� �������� ������� �� ���, ���� readedRAM == true.

static bool readedROM = false;      ///< ���� true, �� � inA(B) �������� ������, ��������� �� ����.
static bool numFromROM = 0;         ///< ����� ���������� �� ���� �������, ���� readedROM == true.

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������� ������ 
static void GetDataFromStorage(void);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_Clear(void)
{
    pDS = 0;
    readedRAM = readedROM = false;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadDataRAM(int fromEnd)
{
    if(readedRAM && fromEnd == fromEndRAM)
    {
        return;
    }

    Data_Clear();

    if(DS_GetDataFromEnd(fromEnd, &dataSettings, inA, inB))
    {
        if (ENUM_POINTS(&dataSettings) == FPGA_ENUM_POINTS) /** \todo ��� ��������. ����� ������� �������� � ������������� ����� ������ � 
                                                               � ProcessingSignal_SetData(), ����� �� �������� �� ������. */
        {
            readedRAM = true;
            fromEndRAM = fromEnd;
            pDS = &dataSettings;

            Processing_SetData();
        }
    }
}

void Data_GetFromIntMemory(void)
{
    /*
    if(FLASH_GetData(NUM_ROM_SIGNAL, &pDSROM, &dataROMA, &dataROMB))
    {
    memcpy(&dataSettingsROM, (void*)pDSROM, sizeof(DataSettings));
    }
    */
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_ReadDataROM(void)
{
    if(readedROM && numFromROM == NUM_ROM_SIGNAL)
    {
        return;
    }

    Data_Clear();

    if (FLASH_GetData(NUM_ROM_SIGNAL, &dataSettings, inA, inB))
    {
        readedROM = true;
        numFromROM = NUM_ROM_SIGNAL;
        pDS = &dataSettings;

        Processing_SetData();
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_GetAverageFromDataStorage(void)
{
    if(DS)
    {
        if(G_ENABLED_A)
        {
            memcpy(inA, DS_GetAverageData(A), BYTES_IN_CHANNEL(DS));
        }
        if(G_ENABLED_B)
        {
            memcpy(inB, DS_GetAverageData(B), BYTES_IN_CHANNEL(DS));
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_Load(void)
{
    Data_Clear();

    if (DS_NumElementsInStorage() == 0)
    {
        return;
    }

    if (MODE_WORK_DIR)                              // ���� ��������� � �������� ������
    {   
        GetDataFromStorage();                       // ��������� ������ �� ���������

        if (ALWAYS_SHOW_ROM_SIGNAL)                 // �, ���� ����� ���������� ������ �� ���� � � �������� ������
        {
            Data_GetFromIntMemory();                // �� �� ��������
        }
    }
    else if (MODE_WORK_RAM)                         // ���� ��������� � ������ ����������� ���������
    {
//        DS_GetDataFromEnd_RAM(NUM_RAM_SIGNAL, &pDSRAM, (uint16**)&dataRAMA, (uint16**)&dataRAMB);
    }
    else if (MODE_WORK_ROM)
    {
        if (!SHOW_IN_INT_DIRECT)                    // ���� ������������ �� ������ ���������������� ������
        {
            Data_GetFromIntMemory();                // �� ������ ����������� �� ����
        }

        if (SHOW_IN_INT_DIRECT || SHOW_IN_INT_BOTH) // �, ���� �����
        {
            GetDataFromStorage();                   // �� ���������
        }
    }
    
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Data_PrepareToDrawSettings(void)
{
    if (MODE_WORK_DIR)
    {

    }
    else if (MODE_WORK_RAM)
    {

    }
    else if (MODE_WORK_ROM)
    {
        if (SHOW_IN_INT_SAVED)                      // ���� ��������� ������ ����������� ������
        {
        }
        else                                        // � ���� �� ������ ���� � ������ ������
        {
            if (EXIT_FROM_ROM_TO_RAM)               // ���� ������ �� ���
            {
            }
            else                                    // ���� ���������������� ������
            {
            }
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
static void GetDataFromStorage(void)
{
    /*
    int fromEnd = 0;

    if (IN_P2P_MODE &&                              // ��������� � ������ ����������� ������
    START_MODE_WAIT &&                          // � ������ ������ �������������
    DS_NumElementsWithCurrentSettings() > 1)    // � � ��������� ��� ���� ��������� ������� � ������ �����������
    {
    fromEnd = 1;
    }

    DS_GetDataFromEnd_RAM(fromEnd, &pDSDir, (uint16**)&dataDirA, (uint16**)&dataDirB);

    if (sDisplay_NumAverage() != 1 || IN_RANDOM_MODE)
    {
    ModeFSMC mode = FSMC_GetMode();
    FSMC_SetMode(ModeFSMC_RAM);
    Data_GetAverageFromDataStorage();
    FSMC_SetMode(mode);
    }
    */
}


/** @}  @}
 */
