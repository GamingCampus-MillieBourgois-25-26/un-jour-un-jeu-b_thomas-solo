#include "DemoScene.h"

#include <random>

#include "AssetsModule.h"
#include "RectangleShapeRenderer.h"
#include "SpriteRenderer.h"
#include "SquareCollider.h"
#include "TextRenderer.h"
#include "Texture.h"
#include "WindowModule.h"

#include "Demo/Player.h"
#include "Demo/TileCounter.h"
#include "Demo/TileSpawner.h"

Demo::DemoScene::DemoScene(): Scene("DemoScene")
{
    AssetsModule* assets_module = Engine::GetInstance()->GetModuleManager()->GetModule<AssetsModule>();
    Texture* logo_texture = assets_module->LoadAsset<Texture>("Engine/sfml_logo.png");

    GameObject* const& logo = CreateGameObject("SFML Logo");
    SpriteRenderer* const& logo_renderer = logo->CreateComponent<SpriteRenderer>(logo_texture, false);
    logo->CreateComponent<SquareCollider>(logo_renderer);

    GameObject* const& player = CreateGameObject("Player");
    player->CreateComponent<Player>();
    SpriteRenderer* const& player_sprite = logo->CreateComponent<SpriteRenderer>(logo_texture, false);
    player->CreateComponent<SquareCollider>(player_sprite);
    player->SetPosition({150, 150});

    GameObject* tile_spawner = CreateGameObject("TileSpawner");
    tile_spawner->CreateComponent<TileSpawner>();
    tile_spawner->CreateComponent<TileCounter>();
    tile_spawner->SetPosition({200, 0});
}
