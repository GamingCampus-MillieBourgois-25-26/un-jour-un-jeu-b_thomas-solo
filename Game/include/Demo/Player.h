#pragma once

#include "GameObject.h"
#include "Scene.h"
#include "SquareCollider.h"

#include "Core/Component.h"
#include "Modules/InputModule.h"

namespace Demo
{
    class Player : public Component
    {
    public:
        void Update(const float _delta_time) override
        {
            Maths::Vector2<float> position = GetOwner()->GetPosition();

            if (InputModule::GetKey(sf::Keyboard::Key::D))
            {
                position.x += speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::Q))
            {
                position.x -= speed * _delta_time;
            }

            if (InputModule::GetKey(sf::Keyboard::Key::Z))
            {
                position.y -= speed * _delta_time;
            }
            if (InputModule::GetKey(sf::Keyboard::Key::S))
            {
                position.y += speed * _delta_time;
            }

            GetOwner()->SetPosition(position);

            if (InputModule::GetKeyDown(sf::Keyboard::Key::Escape))
            {
                Engine::GetInstance()->RequestQuit();
            }

            const SquareCollider* square_collider = GetOwner()->GetComponent<SquareCollider>();
            const Scene* scene = GetOwner()->GetScene();
            GameObject* object = scene->FindGameObject("SFML Logo");
            const SquareCollider* other_square_collider = object->GetComponent<SquareCollider>();
        }

        float speed = 100.0f;
    };
}
