#include "Settings.h"
#include "Display/Grid.h"
#include "SettingsCursors.h"
#include "Utils/Math.h"
#include "Utils/GlobalFunctions.h"
#include "Menu/MenuFunctions.h"
#include "FPGA/FPGAtypes.h"


#include <math.h>


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float sCursors_GetCursPosU(Channel ch, int numCur)
{
    return CURsU_POS(ch, numCur) / (GridChannelBottom() == GridFullBottom() ? 1.0f : 2.0f);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
bool sCursors_NecessaryDrawCursors(void)
{
    return (CURsU_ENABLED || CURsT_ENABLED) && (set.cursors.showCursors || GetNameOpenedPage() == Page_SB_Curs);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* sCursors_GetCursVoltage(Channel source, int numCur, char buffer[20])
{
    float voltage = Math_VoltageCursor(sCursors_GetCursPosU(source, numCur), RANGE(source), RSHIFT(source));
    if (DIVIDER_10(source))
    {
        voltage *= 10.0f;
    }
    return Voltage2String(voltage, true, buffer);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* sCursors_GetCursorTime(Channel source, int numCur, char buffer[20])
{
    float time = Math_TimeCursor(CURsT_POS(source, numCur), TBASE);
        
    return Time2String(time, true, buffer);
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* sCursors_GetCursorPercentsU(Channel source, char buffer[20])
{
    buffer[0] = 0;
    float dPerc = dUperc(source);
    float dValue = fabsf(sCursors_GetCursPosU(source, 0) - sCursors_GetCursPosU(source, 1));
    char bufferOut[20];
    char* percents = Float2String(dValue / dPerc * 100.0f, false, 5, bufferOut);
    strcat(buffer, percents);
    strcat(buffer, "%");
    return buffer;
}


//------------------------------------------------------------------------------------------------------------------------------------------------------
const char* sCursors_GetCursorPercentsT(Channel source, char buffer[20])
{
    buffer[0] = 0;
    float dPerc = dTperc(source);
    float dValue = fabsf(CURsT_POS(source, 0) - CURsT_POS(source, 1));
    char bufferOut[20];
    char* percents = Float2String(dValue / dPerc * 100.0f, false, 6, bufferOut);
    strcat(buffer, percents);
    strcat(buffer, "%");
    return buffer;
}
