#include <iostream>
#include <climits>

using namespace std;

int main(){
    int smallest = INT_MAX;
    int second = INT_MAX;
    int val;
    while(cin>>val){
        if(val<smallest){
            second=smallest;
            smallest=val;
        }else if (val<second && val!=smallest )
        {   
            second=val;
        }
    }

    cout<<smallest<<endl;
    cout<<second;
    return 0;
}