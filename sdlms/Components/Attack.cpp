#include "Attack.h"

AttackWarp::AttackWarp(SDL_FPoint &lt, SDL_FPoint &rb, AnimatedSpriteWarp *hit,
                       int mobCount, int attackCount, SoundWarp *souw) : hit(hit),
                                                                         mobCount(mobCount),
                                                                         attackCount(attackCount),
                                                                         souw(souw)
{
    rect.x = lt.x;
    rect.y = lt.y;
    rect.w = rb.x - lt.x;
    rect.h = rb.y - lt.y;
}