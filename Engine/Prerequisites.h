#pragma once
#include <memory>

#define MakePtr(ptr) std::make_shared<ptr>

class SwapChain;
class DeviceContext;
class VertexShader;
class PixelShader;
class VertexBuffer;
class ConstantBuffer;
class IndexBuffer;
class RenderSystem;
class ResourceManager;
class Resource;
class Font2D;
class Font;
class Texture;
class Mesh;
class Model;
class Shader;
class Material;
class GraphicsEngine;
class Level;
class Viewport;

typedef std::shared_ptr<SwapChain> SwapChainPtr;
typedef std::shared_ptr<DeviceContext> DeviceContextPtr;
typedef std::shared_ptr<VertexBuffer> VertexBufferPtr;
typedef std::shared_ptr<IndexBuffer> IndexBufferPtr;
typedef std::shared_ptr<ConstantBuffer> ConstantBufferPtr;
typedef std::shared_ptr<VertexShader> VertexShaderPtr;
typedef std::shared_ptr<PixelShader> PixelShaderPtr;
typedef std::shared_ptr<Resource> ResourcePtr;
typedef std::shared_ptr<Font2D> Font2DPtr;
typedef std::shared_ptr<Font> FontPtr;
typedef std::shared_ptr<Texture> TexturePtr;
typedef std::shared_ptr<Mesh> MeshPtr;
typedef std::shared_ptr<Model> ModelPtr;
typedef std::shared_ptr<Shader> ShaderPtr;
typedef std::shared_ptr<Level> LevelPtr;
typedef std::shared_ptr<Material> MaterialPtr;
typedef std::shared_ptr<GraphicsEngine> GraphicsEnginePtr;
typedef std::shared_ptr<Viewport> ViewportPtr;