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
    DataInstance::DataInstance(std::wstring dataRootPath, unsigned int day, Type type, unsigned aux)
        : m_path(dataRootPath)
        , m_day(day)
        , m_type(type)
        , m_aux(aux)
    {
        std::wstring number = (m_day < 10 ? L"0" : L"") + std::to_wstring(m_day);
        std::wstring auxNb = (m_aux != 0 ? std::to_wstring(aux) : L"");
        std::wstring m_uri = m_path + L"day" + number + L"/" + type_to_textual(m_type) + auxNb + L".txt";
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

    DataInstance DataInstance::CreateDataInstance(std::wstring dataRootPath, unsigned int day, Type type, unsigned aux = 0u)
    {
        return DataInstance(dataRootPath, day, type, aux);
    }

}}