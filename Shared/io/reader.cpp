#include "reader.h"

namespace AoC22 { namespace IO {


InputDataReader::InputDataReader(std::wstring dataRootPath)
	: m_path(dataRootPath)
{
}

DataInstance InputDataReader::GetData(unsigned int _day, DataInstance::Type _type, unsigned auxIdx)
{
	return DataInstance::CreateDataInstance(m_path, _day,_type, auxIdx);
}

}}