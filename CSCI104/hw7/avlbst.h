#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item);
    virtual void remove(const Key& key);
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    bool isLeftChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p);
    bool isRightChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p);
    void rotateLeft(AVLNode<Key,Value>* n);
    void rotateRight(AVLNode<Key,Value>* n);
    void insertFix(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p);
    void removeFix(AVLNode<Key,Value>* n, char diff);


};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    if(BinarySearchTree<Key, Value>::root_ == NULL) //if tree is empty
    {
        AVLNode<Key, Value>* new_root = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
        BinarySearchTree<Key, Value>::root_ = new_root;
    }
    else
    {
        Node<Key, Value> *to_cast = BinarySearchTree<Key, Value>::root_;
        AVLNode<Key, Value> *curr = (AVLNode<Key, Value>*) to_cast;

        while(curr != NULL)
        {
            if(new_item.first > curr->getKey()) 
            {
                if(curr->getRight() == NULL)
                {
                    AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
                    curr->setRight(temp); //inserting on the right
                    curr->updateBalance(1);

                    if(curr->getBalance() == 1 || curr->getBalance() == -1)
                    {
                        insertFix(temp, curr);
                    }
                    break;
                }
                curr = curr->getRight();
            }
            else if(new_item.first < curr->getKey())
            {
                if(curr->getLeft() == NULL)
                {
                    AVLNode<Key, Value>* temp = new AVLNode<Key, Value>(new_item.first, new_item.second, curr);
                    curr->setLeft(temp); //inserting on the left
                    curr->updateBalance(-1);

                    if(curr->getBalance() == 1 || curr->getBalance() == -1)
                    {
                        insertFix(temp, curr);
                    }
                    break;
                }
                curr = curr->getLeft();
            }
            else //key already exists, so update
            {
                curr->setValue(new_item.second);
                break;
            }
        }
    }
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with the predecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    Node<Key, Value> *to_cast = BinarySearchTree<Key, Value>::root_;
    AVLNode<Key, Value> *curr = (AVLNode<Key, Value>*) to_cast;
    char diff = 0;

    //search for node first
    while(curr != NULL)
    {
        if(key > curr->getKey())
        {
            curr = curr->getRight();
        }
        else if(key < curr->getKey())
        {
            curr = curr->getLeft();
        }
        else //if keys are equal, we remove
        {
            if(curr->getLeft() == NULL && curr->getRight() == NULL) //if it is a leaf
            {
                if(curr == BinarySearchTree<Key, Value>::root_) //if it is the root that is the only node
                {
                    delete curr;
                    BinarySearchTree<Key, Value>::root_ = NULL;
                    return;
                }
                if(isLeftChild(curr, curr->getParent())) //if it was a left child
                {
                    curr->getParent()->setLeft(NULL);
                    diff = 1;
                }
                else //if it was a right child
                {
                    curr->getParent()->setRight(NULL);
                    diff = -1;
                }
            }
            else if(curr->getLeft() != NULL && curr->getRight() != NULL) //if node has 2 children
            {
                Node<Key, Value>* to_cast_pred = BinarySearchTree<Key, Value>::predecessor(curr);
                AVLNode<Key, Value> *pred = (AVLNode<Key, Value>*) to_cast_pred;

                //swap with pred to make curr a leaf node or node with 1 child
                AVLTree<Key, Value>::nodeSwap(curr, pred);

                if(isLeftChild(curr, curr->getParent())) //if it is now a left child
                {
                    if(curr->getLeft() != NULL) //promote if necessary
                    {
                        curr->getParent()->setLeft(curr->getLeft());
                        curr->getLeft()->setParent(curr->getParent());
                    }
                    else
                    {
                        curr->getParent()->setLeft(NULL);
                    }
                    diff = 1;
                }
                else //if it is now a right child
                {
                    //promote if necessary
                    if(curr->getLeft() != NULL)
                    {
                        curr->getParent()->setRight(curr->getLeft());
                        curr->getLeft()->setParent(curr->getParent());
                    }
                    else
                    {
                        curr->getParent()->setRight(NULL);
                    }
                    diff = -1;
                }
            }
            else //if it has 1 child
            {
                if(curr == BinarySearchTree<Key, Value>::root_) //if node was the root
                {
                    if(curr->getLeft() != NULL) //if the child is a left child
                    {
                        curr->getLeft()->setParent(NULL);
                        BinarySearchTree<Key, Value>::root_ = curr->getLeft();
                    }
                    else //if the child is a right child
                    {
                        curr->getRight()->setParent(NULL);
                        BinarySearchTree<Key, Value>::root_ = curr->getRight();
                    }
                    delete curr;
                    break;
                }
                if(isLeftChild(curr, curr->getParent())) //if node was a left child
                {
                    if(curr->getLeft() != NULL) //if the child is a left child
                    {
                        curr->getLeft()->setParent(curr->getParent());
                        curr->getParent()->setLeft(curr->getLeft());
                    }
                    else //if the child is a right child
                    {
                        curr->getRight()->setParent(curr->getParent());
                        curr->getParent()->setLeft(curr->getRight());
                    }
                    diff = 1;
                }
                else //if node was a right child
                {
                    if(curr->getLeft() != NULL) //if the child is a left child
                    {
                        curr->getLeft()->setParent(curr->getParent());
                        curr->getParent()->setRight(curr->getLeft());
                    }
                    else //if the child is a right child
                    {
                        curr->getRight()->setParent(curr->getParent());
                        curr->getParent()->setRight(curr->getRight());
                    }
                    diff = -1;
                }
            }
            AVLNode<Key, Value> *parent = curr->getParent();
            delete curr;
            removeFix(parent, diff);
            break;
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    char tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


//helper function to check if n is left child
template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p)
{  
    if(p->getLeft() != NULL)
    {
        return p->getLeft() == n;
    }
    return false;
}

//helper function to check if n is right child
template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p)
{
    if(p->getRight() != NULL)
    {
        return p->getRight() == n;
    }
    return false;
}



