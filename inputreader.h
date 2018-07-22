#ifndef CSVREADINGFILE_H
#define CSVREADINGFILE_H

#include <string>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>

class InputReader
{
private:
    std::vector<std::string>    m_data;
public:
    InputReader();
    std::string const& operator[](std::size_t index) const;
    std::size_t size() const;
    void ReadNextRow(std::istream& str);
    friend std::istream& operator>>(std::istream& str, InputReader& data);
};

std::istream& operator>>(std::istream& str, InputReader& data);

#endif // CSVREADINGFILE_H
