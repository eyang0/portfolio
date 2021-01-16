#include <iostream>
#include <map>
#include "bst.h"
#include "avlbst.h"

using namespace std;


int main(int argc, char *argv[])
{
    // Binary Search Tree tests
    BinarySearchTree<char,int> bt;
    bt.print();
    bt.insert(std::make_pair('a',1));
    bt.print();
    bt.insert(std::make_pair('c',2));
    bt.insert(std::make_pair('b',2));
    bt.print();
    
    cout << "Binary Search Tree contents:" << endl;
    for(AVLTree<char,int>::iterator it = bt.begin(); it != bt.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(bt.find('b') != bt.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    bt.remove('b');
    bt.print();



    // AVL Tree Tests
    cout<< "Start of AVLTree Tests" << endl;
    AVLTree<char,int> at;
    at.insert(std::make_pair('a',1));
    at.print();
    at.insert(std::make_pair('c',2));
    at.insert(std::make_pair('c',3));
    at.insert(std::make_pair('l',2));
    at.insert(std::make_pair('v',2));
    at.insert(std::make_pair('f',2));
    at.insert(std::make_pair('e',2));
    at.print();
    at.insert(std::make_pair('b',2));
    at.print();

    cout << "\nAVLTree contents:" << endl;
    for(AVLTree<char,int>::iterator it = at.begin(); it != at.end(); ++it) {
        cout << it->first << " " << it->second << endl;
    }
    if(at.find('b') != at.end()) {
        cout << "Found b" << endl;
    }
    else {
        cout << "Did not find b" << endl;
    }
    cout << "Erasing b" << endl;
    at.remove('b');
    at.print();
    at.remove('c');
    at.remove('f');
    
    return 0;
}
