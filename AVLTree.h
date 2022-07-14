// Created by Samina Faheem on 6/23/2022.
// Possibly swap out vector V with a map<V,int>?

#ifndef INC_22SU_SEARCH_ENGINE_AVLTREE_H
#define INC_22SU_SEARCH_ENGINE_AVLTREE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>


using namespace std;

template<typename K, typename V>
class AVLTree {
private:
    class AVLNode{
    public:
        K key;
        map<V,pair<int,int>> value;
        AVLNode* left = nullptr; //Left ptr
        AVLNode* right = nullptr; //Right ptr
        int height =0;

    };
    AVLNode* root; //root of the node
    int treeSize;

    void insert(AVLNode*& node , const K& k , const V& v);
    // 3 traversal / printing
    void PreOrder_print(AVLNode* curr, int level);
    void Inorder_print(AVLNode* curr, int level);
    void Postorder_print(AVLNode* curr, int level);


    int  getheight(AVLNode *curr);
    void assignment(AVLNode*);

    //4 cases where the imbalance could happen
    //Case 1
    void RotateWithLeftChild(AVLNode *&);
    //Case 2
    void DoubleWithLeftChild(AVLNode *&);
    //Case 3
    void DoubleWithRightChild(AVLNode *&);
    //Case 4
    void RotateWithRightChild(AVLNode *&);
    void Balance(AVLNode*& curr);

public:
    //Rule of 3
    AVLTree();
    AVLTree<K,V>(const AVLTree&);
    ~AVLTree();
    AVLTree<K,V>& operator=(const AVLTree<K,V>&);
    void insert(const K&, const V&);
    void print();
    map<V,pair<int,int>> find(const K&);
    void clear(AVLNode* curr);
    int getSize();
};

template <typename K, typename V>
AVLTree<K,V>:: AVLTree(){
    root = nullptr;
    treeSize = 0;
}

template <typename K, typename V>
AVLTree<K,V>::AVLTree(const AVLTree& copy){
    clear(copy);
    if(copy != nullptr) {
        insert(copy);
        AVLTree(copy->left);
        AVLTree(copy->right);
    }
}

template<typename K, typename V>
AVLTree<K,V>::~AVLTree(){
    clear(root);
}

template <typename K, typename V>
AVLTree<K,V>& AVLTree<K,V>::operator=(const AVLTree<K,V> &copy) {
    clear(copy);
    assignment(copy-> root);
    return *this;
}
template <typename K, typename V>
void AVLTree<K,V>:: assignment(AVLNode* copy){
    if(copy != nullptr) {
        for(int i=0; i < copy->value.size() ; i++){
            insert(copy->key,copy->value[i]);
        }
        assignment(copy->left);
        assignment(copy->right);
    }
}

template <typename K, typename V>
void AVLTree<K,V>::insert(const K& k , const V& v){
    insert(root, k ,v);
}

template <typename K, typename V>
void AVLTree<K,V>::print(){
    Inorder_print(root, 0);
}


template <typename K, typename V>
map<V,pair<int,int>> AVLTree<K,V>::find(const K& finding){
    AVLNode* iterator = root;  // node that we will use
    while(iterator != nullptr){
        if(iterator-> key == finding){
            map<V,pair<int,int>> result;
            // loops through all values
            for (auto itr : iterator->value) {
                // create pair where first is times a term appears in a particular article
                // second is size of the map, represents the number of articles that the term appears in
                pair<int,int> intPair(itr.second.first,iterator->value.size());
                result[itr.first] = intPair; // changed from itr.first
            }
            return result;
        }
        else if(iterator-> key < finding){
            iterator = iterator-> right;
        }
        else
        {
            iterator = iterator-> left;
        }
    }
    // if empty
    map<V,pair<int,int>> result;
    return result;
}

template <typename K, typename V>
void AVLTree<K,V>::clear(AVLNode* curr){
    if(curr != nullptr){
        clear(curr->left);
        clear(curr->right);
        delete curr;
        treeSize--;
    }
}

