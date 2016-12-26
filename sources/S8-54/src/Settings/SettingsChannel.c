#include "Settings.h"
#include "SettingsChannel.h"
#include "FPGA/FPGA.h"
#include "Utils/Math.h"
#include "Utils/GlobalFunctions.h"


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������� ��� �������� ��������� �������� �� ����������.
typedef struct
{
    const char* name[2][2];     // �������� ��������� � ��������� ����, ��������� ��� ������ �� �����.
} RangeStruct;


// ������ �������� �������� ��������� �� ����������.
static const RangeStruct ranges[RangeSize] =
{
    {"2\x10��", "20\x10��", "2\x10�V",  "20\x10�V"},
    {"5\x10��", "50\x10��", "5\x10mV",  "50\x10mV"},
    {"10\x10��","0.1\x10�", "10\x10mV", "0.1\x10V"},
    {"20\x10��","0.2\x10�", "20\x10mV", "0.2\x10V"},
    {"50\x10��","0.5\x10�", "50\x10mV", "0.5\x10V"},
    {"0.1\x10�","1\x10�",   "0.1\x10V", "1\x10V"},
    {"0.2\x10�","2\x10�",   "0.2\x10V", "2\x10V"},
    {"0.5\x10�","5\x10�",   "0.5\x10V", "5\x10V"},
    {"1\x10�",  "10\x10�",  "1\x10V",   "10\x10V"},
    {"2\x10�",  "20\x10�",  "2\x10V",   "20\x10V"},
    {"5\x10�",  "50\x10�",  "5\x10V",   "50\x10V"}
};


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sChannel_SetRange(Channel ch, Range range)
{
    RANGE(ch) = range;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
int sChannel_MultiplierRel2Abs(Divider divider)
{
    switch (divider)
    {
        case Multiplier_10:
            return 10;
    }
    return 1;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sChannel_Enabled(Channel ch)
{
    if (ch == Math && FUNC_ENABLED)
    {
        return true;
    }
    return set.chan[ch].enable;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* sChannel_Range2String(Range range, Divider divider)
{
    return ranges[range].name[LANG][divider];
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* sChannel_RShift2String(uint16 rShiftRel, Range range, Divider divider, char buffer[20])
{
    float rShiftVal = RSHIFT_2_ABS(rShiftRel, range) * sChannel_MultiplierRel2Abs(divider);
    return Voltage2String(rShiftVal, true, buffer);
};


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sChannel_NeedForDraw(const uint8 *data, Channel ch, DataSettings *ds)
{
    if (!data)
    {
        return false;
    }

    if (WORK_DIRECT)
    {
        if (!sChannel_Enabled(ch))
        {
            return false;
        }
    }
    else if (ds != 0)
    {
        if ((ch == A && ds->enableChA == 0) || (ch == B && ds->enableChB == 0))
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    return true;
}