//helper function to rotate left
template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* n_parent = n->getParent();
    AVLNode<Key,Value>* right_child = n->getRight();

    //set new parent of right child
    right_child->setParent(n_parent);
    if(n_parent != NULL)
    {
        if(isLeftChild(n, n_parent))
        {
            n_parent->setLeft(right_child);
        }
        else
        {
            n_parent->setRight(right_child);
        }
    }
    else //if n was the root node
    {
        BinarySearchTree<Key, Value>::root_ = right_child;
    }

    //reparenting right child's left child
    AVLNode<Key,Value>* temp = right_child->getLeft();
    n->setRight(temp);
    if(temp != NULL)
    {
        temp->setParent(n);
    }

    n->setParent(right_child);
    right_child->setLeft(n);
}

//helper function to rotate right
template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n)
{
    AVLNode<Key,Value>* n_parent = n->getParent();
    AVLNode<Key,Value>* left_child = n->getLeft();

    //set new parent of left child
    left_child->setParent(n_parent);
    if(n_parent != NULL)
    {
        if(isLeftChild(n, n_parent))
        {
            n_parent->setLeft(left_child);
        }
        else
        {
            n_parent->setRight(left_child);
        }
    }
    else //if n was the root node
    {
        BinarySearchTree<Key, Value>::root_ = left_child;
    }

    //reparenting left child's right child
    AVLNode<Key,Value>* temp = left_child->getRight();
    n->setLeft(temp);
    if(temp != NULL)
    {
        temp->setParent(n);
    }

    n->setParent(left_child);
    left_child->setRight(n);
}


