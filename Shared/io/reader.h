#pragma once
#include <string>
#include "dataInstance.h"

namespace AoC22 { namespace IO {

	class InputDataReader
	{
	protected:
		std::wstring m_path;

	public:
		InputDataReader(std::wstring dataRootPath);

		DataInstance GetData(unsigned int _day, DataInstance::Type _type);
	};



}}
