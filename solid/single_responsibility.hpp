#ifndef SINGLE_RESPONSIBILITY_HPP
#define SINGLE_RESPONSIBILITY_HPP

#include <iostream>
#include <string>
#include <vector>
#include <boost/lexical_cast.hpp>
#include <fstream>

namespace solid::single_responsibility {
struct Journal {
    std::string title;
    std::vector<std::string> entries;

    explicit
    Journal(std::string const &&title)
        : title { std::move(title) } {/*Nill*/}

    void add_new_entry(std::string const &&new_entry) {
        static uint8_t counter = 1;
        entries.push_back( boost::lexical_cast<std::string>(counter++) + ") " + new_entry );
    }
};

struct persistance_manager {
    static void save(std::string const &&filename,
                     Journal const &journal) {
        std::ofstream ofs(filename);
        for (const auto& o : journal.entries)
            ofs << o << '\n';

        std::cout << "saved!" << std::endl;
    }
};

void main() {
    Journal j("Diary");
    j.add_new_entry("I ate bug!");
    j.add_new_entry("I cried today.");

    persistance_manager::save("diary.txt", j);
}
}

#endif // SINGLE_RESPONSIBILITY_HPP
