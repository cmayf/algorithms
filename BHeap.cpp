#include <iostream>

template<class keytype, class valuetype>
class BHeap {
    private:

    public:
        BHeap();
        BHeap(keytype k[], valuetype v[], int s);
        ~BHeap();
        keytype peakKey();
        valuetype peakValue();
        keytype extractMin();
        void insert(keytype k, valuetype v);
        void merge(BHeap<keytype, valuetype> H2);
        void printKey();
};

//####################################################################

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap() {
/*
Constructor - empty
*/

}

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(keytype k[], valuetype v[], int s) {
/*
Constructor - repeated insertion
*/
   
}

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::~BHeap() {
/*
Destructor
*/

}

//####################################################################

template<class keytype, class valuetype>
keytype BHeap<keytype, valuetype>::peakKey() {
/*
Returns minimum key in heap w/o modifying the heap
*/

}

template<class keytype, class valuetype>
valuetype BHeap<keytype, valuetype>::peakValue() {
/*
Returns associated value of minimum key in heap w/o modifying the heap
*/

}

template<class keytype, class valuetype>
keytype BHeap<keytype, valuetype>::extractMin() {
/*
Removes the minimum key in the heap and returns the key
*/

}

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::insert(keytype k, valuetype v) {
/*
Inserts the key k and value v pair into the heap
*/

}

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::printKey() {
/*
Writes the keys stored in the heap, printing the smallest binomial tree first
*/

}