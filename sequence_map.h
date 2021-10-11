#pragma once
#include <iostream>
#include <vector>

class SequenceMap
{
    public:

        SequenceMap(std::string &an_enz_acro, std::string &a_rec_seq)
        {
            this->recognition_sequence_ = a_rec_seq;
            this->enzyme_acronyms_.push_back(an_enz_acro);
        };

        bool operator<(const SequenceMap &rhs)
        {
            return this->recognition_sequence_ < rhs.recognition_sequence_;
        };

        friend std::ostream &operator<<(std::ostream &os, const SequenceMap &dt)
        {
            os << dt.recognition_sequence_ << "   :";
            for (auto x : dt.enzyme_acronyms_)
            {
                os << x << ",  ";
            }
            return os;
        };

        void Merge(const SequenceMap &rhs)
        {
            for (auto x : rhs.enzyme_acronyms_)
            {
                this->enzyme_acronyms_.push_back(x);
            }
        };
    private:
        std::string recognition_sequence_;
        std::vector<std::string> enzyme_acronyms_;
};
