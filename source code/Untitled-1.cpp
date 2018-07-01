#include<iostream>
#include<vector>
using namespace std;

int main(){
    vector<int> i(10);
    i[3] = 9;
    cout << i[3];
    return 0;
}