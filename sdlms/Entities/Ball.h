#pragma once

#include "Components/Components.h"

#include "entt/entt.hpp"

void load_ball(AnimatedSpriteWarp *asprw, Transform *tran, entt::entity owner);

void load_ball(unsigned char num=1);
