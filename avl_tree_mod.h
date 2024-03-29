#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// AvlTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x (unimplemented)
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class AvlTree
{
public:
    AvlTree() : root{nullptr}
    {
    }

    AvlTree(const AvlTree &rhs) : root{nullptr}
    {
        root = clone(rhs.root);
    }

    AvlTree(AvlTree &&rhs) : root{rhs.root}
    {
        rhs.root = nullptr;
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    /**
     * Deep copy.
     */
    AvlTree &operator=(const AvlTree &rhs)
    {
        AvlTree copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    /**
     * Move.
     */
    AvlTree &operator=(AvlTree &&rhs)
    {
        std::swap(root, rhs.root);

        return *this;
    }

    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMin() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMin(root)->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable &findMax() const
    {
        if (isEmpty())
            throw UnderflowException{};
        return findMax(root)->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains(const Comparable &x) const
    {
        return contains(x, root);
    }

    bool contains(std::string x)
    {
        return this->getAcronym(x) != "Not Found";
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty() const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree() const
    {
        if (isEmpty())
            cout << "Empty tree" << endl;
        else
            printTree(root);
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty()
    {
        makeEmpty(root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(const Comparable &x)
    {
        insert(x, root);
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert(Comparable &&x)
    {
        insert(std::move(x), root);
    }

    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove(Comparable &x)
    {
        remove(x, root);
    }

    std::string getAcronym(std::string sequence)
    {
        auto x = getAcronym(sequence, root);
        if (x == nullptr)
        {
            return "Not Found";
        }
        else
        {
            std::string out;
            auto acros = x->element.enzyme_acronyms_;
            for (auto z : acros)
            {
                out += z;
                out += " ";
            }

            return out + " ";
        }
    }


    /**
     * @brief private struct for an internally used AvlNode
     * 
     */
    struct AvlNode
    {
        Comparable element;
        AvlNode *left;
        AvlNode *right;
        int height;

        AvlNode(const Comparable &ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{ele}, left{lt}, right{rt}, height{h} {}

        AvlNode(Comparable &&ele, AvlNode *lt, AvlNode *rt, int h = 0)
            : element{std::move(ele)}, left{lt}, right{rt}, height{h} {}
    };
    int arbit_counter = 0;
    int rm_counter = 0;
    AvlNode *root;


    /**
     * @brief wrapper for recursive getNode
     * 
     * 
     * @param seq 
     * @return Comparable 
     */
    Comparable getNode(std::string seq)
    {
        return getNode(seq, root)->element;
    }


    /**
     * @brief returns itself if the requested sequence is found, otherwise
     * searches it's children nodes
     * 
     * @param sequence 
     * @param node 
     * @return AvlNode* 
     */
    AvlNode *getNode(std::string sequence, AvlNode *node)
    {
        arbit_counter++;
        if (node == nullptr)
        {
            return nullptr;
        }
        if (node->element.recognition_sequence_ == sequence)
        {
            return node;
        }
        else
        {
            if (node->element.recognition_sequence_ < sequence)
            {
                return getNode(sequence, node->right);
            }
            return getNode(sequence, node->left);
        }
    }


    /**
     * @brief wrapper for recursice internalPathLength
     * 
     * @return int 
     */
    int internalPathLength()
    {
        return internalPathLength(this->root, 0);
    }


    /**
     * @brief 
     * 
     * @param node 
     * @param pathdist 
     * @return int 
     */
    int internalPathLength(AvlNode *node, int pathdist)
    {
        arbit_counter++;
        if (node == nullptr)
        {
            return 0;
        }
        return pathdist + internalPathLength(node->left, pathdist + 1) + internalPathLength(node->right, pathdist + 1);
    }


    /**
     * @brief wrapper for recursive numberNodes
     * 
     * 
     */
    int numberNodes()
    {
        return numberNodes(this->root);
    }


    /**
     * @brief calculates the number of children nodes, and adds one for the parent
     * 
     * @param node 
     * @return int 
     */
    int numberNodes(AvlNode *node)
    {
        arbit_counter++;
        if (node == nullptr)
        {
            return 0;
        }

        int lsum, rsum;

        lsum = numberNodes(node->left);
        rsum = numberNodes(node->right);

        return 1 + lsum + rsum;
    }


    /**
     * @brief wrapper for the height
     * 
     * 
     */
    int getHeight()
    {
        return getHeight(this->root);
    }


    /**
     * @brief Calculate the total height of a tree
     * 
     * @param node 
     * @return int 
     */
    int getHeight(AvlNode *node)
    {
        arbit_counter++;
        if (node == nullptr)
        {
            return 0;
        }

        return 1 + std::max(getHeight(node->left), getHeight(node->right));
    }


    /**
     * @brief recursive search function for acronyms 
     * 
     * @param sequence 
     * @param node 
     * @return AvlNode* 
     */
    AvlNode *getAcronym(std::string sequence, AvlNode *node)
    {
        this->arbit_counter++;

        if (node == nullptr)
        {
            return nullptr;
        }

        if (node->element.recognition_sequence_ == sequence)
        {
            return node;
        }

        else
        {
            if (node->element.recognition_sequence_ < sequence)
            {
                return getAcronym(sequence, node->right);
            }

            return getAcronym(sequence, node->left);
        }
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(const Comparable &x, AvlNode *&t)
    {
        if (t == nullptr)
            t = new AvlNode{x, nullptr, nullptr};
        else if (x < t->element)
            insert(x, t->left);
        else if (t->element < x)
            insert(x, t->right);
        else
        {
            t->element.Merge(x);
        }
        balance(t);
    }

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert(Comparable &&x, AvlNode *&t)
    {
        if (t == nullptr)
            t = new AvlNode{std::move(x), nullptr, nullptr};
        else if (x < t->element)
            insert(std::move(x), t->left);
        else if (t->element < x)
            insert(std::move(x), t->right);
        else
        {
            t->element.Merge(x);
        }
        balance(t);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove(Comparable &x, AvlNode *&t)
    {
        rm_counter+=1;
        if (t == nullptr)
            return; // Item not found; do nothing

        if (x < t->element)
            remove(x, t->left);
        else if (t->element < x)
            remove(x, t->right);
        else if (t->left != nullptr && t->right != nullptr) // Two children
        {
            rm_counter += 1;
            t->element = findMin(t->right)->element;
            remove(t->element, t->right);
        }
        else
        {
            AvlNode *oldNode = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete oldNode;
        }

        balance(t);
    }

    static const int ALLOWED_IMBALANCE = 1;

    // Assume t is balanced or within one of being balanced
    void balance(AvlNode *&t)
    {
        if (t == nullptr)
            return;

        if (height(t->left) - height(t->right) > ALLOWED_IMBALANCE)
        {
            if (height(t->left->left) >= height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
        }
        else if (height(t->right) - height(t->left) > ALLOWED_IMBALANCE)
        {
            if (height(t->right->right) >= height(t->right->left))
                rotateWithRightChild(t);
            else
                doubleWithRightChild(t);
        }
        t->height = max(height(t->left), height(t->right)) + 1;
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    AvlNode *findMin(AvlNode *t)
    {
        if (t == nullptr)
            return nullptr;
        if (t->left == nullptr)
            return t;
        return findMin(t->left);
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    AvlNode *findMax(AvlNode *t)
    {
        if (t != nullptr)
            while (t->right != nullptr)
                t = t->right;
        return t;
    }

    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the tree.
     */
    bool contains(const Comparable &x, AvlNode *t) const
    {
        if (t == nullptr)
            return false;
        else if (x < t->element)
            return contains(x, t->left);
        else if (t->element < x)
            return contains(x, t->right);
        else
            return true; // Match
    }
    /****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, AvlNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty(AvlNode *&t)
    {
        if (t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree(AvlNode *t) const
    {
        if (t != nullptr)
        {
            printTree(t->left);
            cout << t->element << endl;
            printTree(t->right);
        }
    }

    /**
     * Internal method to clone subtree.
     */
    AvlNode *clone(AvlNode *t) const
    {
        if (t == nullptr)
            return nullptr;
        else
            return new AvlNode{t->element, clone(t->left), clone(t->right), t->height};
    }
    // Avl manipulations
    /**
     * Return the height of node t or -1 if nullptr.
     */
    int height(AvlNode *t) const
    {
        return t == nullptr ? -1 : t->height;
    }

    int max(int lhs, int rhs) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    /**
     * Rotate binary tree node with left child.
     * For AVL trees, this is a single rotation for case 1.
     * Update heights, then set new root.
     */
    void rotateWithLeftChild(AvlNode *&k2)
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left), height(k2->right)) + 1;
        k1->height = max(height(k1->left), k2->height) + 1;
        k2 = k1;
    }

    /**
     * Rotate binary tree node with right child.
     * For AVL trees, this is a single rotation for case 4.
     * Update heights, then set new root.
     */
    void rotateWithRightChild(AvlNode *&k1)
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        k2->height = max(height(k2->right), k1->height) + 1;
        k1 = k2;
    }

    /**
     * Double rotate binary tree node: first left child.
     * with its right child; then node k3 with new left child.
     * For AVL trees, this is a double rotation for case 2.
     * Update heights, then set new root.
     */
    void doubleWithLeftChild(AvlNode *&k3)
    {
        AvlNode *l = k3->left;
        AvlNode *r = l->right;
        l->right = r->left;
        r->left = l;
        k3->left = r->right;
        r->right = k3;

        //re-adjust the height after changing the pointers
        l->height = max(height(l->left), height(l->right)) + 1;
        k3->height = max(height(k3->left), height(k3->right)) + 1;
        r->height = max(l->height, k3->height) + 1;

        //set the head to y
        k3 = r;
    }

    /**
     * Double rotate binary tree node: first right child.
     * with its left child; then node k1 with new right child.
     * For AVL trees, this is a double rotation for case 3.
     * Update heights, then set new root.
     */
    void doubleWithRightChild(AvlNode *&k1)
    {
        AvlNode *r = k1->right;
        AvlNode *l = r->left;
        r->left = l->right;
        l->right = r;
        k1->right = l->left;
        l->left = k1;

        //re-adjust the height after changing the pointers
        k1->height = max(height(k1->left), height(k1->right)) + 1;
        r->height = max(height(r->left), height(r->right)) + 1;
        l->height = max(k1->height, r->height) + 1;

        //set the head to x
        k1 = l;
    }
};

#endif
