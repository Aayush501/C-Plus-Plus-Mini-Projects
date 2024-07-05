#include<iostream>
#include<ctime>
#include<string>
using namespace std;

string getPassword(int length){
    string password = "";
    string characters = "abcdefghijklmnopqrstuvwxyz@#%$*ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789";
    int charSize = characters.size();
    srand(time(0));
    for(int i=0; i<length; i++){
        int randomIndex = rand()%charSize;
        password = password + characters[randomIndex];
    }
    return password;
}

int main(){
    int length;
    cout<<"Enter the length of the Password : ";
    cin>>length;
    string password = getPassword(length);
    cout<<"Generated Password is : "<<password<<endl;
    return 0;
}