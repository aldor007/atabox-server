#include <vector>
#include <utility>

#include "utils/LightVector.h"



struct Batch: public std::pair<std::vector<Vector>::iterator, std::vector<Vector>::iterator>
{
    using Iterator = std::vector<Vector>::iterator;
    using Parent = std::pair<Iterator, Iterator>;

    template <typename... Arg> Batch(Arg&& ... arg): Parent(std::forward<Arg>(arg) ...) {}

    Iterator begin() const { 
        return first; 
    }
  
    Iterator end() const {
        return second; 
    }

    size_t size() const {
        return std::distance(first, second); 
    }
    
    bool empty() const  {
        return first == second; 
    }

    Vector& operator[](size_t i) {
        return *(first + i); 
    }

    const Vector& operator[](size_t i) const {
        return *(first + i); 
    }
};