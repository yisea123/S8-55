﻿#pragma once
#include "Settings/DataSettings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DS              pDS             

#define DATA(ch)        (dataChan[ch])  
#define DATA_INT(ch)    (dataChanInt[ch])
#define DATA_LAST(ch)   (dataChanLast[ch])

#ifndef _INCLUDE_DATA_
    #define EXTERN extern
#else
    #define EXTERN
#endif

EXTERN DataSettings *pDS;

EXTERN uint8* dataChan[2];
EXTERN uint8 *dataChanLast[2];
EXTERN uint8 *dataChanInt[2];

#undef EXTERN

#define DS_TSHIFT       (DS->tShift)
#define DS_TBASE        ((TBase)(DS->tBase))
#define DS_INVERSE(ch)  ((bool)((ch == A) ? DS->inverseA : DS->inverseB))
#define DS_COUPLE(ch)   ((ModeCouple)((ch == A) ? DS->coupleA : DS->coupleB))
#define DS_DIVIDER(ch)  ((Divider)((ch == A) ? DS->multiplierA : DS->multiplierB))
#define DS_RANGE(ch)    ((Range)(DS->range[ch]))
#define DS_ENABLED(ch)  ((bool)((ch == A) ? DS->enableA : DS->enableB))
#define DS_RSHIFT(ch)   (DS->rShift[ch])

#define DS_TIME_DAY     (DS->time.day)
#define DS_TIME_HOURS   (DS->time.hours)
#define DS_TIME_MINUTES (DS->time.minutes)
#define DS_TIME_SECONDS (DS->time.seconds)
#define DS_TIME_MONTH   (DS->time.month)
#define DS_TIME_YEAR    (DS->time.year)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_GetFromIntMemory(void);           // Считать из ППЗУ информацию о настройках и указатели на данные
void Data_GetAverageFromDataStorage(void);
void Data_Load(void);