#include <iostream>
#include <cmath>
#include <limits>
#include <string>
#include <algorithm>

template <class T>

class CircularDynamicArray {
    private:
        T* arr; //Dynamic array pointer
        T elmtype; //Out of bounds reference
        int len; //Number of elements in the array
        int cap; //Total capacity of the array

        void resize(int size);
        int pivot(int left, int right, int pivotIndex);
        int partition(T a[], int left, int right, int pivotIndex);
        T findMedian(T a[], int n);
        int KthSelect(T a[], int left, int right, int k);
        void merge(int p, int q, int r);
        void mergeSort(int p, int r);
        int maxIndex(T* a);

    public:
        CircularDynamicArray(); 
        CircularDynamicArray(int s); 
        CircularDynamicArray(CircularDynamicArray<T>& a);
        ~CircularDynamicArray(); 
        CircularDynamicArray<T> operator=(CircularDynamicArray<T> other);
        T& operator[](int i); 
        void addEnd(T v); 
        void addFront(T v); 
        void delEnd(); 
        void delFront(); 
        int length(); 
        int capacity(); 
        int clear(); 
        T QuickSelect(int k); 
        T WCSelect(int k); 
        void stableSort(); 
        void radixSort(int i); 
        int linearSearch(T e); 
        int binSearch(T e);
};

