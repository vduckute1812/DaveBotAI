#include "inputreader.h"

InputReader::InputReader()
{

}

std::string const& InputReader::operator[](std::size_t index) const
{
    return m_data[index];
}

std::size_t InputReader::size() const
{
    return m_data.size();
}

void InputReader::ReadNextRow(std::istream& str)
{
    std::string         line;
    std::getline(str, line);
    std::stringstream   lineStream(line);
    std::string         cell;
    m_data.clear();

    while(std::getline(lineStream, cell, ','))
    {
        m_data.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty())
    {
    // If there was a trailing comma then add an empty element.
        m_data.push_back("");
    }
}

std::istream& operator>>(std::istream& str, InputReader& data)
{
    data.ReadNextRow(str);
    return str;
}
