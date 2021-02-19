#ifndef SHADERHANDLER_H
#define SHADERHANDLER_H

#include <sstream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <glew.h>
#include "../../Debug/Debug.h"
class ShaderHandler
{
public:
	//disable move copy function
	ShaderHandler(const ShaderHandler&) = delete;
	ShaderHandler(ShaderHandler&&) = delete;
	ShaderHandler& operator=(const ShaderHandler&) = delete;
	ShaderHandler& operator=(ShaderHandler&&) = delete;

	static ShaderHandler* GetInstance();
	
	//create program by passing name of program, vertex and frag shader file
	void CreateProgram(const std::string& shaderName_,
		const std::string& vertexShaderFileName_,
		const std::string& fragmentShaderFileName_);
	//pass in shader name return id of specific shader gluint
	GLuint GetShader(const std::string& shaderName_);
	void OnDestroy();

private:

	ShaderHandler();
	~ShaderHandler();

	static std::unique_ptr<ShaderHandler> shaderInstance;
	friend std::default_delete<ShaderHandler>;
	//Read shader file return a string of that file
	std::string ReadShader(const std::string& filePath_);
	//create a shader object(not entire program) 
	GLuint CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_);
	//keep track of shader programs
	//key(word) pair entry value(def)(string) pair to
	//key is searching through the map
	static std::unordered_map<std::string, GLuint> programs;
};

#endif // !SHADERHANDLER_H