#include "Pet.h"

#include "Core/Core.h"
#include "Components/Components.h"
#include "Commons/Commons.h"
#include "Resources/Wz.h"

entt::entity load_pet(const u16string id, entt::entity owner)
{
    auto ent = World::registry->create();

    auto node = Wz::Item->get_root()->find_from_path(u"Pet/" + id + u".img");

    auto pet = &World::registry->emplace<Pet>(ent);
    pet->a[u"move"] = AnimatedSprite(node->get_child(u"move"));
    pet->a[u"jump"] = AnimatedSprite(node->get_child(u"jump"));
    pet->a[u"stand0"] = AnimatedSprite(node->get_child(u"stand0"));
    pet->a[u"hang"] = AnimatedSprite(node->get_child(u"hang"));

    for (auto &[key, val] : pet->a)
    {
        for (auto &sprs : val.asprw->sprites)
        {
            SDL_SetTextureScaleMode(sprs->texture, SDL_SCALEMODE_NEAREST);
        }
    }

    pet->index = u"jump";
    pet->id = id;
    pet->owner = owner;

    World::registry->emplace<Effect>(ent);
    auto mv = &World::registry->emplace<Move>(ent);
    mv->hspeed_max = 200;
    mv->hspeed_min = -200;
    World::registry->emplace<Animated>(ent);
    auto count = World::registry->view<Pet>().size();
    auto owner_tr = World::registry->try_get<Transform>(owner);
    World::registry->emplace<Transform>(ent, owner_tr->position, PET_Z - count);
    World::zindex = true;

    return ent;
}
