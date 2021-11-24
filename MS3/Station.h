#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <ostream>
#include <string>

namespace sdds {
class Station {
public:
  Station() = default;
  Station(const std::string &str);
  Station(Station &&) = default;
  Station(const Station &) = default;
  Station &operator=(Station &&) = default;
  Station &operator=(const Station &) = default;
  ~Station() = default;

  const std::string &getItemName() const;
  size_t getNextSerialNumber();
  size_t getQuantity() const;
  void updateQuantity();
  void display(std::ostream &os, bool full) const;

private:
  int m_id;
  std::string m_itemName;
  std::string m_desc;
  size_t m_serialNumber;
  size_t m_stock;

  static size_t m_widthField;
  static size_t id_generator;
};
} // namespace sdds

#endif // !SDDS_STATION_H
