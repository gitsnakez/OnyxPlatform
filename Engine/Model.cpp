#include "Model.h"

std::wstring AsModel(std::wstring filename)
{
	auto wstrBuilder = std::wstringstream();
	wstrBuilder << MODELPATH << filename;
	return wstrBuilder.str();
}

std::wstring AsMaterial(std::wstring filename)
{
	auto wstrBuilder = std::wstringstream();
	wstrBuilder << MATERIALPATH << filename;
	return wstrBuilder.str();
}

std::wstring AsShader(std::wstring filename)
{
	auto wstrBuilder = std::wstringstream();
	wstrBuilder << SHADERPATH << filename;
	return wstrBuilder.str();
}

// You don't have any chance to understand that constructor
// I completely broke my brain while doing this
Model::Model(OnyxFileNode& node, ResourceManager* rManager)
{
	std::wstring model_filename = AsModel(node.GetValueByName(L"model"));
	auto model = ReadFile(model_filename.c_str());

	if (rManager->_meshRes.count(model_filename)) this->_pMesh = rManager->_meshRes[model_filename];
	else
	{
		rManager->_meshRes[model_filename] = MakePtr(Mesh)(AsModel(model.GetValueByName(L"mesh")).c_str(), rManager->_gEngine->GetRenderSystem());
		this->_pMesh = rManager->_meshRes[model_filename];
	}

	this->Name = node.Name;
	this->transform = new Transform();
	this->transform->position = Vector3D::Parse(node.GetNodeByName(L"transform").GetValueByName(L"position").c_str());
	this->transform->rotation = Vector3D::Parse(node.GetNodeByName(L"transform").GetValueByName(L"rotation").c_str());
	this->transform->scale = Vector3D::Parse(node.GetNodeByName(L"transform").GetValueByName(L"scale").c_str());

	std::wstring cullmode_raw = model.GetValueByName(L"cullmode");

	CULL_MODE cullmode = CULL_BACK;
	if (cullmode_raw == L"back") cullmode = CULL_BACK;
	else if (cullmode_raw == L"front") cullmode = CULL_FRONT;

	std::wstring shader_filename;
	std::wstring material_filename;

	auto materialsNode = model.GetNodeByName(L"materials");
	for (size_t i = 0; i < materialsNode.Tree.size(); i++)
	{
		auto material = ReadFile(AsMaterial(materialsNode.Tree[i].Value).c_str());
		shader_filename = AsShader(material.GetValueByName(L"shader"));
		ShaderPtr sdr;

		if (rManager->_shaderRes.count(shader_filename)) sdr = rManager->_shaderRes[shader_filename];
		else
		{
			auto shader = ReadFile(shader_filename.c_str()); 

			rManager->_shaderRes[shader_filename] = MakePtr(Shader)(
				rManager->_gEngine,
				AsShader(shader.GetValueByName(L"vertex_shader")).c_str(),
				AsShader(shader.GetValueByName(L"pixel_shader")).c_str());

			sdr = rManager->_shaderRes[shader_filename];
		}

		MaterialPtr mat = MakePtr(Material)(rManager->_shaderRes[shader_filename]);
		mat->SetCullMode(cullmode);
		auto texturesGroup = material.GetNodeByName(L"textures");

		for (size_t j = 0; j < texturesGroup.Tree.size(); j++)
		{
			if (texturesGroup.Tree[j].Name == L"basecolor" ||
				texturesGroup.Tree[j].Name == L"normal")
			{
				auto tex_filename = AsMaterial(texturesGroup.Tree[j].Value);
				if (rManager->_textureRes.count(tex_filename))
					mat->AddTexture(rManager->_textureRes[tex_filename]);
				else
				{
					rManager->_textureRes[tex_filename] = MakePtr(Texture)(AsMaterial(texturesGroup.Tree[j].Value).c_str(), rManager->_gEngine->GetRenderSystem());
					mat->AddTexture(rManager->_textureRes[tex_filename]);
				}
			}
		}

		rManager->_materialRes[AsMaterial(materialsNode.Tree[i].Value)] = mat;
		_pMaterials.push_back(mat);
	}
	
}

Model::~Model()
{
	_pMaterials.clear();
	delete transform, _pMesh, Name;
}

MeshPtr Model::GetMesh()
{
	return _pMesh;
}

std::vector<MaterialPtr> Model::GetMaterialSet()
{
	return _pMaterials;
}

const wchar_t* Model::GetName()
{
	return Name.c_str();
}
