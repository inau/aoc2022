#pragma once
#include <string>
#include <fstream>

namespace AoC22 { namespace IO {

	class DataInstance
	{
	public:
		enum class Type 
		{
			EXAMPLE,
			INPUT
		};

	protected:
		std::wstring m_path;
		unsigned int m_day;
		Type m_type;
		unsigned int m_aux;

		std::ifstream m_file;
		

		DataInstance(std::wstring dataRootPath, unsigned int day, Type type, unsigned aux);

	public:
		DataInstance::Type getType();
		unsigned int getDay();
		std::ifstream& getStream();

		static DataInstance CreateDataInstance(std::wstring dataRootPath, unsigned int day, Type type, unsigned aux);
		static std::wstring type_to_textual(const Type& type);
	};



}}
