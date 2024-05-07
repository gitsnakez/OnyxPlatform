#include "Texture.h"
#include <DirectXTex.h>
#include "ErrorDispatcher.h"
#include "GraphicsEngine.h"

Texture::Texture(const wchar_t* full_filename, RenderSystem* rsystem): Resource(full_filename, rsystem)
{
	DirectX::ScratchImage image_data;
	HRESULT res = DirectX::LoadFromWICFile(full_filename, DirectX::WIC_FLAGS_IGNORE_SRGB, nullptr, image_data);

	if (SUCCEEDED(res))
	{
		res = DirectX::CreateTexture(GraphicsEngine::Get()->GetRenderSystem()->m_d3d_device, image_data.GetImages(), image_data.GetImageCount(), image_data.GetMetadata(), &m_texture);

		D3D11_SHADER_RESOURCE_VIEW_DESC desc = {};
		desc.Format = image_data.GetMetadata().format;
		desc.ViewDimension = D3D_SRV_DIMENSION_TEXTURE2D;
		desc.Texture2D.MipLevels = image_data.GetMetadata().mipLevels;
		desc.Texture2D.MostDetailedMip = 0;

		D3D11_SAMPLER_DESC samplerdesc = {};
		samplerdesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerdesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerdesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerdesc.Filter = D3D11_FILTER_ANISOTROPIC;
		samplerdesc.MinLOD = 0;
		samplerdesc.MaxLOD = (UINT)image_data.GetMetadata().mipLevels;

		res = GraphicsEngine::Get()->GetRenderSystem()->m_d3d_device->CreateSamplerState(&samplerdesc, &m_sampler_state);

		res = GraphicsEngine::Get()->GetRenderSystem()->m_d3d_device->CreateShaderResourceView(m_texture, &desc, &m_shader_res_view);
	}
	else { ShowErrorMessage("Texture initialization failure!"); }
}

Texture::~Texture()
{
	m_shader_res_view->Release();
	m_texture->Release();
}