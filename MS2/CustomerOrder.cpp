#include <iomanip>
#include <utility>
#include "CustomerOrder.h"
#include "Utilities.h"

namespace sdds {
size_t CustomerOrder::m_widthField = 0;

void CustomerOrder::setEmpty() {
  if (m_listItem) {
    for (size_t i = 0; i < m_cntItem; i++) {
      delete m_listItem[i];
      m_listItem[i] = nullptr;
    }
    delete[] m_listItem;
    m_listItem = nullptr;
  }
}

CustomerOrder::CustomerOrder() : m_cntItem(0), m_listItem(nullptr) {}

CustomerOrder::CustomerOrder(const std::string &str) : CustomerOrder() {
  Utilities util;
  size_t next_pos = 0;
  bool more = true;
  m_name = util.extractToken(str, next_pos, more);
  if (more) {
    m_product = util.extractToken(str, next_pos, more);
    if (more) {
      size_t capacity = 1;
      m_listItem = new Item *[capacity];
      while (more) {
        if (m_cntItem >= capacity) {
          capacity += 5;
          Item **temp = new Item *[capacity];
          for (size_t i = 0; i < m_cntItem; i++) {
            temp[i] = m_listItem[i];
          }
          delete[] m_listItem;
          m_listItem = temp;
        }
        m_listItem[m_cntItem] =
            new Item(util.extractToken(str, next_pos, more));
        m_cntItem++;
      }
    }
  }
  CustomerOrder::m_widthField =
      CustomerOrder::m_widthField > util.getFieldWidth()
          ? CustomerOrder::m_widthField
          : util.getFieldWidth();
}
CustomerOrder::~CustomerOrder() { setEmpty(); }

CustomerOrder &CustomerOrder::operator=(CustomerOrder &&C) noexcept {
  if (this != &C) {
    this->setEmpty();
    m_name = std::move(C.m_name);
    m_product = std::move(C.m_product);
    m_cntItem = C.m_cntItem;
    m_listItem = C.m_listItem;
    C.m_listItem = nullptr;
    C.m_cntItem = 0;
  }
  return *this;
}
CustomerOrder::CustomerOrder(CustomerOrder &&C) noexcept : CustomerOrder() {
  *this = std::move(C);
}

bool CustomerOrder::isFilled() const {
  size_t i = 0;

  while (i < m_cntItem && m_listItem[i]->m_isFilled) {
    i++;
  }
  return i == m_cntItem;
}

bool CustomerOrder::isItemFilled(const std::string &itemName) const {
  size_t i = 0;
  bool isFilled = true;
  while (i < m_cntItem && isFilled) {
    if (!m_listItem[i]->m_isFilled && m_listItem[i]->m_itemName == itemName) {
      isFilled = false;
    }
    i++;
  }
  return isFilled;
}
void CustomerOrder::fillItem(Station &station, std::ostream &os) {
  using std::setfill;
  using std::setw;
  for (size_t i = 0; i < m_cntItem; i++) {
    if (!m_listItem[i]->m_isFilled &&
        station.getItemName() == m_listItem[i]->m_itemName) {
      os << setfill(' ') << setw(4) << "";
      if (station.getQuantity()) {
        station.updateQuantity();
        m_listItem[i]->m_isFilled = true;
        m_listItem[i]->m_serialNumber = station.getNextSerialNumber();
        os << "Filled " << m_name << ", " << m_product << " ["
           << m_listItem[i]->m_itemName << "]";
      } else {
        os << "Unable to fill " << m_name << ", " << m_product << " ["
           << m_listItem[i]->m_itemName << "]";
      }
      os << std::endl;
    }
  }
}
void CustomerOrder::display(std::ostream &os) const {
  using std::endl;
  using std::left;
  using std::right;
  using std::setfill;
  using std::setw;

  os << m_name << " - " << m_product << endl;
  for (size_t i = 0; i < m_cntItem; i++) {
    os << "[" << setw(6) << right << setfill('0')
       << m_listItem[i]->m_serialNumber << "] " << setw(m_widthField) << left
       << setfill(' ') << m_listItem[i]->m_itemName << " - "
       << (m_listItem[i]->m_isFilled ? "FILLED" : "TO BE FILLED") << endl;
  }
}

} // namespace sdds
