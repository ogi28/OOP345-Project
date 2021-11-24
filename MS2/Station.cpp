// Name: Ogulcan Tayhan
// Seneca Student ID: 104472204
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <iomanip>
#include "Station.h"
#include "Utilities.h"

namespace sdds {

size_t Station::m_widthField = 0;
size_t Station::id_generator = 0;

Station::Station(const std::string &str) {
  Utilities util;
  size_t next_pos = 0;
  bool more = true;
  m_id = ++Station::id_generator;
  m_itemName = util.extractToken(str, next_pos, more);
  if (more) {
    m_serialNumber = stoul(util.extractToken(str, next_pos, more));
    if (more) {
      m_stock = stoul(util.extractToken(str, next_pos, more));
      Station::m_widthField = Station::m_widthField > util.getFieldWidth()
                                  ? Station::m_widthField
                                  : util.getFieldWidth();
      if (more) {
        m_desc = util.extractToken(str, next_pos, more);
      }
    }
  }
}

const std::string &Station::getItemName() const { return m_itemName; }

size_t Station::getNextSerialNumber() {
  return m_serialNumber++;
}

size_t Station::getQuantity() const { return m_stock; }

void Station::updateQuantity() { m_stock ? m_stock-- : m_stock; }

void Station::display(std::ostream &os, bool full) const {
  using std::left;
  using std::right;
  using std::setfill;
  using std::setw;

  os << "[" << setw(3) << right << setfill('0') << m_id
     << "] Item: " << setfill(' ') << setw(m_widthField) << left << m_itemName
     << " [" << setfill('0') << setw(6) << right << m_serialNumber << "]";
  if (full) {
    os << setfill(' ') << left << " Quantity: " << setw(m_widthField) << m_stock
       << " Description: " << m_desc;
  }
  os << '\n';
}

} // namespace sdds
