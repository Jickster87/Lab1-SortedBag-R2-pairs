#include "SortedBag.h"
#include "SortedBagIterator.h"

SortedBag::SortedBag(Relation r) {
    capacity = 64;
    sizeBag = 0;
    mainArray = new TPair[capacity]();
    rel = r; // dont understand the link yet
}

void SortedBag::add(TComp e) {
	//resize
    if (sizeBag == capacity) {
        capacity *= 2;
        TPair* tempArray = new TPair[capacity]();
        for (int i = 0; i < sizeBag; i++) {
            tempArray[i] = mainArray[i];
        }
        delete [] mainArray;
        mainArray = tempArray;
    }
    
    //search for the elem and increase freq++ if exists
    for (int i=0; i<sizeBag; i++) {
        if (e == mainArray[i].first) {
            mainArray[i].second++;
        }
    }
    
    //else determine elemPos to insert Tpair with elem and freq=1
    //find index in main array and store value;
    int elemPos = 0;
    while (elemPos < sizeBag && rel(mainArray[elemPos].first, e)) {
       elemPos++;
    }
    //shift from elemPos to end of bag;
    for (int i = sizeBag; i > elemPos; i--) {
       mainArray[i] = mainArray[i-1];
    }
    //insert elem at elemPos
    mainArray[elemPos].first = e;
    mainArray[elemPos].second = 1;
    //and add one more empty slot
    sizeBag++;
    
}


bool SortedBag::remove(TComp e) {
    // If the bag is empty, return false
     if (sizeBag == 0) {
         return false;
     }
   
    //find elem
    int elemPos = -1;
    for (int i = sizeBag; i >= 0; i--) {
        if (mainArray[i].first == e) {
            elemPos = i;
            break;
        }
    }
    
    // not found get out
    if (elemPos == -1) {
        return false;
    }
    
    // decrement freq
    mainArray[elemPos].second--;
    
    // if freq is now 0 also remove pair
    if (mainArray[elemPos].second == 0) {
        for (int i = elemPos; i < sizeBag-1; i++) {
                mainArray[i] = mainArray[i+1];
            }
            sizeBag--;
    }
       
	return true;
}


bool SortedBag::search(TComp elem) const {
    for (int i=0; i<sizeBag; i++) {
        if (elem == mainArray[i].first) {
            return true;
        }
    }
	return false;
}


int SortedBag::nrOccurrences(TComp elem) const {
    for (int i=0; i<sizeBag; i++) {
        if (elem == mainArray[i].first) {
            return mainArray[i].second;
        }
    }
	return 0;
}



int SortedBag::size() const {
    //size is all freq counted? - getting errors in size
    int counter = 0;
    for (int i=0; i<sizeBag; i++) {
        counter += mainArray[i].second;
    }
	return counter;
    //return sizeBag;
}


bool SortedBag::isEmpty() const {
	//TODO - Implementation
	return sizeBag==0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
    delete [] mainArray;
}
