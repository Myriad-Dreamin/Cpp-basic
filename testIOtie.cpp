#include <iostream>
#include <string>
using namespace std;
int main(){
    ostream tstream;
    ostream *old_ostream = cout.tie(&tstream);
    tstream << "123456";
    
    cout << reinterpret_cast<unsigned long long>(old_ostream) << " " << reinterpret_cast<unsigned long long>(&cout) <<endl;
    // cout << "123456";
    string x = "123456";
    (*old_ostream) << x << endl;
    // cin >> x;
    // cin.tie(old_ostream);
    // cin >> x;
    // cout << x;
}