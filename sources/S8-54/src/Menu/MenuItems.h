#pragma once
#include "Display/Colors.h"
#include "Display/Display.h"
#include "Utils/GlobalFunctions.h"
#include "defines.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/** @addtogroup Menu
 *  @{
 *  @defgroup MenuItems Menu Items
 *  @{
 */

extern int8 gCurDigit;

#define MAX_NUM_SUBITEMS_IN_CHOICE  12  ///< ������������ ���������� ��������� ������ � �������� Choice.
#define MAX_NUM_ITEMS_IN_PAGE       16  ///< ������������ ���������� ������� �� ��������.
#define MENU_ITEMS_ON_DISPLAY       5   ///< ������� ������� ���� ���������� �� ������ �� ���������.
#define MAX_NUM_CHOICE_SMALL_BUTTON 6   ///< ������������ ���������� ��������� ��������� ������ + 1


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ������ ���� ������� ����
typedef enum
{
    Item_None,           
    Item_Choice,        ///< ����� ������ - ��������� ������� ���� �� ���������� �������� ��������.
    Item_Button,        ///< ������.
    Item_Page,          ///< ��������.
    Item_Governor,      ///< ��������� - ��������� ������� ����� ����� �������� �������� �� ������� ��������� ����������.
    Item_Time,          ///< ��������� ������ �����.
    Item_IP,            ///< ��������� ������ IP-�����.
    Item_GovernorColor, ///< ��������� ������� ����.
    Item_Formula,       ///< ��������� ������� ���� � ������������ ��� �������������� ������� (��������� � ��������)
    Item_MAC,           ///< MAC-�����
    Item_ChoiceReg,     ///< ������� ������, � ������� ����� �������������� �� �������, � ������
    Item_SmallButton,   ///< ������ ��� ������ ����� ������
    Item_NumberItems
} TypeItem;

/// ����� ID ���� �������������� � ���� �������
typedef enum
{
    Page_Main,                      ///< ������� �������� ����
    Page_Display,                   ///< ������
    Page_Display_Accum,             ///< ������� - ����������
    Page_Display_Average,           ///< ������� - ����������
    Page_Display_Grid,              ///< ������� - �����
    Page_Display_Settings,          ///< ������� - ���������
    Page_Display_Settings_Colors,   ///< ������� - ��������� - �����
    Page_ChannelA,                  ///< ����� 1
    Page_ChannelB,                  ///< ����� 2
    Page_Trig,                      ///< �����
    Page_Trig_Search,               ///< ����� - �����
    Page_Time,                      ///< ���������
    Page_Cursors,                   ///< �������
    PageSB_Cursors_Set,             ///< ������� - ����������
    Page_Memory,                    ///< ������
    PageSB_Memory_Last,             ///< ������ - ���������
    PageSB_Memory_Internal,         ///< ������ - ����� ��
    Page_Memory_Drive,              ///< ������ - ����� ��
    PageSB_Memory_Drive_Manager,    ///< ������ - ����� �� - �������
    PageSB_Memory_Drive_Mask,       ///< ������ - ����� �� - �����
    PageSB_Memory_SetName,          ///< \brief ���������� ����� ����������� ����� �� ������ ��� ������� ����� ����� ��� ��������������� ����� 
                                    ///< ����� �� - ��� �����
    Page_Measures,                  ///< ���������
    PageSB_Measures_Tune,           ///< ��������� - ���������
    Page_Service,                   ///< ������
    Page_Service_Calibrator,        ///< ������ - ����������
    Page_Service_Ethernet,          ///< ������ - ETHERNET
    Page_Service_FreqMeter,         ///< ������ - ����������
    Page_Service_Sound,             ///< ������ - ����
    Page_Service_RTC,               ///< ������ - �����
    Page_Service_FFT,               ///< ������ - ������
    PageSB_Service_FFT_Cursors,     ///< ������ - ������ - �������
    PageSB_Service_Function,        ///< ������ - �������
    PageSB_Service_Information,     ///< ������ - ����������
    PageSB_Service_Recorder,        ///< ������ - �����������
    PageSB_Help,                    ///< ������
    Page_Debug,                     ///< �������
    Page_Debug_Console,             ///< ������� - �������
    Page_Debug_Console_Registers,   ///< ������� - ������� - ��������
    Page_Debug_ADC,                 ///< ������� - ���
    Page_Debug_ADC_Balance,         ///< ������� - ��� - ������
    Page_Debug_ADC_Stretch,         ///< ������� - ��� - ��������
    Page_Debug_ADC_Shift,           ///< ������� - ��� - ��� ����
    Page_Debug_ADC_AltShift,        ///< ������� - ��� - ��� ���� ���
    Page_Debug_Rand,                ///< ������� - ����-���
    Page_Debug_Channels,            ///< ������� - ������
    PageSB_Debug_Settings,          ///< ������� - ���������
    PageSB_Debug_SerialNumber,      ///< ������� - �/�
    Page_NumPages,
    Page_NoPage
} NamePage;

#define FuncDraw    EmptyFuncVII
#define FuncActive  EmptyFuncBV
#define FuncPress   EmptyFuncVV

class Control
{
public:
    /*
    Control(TypeItem type_, char *titleRu, char *titleEn, char *hintRu, char *hintEn) : type(type_)
    {
    titleHint[0] = titleRu;
    titleHint[1] = titleEn;
    titleHint[2] = hintRu;
    titleHint[3] = hintEn;
    };
    */
protected:
    //TypeItem type;
};

/// ����� ����� ��� ���� ����� ��������� ����
#define COMMON_PART_MENU_ITEM                                                                                   \
    TypeItem                type;           /* ��� ����� */                                                     \
    const struct Page      *keeper;         /* ����� ��������, ������� �����������. ��� Page_Main = 0 */        \
    pFuncBV                 funcOfActive;   /* ������� �� ������ ������� */                                     \
    const char             *titleHint[4];   /* �������� �������� �� ������� � ���������� ������. ����� ��������� ��� ������ ������ */

#define COMMON_PART_MENU_ITEM_NEW                                                                               \
    TypeItem                type;           /* ��� ����� */                                                     \
    const struct Page      *keeper;         /* ����� ��������, ������� �����������. ��� Page_Main = 0 */        \
    pFuncBV                 funcOfActive;   /* ������� �� ������ ������� */                                     \
    const char             **titleHint;     /* �������� �������� �� ������� � ���������� ������. ����� ��������� ��� ������ ������ */

struct SButton;

/// ��������� �������� ����.
struct Page
{
    COMMON_PART_MENU_ITEM
    NamePage name;                          ///< ��� �� ������������ NamePage
    void    *items[MAX_NUM_ITEMS_IN_PAGE];  ///< ����� ��������� �� ������ ���� �������� (� ������� ��������)
                                            ///< ��� �������� ����� ������  ����� �������� 6 ���������� �� SButton : 0 - B_Menu, 1...5 - B_F1...B_F5
    bool     isPageSB;                      ///< ���� true, �� ��� �������� ����� ������
    pFuncVV  funcOnPress;                   ///< ����� ���������� ��� ������� �� �������� ��������
    pFuncVV  funcOnDraw;                    ///< ����� ���������� ����� ��������� ������
    pFuncVI  funcRegSetSB;                  ///< � �������� ����� ������ ���������� ��� �������� ����� ���������
    int NumSubPages() const;                ///< D��������� ����� ���������� � �������� �� ������ page
    int NumItems() const;                   ///< ���������� ���������� ��������� � �������� �� ������ page
    int NumCurrentSubPage();                ///< ���������� ����� ������� ���������� �������� �� ������ page
    NamePage GetNamePage() const;           ///< ���������� ��� �������� page
    void SetCurrentSB() const;              ///< ���������� ������� ������ �������� � ������ ��������.
    
    void *Item(int numElement) const;       ///< ���������� ����� �������� ���� �������� ��������
    SButton* SmallButonFromPage(int numButton);
    /// \todo ���������� ������� ������� �������� �������� �� ������ page �� ������. ���� ������� ����������� 0, ��� ����� 0, ���� ������� 
    /// ����������� 1, ��� ����� 5 � �.�.
    int PosItemOnTop();
    /// �������� ������� ��������� ������� ������ ��� ������ numItem �������� page
    void ShortPressOnItem(int numItem);
    /// ���������� ������� �������� �������� ������� page
    int8 PosCurrentItem() const;
    void ChangeSubPage(int delta) const;
    void Draw(int x, int y);
};

typedef struct Page Page;

/// ������ �������
typedef struct
{
    COMMON_PART_MENU_ITEM
} Empty;

#define COMMON_INIT                     \
    if (funcOnPress == 0)               \
    {                                   \
        funcOnPress = EmptyFuncVV;      \
    }                                   \
    if (funcOfActive == 0)              \
    {                                   \
        funcOfActive = EmptyFuncBV;     \
    }                                   \
    if (funcForDraw == 0)               \
    {                                   \
        funcForDraw = EmptyFuncVII;     \
    }


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ������.
struct Button
{
    COMMON_PART_MENU_ITEM
    pFuncVV     funcOnPress;        ///< �������, ������� ���������� ��� ������� �� ������.
    pFuncVII    funcForDraw;        ///< ������� ����� ���������� �� ����� ��������� ������.
    void CallFuncOnDraw(int x, int y);
    void Draw(int x, int y);
};

#define DEF_BUTTON(name, titleRU, titleEN, hintRU, hintEN, keeper, funcActive, funcPress, funcDraw) \
static const Button name = { Item_Button, &keeper, funcActive, {titleRU, titleEN, hintRU, hintEN}, funcPress, funcDraw };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef struct
{
    pFuncVII    funcDrawUGO;        ///< ��������� �� ������� ��������� ����������� �������� ������
    const char * const helpUGO[2];  ///< ������� � ������� �����������.
} StructHelpSmallButton;


/// ��������� ������ ��� ��������������� ������ ����.
class SButton
{
public:
    SButton(const char * const title[4], const Page *keeper_,
        pFuncVV funcOnPress_, pFuncVII funcForDraw_ = EmptyFuncVII, pFuncBV funcActive_ = EmptyFuncBV, const StructHelpSmallButton *hintsUGO = 0,
        int numHints_ = 0) :
        type(Item_SmallButton), keeper(keeper_), funcOfActive(funcActive_), titleHint((const char **)title), 
        funcOnPress(funcOnPress_), funcForDraw(funcForDraw_), hintUGO(hintsUGO), numHints(numHints_)
    {
        COMMON_INIT;
    }
    COMMON_PART_MENU_ITEM_NEW
    pFuncVV                             funcOnPress;    ///< ��� ������� ��������� ��� ��������� ������� ������.
    pFuncVII                            funcForDraw;    ///< ��� ������� ���������� ��� ��������� ������ � ����� � ������������ x, y.
    const StructHelpSmallButton *hintUGO; 
    int numHints;
    void Draw(int x, int y);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ��������� ���������.
typedef struct
{
    COMMON_PART_MENU_ITEM
    int16  *cell;
    int16   minValue;       ///< ���������� ��������, ������� ����� ��������� ���������.
    int16   maxValue;       ///< ������������ ��������.
    pFuncVV funcOfChanged;  ///< �������, ������� ����� �������� ����� ����, ��� �������� ���������� ����������.
    pFuncVV funcBeforeDraw; ///< �������, ������� ���������� ����� ����������
    /// ��������� �������� �������� ���������� ��� ���������� �������� ���� ���� Governor (� ����������� �� ����� delta).
    void StartChange(int detla);
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 NextValue();
    /// ���������� ��������� ������� ��������, ������� ����� ������� governor.
    int16 PrevValue();
    /// ������������ ��������� ���� ��������.
    float Step();
    /// �������� �������� � ������� ������� ��� ��������� ��������.
    void ChangeValue(int delta);
    /// ��� �������� �������� ������������ ������ �� ��������� �������.
    void NextPosition();
    /// ���������� ����� ��������� � ���� ��� ����� �������� governor. ������� �� ������������� ��������, ������� ����� ��������� governor.
    int  NumDigits();
    void Draw(int x, int y, bool opened);
    void DrawOpened(int x, int y);
    void DrawClosed(int x, int y);
    void DrawValue(int x, int y);
    void DrawLowPart(int x, int y, bool pressed, bool shade);
} Governor;

typedef struct
{
    COMMON_PART_MENU_ITEM
    uint8 *ip0;
    uint8 *ip1;
    uint8 *ip2;
    uint8 *ip3;
    pFuncVB funcOfChanged;
    uint16 *port;
    void NextPosition();                            ///< ��� �������� �������� ������������ ������ �� ��������� �������.
    void ChangeValue(int delta);                    ///< �������� �������� � ������� ������� ��� �������� ��������.
    void GetNumPosIPvalue(int *numIP, int *selPos); ///< ���������� ����� �������� ����� (4 - ����� �����) � ����� ������� ������� � �����.
    void Draw(int x, int y, bool opened);
    void DrawOpened(int x, int y);
    void DrawClosed(int x, int y);
    void DrawValue(int x, int y);
    void DrawLowPart(int x, int y, bool pressed, bool shade);
} IPaddress;

typedef struct
{
    COMMON_PART_MENU_ITEM
    uint8 *mac0;
    uint8 *mac1;
    uint8 *mac2;
    uint8 *mac3;
    uint8 *mac4;
    uint8 *mac5;
    pFuncVB funcOfChanged;
    void ChangeValue(int delta);
    void Draw(int x, int y, bool opened);
    void DrawOpened(int x, int y);
    void DrawClosed(int x, int y);
    void DrawValue(int x, int y);
    void DrawLowPart(int x, int y, bool pressed, bool shade);
} MACaddress;

/// ��������� ������� ���� ��� ��������� ������������� � ������ �������������� �������
#define FIELD_SIGN_MEMBER_1_ADD 0
#define FIELD_SIGN_MEMBER_1_MUL 1
#define FIELD_SIGN_MEMBER_2_ADD 2
#define FIELD_SIGN_MEMBER_2_MUL 3
#define POS_SIGN_MEMBER_1       0
#define POS_KOEFF_MEMBER_1      1
#define POS_SIGN_MEMBER_2       2
#define POS_KOEFF_MEMBER_2      3
typedef struct
{
    COMMON_PART_MENU_ITEM
    int8   *function;       ///< ����� ������, ��� �������� Function, �� ������� ������ ���� ��������
    int8   *koeff1add;      ///< ����� ������������ ��� ������ ����� ��� ��������
    int8   *koeff2add;      ///< ����� ������������ ��� ������ ����� ��� ��������
    int8   *koeff1mul;      ///< ����� ������������ ��� ������ ����� ��� ���������
    int8   *koeff2mul;      ///< ����� ������������ ��� ������ ����� ��� ���������
    int8   *curDigit;       ///< ������� ������ : 0 - ���� ������� �����, 1 - ����������� ������� �����, 2 - ���� ������� �����, 3 - ����������� ������� �����
    pFuncVV funcOfChanged;  ///< ��� ������� ���������� ����� ��������� ��������� �������� ����������.
    void Draw(int x, int y, bool opened);
    void DrawClosed(int x, int y);
    void DrawLowPart(int x, int y, bool pressed, bool shade);
    void WriteText(int x, int y, bool opened);
} Formula;

typedef struct
{
    COMMON_PART_MENU_ITEM
    ColorType  *ct;                 ///< ��������� ��� �������� �����.
    pFuncVV     funcOnChanged;      ///< ��� ������� ����� �������� ����� ��������� �������� ��������.
    void ChangeValue(int delta);    ///< �������� ������� ����� � governor.
    void Draw(int x, int y, bool opened);
private:
    void DrawOpened(int x, int y);
    void DrawClosed(int x, int y);
    void DrawValue(int x, int y, int delta);
} GovernorColor;

typedef struct
{
    COMMON_PART_MENU_ITEM
    const char * const  names[MAX_NUM_SUBITEMS_IN_CHOICE][2];   ///< �������� ������ �� ������� � ���������� ������.
    int8 *               cell;                                  ///< ����� ������, � ������� �������� ������� �������� ������.
    pFuncVB			    funcOnChanged;                          ///< ������� ������ ���������� ����� ��������� �������� ��������.
    pFuncVII            funcForDraw;                            ///< ������� ���������� ����� ��������� ��������. 
    void StartChange(int delta);
    float Step();                                               ///< ������������ ��������� ���� ��������.
    void ChangeIndex(int delta);                                ///< �������� �������� choice � ����������� �� �������� � ����� delta.
    int NumSubItems();                                          ///< ���������� ���������� ��������� ������ � �������� �� ������ choice
    void Draw(int x, int y, bool opened);
    void DrawOpened(int x, int y);
    void DrawClosed(int x, int y);
    /// ���������� ��� �������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    const char *NameCurrentSubItem();
    /// ���������� ��� ���������� �������� ������ �������� choice, ��� ��� �������� � �������� ���� ���������
    const char *NameNextSubItem();
    const char *NamePrevSubItem();
    /// ���������� ��� �������� ������ �������� choice � ������� i ��� ��� �������� � �������� ���� ���������
    const char *NameSubItem(int i);
} Choice;


#define iEXIT   0
#define iDAY    1
#define iMONTH  2
#define iYEAR   3
#define iHOURS  4
#define iMIN    5
#define iSEC    6
#define iSET    7

/// ������������� � ���������� �����.
class Time
{
public:
    COMMON_PART_MENU_ITEM
    int8 *curField;   ///< ������� ���� ���������. 0 - �����, 1 - ���, 2 - ���, 3 - ����, 4 - ����, 5 - �����, 6 - ���, 7 - ����������.
    int8 *hours;
    int8 *minutes;
    int8 *seconds;
    int8 *month;
    int8 *day;
    int8 *year;
    void SetOpened();
    void IncCurrentPosition();
    void SetNewTime();
    void SelectNextPosition();
    void DecCurrentPosition();
    void Draw(int x, int y, bool opened);
    void DrawClosed(int x, int y);
    void DrawOpened(int x, int y);
};

#define DEF_TIME(name, titleRU, titleEN, hintRU, hintEN, keeper, funcActive, cur, h, mi, s, mo, d, y)   \
static const Time name = { Item_Time, &keeper, funcActive, {titleRU, titleEN, hintRU, hintEN}, &cur, &h, &mi, &s, &mo, &d, &y };


/// ��������� ��� �������� ����, ����������� �� ������� �����
typedef struct
{
    int16 i;
} StructFuncReg;

#define CHOICE_RUN_FUNC_CHANGED(c, val)     \
    if(c->funcOnChanged)                    \
    {                                       \
        c->funcOnChanged(val);              \
    }

/** @}  @}
 */
