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
               next_pos); // find the delimiter's position and store it in index
  if (index == string::npos) { // check if there are no more delimiters
    more = false;
    token = str.substr(next_pos);
  } else {
    // this means there are more delimiters, so the next_pos is now delimiter+1
    more = true;
    // so token is from after delimiter to before the next delimiter
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