//insertFix helper function
template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* n, AVLNode<Key,Value>* p)
{
    AVLNode<Key,Value>* grandparent = p->getParent();
    if(p == NULL || grandparent == NULL) //do nothing if the parent is the root
    {
        return;
    }

    if(isLeftChild(p, grandparent)) //if p is left child of grandparent
    {
        grandparent->updateBalance(-1);
        if(grandparent->getBalance() == 0)
        {
            return;
        }
        else if(grandparent->getBalance() == -1)
        {
            //recurse upward
            insertFix(p, grandparent);
        }
        else //if it equals -2
        {
            if(isLeftChild(n, p)) //zig-zig
            {
                rotateRight(grandparent);
                p->setBalance(0);
                grandparent->setBalance(0);
            }
            else //zig-zag
            {
                rotateLeft(p);
                rotateRight(grandparent);
                if(n->getBalance() == -1)
                {
                    p->setBalance(0);
                    grandparent->setBalance(1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0)
                {
                    p->setBalance(0);
                    grandparent->setBalance(0);
                    n->setBalance(0);
                }
                else //if balance of n is 1
                {
                    p->setBalance(-1);
                    grandparent->setBalance(0);
                    n->setBalance(0);
                }
            }
            return; //stop recursing after a fix is made
        }
    }
    else //if p is right child
    {
        grandparent->updateBalance(1);
        if(grandparent->getBalance() == 0)
        {
            return;
        }
        else if(grandparent->getBalance() == 1)
        {
            //recurse upward
            insertFix(p, grandparent);
        }
        else //if it equals 2
        {
            if(isRightChild(n, p)) //zig-zig
            {
                rotateLeft(grandparent);
                p->setBalance(0);
                grandparent->setBalance(0);
            }
            else //zig-zag
            {
                rotateRight(p);
                rotateLeft(grandparent);
                if(n->getBalance() == 1)
                {
                    p->setBalance(0);
                    grandparent->setBalance(-1);
                    n->setBalance(0);
                }
                else if(n->getBalance() == 0)
                {
                    p->setBalance(0);
                    grandparent->setBalance(0);
                    n->setBalance(0);
                }
                else //if balance of n is -1
                {
                    p->setBalance(1);
                    grandparent->setBalance(0);
                    n->setBalance(0);
                }
            }
            return; //stop recursing after a fix is made
        }
    }
}


//removeFix helper function
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* n, char diff)
{
    if(n == NULL)
    {
        return;
    }

    AVLNode<Key,Value>* p = n->getParent();
    char nextdiff = 0;
    if(p != NULL)
    {
        if(isLeftChild(n, p))
        {
            nextdiff = 1;
        }
        else
        {
            nextdiff = -1;
        }
    }

    if(diff == -1)
    {
        if(n->getBalance()+diff == -2) //found an imbalance
        {
            AVLNode<Key,Value>* c = n->getLeft(); //the taller child of n
            if(c->getBalance() == -1) //zig zig
            {
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, nextdiff);
            }
            else if(c->getBalance() == 0) //zig zig
            {
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
                //balanced now
            }
            else //if balance is +1, zig zag
            {
                AVLNode<Key,Value>* grand_c = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if(grand_c->getBalance() == 1)
                {
                    n->setBalance(0);
                    c->setBalance(-1);
                    grand_c->setBalance(0);
                }
                else if(grand_c->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    grand_c->setBalance(0);
                }
                else //grand_c balance was -1
                {
                    n->setBalance(1);
                    c->setBalance(0);
                    grand_c->setBalance(0);
                }
                removeFix(p, nextdiff);
            }
        }
        else if(n->getBalance()+diff == -1)
        {
            n->setBalance(-1);
        }
        else //if it is 0
        {
            n->setBalance(0);
            removeFix(p, nextdiff);
        }
    }
    else //if diff is 1
    {
        if(n->getBalance()+diff == 2) //found an imbalance
        {
            AVLNode<Key,Value>* c = n->getRight(); //the taller child of n
            if(c->getBalance() == 1) //zig zig
            {
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, nextdiff);
            }
            else if(c->getBalance() == 0) //zig zig
            {
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
                //balanced now
            }
            else //if balance is -1, zig zag
            {
                AVLNode<Key,Value>* grand_c = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                if(grand_c->getBalance() == -1)
                {
                    n->setBalance(0);
                    c->setBalance(1);
                    grand_c->setBalance(0);
                }
                else if(grand_c->getBalance() == 0)
                {
                    n->setBalance(0);
                    c->setBalance(0);
                    grand_c->setBalance(0);
                }
                else //grand_c balance was 1
                {
                    n->setBalance(-1);
                    c->setBalance(0);
                    grand_c->setBalance(0);
                }
                removeFix(p, nextdiff);
            }
        }
        else if(n->getBalance()+diff == 1)
        {
            n->setBalance(1);
        }
        else //if it is 0
        {
            n->setBalance(0);
            removeFix(p, nextdiff);
        }
    }
}



#endif
