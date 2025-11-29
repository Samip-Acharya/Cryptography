#include<iostream>
#include<string>
using namespace std; 

class VignereCipher{
    string key; 
    int m;
    public:
        VignereCipher(string s) : key(s),m(s.length()) {}
        string encrypt(string plainText){
            string encrypted = "";
            int n = plainText.length();
            for(int i=0 ; i<n; i++){
                encrypted += ('a'+ (plainText[i]-'a'+(key[i%m]-'a'))%26);
            }
            return encrypted; 
        }
        string decrypt(string cipherText){
            string decrypted = ""; 
            int n = cipherText.length(); 
            for(int i=0 ; i<n; i++){
                decrypted += ('a'+ ((cipherText[i]-'a'-(key[i%m]-'a'))%26 + 26)%26);
            }
            return decrypted; 
        }   
};

int main(){
   VignereCipher VC = VignereCipher("worlds");
   cout << VC.decrypt("dscwrwrsijrfa") << endl;
   return 0; 

}