#pragma once

#include <functional>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "Core/Module.h"
#include "Core/Scene.h"

class TimeModule;
class WindowModule;

class SceneModule final : public Module
{
public:
    void Start() override;
    void Render() override;
    void Update() override;
    void Awake() override;
    void Destroy() override;
    void Finalize() override;
    void OnDebug() override;
    void OnDebugSelected() override;
    void OnDisable() override;
    void OnEnable() override;
    void OnGUI() override;
    void PostRender() override;
    void PreRender() override;
    void Present() override;

    template <typename T>
    Scene* SetScene();

    Scene* SetSceneById(const std::type_index& _type_index);

    template <typename SceneType> requires IsScene<SceneType>
    SceneType* CreateSceneAdditive();

    template <typename SceneType> requires IsScene<SceneType>
    Scene* GetSceneByType() const;
    Scene* GetSceneByName(const std::string& _scene_name) const;

    const std::vector<std::unique_ptr<Scene>>& GetScenesList() const;

    bool DeleteSceneByName(const std::string& _scene_name) const;
    void DeleteAllScenes() const;

    template <typename SceneType> requires IsScene<SceneType>
    void RegisterSceneCreationFunction();

    std::vector<std::type_index> GetRegisteredSceneTypes() const;

private:
    void DeleteMarkedScenes();

    std::vector<std::unique_ptr<Scene>> scenes;

    std::unordered_map<std::type_index, std::function<Scene*()>> sceneCreationFunctions;

    WindowModule* windowModule = nullptr;
    TimeModule* timeModule = nullptr;

    Scene* nextFrameScene = nullptr;
};

#include "SceneModule.inl"
