template <class keytype, class valuetype>

class RBTree {      // left-leaning red-black tree
    private:


    public:
        RBTree();
        RBTree(keytype k[], valuetype V[], int s);
        ~RBTree();
        valuetype* search(keytype k);
        int delete(keytype k);
        int rank(keytype k);
        keytype select(int pos);
        void split(keytype k, RBTree<keytype, valuetype>& T1, RBTree<keytype, valuetype>& T2);
        int size();
        void preorder();
        void inorder();
        void postorder();

};

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree() {}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype k[], valuetype V[], int s) {}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::~RBTree() {}

template <class keytype, class valuetype>
valuetype* RBTree<keytype, valuetype>::search(keytype k) {}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::rank(keytype k) {}

template <class keytype, class valuetype>
keytype RBTree<keytype, valuetype>::select(int pos) {}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::split(keytype k, RBTree<keytype, valuetype>& T1, RBTree<keytype, valuetype>& T2) {}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::size() {}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::preorder() {}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::inorder() {}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::postorder() {}