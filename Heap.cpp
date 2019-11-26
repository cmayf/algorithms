#include <iostream>

template<class keytype, class valuetype>
class Heap {
    private:
        struct Node {
            keytype key;
            valuetype value;
            Node *left, *right, *parent;
        };
        Node* A;
        int length;
        int heap_size;

        int parent(int i) { return i/2;     }
        int left(int i)   { return 2*i;     }
        int right(int i)  { return 2*i + 1; }
        void max_heapify(int i) {
            int l = left(i);
            int r = right(i);
            int largest;
            if (l <= heap_size && A[l] > A[i])
                largest = l;
            else largest = i;
            if (r <= heap_size && A[r] > A[largest])
                largest = r;
            if (largest != i) {
                int tmp = A[i];
                A[i] = A[largest];
                A[largest] = tmp;
                max_heapify(largest);
            }
        }

    public:
        Heap();
        Heap(keytype k[], valuetype v[], int s);
        ~Heap();
        keytype peakKey();
        valuetype peakValue();
        keytype extractMin();
        void insert(keytype k, valuetype v);
        void printKey();
};

template<class keytype, class valuetype>
Heap<keytype, valuetype>::Heap() {}

template<class keytype, class valuetype>
Heap<keytype, valuetype>::Heap(keytype k[], valuetype v[], int s) {
    
    heap_size = length;
    for (int i = length/2; i >= 1; i--) {
        max_heapify(i);
    }
}

template<class keytype, class valuetype>
Heap<keytype, valuetype>::~Heap() {}

template<class keytype, class valuetype>
keytype Heap<keytype, valuetype>::peakKey() {}

template<class keytype, class valuetype>
valuetype Heap<keytype, valuetype>::peakValue() {}

template<class keytype, class valuetype>
keytype Heap<keytype, valuetype>::extractMin() {}

template<class keytype, class valuetype>
void Heap<keytype, valuetype>::insert(keytype k, valuetype v) {}

template<class keytype, class valuetype>
void Heap<keytype, valuetype>::printKey() {}

