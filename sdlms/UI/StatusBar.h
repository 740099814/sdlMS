#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "Components/Components.h"
#include <SDL3/SDL.h>

struct StatusBar
{
    static void run();
    static void over();
    static void init();
    static inline SDL_Texture *backgrnd;
    static inline SDL_Texture *backgrnd2;
    static inline SDL_Texture *quickSlot;
    static inline SDL_Texture *chatTarget;
    static inline SDL_Texture *iconRed;
    static inline SDL_Texture *iconBlue;
    static inline SDL_Texture *iconMemo;
    static inline SDL_Texture *chat;
    static inline SDL_Texture *box;

    static inline SDL_Texture *graduation;
    static inline SDL_Texture *bar;
    static inline SDL_Texture *gray;

    static inline SDL_Texture *LevelNo[10];
    static inline SDL_Texture *number[10];

    static inline SDL_Texture *job;
    static inline SDL_Texture *name;

    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> BtShop;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> BtChat;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> BtNPT;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> BtMenu;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> BtShort;

    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> BtClaim;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> EquipKey;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> InvenKey;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> StatKey;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> SkillKey;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> KeySet;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> QuickSlot;
    static inline std::pair<std::u16string, std::unordered_map<std::u16string, AnimatedSprite>> QuickSlotD;
};
