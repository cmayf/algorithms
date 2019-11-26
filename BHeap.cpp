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

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap() {}

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::BHeap(keytype k[], valuetype v[], int s) {}

template<class keytype, class valuetype>
BHeap<keytype, valuetype>::~BHeap() {}

template<class keytype, class valuetype>
keytype BHeap<keytype, valuetype>::peakKey() {}

template<class keytype, class valuetype>
valuetype BHeap<keytype, valuetype>::peakValue() {}

template<class keytype, class valuetype>
keytype BHeap<keytype, valuetype>::extractMin() {}

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::insert(keytype k, valuetype v) {}

template<class keytype, class valuetype>
void BHeap<keytype, valuetype>::printKey() {}