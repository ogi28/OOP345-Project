// Name: Ogulcan Tayhan
// Seneca Student ID: 104472204
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef SDDS_WORKSTATION_H
#define SDDS_WORKSTATION_H

#include <deque>
#include <string>
#include "CustomerOrder.h"
#include "Station.h"


extern std::deque<sdds::CustomerOrder> pending;
extern std::deque<sdds::CustomerOrder> completed;
extern std::deque<sdds::CustomerOrder> incomplete;

namespace sdds {

class Workstation : public Station {
public:
  Workstation() = default;
  Workstation(const std::string str);
  Workstation(Workstation &&) = default;
  Workstation(const Workstation &) = default;
  Workstation &operator=(Workstation &&) = default;
  Workstation &operator=(const Workstation &) = default;
  ~Workstation() = default;

  void fill(std::ostream &os);
  bool attemptToMoveOrder();
  void setNextStation(Workstation *station = nullptr);
  Workstation *getNextStation() const;
  void display(std::ostream &os) const;
  Workstation &operator+=(CustomerOrder &&newOrder);

private:
  // works like a linked list
  std::deque<CustomerOrder> m_orders;
  Workstation *m_pNextStation;
};

} // namespace sdds

#endif // !SDDS_WORKSTATION_H
