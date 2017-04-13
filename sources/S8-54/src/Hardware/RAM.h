#pragma once


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Hardware
 *  @{
 *  @defgroup RAM
 *  @brief ������ � ������� ���
 *  @{
 */

typedef enum
{
    FPGA_DATA_A             = 0,
    FPGA_DATA_B             = 1,

    // DataStorage
    DS_DATA_IMPORT_REL_A    = 2,
    DS_DATA_IMPORT_REL_B    = 3,
    DS_AVE_DATA_A           = 4,
    DS_AVE_DATA_B           = 5,
    DS_SUM_A                = 6,
    DS_SUM_B                = 7,
    DS_LIMIT_UP_A           = 8,
    DS_LIMIT_UP_B           = 9,
    DS_LIMIT_DOWN_A         = 10,
    DS_LIMIT_DOWN_B         = 11,

    // ProcessingSignal
    PS_DATA_OUT_A           = 12,
    PS_DATA_OUT_B           = 13,
    PS_DATA_IN_A            = 14,
    PS_DATA_IN_B            = 15,

    DRAW_MATH_DATA_REL_A    = 16,
    DRAW_MATH_DATA_REL_B    = 17,

    DS_POOL_BEGIN           = 18,   ///< ����� ������ �����, ��� �������� ������� �� ������� ���
    DS_POOL_END             = 19    ///< ����� ����� �����, ��� �������� ������� �� ������� ���
} Address;


/// �������������
void RAM_Init(void);
/// ����� � �������� ������� ��������� �� ���������� ����, ������� ������ numBytes
void RAM_WriteRead_Sinch2(void *src, void *dest, int numBytes);
/// ��� ������ �����, ��� ������ ��������
void RAM_WriteRead_Sinch4(void *src, void *dest, int numBytes);

void RAM_WriteRead_Sinch8(void *src, void *dest, int numBytes);
/// ��� ������ ���������� ����� DMA. �� ��������, ���� ������ ��������� � ������ CCM data RAM
void RAM_WriteRead_Asinch(uint16 *src, uint16 *dest, int numHalfWords);

bool RAM_WriteReadComplete(void);

void RAM_WaitWriteReadComplete(void);

void RAM_MemSet_Sinch(uint8 *dest, uint8 value, int numBytes);

void RAM_MemShiftLeft(uint8 *address, int numBytes, int shift);

void RAM_WriteByte(void *dest, uint8 value);

uint8 RAM_ReadByte(void *src);

void RAM_WriteWord(void *dest, uint value);

uint RAM_ReadWord(void *src);
/// �������� ����� � ��������, ������� 16. ����� �� ������� ��� ������ ���� �������� �� ����������
void RAM_MemCpy16(void *src, void *dest, int numBytes);
/// ������ ������ �� ���. ������ ������ ������ �����. src ����� ���� ������ �����
void RAM_ReadBuffer1(void *src, void *dest, int numBytes);

void RAM_MemClear(void *address, int numHalfWords);

void RAM_Test(void);

uint8* RAM(Address address);

/** @}  @}
 */
