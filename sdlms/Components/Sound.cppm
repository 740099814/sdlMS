module;

#include "wz/Property.hpp"

export module components:sound;

export struct SoundWarp
{
    std::vector<uint8_t> pcm_data;
    SoundWarp(wz::Node *node);
    SoundWarp() = default;
    static SoundWarp *load(wz::Node *node);
};

export struct Sound
{
    SoundWarp *souw = nullptr;
    Sound(wz::Node *node);
    Sound(const std::u16string &path);
    Sound() = default;

    unsigned int offset = 0; // 记录当前播放的位置
    unsigned int delay = 0;  // 记录当前播放是否延迟,数值表示延迟时间
    bool circulate = false;  // 当前是否循环
    bool bgm = false;        // 当前是否bgm

    static bool init();
    static void push(SoundWarp *souw, int delay = 0, int pos = -1);
    static void push(Sound sou, int pos = -1);
    static void remove(int pos);
    static Sound *at(int pos);
};
