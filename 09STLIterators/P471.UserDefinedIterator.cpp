#include <iostream>
#include <iterator>
#include <vector>
#include <array>
using namespace std;

// user-defined iterator that support iterator traits
// 1. supply the 5 types: iterator_category, value_type, difference_type, pointer, reference
//      derived from iterator<>
//      define these types for your iterator
// 2. supply a template (partial) specialization version for iterator_traits


// solution 1.1 : derived from iterator<>
template<typename T, size_t size>
class MyArray1
{
public:
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
public:
    template<typename T2>
    // define as input iterator, although it can be defined as random-access iterator
    class IteratorImp : public iterator<input_iterator_tag, T2, ptrdiff_t, T2*, T2&> // last 3 have default parameters
    {
    public:
        IteratorImp(value_type* p) : ptr(p) {}
        value_type& operator*() { return *ptr; }
        IteratorImp& operator++() // pre++
        {
            ++ptr;
            return *this;
        }
        bool operator==(const IteratorImp& rhs) { return ptr == rhs.ptr; }
        bool operator!=(const IteratorImp& rhs) { return ptr != rhs.ptr; }
    private:
        value_type* ptr;
    };
    using iterator = IteratorImp<T>;
    using const_iterator = IteratorImp<const T>;
     MyArray1()
    {
        copy(begin(arr), end(arr), 0);
    }
    template<typename T2>
    MyArray1(const initializer_list<T2>& il)
    {
        if (il.size() > size)
        {
            throw out_of_range("initializer_list too long");
        }
        copy(il.begin(), il.end(), arr);
        if (il.size() < size)
        {
            fill(arr + il.size(), arr + size, 0);
        }
    }
    iterator begin() { return iterator(arr); }
    iterator end() { return iterator(arr+size); }
    const_iterator begin() const { return const_iterator(arr); }
    const_iterator end() const { return const_iterator(arr+size); }
private:
    T arr[size];
};

// solution 1.2 : define these types for self-defined iterator
template<typename T, size_t size>
class MyArray2
{
public:
    using value_type = T;
    using difference_type = ptrdiff_t;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
private:
    template<typename T2>
    class IteratorImp
    {
    public:
        using iterator_category = random_access_iterator_tag;
        using value_type = T2;
        using difference_type = ptrdiff_t;
        using pointer = T2*;
        using reference = T2&;
        IteratorImp(value_type* p) : ptr(p) {}
        value_type& operator*() { return *ptr; }
        IteratorImp& operator++() // pre++
        {
            ++ptr;
            return *this;
        }
        IteratorImp operator++(int) // post++
        {
            IteratorImp ret(ptr);
            ++ptr;
            return ret;
        }
        value_type* operator->() { return ptr; }
        bool operator==(const IteratorImp& rhs) { return ptr == rhs.ptr; }
        bool operator!=(const IteratorImp& rhs) { return ptr != rhs.ptr; }
        difference_type operator-(const IteratorImp& rhs) { return ptr - rhs.ptr; }
        IteratorImp operator+(size_type offset) { return IteratorImp(ptr + offset); }
        IteratorImp<const T2> operator+(size_type offset) const { return IteratorImp<const T2>(ptr + offset); }
    private:
        value_type* ptr;
    };
public:
    using iterator = IteratorImp<T>;
    using const_iterator = IteratorImp<const T>;
    MyArray2()
    {
        copy(begin(arr), end(arr), 0);
    }
    template<typename T2>
    MyArray2(const initializer_list<T2>& il)
    {
        if (il.size() > size)
        {
            throw out_of_range("initializer_list too long");
        }
        copy(il.begin(), il.end(), arr);
        if (il.size() < size)
        {
            fill(arr + il.size(), arr + size, 0);
        }
    }
    iterator begin() { return iterator(arr); }
    iterator end() { return iterator(arr+size); }
    const_iterator begin() const { return const_iterator(arr); }
    const_iterator end() const { return const_iterator(arr+size); }
private:
    T arr[size];
};

// solution 2: supply a template (partial) specialization version for iterator_traits
// ...

int main(int argc, char const *argv[])
{
    MyArray1<int, 10> arr1 { 1, 2, 3 };
    copy(arr1.begin(), arr1.end(), ostream_iterator<decltype(arr1)::value_type>(cout, " "));
    cout << endl;

    MyArray2<int, 10> arr2 { 1, 2, 3 };
    copy(arr2.begin(), arr2.end(), ostream_iterator<decltype(arr2)::value_type>(cout, " "));
    cout << endl;
    return 0;
}