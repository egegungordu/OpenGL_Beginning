#pragma once
#include <memory>
namespace Shaders
{
    void initialize();
    std::shared_ptr<Shader> getChunkShader();
}