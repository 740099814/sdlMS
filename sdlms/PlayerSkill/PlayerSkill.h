#pragma once

#include <string>
#include <functional>
#include "entt/entt.hpp"
#include "Components/Components.h"

int skill_1001004(entt::entity ent);
int skill_1001005(entt::entity ent);
int skill_2201002(entt::entity ent);
int skill_2121005(entt::entity ent);
int skill_2221005(entt::entity ent);
int skill_2221006(entt::entity ent);
int skill_2301002(entt::entity ent);
int skill_3121006(entt::entity ent);
int skill_4211006(entt::entity ent);
int skill_1311006(entt::entity ent);
int skill_4001344(entt::entity ent);
int skill_4111002(entt::entity ent);
int skill_4211002(entt::entity ent);
int skill_4201004(entt::entity ent);
int skill_3101005(entt::entity ent);
int skill_1121008(entt::entity ent);
int skill_4201005(entt::entity ent);
int skill_4121007(entt::entity ent);
int skill_1121006(entt::entity ent);
int skill_2101005(entt::entity ent);
int skill_2201004(entt::entity ent);
int skill_2211002(entt::entity ent);
int skill_4101004(entt::entity ent);
int skill_1111002(entt::entity ent);
int skill_2001002(entt::entity ent);
int skill_21100005(entt::entity ent);
int skill_14101006(entt::entity ent);
int skill_1101004(entt::entity ent);
int skill_1111008(entt::entity ent);
int skill_4001003(entt::entity ent);
int skill_1101007(entt::entity ent);

struct PlayerSkill
{
    static void skill_sound(SkillWarp *souw, int delay = 0);

    static void skill_effect(Skill *ski, entt::entity ent);

    static void skill_action(Skill *ski, entt::entity ent);

    static void skill_attack(Skill *ski);

    static const inline std::unordered_map<std::u16string, std::function<int(entt::entity)>> Skills = {
        {u"1001004", skill_1001004},
        {u"1001005", skill_1001005},
        {u"2201002", skill_2201002},
        {u"2121005", skill_2121005},
        {u"2221005", skill_2221005},
        {u"2221006", skill_2221006},
        {u"2301002", skill_2301002},
        {u"3121006", skill_3121006},
        {u"4211006", skill_4211006},
        {u"1311006", skill_1311006},
        {u"4001344", skill_4001344},
        {u"4111002", skill_4111002},
        {u"4211002", skill_4211002},
        {u"4201004", skill_4201004},
        {u"3101005", skill_3101005},
        {u"1121008", skill_1121008},
        {u"4201005", skill_4201005},
        {u"4121007", skill_4121007},
        {u"1121006", skill_1121006},
        {u"2101005", skill_2101005},
        {u"2201004", skill_2201004},
        {u"2211002", skill_2211002},
        {u"4101004", skill_4101004},
        {u"1111002", skill_1111002},
        {u"2001002", skill_2001002},
        {u"21100005", skill_21100005},
        {u"14101006", skill_14101006},
        {u"1101004", skill_1101004},
        {u"1111008", skill_1111008},
        {u"4001003", skill_4001003},
        {u"1101007", skill_1101007},
    };

    enum SkillResult
    {
        None = -1,
        EFF = 1,
        SOU = 2,
        ATK = 4,
        ACT = 8,
        ALERT = 16
    };
};
