#ifndef DEBUG_H
#define DEBUG_H

#include <string>
#include <iostream>
#include <fstream>
class Debug
{
public:
	//enum= creating a varible but each value of varible has a meaningful name
	enum class MessageType : unsigned short {

		TYPE_NONE = 0,
		TYPE_FATAL_ERROR,
		TYPE_ERROR,
		TYPE_WARNING,
		TYPE_TRACE,
		TYPE_INFO

	};

	Debug() = delete;
	Debug(const Debug&) = delete;
	Debug(Debug&&) = delete;
	Debug& operator=(const Debug&) = delete;
	Debug& operator=(Debug&&) = delete;

	static void Oncreate(const std::string& name_ = "Game258Log");
		static void SetSeverity(MessageType type_);
	static void Info(const std::string& message_, const std::string& fileName_, const int line_);
	static void Trace(const std::string& message_, const std::string& fileName_, const int line_);
	static void Warning(const std::string& message_, const std::string& fileName_, const int line_);
	static void Error(const std::string& message_, const std::string& fileName_, const int line_);
	static void FatalError (const std::string& message_, const std::string& fileName_, const int line_);
	

	

private:
	static void Log(const MessageType type_, const std::string& message_, const std::string& fileName_, const int line_);
	static MessageType currentSev;
	static std::string outputName;

};
#endif

