#include "ShaderHandler.h"
//redeclare static varible
std::unique_ptr<ShaderHandler> ShaderHandler::shaderInstance = nullptr;


//
std::unordered_map<std::string, GLuint> ShaderHandler::programs =
std::unordered_map < std::string, GLuint>();



ShaderHandler* ShaderHandler::GetInstance()
{
	if (shaderInstance.get() == nullptr) {
		shaderInstance.reset(new ShaderHandler);
	}
	return shaderInstance.get();
}

void ShaderHandler::CreateProgram(const std::string& shaderName_, 
	const std::string& vertexShaderFileName_, const std::string& fragmentShaderFileName_)
{
	//read the files
	std::string vertexShaderCode = ReadShader(vertexShaderFileName_);
	std::string fragmentShaderCode = ReadShader(fragmentShaderFileName_);

	if (vertexShaderCode == "" || fragmentShaderCode == "") {
		return;
	}

	GLuint vertexShader = CreateShader(GL_VERTEX_SHADER, vertexShaderCode, shaderName_);
	GLuint fragmentShader = CreateShader(GL_FRAGMENT_SHADER, fragmentShaderCode, shaderName_);

	if (vertexShader == 0 || fragmentShader == 0) {
		return;
	}

	GLint linkResult = 0;
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &linkResult);

	if (!linkResult) {
		GLint infoLogLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
		std::vector<char>programLog(infoLogLength);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programLog[0]);
		std::string programString(programLog.begin(), programLog.end());
		Debug::Error("FAILED TO LINK SHADER" + shaderName_ + ". ERROR:" + programString, "ShaderHandler.cpp", __LINE__);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(program);

		return;
	}
	//create new entry where the key is shaderName_, and the value is program
	programs[shaderName_] = program;
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}

GLuint ShaderHandler::GetShader(const std::string& shaderName_)
{
	//pass in name of shader, it will look through of unorder map
	//if it exist, it will return the value that associate of shader name
	//if not return 0

	//.find go to each element of the map
	//.end once it has reached the key match parameter (very end of the map)
	if (programs.find(shaderName_) != programs.end()){
		return programs[shaderName_];
	}

	return 0;
}

void ShaderHandler::OnDestroy()
{
	//make sure go through the map and delete them
	if (programs.size() > 0) {
		for (auto p : programs) {
			//.first is key, .second is value
			glDeleteProgram(p.second);
		}
		programs.clear();
	}
}

ShaderHandler::ShaderHandler() {

}

ShaderHandler::~ShaderHandler()
{
	OnDestroy();
}

std::string ShaderHandler::ReadShader(const std::string& filePath_)
{
	//create a string to represent content of file
	std::string shaderCode = "";
	//object going to use to read the file
	std::ifstream file;
	//return a flag check if sth wrong with this file (badbit)
	file.exceptions(std::ifstream::badbit);

	try {

		//try open the file based on filepath
		file.open(filePath_);
		//create a string a stream class that work on string
		std::stringstream tmpStream;
		//taking whatever in the file and pass in string stream 
		tmpStream << file.rdbuf();
	
		file.close();
		shaderCode = tmpStream.str();
	}
	//if anything happen catch this type of this section()
	catch (std::ifstream::failure error_) {
		Debug::Error("COULD NOT READ THE SHADER: " + filePath_, "ShaderHandler.cpp", __LINE__);
		//return empty string
		return"";
	}
	return shaderCode;
}

GLuint ShaderHandler::CreateShader(GLenum shaderType_, const std::string& source_, const std::string& shaderName_)
{

	GLint compileResult = 0;
	//try to create shader based on this type
	GLuint shader = glCreateShader(shaderType_);

	//convert string .into char* obj
	const char* shaderCodePtr = source_.c_str();
	//get acutal size of shader(size of the string)
	const int shaderCodeSize = source_.size();

	//once shader is created pass in source of the shader
	glShaderSource(shader, 1, &shaderCodePtr, &shaderCodeSize);
	//Compile the shader
	glCompileShader(shader);

	//Error checking compile shader line
	//glgetshaderiv will get compile status of shader will set compile result set the value to the status of shader compile
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileResult);

	//if not compileresult
	if (!compileResult) {
		//get the length of info that shader will give
		GLint infoLogLength = 0;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
		//create vector with size of the log length
		std::vector<char> shaderLog(infoLogLength);
		//the place we want OPengl put in this log is address of 
		glGetShaderInfoLog(shader, infoLogLength, NULL, &shaderLog[0]);
		//convert vector of <character> into string
		std::string shaderString(shaderLog.begin(), shaderLog.end());
		Debug::Error("ERROR COMPILING SHADER" + shaderName_ + ".Error: \n" +
			shaderString, "ShaderHandler.cpp", __LINE__);
		return 0;
	}
	return shader;
}