template <typename K, typename V>
void AVLTree<K,V>:: insert(AVLNode*& node , const K& k , const V& v){
    // test swap V& v for maps
    if(node == nullptr){
        node = new AVLNode;
        node->key = k;
        node->value[v].first = 1; // changed from value[v] = 1
        treeSize++;
    }
    else if(node-> key < k ) {
        insert(node->right,k, v);
    }
    else if(k <node->key){
        insert(node->left, k ,v);
    }
    else{
        // if finds value in map(found in the same article), value exists, increment count
        if (node->value.find(v) != node->value.end()) {
            node->value[v].first++;
        } else {
            // new article
            node->value[v].first = 1;
        }
    }
    Balance(node);
}

//preorder - VLR
template <typename K, typename V>
void AVLTree<K,V>::PreOrder_print(AVLNode* curr, int level){
    if(curr != nullptr) {
        cout << setw(level * 2) << curr->key << ": " << curr->value << endl;
        PreOrder_print(curr->left, level + 1);
        PreOrder_print(curr->right, level + 1);
    }
}

//In order - LVR
template <typename K, typename V>
void AVLTree<K,V>::Inorder_print(AVLNode* curr, int level){
    if(curr != nullptr) {
        Inorder_print(curr->left, level + 1);
        cout << setw(level * 2) << curr->key << ": " << curr->value << endl;
        Inorder_print(curr->right, level + 1);
    }
}
//Post LRV
template<typename K, typename V>
void AVLTree<K,V>::Postorder_print(AVLNode *curr, int level) {
    Postorder_print(curr->left, level+1);
    Postorder_print(curr->right, level +1);
    cout << setw(level * 2) << curr->key << ": " << curr->value << endl;
}


template <typename K, typename V>
int AVLTree<K,V>::getheight(AVLNode *curr) {
    if (curr == nullptr) {
        return -1;
    } else {
        return curr->height;
    }
}

//case 1
template <typename K, typename V>
void AVLTree<K,V>::  RotateWithLeftChild(AVLNode *& k1){
    AVLNode* k2 = k1 ->left;  //new node k2 is k1 left child, it would be the note of imbalance
    //rearrange pointers
    //k1 left pointer to k2 right child
    k1->left = k2-> right;
    k2->right = k1;
    k1-> height = max(getheight(k1-> right), getheight(k1->left))+1;
    //update k2
    k2-> height = max(getheight(k2->right), k1->height)+1;
    // to make alpha move into the place of k2
    k1= k2;
}

//Case2
template <typename K, typename V>
void AVLTree<K,V>:: DoubleWithLeftChild(AVLNode *& k1){
    //Case 4
    RotateWithRightChild(k1->left);
    //then case 1
    RotateWithLeftChild(k1);
}
//Case3
template <typename K, typename V>
void AVLTree<K,V>::  DoubleWithRightChild(AVLNode *& k1){
    // first part is case 1
    RotateWithLeftChild(k1->right);
    // then case 4
    RotateWithRightChild(k1);
}

//Case 4
template <typename K, typename V>
void AVLTree<K,V>::  RotateWithRightChild(AVLNode *& k1){
    AVLNode* k2 = k1 ->right;  //new node k2 is k1 right child, it would be the note of imbalance
    //rearrange pointers
    //k1 right pointer to k2 left child
    k1->right = k2-> left;
    k2->left = k1;
    k1-> height = max(getheight(k1-> left), getheight(k1->right))+1;
    //update k2
    k2-> height = max(getheight(k2->left), k1-> height)+1;
    // to make alpha move into the place of k2
    k1= k2;
}

template <typename K, typename V>
void AVLTree<K,V>:: Balance(AVLNode*& curr) {
    if (getheight(curr->left) - getheight(curr->right) > 1) {
        //figure out case 1 or 2
        if (getheight(curr->left->left) > getheight(curr->left->right)){
            RotateWithLeftChild(curr);
        } else {
            DoubleWithLeftChild(curr);
        }
    } else if (getheight(curr->right) - getheight(curr->left) >1 ) {
        //case 4
        if (getheight(curr->right->left) > getheight(curr->right->right)) {
            DoubleWithRightChild(curr);
        } else {
            RotateWithRightChild(curr);
        }
    }
    curr->height = max(getheight(curr->left), getheight(curr->right)) + 1;
}

template <typename K, typename V>
int AVLTree<K,V>::getSize() {
    return treeSize;
}

#endif //INC_22SU_SEARCH_ENGINE_AVLTREE_H