// Seneca Student ID: 104472204
// Name: Ogulcan Tayhan
// Seneca email: otayhan@myseneca.ca
// Date of completion: 19/11/2021
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include <algorithm>
#include <fstream>
#include "LineManager.h"
#include "Utilities.h"

// Refer to image
//  pink rectangles are customer orders
//  A workstation has customer orders.
//  But workstation only has 1 customer order despite the image.
//  workstation 1 can take a new order as soon as its empty rather than
// going through the whole thing.
//  In filling orders part of the expected output, first workstation is bed,
//  second is dresser etc. We don't see workstation numbers but because each one
//  can only have one customerOrder at any given time, the expected output is
//  like that.
// Essentially only one bed can be processed at a time, one dresser etc. If we
// don't see any that means there were no orders for it.
// If one person buys the same item twice, then they can be processed at the
// same time by the workstation.

namespace sdds {

LineManager::LineManager(const std::string &file,
                         const std::vector<Workstation *> &stations) {
  std::ifstream inFile(file);
  if (!inFile.is_open()) {
    throw "Failed to open the file.";
  }
  std::string wsName;
  std::string line;
  // had to capture by reference?
  // If you don't capture by reference, the old value of wsName gets captured
  // which is empty. 
  auto findWSByName = [&wsName](const Workstation *ws) -> bool {
    return ws->getItemName() == wsName;
  };

  while (!inFile.eof()) {
    Utilities util;
    size_t next_pos = 0;
    bool more = true;
    getline(inFile, line);
    wsName = util.extractToken(line, next_pos, more);
    auto i = std::find_if(stations.begin(), stations.end(), findWSByName);
    if (i == stations.end()) {
      throw std::string("Station not found!: " + wsName);
    }
    // we are adding the workstation to active line because we found it.
    // we are also sorting by storing in the pointers, not the vector
    activeLine.push_back(*i);
    if (more) {
      wsName = util.extractToken(line, next_pos, more);
      auto j = std::find_if(stations.begin(), stations.end(), findWSByName);
      if (j == stations.end()) {
        throw "No such station!";
      }
      (*i)->setNextStation(*j);
    } else {
      (*i)->setNextStation();
    }
  }
  inFile.close();
  m_cntCustomerOrder = pending.size();

  // have to capture 'this' explicitly because we need access to entire object
  // did nested lambdas, making it a nested loop.
  // Find if calls findFirstWS for each workstation, which then calls none of
  // which calls isNext; complexity of O(n^2)
  auto findFirstWS = [this](const Workstation *ws) -> bool {
    auto isNext = [ws](const Workstation *current) -> bool {
      return current->getNextStation() == ws;
    };
    return std::none_of(activeLine.begin(), activeLine.end(), isNext);
  };
  // this just finds the first one from the file, looping through all the
  // elements and making sure it gets the one where it doesn't appear after the
  // delimiter, we check with next of nothing not delimiter
  auto firstInLine =
      std::find_if(activeLine.begin(), activeLine.end(), findFirstWS);
  if (firstInLine == activeLine.end()) {
    throw "No stations are first in line";
  }
  m_firstStation = *firstInLine;
}

void LineManager::linkStations() {
  activeLine.erase(activeLine.begin(), activeLine.end());
  Workstation *temp = m_firstStation;
  while (temp) {
    activeLine.push_back(temp);
    temp = temp->getNextStation();
  }
}

bool LineManager::run(std::ostream &os) {
  static size_t count = 1;
  os << "Line Manager Iteration: " << count++ << std::endl;
  if (!pending.empty()) {
    CustomerOrder &C = pending.front();
    *m_firstStation += std::move(C);
    pending.pop_front();
  }
  auto fillOrder = [&os](Workstation *ws) { ws->fill(os); };
  std::for_each(activeLine.begin(), activeLine.end(), fillOrder);
  auto attemptMove = [](Workstation *ws) { ws->attemptToMoveOrder(); };
  std::for_each(activeLine.begin(), activeLine.end(), attemptMove);
  // from pending it goes to completed or incomplete, if they all went to one or
  // the other order is done. Because we set m_cntCustomerOrder to pending
  // initially. Can't check if pending is empty because they can be in active
  // line, which would mean it is still being processed and not complete.
  return m_cntCustomerOrder == (completed.size() + incomplete.size());
}

void LineManager::display(std::ostream &os) const {
  auto callDisplay = [&os](const Workstation *ws) { ws->display(os); };
  for_each(activeLine.begin(), activeLine.end(), callDisplay);
}
} // namespace sdds
