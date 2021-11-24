// Seneca Student ID: 104472204
// Name: Ogulcan Tayhan
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_LINEMANAGER_H
#define SDDS_LINEMANAGER_H

#include <vector>
#include "Workstation.h"

namespace sdds {
class LineManager {
public:
  LineManager() = default;
  LineManager(const std::string &file,
              const std::vector<Workstation *> &stations);
  LineManager(LineManager &&) = default;
  LineManager(const LineManager &) = default;
  LineManager &operator=(LineManager &&) = default;
  LineManager &operator=(const LineManager &) = default;
  ~LineManager() = default;

  void linkStations();
  bool run(std::ostream &os);
  void display(std::ostream &os) const;

private:
  std::vector<Workstation *> activeLine;
  size_t m_cntCustomerOrder;
  Workstation *m_firstStation;
};

} // namespace sdds

#endif // !SDDS_LINEMANAGER_H
