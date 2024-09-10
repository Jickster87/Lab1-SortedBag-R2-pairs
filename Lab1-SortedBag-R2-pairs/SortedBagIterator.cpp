#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
    currentPosition = 0;
    freqCount = 1;
}

void SortedBagIterator::first() {
    currentPosition = 0;
    freqCount = 1;
}


void SortedBagIterator::next() {
    if (currentPosition == bag.sizeBag) {
         throw exception();
     }
     freqCount++;
     if (freqCount > bag.mainArray[currentPosition].second) {
         currentPosition++;
         freqCount = 1;
     }
}

TComp SortedBagIterator::getCurrent() {
    if (currentPosition == bag.sizeBag) {
          throw exception();
      }
      return bag.mainArray[currentPosition].first;;
}

bool SortedBagIterator::valid() {
    return currentPosition < bag.sizeBag;
}

