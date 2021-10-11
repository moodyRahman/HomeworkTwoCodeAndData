
Moududur Rahman
CSCI 335
Project 2

TREE FUNCTIONS IMPLEMENTED
the following are all the methods and changes I implemented for each of the tree's 
and the methodology behind them

std::string getAcronym(std::string)
    I made this function to maximize integration stability with the testing platform, 
    so the string processing of the resultant vector is done in this call and returns
    a string meant to be immediately displayed.

int arbit_counter
    A variable that gets reset to 0 externally every time a recursive call wants
    to be counted. Consider it more readable than passing the count variable into 
    every recursive call

Comparable getNode(std::string)
    This is a more raw tree accessor function, that returns the node itself and
    can be manupilated however desired

int internalPathLength()
    A clean function that sums up all the heights of every node

int numberNodes()
    Returns total number of nodes in the tree

int getHeight()
    Returns height of tree



Any further documentation on functions can be viewed in the inline documentation