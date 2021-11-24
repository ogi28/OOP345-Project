// Name: Ogulcan Tayhan
// Seneca Student ID: 104472204
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Utilities.h"

namespace sdds {
char Utilities::m_delimiter;

void Utilities::setFieldWidth(size_t newWidth) { m_widthField = newWidth; }

size_t Utilities::getFieldWidth() const { return m_widthField; }

std::string Utilities::extractToken(const std::string &str, size_t &next_pos,
                                    bool &more) {

  using std::string;
  string token;
  if (str[next_pos] == m_delimiter) {
    more = false;
    throw "Delimiter found";
  }
  size_t index =
      str.find(m_delimiter,
               next_pos);
  if (index == string::npos) { 
    more = false;
    token = str.substr(next_pos);
  } else {
    more = true;
    token = str.substr(next_pos, index - next_pos);
    next_pos = index + 1;
  }
  m_widthField = m_widthField > token.length() ? m_widthField : token.length();
  return token;
}

void Utilities::setDelimiter(char newDelimiter) {
  Utilities::m_delimiter = newDelimiter;
}

char Utilities::getDelimiter() { return m_delimiter; }

} // namespace sdds
