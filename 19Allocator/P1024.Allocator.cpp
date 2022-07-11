#include <iostream>
#include <memory>
#include <string>
using namespace std;

// alloctor:
// interfaces:
//      allocate(num)
//      construct(p, args...)
//      destroy(p)
//      deallocate(p, num)

// auxiliary functions/algorithms for unintilized memory:
//      uninitialized_fill(beg, end, val)
//      uninitialized_fill_n(beg, num, val)
//      uninitialized_copy(beg, end, val)
//      uninitialized_copy_n(beg, num, val)

// iterator for uninitialized memory:
//      raw_storage_iterator<OutputIt, ElemType> // typically <T*, T>

// get a temporary buffer(uninitialized memory):
//      get_temporary_buffer() to allocate
//      return_temprary_buffer() to deallocate
//      they are not exception-safe, so it's almost deprecated in practice.

// implement an allocator class just like std::alloctor

template<typename T>
class MyAlloc
{
public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    MyAlloc() noexcept
    {
        // no state to initialize
    }
    template<typaname U>
    MyAlloc(const MyAlloc<U>&) noexcept
    {
        // no state to copy
    }
    T* allocate(size_type num)
    {
        return static_cast<T*>(::operator new(num * sizeof(T)));
    }
    void deallocate(T* p, std::size_t num)
    {
        ::operator delete(p);
    }
};

template<typename T1, typename T2>
bool operator==(const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept
{
    return true;
}

template<typename T1, typename T2>
bool operator!=(const MyAlloc<T1>&, const MyAlloc<T2>&) noexcept
{
    return false;
}

int main(int argc, char const *argv[])
{
    
    return 0;
}
