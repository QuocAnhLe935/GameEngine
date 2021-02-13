#include "Debug.h"


Debug::MessageType Debug::currentSev = MessageType::TYPE_NONE;
//outputname empty string
std::string Debug::outputName = "";
//take it whatever name first take
void Debug::Oncreate(const std::string& name_)
{
	outputName = name_ + ".txt";
	//write to debug file
	std::ofstream out;
	//open the file with specific name with ability to write
	out.open(outputName.c_str(), std::ios::out);
	out.close();
	currentSev = MessageType::TYPE_INFO;
}

void Debug::SetSeverity(MessageType type_)
{
	currentSev = type_;
}

void Debug::Info(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_INFO, "[INFO]: " + message_, fileName_, line_);
}

void Debug::Trace(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_TRACE, "[TRACE]: " + message_, fileName_, line_);
}

void Debug::Warning(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_WARNING, "[WARNING]: " + message_, fileName_, line_);
}

void Debug::Error(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_ERROR, "[ERROR]: " + message_, fileName_, line_);
}

void Debug::FatalError(const std::string& message_, const std::string& fileName_, const int line_)
{
	Log(MessageType::TYPE_FATAL_ERROR, "[FATALERROR]: " + message_, fileName_, line_);
}

void Debug::Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_)
{
	//check a specific type of message that we want to log
	//if it less than or == to sev
	//second if check if on create is called 
	if (type_ <= currentSev && currentSev > MessageType::TYPE_NONE) {
		std::ofstream out;
		//				don't overwrite just add to the end(app)	to write
		out.open(outputName.c_str(), std::ios::app | std::ios::out);
		//write to file
		out << message_ << "in:" << fileName_ << "on line: " << line_ << std::endl;
		//flush screen buffer
		out.flush();
		out.close();
		//print out console
		//std::cout << message_ << "in:" << fileName_ << "on line: " << line_ << std::endl;
	}
}
