#include "dataInstance.h"

namespace AoC22 { namespace IO {
    std::wstring DataInstance::type_to_textual(const Type& type)
    {
        std::wstring str;
        switch (type)
        {
            case Type::EXAMPLE:  str = L"example"; break;
            case Type::INPUT:    str = L"input"; break;
        }
        return str;
    }
    DataInstance::DataInstance(std::wstring dataRootPath, unsigned int day, Type type)
        : m_path(dataRootPath)
        , m_day(day)
        , m_type(type)
    {
        std::wstring m_uri = m_path + L"day" + std::to_wstring(m_day) + L"/" + type_to_textual(m_type) + L".txt";
        m_file.open(m_uri);
    }

    DataInstance::Type AoC22::IO::DataInstance::getType()
    {
        return m_type;
    }

    unsigned int AoC22::IO::DataInstance::getDay()
    {
        return m_day;
    }

    std::ifstream& AoC22::IO::DataInstance::getStream()
    {
        return m_file;
    }

    DataInstance DataInstance::CreateDataInstance(std::wstring dataRootPath, unsigned int day, Type type)
    {
        return DataInstance(dataRootPath, day, type);
    }

}}