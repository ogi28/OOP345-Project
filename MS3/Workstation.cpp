// Name: Ogulcan Tayhan
// Seneca Student ID: 104472204
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.


#include "Workstation.h"

std::deque<sdds::CustomerOrder> pending;
std::deque<sdds::CustomerOrder> completed;
std::deque<sdds::CustomerOrder> incomplete;

namespace sdds {
Workstation::Workstation(const std::string str)
    : Station(str), m_pNextStation(nullptr) {}

void Workstation::fill(std::ostream &os) {
  if (!m_orders.empty()) {
    // need to reference else it copies. And we deleted copy.
    CustomerOrder &C = m_orders.front();
    C.fillItem(*this, os);
  }
}

bool Workstation::attemptToMoveOrder() {
  // take the first order.
  if (m_orders.empty()) {
    return false;
  }
  CustomerOrder &C = m_orders.front();
  if (C.isItemFilled(this->getItemName())) {
    if (m_pNextStation) {
      // This line sends to next station
      *m_pNextStation += std::move(C);
    } else {
      // This line either sends to completed or incomplete queue
      C.isFilled() ? completed.push_back(std::move(C))
                   : incomplete.push_back(std::move(C));
      // they didn't write this, but we're supposed to move to incomplete here
      // too.
    }
    m_orders.pop_front();
  } else if (!getQuantity()) {
    if (m_pNextStation) {
      *m_pNextStation += std::move(C);
    } else {
      incomplete.push_back(std::move(C));
    }
    m_orders.pop_front();
  } else {
    // means we have enough inventory and we're not moving the order.
    return false;
  }
  // if else didn't happen, we return true.
  return true;
}

void Workstation::setNextStation(Workstation *station) {
  m_pNextStation = station;
}

Workstation *Workstation::getNextStation() const { return m_pNextStation; }

void Workstation::display(std::ostream &os) const {
  os << getItemName() << " --> ";
  if (m_pNextStation) {
    os << m_pNextStation->getItemName();
  } else {
    os << "End of Line";
  }
  os << std::endl;
}

Workstation &Workstation::operator+=(CustomerOrder &&newOrder) {
  m_orders.push_back(std::move(newOrder));
  return *this;
}

} // namespace sdds
