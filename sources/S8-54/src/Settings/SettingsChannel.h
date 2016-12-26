#pragma once


#include "SettingsTypes.h"


#define INVERSE(ch) (set.chan[ch].inverse)
#define RANGE(ch)   (set.chan[ch].range)
#define RANGE_A     (set.chan[A].range)
#define RANGE_B     (set.chan[B].range)
#define RSHIFT(ch)  (set.chan[ch].rShiftRel)
#define RSHIFT_A    (set.chan[A].rShiftRel)
#define RSHIFT_B    (set.chan[B].rShiftRel)
#define COUPLE(ch)  (set.chan[ch].modeCouple)
#define COUPLE_A    (set.chan[A].modeCouple)
#define COUPLE_B    (set.chan[B].modeCouple)
#define TRIGLEV(ch) (set.trig.levelRel[ch])
#define TRIGSOURCE  (set.trig.source)
#define RSHIFT_MATH (set.math.rShift)
#define RANGE_MATH  (set.math.range)


void    sChannel_SetRange(Channel ch, Range range);           // ���������� ������� �� ���������� ������ ch.
int     sChannel_MultiplierRel2Abs(Divider divider);
bool    sChannel_Enabled(Channel ch);                         // ���������� true, ���� ����� ch �������.
bool    sChannel_NeedForDraw(const uint8 *data, Channel ch, DataSettings *ds);

const char *sChannel_Range2String(Range range, Divider divider);
const char *sChannel_RShift2String(uint16 rShiftRel, Range range, Divider divider, char buffer[20]);
const char *sChannel_TShift2String(int16 tShiftRel, TBase tBase);