template <class T>
CircularDynamicArray<T>::CircularDynamicArray() {
    T* tmp = new T[2];
    elmtype = T();
    cap = 2;
    len = 0;
    arr = tmp;
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(int s) {
    T* tmp = new T[s];
    elmtype = T();
    cap = s;
    len = s;
    arr = tmp;
}

template <class T>
CircularDynamicArray<T>::CircularDynamicArray(CircularDynamicArray& a) {
    //std::cout << "Copy constructor" << std::endl << std::endl;
    arr = new T[a.cap];
    elmtype = a.elmtype;
    cap = a.cap;
    len = a.len;
    for (int i = 0; i < len; i++) arr[i] = a[i];
}

template <class T>
CircularDynamicArray<T>::~CircularDynamicArray() {
    delete [] arr;
}

template <class T>
CircularDynamicArray<T> CircularDynamicArray<T>::operator=(CircularDynamicArray<T> other) {
    //std::cout << "Copy assignment" << std::endl;
    std::swap(arr, other.arr);
    std::swap(elmtype, other.elmtype);
    std::swap(cap, other.cap);
    std::swap(len, other.len);
    return *this;
}

template <class T>
T& CircularDynamicArray<T>::operator[](int index) {
    if(index > cap) {
        std::cout << "Out of bounds reference : " << index << std::endl << std::endl;
        return elmtype;
    }
    return arr[index];
}

//#####################################################################

template <class T>
void CircularDynamicArray<T>::resize(int size) {
    T* buffer = new T[size];
    std::copy(arr, arr + len, buffer);
    delete [] arr;
    arr = buffer;
}

template <class T>
void CircularDynamicArray<T>::addEnd(T v) {
    ++len;
    if(len == cap) {
        cap *= 2;
        resize(cap);
    }
    arr[len - 1] = v;
}

template <class T>
void CircularDynamicArray<T>::addFront(T v) {
    ++len;
    if(len == cap) {
        cap *= 2;
        resize(cap);
    }
    for(int i = len - 1; i >= 0; i--) {
        T tmp = arr[i];
        arr[i+1] = tmp;
    }
    arr[0] = v;
}

template <class T>
void CircularDynamicArray<T>::delEnd() {
    --len;
    if(len == (cap/4)) {
        cap /= 2;
        resize(cap);
    }
}

template <class T>
void CircularDynamicArray<T>::delFront() {
    --len;
    for(int i = 0; i < len; i++) {
        arr[i] = arr[i+1];
    }
    if(len == (cap/4)) {
        cap /= 2;
        resize(cap);
    }
}

template <class T>
int CircularDynamicArray<T>::length() {
    return len;
}

template <class T>
int CircularDynamicArray<T>::capacity() {
    return cap;
}

template <class T>
int CircularDynamicArray<T>::clear() {
    delete [] arr;
    arr = new T[2];
    cap = 2;
    len = 0;
    return cap;
}


//#####################################################################
//Returns the k^th smallest element in the array using the quickselect algorithm


template <class T>
int CircularDynamicArray<T>::partition(T a[], int left, int right, int pivotIndex) {
    T pivot = a[pivotIndex];
    swap(a[pivotIndex], a[right]);
    int i = left;
    for (int j = left; j <= right - 1; j++) {
        if (a[j] <= pivot) {
            swap(a[i], a[j]);
            i = i + 1;
        }
    }
    swap(arr[i], arr[right]);
    return i;
}


template <class T>
T CircularDynamicArray<T>::QuickSelect(int k) {
    if(k != 0) k = k - 1;  // k is decreased for indexing purposes.
    int left = 0, right = len - 1;
    while(1) {
        if (left == right) {
            return arr[left];
        }
        srand(time(NULL));
        int pivotIndex = left + floor(rand() % (right - left) + 1);
        pivotIndex = partition(arr, left, right, pivotIndex);
        if (k == pivotIndex)
            return arr[k];
        else if (k < pivotIndex)
            right = pivotIndex - 1;
        else
            left = pivotIndex + 1;
    }
    std::numeric_limits<T>::max();
}

//#####################################################################
//Returns the k^th smallest element in the array using the worst case O(N) time algorithm

template <class T>
T CircularDynamicArray<T>::findMedian(T a[], int n) {
    sort(a, a+n);
    return a[n/2];
}

template <class T>
int CircularDynamicArray<T>::KthSelect(T a[], int left, int right, int k) {
    if (k > 0 && k <= right - left + 1) {
        int n = right - left + 1;

        T* median = new T[(n+4)/5];
        int i;
        for (i = 0; i < n/5; i++)
            median[i] = findMedian(a+left+i*5, 5);
        if (i*5 < n) {
            median[i] = findMedian(a+left+i*5, n%5);
            i++;
        }

        int medOfMed = (i == 1) ? median[i-1]: KthSelect(median, 0, i-1, i/2);
        int pos = partition(a,left, right, i - 1);

        delete [] median;
        if (pos-left == k-1)
            return pos;
        if (pos-left > k-1)
            return KthSelect(a, left, pos-1, k);
        return KthSelect(a, pos+1, right, k-pos+left-1);
    }
    return std::numeric_limits<T>::max();
}

template <class T>
T CircularDynamicArray<T>::WCSelect(int k) {
    return arr[KthSelect(arr, 0, len, k)];
}

//#####################################################################
//Sorts the values in the array using a comparison based O(NlgN) algorithm. 
//The sort must be stable.

template <class T>
void CircularDynamicArray<T>::merge(int p, int q, int r) {
    int m = q - p + 1, n = r - q;
    T left[m + 2], right[n + 2];
    for (int a = 1; a <= m; a++)
        left[a] = arr[p + a - 1];
    for (int b = 1; b <= n; b++)
        right[b] = arr[q + b];
    left[m + 1] = std::numeric_limits<T>::max();
    right[n + 1] = std::numeric_limits<T>::max();

    int i = 1, j = 1, k = p;
    while (i <= m && j <= n) {
        if (left[i] <= right[j]) {
            arr[k] = left[i];
            i++;
        }
        else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }
    
    while (i <= m) {
        arr[k] = left[i];
        i++;
        k++;
    }
    while (j <= n) {
        arr[k] = right[j];
        j++;
        k++;
    }
}

template <class T>
void CircularDynamicArray<T>::mergeSort(int p, int r) {
    if (p < r) {
        int q = floor((p + r) / 2);
        mergeSort(p, q);
        mergeSort(q + 1, r);
        merge(p, q, r);
    }
}

template <class T>
void CircularDynamicArray<T>::stableSort() {
    mergeSort(0, len - 1);
}

//#####################################################################
//Sorts the values in the array using a radix based sort on the lower order i bits of elmtype.

template <class T>
int CircularDynamicArray<T>::maxIndex(T* a) {
    int maxIndex = 0;
    for(int i = 1; i < len; i++) {
        if(a[i] >= a[maxIndex])
            maxIndex = i;
    }
    return maxIndex;
}

template <class T>
void CircularDynamicArray<T>::radixSort(int i) {
    T* B = new T[cap];

    int a = 0, pos = 0;
    int buckets = 1 << i;
    int mask = buckets - 1;
    //T m = arr[maxIndex(arr)];
    T m = arr[len - 1];
    while ((m >> (pos * i)) > 0) {
        int bucket[buckets];
        for(a = 0; a < (buckets); a++)          bucket[a] = 0;
        for(a = 0; a < len; a++)                bucket[ (arr[a] >> (pos*i)) & mask]++;
        for(a = 1; a < buckets; a++)            bucket[a] += bucket[a - 1];
        for(a = len - 1; a >= 0; a--)           B[--bucket[(arr[a] >> (pos*i)) & mask]] = arr[a];
        /* The following line creates partially sorted array */
        for(a = 0; a < len; a++)                arr[a] = B[a];
        /* The following three lines create sorted array of signed integers */
        //int max = maxIndex(B);
        //for(a = 0; a < len - max; a++)            arr[a] = B[a+max+1];
        //for(a = 0; a <= max; a++)                 arr[len-max-1+a] = B[a]; 
        pos++;
    }
    delete [] B;
    return;  

}

//#####################################################################
//Performs a linear search of the array looking for the item e. 
//Returns the index of the item if found or -1 otherwise.

template <class T>
int CircularDynamicArray<T>::linearSearch(T e) {
    for(int i = 0; i < len; i++) {
        if(arr[i] == e)
            return i;
    }
    return -1;
}

//Performs a binary search of the array looking for the item e. 
//Returns the index of the item if found or -1 otherwise. 
//Assumes that the array is in sorted order.
template <class T>
int CircularDynamicArray<T>::binSearch(T e) {
    int left = 0, right = len - 1, m = 0;
    while (left <= right) {
        m = floor((left + right + 1) / 2);
        if (arr[m] < e)
            left = m + 1;
        else if (arr[m] > e)
            right = m - 1;
        else
            return m;
    }
    return -1;
}
