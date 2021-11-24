// Name: Ogulcan Tayhan
// Seneca Student ID: 104472204
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_UTILITIES_H
#define SDDS_UTILITIES_H

#include <string>

namespace sdds {
class Utilities {

public:
  Utilities() : m_widthField (1){}; 
  Utilities(Utilities &&) = default;
  Utilities(const Utilities &) = default;
  Utilities &operator=(Utilities &&) = default;
  Utilities &operator=(const Utilities &) = default;
  ~Utilities() = default;

  void setFieldWidth(size_t newWidth);
  size_t getFieldWidth() const;
  std::string extractToken(const std::string &str, size_t &next_pos,
                           bool &more);
  static void setDelimiter(char newDelimiter);
  static char getDelimiter();

private:
  size_t m_widthField;
  static char m_delimiter;
};

} // namespace sdds
#endif // !SDDS_UTILITIES_H
