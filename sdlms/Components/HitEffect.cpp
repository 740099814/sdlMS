module;

module components;
import :animatedsprite;

HitEffect::HitEffect(AnimatedSpriteWarp *aspr)
{
    effect = new AnimatedSprite(aspr);
}