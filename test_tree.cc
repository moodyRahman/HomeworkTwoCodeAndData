// <Your name>
// Main file for Part2(b) of Homework 2.
// Code will compile and run after you have completed sequence_map.h.

#include "avl_tree.h"
#include "bst_tree.h"
#include "sequence_map.h"

#include <iostream>
#include <string>
#include <fstream>
#include <math.h>
using namespace std;

namespace
{

  // @db_filename: an input database filename.
  // @seq_filename: an input sequences filename.
  // @a_tree: an input tree of the type TreeType. It is assumed to be
  //  empty.
  template <typename TreeType>
  void TestTree(const string &db_filename, const string &seq_filename, TreeType &a_tree)
  {

    std::string line;
    std::ifstream db(db_filename);
    std::ifstream seq(seq_filename);

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
          }
          line.erase(0, pos + 1);
        }
      }
    }

    std::cout << a_tree.numberNodes() << std::endl;
    std::cout << ((float)a_tree.internalPathLength() / (float)a_tree.numberNodes()) << std::endl;
    std::cout << ((float)a_tree.internalPathLength() / (float)a_tree.numberNodes()) / std::log2(a_tree.numberNodes()) << std::endl;
    std::cout << "" << std::endl;
    std::cout << "starting the counters" << std::endl;

    std::vector<int> rec_calls;
    int found_sequence = 0;
    int sum = 0;

    if (seq.is_open())
    {
      while (std::getline(seq, line))
      {
        a_tree.arbit_counter = 0;
        if (a_tree.getAcronym(line) != "Not Found")
        {
          found_sequence++;
        }
        rec_calls.push_back(a_tree.arbit_counter);
      }
    }
    std::cout << found_sequence << std::endl;

    for (auto x : rec_calls)
    {
      sum += x;
    }

    std::cout << sum / rec_calls.size() << std::endl;
  }

} // namespace

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    cout << "Usage: " << argv[0] << " <databasefilename> <queryfilename> <tree-type>" << endl;
    return 0;
  }
  const string db_filename(argv[1]);
  const string seq_filename(argv[2]);
  const string param_tree(argv[3]);
  cout << "Input file is " << db_filename << ", and sequences file is " << seq_filename << endl;
  cout << "Type of tree is " << param_tree << endl;
  if (param_tree == "BST")
  {
    BinarySearchTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else if (param_tree == "AVL")
  {
    AvlTree<SequenceMap> a_tree;
    TestTree(db_filename, seq_filename, a_tree);
  }
  else
  {
    cout << "Uknown tree type " << param_tree << " (User should provide BST, or AVL)" << endl;
  }
  return 0;
}
