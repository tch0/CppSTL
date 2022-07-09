#include <iostream>
#include <future>
#include <thread>
#include <mutex>
using namespace std;

class DataBaseAccess
{
private:
    std::mutex dbMutex;
public:
    void createTable()
    {
        std::lock_guard<std::mutex> lg(dbMutex);
        cout << "create table" << endl;
        insertData(); // will be a dead lock, dbMutex is locked by createTable
    }
    void insertData()
    {
        std::lock_guard<std::mutex> lg(dbMutex);
        cout << "insert data" << endl;
    }
};

int main(int argc, char const *argv[])
{
    DataBaseAccess db;
    db.createTable();
    // usually, we should use recursive_mutex to avoid deadlock, but mutex works well here, why?
    return 0;
}
