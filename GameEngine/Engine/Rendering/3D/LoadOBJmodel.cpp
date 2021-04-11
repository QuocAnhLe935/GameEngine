#include "LoadOBJmodel.h"

LoadOBJmodel::LoadOBJmodel()
{
	vertices = std::vector<glm::vec3>();
	normals = std::vector<glm::vec3>();
	textureCoords = std::vector<glm::vec2>();
	indices = std::vector<unsigned int>();
	normalIndices=std::vector<unsigned int>();
	textureIndices=std::vector<unsigned int>();
	meshVertices = std::vector<Vertex>();
	submeshs = std::vector<SubMesh>();
	currentTexture = 0;


	vertices.reserve(200);
	normals.reserve(200);
	textureCoords.reserve(200);
	normalIndices.reserve(200);
	textureIndices.reserve(200);
	meshVertices.reserve(200);
	submeshs.reserve(10);
}

LoadOBJmodel::~LoadOBJmodel()
{

	vertices.clear();
	normals.clear();
	textureCoords.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	submeshs.clear();
}

void LoadOBJmodel::LoadModel(const std::string& objFilePath_, const std::string& mtlFilePath_)
{
	LoadMaterialLibrary(mtlFilePath_);
	LoadModel(objFilePath_);
}

std::vector<SubMesh> LoadOBJmodel::GetSubMeshes()
{
	return submeshs;
}

void LoadOBJmodel::PostProcessing()
{
	for (unsigned int i = 0; i < indices.size(); i++) {
		Vertex vert;
		vert.position = vertices[indices[i]];
		vert.normal = normals[normalIndices[i]];
		vert.textureCoordinates = textureCoords[textureIndices[i]];
		meshVertices.push_back(vert);
	}

	SubMesh mesh;
	mesh.vertexList = meshVertices;
	mesh.meshIndices = indices;
	mesh.textureID = currentTexture;

	submeshs.push_back(mesh);
	indices.clear();
	normalIndices.clear();
	textureIndices.clear();
	meshVertices.clear();
	currentTexture = 0;

}

void LoadOBJmodel::LoadModel(const std::string& filePath_)
{
	std::ifstream in(filePath_.c_str(), std::ios::in);

	if (!in) {

		Debug::Error("Cannot open OBJ file: " + filePath_, "LoadOBJmodel.cpp", __LINE__);
		return;
	}

	std::string line;

	while (std::getline(in, line)) {
		//vertex data
		//position
		if (line.substr(0, 2) == "v ") {
			
			std::stringstream v(line.substr(2));
			float x, y, z;
			v >> x >> y >> z;
			vertices.push_back(glm::vec3(x, y, z));

		}

		//new mesh
		else if (line.substr(0, 7) == "usemtl ") {
			if (indices.size() > 0) {
				PostProcessing();
			}
			LoadMaterial(line.substr(7));
		}



		//texture coords UV
		else if (line.substr(0, 3) == "vt ") {	
			float x, y;
			std::stringstream t(line.substr(3));
			t >> x >> y;
			textureCoords.push_back(glm::vec2(x, y));
		}
		//normal
		else if (line.substr(0, 3) == "vn ") {
			float x, y, z;
			std::stringstream t(line.substr(3));
			t >> x >> y >> z;

			normals.push_back(glm::vec3(x, y, z));
		}
		//face pos/text/normal
		else if (line.substr(0, 2) == "f ") {
			
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			
			std::stringstream t(line.substr(2));

			/*std::stringstream t(line.substr(2));
			std::stringstream t1(line.substr(2));
			std::stringstream t2(line.substr(2));

			std::stringstream t(line.substr(2));
			std::stringstream t1(line.substr(2));
			std::stringstream t2(line.substr(2));*/

			

			//extract from the file 

			t >> vertexIndex[0] >> uvIndex[0] >> normalIndex[0]>> vertexIndex[1] >> uvIndex[1] >> normalIndex[1]>> vertexIndex[2] >> uvIndex[2] >> normalIndex[2];
			
			
			

			indices.push_back(vertexIndex[0]);
			indices.push_back(vertexIndex[1]);
			indices.push_back(vertexIndex[2]);
		
			//push texture indices
			textureIndices.push_back(uvIndex[0]);
			textureIndices.push_back(uvIndex[1]);
			textureIndices.push_back(uvIndex[2]);			

			//push normal indices
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

			for (unsigned int i = 0; i < indices.size(); i++) {
				unsigned int vertexIndex = indices[i];
				vertices.push_back(glm::vec3(vertexIndex-1));
			}

			for (unsigned int i = 0; i < textureIndices.size(); i++) {
				unsigned int uvIndex = textureIndices[i];
				textureCoords.push_back(glm::vec2(uvIndex-1));
			}

			for (unsigned int i = 0; i < normalIndices.size(); i++) {
				unsigned int normalIndex = normalIndices[i];
				normals.push_back(glm::vec3(normalIndex-1));
			}


			

		}
	}
	PostProcessing();

}

void LoadOBJmodel::LoadMaterial(const std::string& matName_)
{
	currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	if (currentTexture == 0) {
		TextureHandler::GetInstance()->CreateTexture(matName_, "Resources/Textures/" + matName_ + ".png");
		currentTexture = TextureHandler::GetInstance()->GetTexture(matName_);
	}
}

void LoadOBJmodel::LoadMaterialLibrary(const std::string& matFilePath_)
{
	std::ifstream in(matFilePath_.c_str(), std::ios::in);
	if (!in) {

		Debug::Error("Cannot open MTL file: " + matFilePath_, "loadOBJmodel.cpp", __LINE__);
	}
		std::string line;
		while (std::getline(in, line)) {
			if(line.substr(0, 7)=="newmtl "){
			LoadMaterial(line.substr(7));
			}
		}
}
