#include "MenuItems.h"
#include "MenuFunctions.h"
#include "Settings/Settings.h"


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char *Choice::NameCurrentSubItem()
{
    return ((int8 *)cell == 0) ? "" : names[*((int8 *)cell)][LANG];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Choice::NameNextSubItem()
{
    if (cell == 0)
    {
        return "";
    }

    int index = *((int8 *)cell) + 1;

    if (index == NumSubItems())
    {
        index = 0;
    }
    return names[index][LANG];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Choice::NamePrevSubItem()
{
    if (cell == 0)
    {
        return "";
    }

    int index = *((int8 *)cell) - 1;

    if (index < 0)
    {
        index = NumSubItems() - 1;
    }
    return names[index][LANG];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void *Page::Item(int numElement) const
{
    return items[numElement + (IsPageSB(this) ? 1 : 0)];
}
//----------------------------------------------------------------------------------------------------------------------------------------------------
SButton* Page::SmallButonFromPage(int numButton)
{
    return (SButton *)items[numButton];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Button::CallFuncOnDraw(int x, int y)
{
    if (funcForDraw)
    {
        funcForDraw(x, y);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
int Page::PosItemOnTop()
{
    return NumCurrentSubPage() * MENU_ITEMS_ON_DISPLAY;
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
const char *Choice::NameSubItem(int i)
{
    return names[i][LANG];
}

//----------------------------------------------------------------------------------------------------------------------------------------------------
void Page::ShortPressOnItem(int numItem)
{
    if (TypeMenuItem(this) == Item_Page)
    {
        CallFuncOnPressButton(items[numItem]);
    }
}
