// Name: Ogulcan Tayhan
// Seneca Student ID: 104472204
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_CUSTOMERORDER_H
#define SDDS_CUSTOMERORDER_H

#include <string>
#include "Station.h"
#include "Utilities.h"

namespace sdds {

struct Item {
  std::string m_itemName;
  size_t m_serialNumber{0};
  bool m_isFilled{false};
  Item(const std::string &src) : m_itemName(src){};
};

class CustomerOrder {
public:
  CustomerOrder();
  CustomerOrder(const std::string &str);
  CustomerOrder(CustomerOrder &&) noexcept;
  CustomerOrder(const CustomerOrder &) { throw "tantrum"; }
  CustomerOrder &operator=(CustomerOrder &&) noexcept;
  CustomerOrder &operator=(const CustomerOrder &) = delete;
  ~CustomerOrder();

  bool isFilled() const;
  bool isItemFilled(const std::string &itemName) const;
  void fillItem(Station &station, std::ostream &os);
  void display(std::ostream &os) const;

private:
  static size_t m_widthField;
  std::string m_name;
  std::string m_product;
  size_t m_cntItem;
  Item **m_listItem;
  void setEmpty();
};

} // namespace sdds

#endif // !SDDS_CUSTOMERORDER_H
