#ifndef SEQUENCE_MAP_H
#define SEQUENCE_MAP_H
#include <iostream>
#include <vector>

using namespace std;

class SequenceMap
{
public:
    string recognition_sequence_;
    vector<string> enzyme_acronyms_;

    SequenceMap(const SequenceMap &rhs) = default;
    SequenceMap &operator=(SequenceMap &&rhs) = default;
    ~SequenceMap() = default;
    SequenceMap &operator=(const SequenceMap &rhs) = default;
    SequenceMap(SequenceMap &&rhs) = default;


    /**
     * @brief Construct a new Sequence Map object
     * 
     * @param an_enz_acro the enzyme acronym 
     * @param a_rec_seq the corresponing sequence
     */
    SequenceMap(string &an_enz_acro, string &a_rec_seq)
    {
        this->recognition_sequence_ = a_rec_seq;
        this->enzyme_acronyms_.push_back(an_enz_acro);
    };

    /**
     * @brief the < implementation to fulfill Comparable
     * 
     * @param rhs other SequenceMap to compare against
     * @return bool
     */
    bool operator<(const SequenceMap &rhs)
    {
        return this->recognition_sequence_ < rhs.recognition_sequence_;
    };

    /**
     * @brief Stream SequenceMap directly to an osstream
     * 
     * @param os 
     * @param dt 
     * @return ostream& 
     */
    friend ostream &operator<<(ostream &os, const SequenceMap &dt)
    {
        os << dt.recognition_sequence_ << "   :";
        for (auto x : dt.enzyme_acronyms_)
        {
            os << x << ",  ";
        }
        return os;
    };

    /**
     * @brief Merges this SequenceMap with another with the same sequence
     * 
     * @param rhs 
     */
    void Merge(const SequenceMap &rhs)
    {
        for (auto x : rhs.enzyme_acronyms_)
        {
            this->enzyme_acronyms_.push_back(x);
        }
    };
};

#endif