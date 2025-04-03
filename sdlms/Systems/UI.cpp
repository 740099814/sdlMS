#include "UI.h"

std::list<UIIndex> ui_index = {UIIndex::UI_UIBuff, UIIndex::UI_StatusBar};

void ui_run()
{
    auto type = Cursor::type;
    Cursor::type = u"0";
    WorldMap::run();
    UIBuff::run();
    StatusBar::run();
    KeyConfig::run();
    UIItem::run();
    UISkill::run();
    UIStat::run();
    // 检测左键是否被按住
    if (Window::mouse_state & SDL_BUTTON_LMASK)
    {
        Cursor::left_mouse_press = true;
        Cursor::type = u"12";
        ui_sort();
        Cursor::drag = ui_drag();
    }
    else
    {
        if (Cursor::left_mouse_press)
        {
            // 播放点击的声音
            Sound::push(Sound(u"UI.img/BtMouseClick"));
            // 触发点击事件
            ui_click();
        }
        Cursor::left_mouse_press = false;
        Cursor::drag = false;
        WorldMap::over();
    }
    Cursor::action(type);
    Cursor::run();
}

bool ui_drag()
{
    static float x = 0;
    static float y = 0;
    auto index = ui_index.back();
    if (index == UIIndex::UI_UIBuff || index == UIIndex::UI_StatusBar)
    {
        return false;
    }
    switch (index)
    {
    case UIIndex::UI_KeyConfig:
    {
        if (Cursor::drag)
        {
            KeyConfig::x = Window::mouse_x - x;
            KeyConfig::y = Window::mouse_y - y;
            return true;
        }
        else if (KeyConfig::mousein())
        {
            x = Window::mouse_x - KeyConfig::x;
            y = Window::mouse_y - KeyConfig::y;
            return true;
        }
    }
    break;
    case UIIndex::UI_UIItem:
    {
        if (Cursor::drag)
        {
            UIItem::x = Window::mouse_x - x;
            UIItem::y = Window::mouse_y - y;
            return true;
        }
        else if (UIItem::mousein())
        {
            x = Window::mouse_x - UIItem::x;
            y = Window::mouse_y - UIItem::y;
            return true;
        }
    }
    break;
    case UIIndex::UI_UISkill:
    {
        if (Cursor::drag)
        {
            UISkill::x = Window::mouse_x - x;
            UISkill::y = Window::mouse_y - y;
            return true;
        }
        else if (UISkill::mousein())
        {
            x = Window::mouse_x - UISkill::x;
            y = Window::mouse_y - UISkill::y;
            return true;
        }
    }
    break;
    case UIIndex::UI_UIStat:
    {
        if (Cursor::drag)
        {
            UIStat::x = Window::mouse_x - x;
            UIStat::y = Window::mouse_y - y;
            return true;
        }
        else if (UIStat::mousein())
        {
            x = Window::mouse_x - UIStat::x;
            y = Window::mouse_y - UIStat::y;
            return true;
        }
    }
    break;
    case UIIndex::UI_WorldMap:
        break;
    default:
        break;
    }
    return false;
}

void ui_sort()
{
    for (auto rit = ui_index.rbegin(); rit != ui_index.rend(); ++rit)
    {
        switch (*rit)
        {
        case UIIndex::UI_KeyConfig:
        {
            if (KeyConfig::mousein())
            {
                auto it = --(rit.base());
                ui_index.splice(ui_index.end(), ui_index, it);
                return;
            }
        }
        break;
        case UIIndex::UI_UIItem:
        {
            if (UIItem::mousein())
            {
                auto it = --(rit.base());
                ui_index.splice(ui_index.end(), ui_index, it);
                return;
            }
        }
        break;
        case UIIndex::UI_UISkill:
        {
            if (UISkill::mousein())
            {
                auto it = --(rit.base());
                ui_index.splice(ui_index.end(), ui_index, it);
                return;
            }
        }
        break;
        case UIIndex::UI_UIStat:
        {
            if (UIStat::mousein())
            {
                auto it = --(rit.base());
                ui_index.splice(ui_index.end(), ui_index, it);
                return;
            }
        }
        break;
        case UIIndex::UI_WorldMap:
        {
        }
        break;
        default:
            break;
        }
    }
}

void ui_click()
{
    auto index = ui_index.back();
    switch (index)
    {
    case UIIndex::UI_KeyConfig:
    {
        if (KeyConfig::mousein())
        {
            KeyConfig::click();
            return;
        }
    }
    break;
    case UIIndex::UI_UIItem:
    {
        if (UIItem::mousein())
        {
            UIItem::click();
            return;
        }
    }
    break;
    case UIIndex::UI_UISkill:
    {
        if (UISkill::mousein())
        {
            UISkill::click();
            return;
        }
    }
    break;
    case UIIndex::UI_UIStat:
    {
        if (UIStat::mousein())
        {
            UIStat::click();
            return;
        }
    }
    break;
    case UIIndex::UI_WorldMap:
    {
        WorldMap::click();
    }
    break;
    default:
        break;
    }
    StatusBar::click();
}
