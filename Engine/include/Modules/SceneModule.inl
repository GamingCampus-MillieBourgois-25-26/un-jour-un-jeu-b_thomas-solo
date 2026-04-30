#pragma once

template <typename T>
Scene* SceneModule::SetScene()
{
    DeleteAllScenes();
    nextFrameScene = CreateSceneAdditive<T>();
    return nextFrameScene;
}

template <typename SceneType> requires IsScene<SceneType>
SceneType* SceneModule::CreateSceneAdditive()
{
    auto scene = std::make_unique<SceneType>();
    SceneType* raw_ptr = scene.get();

    scene->Awake();

    scene->FlushPending();

    scenes.push_back(std::move(scene));
    return raw_ptr;
}

template <typename SceneType> requires IsScene<SceneType>
Scene* SceneModule::GetSceneByType() const
{
    for (const auto& scene : scenes)
    {
        if (dynamic_cast<SceneType*>(scene.get()))
        {
            return scene.get();
        }
    }

    Logger::Log(ELogLevel::Warning, "SceneModule::GetSceneByType - No scene of type " + std::string(typeid(SceneType).name()) + " found.");

    return nullptr;
}

template<typename SceneType> requires IsScene<SceneType>
void SceneModule::RegisterSceneCreationFunction()
{
    const std::type_index scene_type = typeid(SceneType);
    std::function<Scene*()> scene_creation_function = [this]() { return SetScene<SceneType>(); };
    sceneCreationFunctions.try_emplace(scene_type, scene_creation_function);
}
