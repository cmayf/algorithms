#include <iostream>

template<class keytype, class valuetype>
class Heap {
    private:
        struct Node {
            keytype key;
            valuetype value;
        };
        Node** A;
        Node NIL;
        int length;
        int heap_size;

        int parent(int i) { return i/2;     }
        int left(int i)   { return 2*i;     }
        int right(int i)  { return 2*i + 1; }
        void min_heapify(int i) {
            int l = left(i);
            int r = right(i);
            int smallest;
            if (l <= length && A[l]->key < A[i]->key)
                smallest = l;
            else smallest = i;
            if (r <= length && A[r]->key < A[smallest]->key)
                smallest = r;
            if (smallest != i) {
                Node* tmp = A[i];
                A[i] = A[smallest];
                A[smallest] = tmp;
                min_heapify(smallest);
            }
        }
        void preorder_heap(int i) {
            if (i > length) return;
            std::cout << A[i]->key << " ";
            preorder_heap(left(i));
            preorder_heap(right(i));
        }
        void grow_heap() {
            heap_size *= 2;
            Node** tmp = new Node*[heap_size];
            for (int i = 0; i < length; i++)
                tmp[i] = A[i];
            A = tmp;
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

//####################################################################

template<class keytype, class valuetype>
Heap<keytype, valuetype>::Heap() {
/*
Constructor - default
*/
    heap_size = 2;
    length = 0;
    A = new Node*[heap_size];
    for (int i = 0; i < heap_size; i++) A[i] = &NIL;
}

template<class keytype, class valuetype>
Heap<keytype, valuetype>::Heap(keytype k[], valuetype v[], int s) {
/*
Constructor - O(n) bottom up heap building method
*/
    heap_size = s * 2;
    length = s;
    A = new Node*[heap_size];
    A[0] = &NIL;
    for (int i = 1; i <= length; i++) {
        Node* n = new Node;
        n->key = k[i-1];
        n->value = v[i-1];
        A[i] = n;
    }
    for (int i = length/2; i >= 1; i--) min_heapify(i);
}

template<class keytype, class valuetype>
Heap<keytype, valuetype>::~Heap() {
/*
Destructor
*/
    for (int i = 1; i < length; i++) {
        free(A[i]);
    }
    delete [] A;
}

//####################################################################

template<class keytype, class valuetype>
keytype Heap<keytype, valuetype>::peakKey() {
/*
Returns minimum key in heap w/o modifying the heap
*/
   return A[1]->key;
}

template<class keytype, class valuetype>
valuetype Heap<keytype, valuetype>::peakValue() {
/*
Returns associated value of minimum key in heap w/o modifying the heap
*/
   return A[1]->value;
}

template<class keytype, class valuetype>
keytype Heap<keytype, valuetype>::extractMin() {
/*
Removes the minimum key in the heap and return the key
*/
    if (length < 1) return std::numeric_limits<keytype>::min();
    Node* min = A[1];
    A[1] = A[length];
    --length;
    min_heapify(1);
    return min->key;
}

template<class keytype, class valuetype>
void Heap<keytype, valuetype>::insert(keytype k, valuetype v) {
/*
Inserts the key k and value v pair into the heap
*/
    ++length;
    if (length == heap_size) grow_heap();

    Node* n = new Node;
    n->key = k;
    n->value = v;
    A[length] = n;

    int i = length;
    while (i > 1 && A[parent(i)]->key > A[i]->key) {
        Node* tmp = A[i];
        A[i] = A[parent(i)];
        A[parent(i)] = tmp;
        i = parent(i);
    }
}


template<class keytype, class valuetype>
void Heap<keytype, valuetype>::printKey() {
/*
Writes the keys stored in the array starting at the root
*/
    preorder_heap(1);
    std::cout << std::endl;
}

