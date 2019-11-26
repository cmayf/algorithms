#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

#define RED 1
#define BLACK 0

template <class keytype, class valuetype>
class RBTree {      // left-leaning red-black tree
    struct Node {
        keytype key;
        valuetype value;
        int color;
        int size;
        int found;
        Node *left, *right, *parent;
    };

    private:
        Node* root;
        Node* NIL;
        int tree_size;

        int compare(keytype a, keytype b);
        Node* findMin(Node* x);
        Node* deleteMin(Node* x);
        Node* rotateLeft(Node* x);
        Node* rotateRight(Node* x); 
        Node* colorFlip(Node* x); 
        Node* moveRedLeft(Node* x); 
        Node* moveRedRight(Node* x); 
        Node* fixUp(Node* x);
        Node* RBinsert(Node* x, keytype k, valuetype v);
        Node* RBremove(Node* x, keytype k);
        int rank_r(keytype k, Node* x);
        keytype select_r(int pos, Node* x);
        void preorder(Node* root);
        void postorder(Node* root);
    

    public:
        RBTree();
        RBTree(keytype K[], valuetype V[], int s);
        RBTree(RBTree<keytype, valuetype>& a);
        ~RBTree();
        RBTree<keytype, valuetype> operator=(RBTree<keytype, valuetype> other);
        valuetype* search(keytype k);
        void insert(keytype k, valuetype v);
        int remove(keytype k);
        int rank(keytype k);
        keytype select(int pos);
        void split(keytype k, RBTree<keytype, valuetype>& T1, RBTree<keytype, valuetype>& T2);
        int size();
        void preorder();
        void inorder();
        void postorder();

};

