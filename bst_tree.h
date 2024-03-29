#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    bool contains(std::string x)
    {
        return this->getAcronym(x) != "Not Found";
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x )
    {
        insert( x, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x )
    {
        insert( std::move( x ), root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( Comparable & x )
    {
        remove( x, root );
    }

    
    /**
     * @brief get a string of the corresponding acronyms to a sequence
     * 
     * @param sequence 
     * @return std::string 
     */
    std::string getAcronym( std::string sequence )
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
            for (auto z:acros)
            {
                out += z;
                out += " ";
            }

            return out + " ";
        }
    }


    /**
     * @brief private struct for an internally used BinaryNode
     * 
     */
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };
    int arbit_counter = 0;
    int rm_counter = 0;
    BinaryNode *root;


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
     * @return BinaryNode* 
     */
    BinaryNode *getNode(std::string sequence, BinaryNode *node)
    {
        arbit_counter++;
        if (node==nullptr)
        {
            return nullptr;
        }
        if ( node->element.recognition_sequence_ == sequence )
        {
            return node;
        }
        else
        {
            if (node->element.recognition_sequence_ < sequence )
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
    int internalPathLength( BinaryNode *node , int pathdist)
    {
        arbit_counter++;
        if (node == nullptr)
        {
            return 0;
        }
        return pathdist + internalPathLength(node->left, pathdist+1) + internalPathLength(node->right, pathdist + 1);
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
    int numberNodes( BinaryNode *node )
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
    int getHeight( BinaryNode *node )
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
     * @return BinaryNode* 
     */
    BinaryNode* getAcronym( std::string sequence, BinaryNode *node )
    {
        arbit_counter++;
        if (node==nullptr)
        {
            return nullptr;
        }

        if ( node->element.recognition_sequence_ == sequence )
        {
            return node;
        }
        
        else
        {
            if (node->element.recognition_sequence_ < sequence )
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
    void insert( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );
        else
        {
            t->element.Merge(x);
        }
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, BinaryNode * & t )
    {
        if( t == nullptr )
            t = new BinaryNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );
        else
        {
            t->element.Merge(x);
        }   // Duplicate; do nothing
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( Comparable & x, BinaryNode * & t )
    {
        rm_counter+=1;
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            rm_counter+=1;
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t )
    {

        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t )
    {
        arbit_counter++;
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
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
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
        if( t != nullptr )
        {
            printTree( t->left, out );
            out << t->element << endl;
            printTree( t->right, out );
        }
    }

    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        else
            return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
};

#endif
