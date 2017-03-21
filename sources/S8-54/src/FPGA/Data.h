﻿#pragma once
#include "Settings/DataSettings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
extern DataSettings *gDSmemLast;        //--
extern uint8        *gDataAmemLast;     // | Здесь данные из ОЗУ, которые должны выводиться на экран
extern uint8        *gDataBmemLast;     //-/


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define DS_MEM_INT  (Data_DSMemInt())
#define CHA_MEM_INT (Data_ChMemInt(A))
#define CHB_MEM_INT (Data_ChMemInt(B))

#define DS      (Data_DS())
#define P_DS    (Data_pDS())
#define DATAA   (Data_ChDS(A))
#define DATAB   (Data_ChDS(B))
#define P_DATAA (Data_pChDS(A))
#define P_DATAB (Data_pChDS(B))


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Data_GetFromIntMemory(void);       // Считать из ППЗУ информацию о настройках и указатели на данные
DataSettings*  Data_DSMemInt(void);     // Возвращает указатель на настройки сигнала из ППЗУ
DataSettings** Data_pDSMemInt(void);    // Возвращает указатель на указатель на настройки сигнала из ППЗУ   TODO Отрефакторить - этой функции не должно быть
uint8*  Data_ChMemInt(Channel ch);      // Получить указатель на канал данных из ППЗУ
uint8** Data_pChMemInt(Channel ch);     // Возвращает указатель на указатель на канал данных на ППЗУ TODO Этой функции не должно остаться после рефакторинга

DataSettings*  Data_DS(void);           // Указатель на настройки рисуемых сигналов
DataSettings** Data_pDS(void);          // Указатель на указатель на настройки рисуемых сигналов    TODO после рефакторинга этого не должно быть
uint8* Data_ChDS(Channel ch);           // Указатель на данные канала рисуемого сигнала
uint8** Data_pChDS(Channel ch);         // Указатель на указатель на рисуемые данные TODO отрефакторить, чтобы не было

void Data_GetAverageFromDataStorage(void);
