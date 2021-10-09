#include "sequence_map.h"
#include <iostream>

SequenceMap::SequenceMap(std::string &a_rec_seq, std::string &an_enz_acro)
{
    this->recognition_sequence_ = a_rec_seq;
    this->enzyme_acronyms_.push_back(an_enz_acro);
}

bool SequenceMap::operator<(const SequenceMap &rhs)
{
    return this->recognition_sequence_ < rhs.recognition_sequence_;
}

void SequenceMap::Merge(const SequenceMap &rhs)
{
    for (auto x : rhs.enzyme_acronyms_)
    {
        this->enzyme_acronyms_.push_back(x);
    }
}

std::ostream& operator<<(std::ostream& os, const SequenceMap& dt)
{
    os << dt.recognition_sequence_ << "   :";
    for (auto x: dt.enzyme_acronyms_)
    {
        os << x << ",  ";
    }
    return os;
}
