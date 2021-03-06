

#include "defines.h"
#include "commonSCPI.h"
#include "Hardware/Hardware.h"
#include "Settings/Settings.h"
#include "VCP/VCP.h"
#include "VCP/SCPI/SCPI.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Process_IDN(uint8 *buffer)
{
    char buf[100] = {0};

    sprintf(buf, "%s, %s, V%s, %0X", "MNIPI", MODEL_EN, NUM_VER, Hardware_CalculateCRC32());

    SCPI_SEND(buf);
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Process_RUN(uint8 *buffer)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Process_STOP(uint8 *buffer)
{

}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Process_RESET(uint8 *buffer)
{
    Settings_Load(true);
}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Process_AUTOSCALE(uint8 *buffer)
{

}


//----------------------------------------------------------------------------------------------------------------------------------------------------
void Process_REQUEST(uint8 *buffer)
{
    SCPI_SEND(MODEL_EN);
}
