// <Your name>
// Main file for Part2(a) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace
{

  // @db_filename: an input filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void QueryTree(const string &db_filename, TreeType &a_tree)
  {
    // Code for running Part2(a)
    // Parse input file @db_filename and feel tree @a_tree
    // Then prompt the user for exactly three strings (do a loop) and
    // provide the results of find() as described in the assignment.

    std::string line;
    std::ifstream db(db_filename);

    if (db.is_open())
    {
      for (int x = 0; x < 10; x++)
      {
        std::getline(db, line);
      }

      while (std::getline(db, line))
      {
        std::size_t pos = 0;

        bool first = true;
        std::string enz_acro;
        std::string reco_seq;

        while ((pos = line.find("/")) != std::string::npos)
        {
          std::string token = line.substr(0, pos);
          if (token.length() > 0 && first)
          {
            enz_acro = token;
            first = false;
          }
          else if (token.length() > 0)
          {
            a_tree.insert(SequenceMap(enz_acro, token));
            // std::cout << enz_acro << "    " << token << std::endl;
          } 
          line.erase(0, pos + 1);
        }
      }
    }
  }

  template <typename TreeType>
  void readCin(TreeType a_tree)
  {
    std::string line;
    while (std::getline(std::cin, line))
    {
      std::cout << a_tree.getAcronym(line) << std::endl;
    }
  }

} // namespace

int main(int argc, char **argv)
{
  if (argc != 3)
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string param_tree(argv[2]);
  cout << "Input filename is " << db_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST")
  {
    BinarySearchTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
    readCin(a_tree);
  }
  else if (param_tree == "AVL")
  {
    AvlTree<SequenceMap> a_tree;
    QueryTree(db_filename, a_tree);
    readCin(a_tree);
  }
  else
  {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
