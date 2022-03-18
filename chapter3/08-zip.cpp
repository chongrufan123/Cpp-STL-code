// 08-zip.cpp
// 构建 zip 迭代适配器

#include <iostream>
#include <vector>
#include <numeric>

class zip_iterator{
    using it_type = std::vector<double>::iterator;  
    it_type it1;
    it_type it2;
public:
    zip_iterator(it_type iterator1, it_type iterator2) : it1{iterator1}, it2{iterator2} {}
    zip_iterator & operator++() {
        ++it1;
        ++it2;
        return *this;
    }
    bool operator!=(const zip_iterator& o) const {
        return it1 != o.it1 && it2 != o.it2;
    }
    bool operator==(const zip_iterator & o) const{
        return !operator!=(o);
    }
    std::pair<double, double> operator*() const {
        return {*it1, *it2};
    }
};