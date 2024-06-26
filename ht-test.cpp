#include "ht.h"
#include "hash.h"
#include <unordered_map>
#include <iostream>
#include <utility>
#include <string>
#include <sstream>
#include <functional>
using namespace std;
int main()
{
    DoubleHashProber<std::string, MyStringHash > dh;
    HashTable<
        std::string, 
        int, 
        DoubleHashProber<std::string, MyStringHash >, 
        std::hash<std::string>, 
        std::equal_to<std::string> > ht(0.7, dh);

    // This is just arbitrary code. Change it to test whatever you like about your 
    // hash table implementation.
    for(size_t i = 0; i < 10; i++){
        std::stringstream ss;
        ss << "hi" << i;
        ht.insert({ss.str(), i});
        cout << "HT size here: " << ht.size() << endl;
    }
    if( ht.find("hi1") != nullptr ){
        cout << "Found hi1" << endl;
        cout << "hi1 value is: " << ht["hi1"] << endl;
        ht["hi1"] += 1;
        cout << "Incremented hi1's value to: " << ht["hi1"] << endl;
    }
    if( ht.find("doesnotexist") == nullptr ){
        cout << "Did not find: doesnotexist" << endl;
    }
    cout << "HT size: " << ht.size() << endl;
    if( ht.find("hi7") != nullptr ){
        cout << "hi7 value is: " << ht["hi7"] << endl;
        cout << "Found hi7" << endl;
    }
    ht.remove("hi7");
    if( ht.find("hi7") == nullptr ){
    cout << "hi7 is removed" << endl;
    }
    ht.remove("hi9");
    cout << "HT size: " << ht.size() << endl;
    if( ht.find("hi9") != nullptr ){
        cout << "Found hi9" << endl;
    }
    else {
        cout << "Did not find hi9" << endl;
    }
    ht.insert({"hi7",17});
    cout << "size: " << ht.size() << endl;
    ht.insert({"hi3",3});
    ht.insert({"hi4",4});
    ht.insert({"hi5",5});
    ht.insert({"hi6",6});
    cout << "size after inserting 3456: " << ht.size() << endl;
    return 0;
}