//#####################################################################
//Constructors/Destructors
//#####################################################################

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree() {
    NIL = new Node;
    NIL->left = NIL->right = NIL->parent = NIL;
    NIL->color = BLACK;
    NIL->size = NIL->found = 0;
    NIL->key = std::numeric_limits<keytype>::min();;
    NIL->value = valuetype();

    root = NIL;
    root->key = std::numeric_limits<keytype>::max();;
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(keytype K[], valuetype V[], int s) {
    NIL = new Node;
    NIL->left = NIL->right = NIL->parent = NIL;
    NIL->color = BLACK;
    NIL->size = NIL->found = 0;
    NIL->key = std::numeric_limits<keytype>::min();;
    NIL->value = valuetype();
    root = NIL;

    for (int i = 0; i < s; i++)
        insert(K[i], V[i]);
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::RBTree(RBTree& a) {
    std::cout << "Copy constructor" << std::endl;
    root = new Node;
    root = a.root;
    NIL = a.NIL;
    tree_size = a.tree_size;
    root->parent = a.root->parent;
    root->left = a.root->left;
    root->right = a.root->right;
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype>::~RBTree() {
    delete root;
    delete NIL;
}

template <class keytype, class valuetype>
RBTree<keytype, valuetype> RBTree<keytype, valuetype>::operator=(RBTree<keytype, valuetype> other) {
    std::cout << "Copy assignment" << std::endl;
    std::swap(root, other.root);
    std::swap(NIL, other.NIL);
    std::swap(tree_size, other.tree_size);
    return *this;
}

//#####################################################################
//RBTree Operations
//#####################################################################

template <class keytype, class valuetype>
valuetype* RBTree<keytype, valuetype>::search(keytype k) {
    Node* x = root;
    while (x != NIL) {
        int cmp = compare(k, x->key);
        if (cmp == 0) return &x->value;
        else if (cmp < 0) x = x->left;
        else x = x->right;
    }
    return &NIL->value;
}

//#####################################################################
//Insert
template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::RBinsert(Node* x, keytype k, valuetype v) {
    if (x == NIL) {
        x = new Node;
        x->key = k;
        x->value = v;
        x->color = RED;
        x->size = 1; 
        x->found = 0;
        x->left = x->right = x->parent = NIL;
        return x;
    }
    else if (x != NIL) {
        int cmp = compare(k, x->key);
        if (cmp == 0) x->value = v;
        else if (cmp < 0) {
            x->left = RBinsert(x->left, k, v);
        }
        else {
            x->right = RBinsert(x->right, k, v);
        }

        if (x->right->color == RED)
            x = rotateLeft(x);
        if (x->left->color == RED && x->left->left->color == RED) 
            x = rotateRight(x);
        if (x->left->color == RED && x->right->color == RED) 
            x = colorFlip(x);
    }
    return x;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::insert(keytype k, valuetype v) {
    ++tree_size;
    root = RBinsert(root, k, v);
}

//#####################################################################
//Remove
template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::RBremove(Node* x, keytype k) {
    int cmp = compare(k, x->key);
    if (cmp < 0) {
        if (x->left->color == BLACK && x->left->left->color == BLACK)
            x = moveRedLeft(x);
        x->left = RBremove(x->left, k);
    }
    else {
        if (x->left->color == RED) 
            x = rotateRight(x);
        if (cmp == 0 && (x->right == NIL)) {
            root->found = 1;
            free(x);
            return NIL;
        }
        if (x->right != NIL) {
            if (x->right->color == RED && (x->right->left->color == BLACK)) 
                x = moveRedRight(x);
            if(cmp == 0) {
                root->found = 1;
                x->size = x->size - 1;
                x->key = findMin(x->right)->key;
                x->value = findMin(x->right)->value;
                x->right = deleteMin(x->right);
            }
            else x->right = RBremove(x->right, k);
        }
    }
    return x = fixUp(x);
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::remove(keytype k) {
    int found = 0;
    root = RBremove(root, k);
    if (root->found) {
        root->color = BLACK;
        --tree_size;
        found = root->found;
        root->found = 0;
    }
    return found;
}

//#####################################################################
//Order Statistics
template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::rank_r(keytype k, Node* x) {
    int rank = x->left->size + 1;
    Node* y = x;
    while (y != root) {
        if (y == y->parent->right)
            rank = rank + y->parent->left->size + 1;
        y = y->parent;
    }
    return rank;
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::rank(keytype k) {
    Node* x = root;
    while (x != NIL) {
        int cmp = compare(k, x->key);
        if (cmp == 0) return rank_r(k, x);
        else if (cmp < 0) x = x->left;
        else x = x->right;
    }
    return 0;
}

template <class keytype, class valuetype>
keytype RBTree<keytype, valuetype>::select_r(int pos, Node* x) {
    int rank = x->left->size + 1;
    if (pos == rank)
        return x->key;
    else if (pos < rank )
        return select_r(pos, x->left);
    else return select_r(pos - rank, x->right);
}

template <class keytype, class valuetype>
keytype RBTree<keytype, valuetype>::select(int pos) {
    return select_r(pos, root);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::split(keytype k, RBTree<keytype, valuetype>& T1, RBTree<keytype, valuetype>& T2) {
    
}

template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::size() {
    return tree_size;
}


//#####################################################################
//Traversals
template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::preorder(Node* root) {
    if (root == NIL) return;
    std::cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::preorder() {
    preorder(root);
    std::cout << std::endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::inorder() {
    if (root == NIL) return;
    std::stack<Node*> s;
    Node* curr = root;

    while (curr != NIL || !s.empty()) {
        if (curr != NIL) {
            s.push(curr);
            curr = curr->left;
        }
        else {
            curr = s.top();
            s.pop();
            std::cout << curr->key << " ";
            curr = curr->right;
        }
    }
    std::cout << std::endl;
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::postorder(Node* root) {
    if (root == NIL) return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->key << " ";
}

template <class keytype, class valuetype>
void RBTree<keytype, valuetype>::postorder() {
    postorder(root);
    std::cout << std::endl;
}

//#####################################################################
//RBTree Utility Functions
template <class keytype, class valuetype>
int RBTree<keytype, valuetype>::compare(keytype a, keytype b) {
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::findMin(Node* x) {
    while (x->left != NIL)
        x = x->left;
    return x;
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::deleteMin(Node* x) {
    if (x->left == NIL) 
        return NIL;
    if (x->left->color != RED && x->left->left->color != RED)
        x = moveRedLeft(x);
    x->left = deleteMin(x->left);
    return fixUp(x);
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::rotateLeft(Node* x) {
    Node* tmp = x->right;
    x->right = tmp->left;

    if (tmp->left != NIL)
        tmp->left->parent = x;
    tmp->parent = x->parent;
    if (x->parent == NIL)
        root = tmp;
    else if (x == x->parent->left)
        x->parent->left = tmp;
    else x->parent->right = tmp;
    tmp->left = x;
    x->parent = tmp;

    tmp->color = x->color;
    x->color = RED;

    tmp->size = x->size;
    x->size = x->left->size + x->right->size + 1;
    

    x = tmp;
    x->size = x->left->size + x->right->size + 1;
    //if (x->parent != NIL)
     //   x->parent->size = x->parent->left->size + x->parent->right->size + 1;
  
    return x;
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::rotateRight(Node* x) {
    Node* tmp = x->left;
    x->left = tmp->right;

    if (tmp->right != NIL)
        tmp->right->parent = x;
    tmp->parent = x->parent;
    if (x->parent == NIL)
        root = tmp;
    else if (x == x->parent->right)
        x->parent->right = tmp;
    else 
        x->parent->left = tmp;
    tmp->right = x;
    x->parent = tmp;

    tmp->color = x->color;
    x->color = RED;

    tmp->size = x->size;
    x->size = x->left->left->size ;
    //if (x->parent != NIL)
    //   x->parent->size = x->parent->left->size + x->parent->right->size + 1;

    x = tmp;
    return x;
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::colorFlip(Node* x) {
    x->color = !x->color;
    x->left->color = !x->left->color;
    x->right->color = !x->right->color;
    return x;
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::moveRedLeft(Node* x) {
    x = colorFlip(x);
    if (x->right->left->color == RED) {
        x->right = rotateRight(x->right);
        x = rotateLeft(x);
        x = colorFlip(x);
    }
    return x;
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::moveRedRight(Node* x) {
    x = colorFlip(x);
    if (x->left->left->color == RED) {
        x = rotateRight(x);
        x = colorFlip(x);
    }
    return x;
}

template <class keytype, class valuetype>
typename RBTree<keytype,valuetype>::Node* RBTree<keytype, valuetype>::fixUp(Node* x) {
    if (x->right->color == RED)
        x = rotateLeft(x);
    if (x->left->color == RED && x->left->left->color == RED)
        x = rotateRight(x);
    if (x->left->color == RED && x->right->color == RED)
        x = colorFlip(x);
    return x;
}
