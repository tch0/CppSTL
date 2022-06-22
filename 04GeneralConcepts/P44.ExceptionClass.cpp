#include <iostream>
#include <exception>
using namespace std;

// exception system_error(public runtime_error) and future_error(public logic_error)
// also have a extra memeber that supply detail infomations
// the specific information could be either a error code or a error condition
// which type is std::error_code and std::error_condition.

// each error condtion corresponds to a errno enum (macro?) value(from C).

// code() member function for those exception will return a error_code type that specify the detials of the error.


int main(int argc, char const *argv[])
{
    
    return 0;
}
