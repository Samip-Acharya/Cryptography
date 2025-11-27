#include<iostream>
#include<vector>
#include<string> 
using namespace std; 

class HillCipher{
    int extendedEuclid(int a, int b, int &x, int &y){
        if(b==0){
            x = 1; y = 0; 
            return a;
        }
        int gcd = extendedEuclid(b,a%b,x,y); 
        int temp=x;
        x = y; 
        y = temp - (a/b)*y; 
        return gcd; 
    }
    vector<vector<int>> key = {{5,3},{4,3}};
    static const int MOD = 26; 
    vector<int> multiply(vector<int>& Pvec){
        vector<int> ans(2,0); 
        for(int i = 0; i<2; i++){
            for(int j = 0; j<2; j++){
                ans[i] = (ans[i] + (key[i][j]*Pvec[j]))%MOD; 
            }
        }
        return ans; 
    }
    vector<int> invertMultiply(vector<int>& Cvec){
        //find K^-1; 
        //adjoint 
        vector<vector<int>> adj = key; 
        swap(adj[0][0],adj[1][1]); 
        adj[0][1] *= -1; 
        adj[1][0] *= -1; 
        int determinant = (((key[0][0] * key[1][1]) - (key[0][1]*key[1][0]))%MOD + MOD)%MOD; 
        int detInverse,_; 
        extendedEuclid(determinant,MOD,detInverse,_); 
        detInverse = (detInverse + MOD)%MOD; 
        vector<int> ans(2,0); 
        for(int i = 0; i<2; i++){
            for(int j = 0; j<2; j++){
                ans[i] = ((ans[i] + (adj[i][j]*Cvec[j]))%MOD + MOD)%MOD;
            }
            ans[i] = (ans[i]*detInverse)%MOD; 
        }
        return ans; 

    }
    public: 
        string encrypt(string plainText){
            //break into 2 
            string encrypted = "";
            int n = plainText.length(); 
            if(n&1){
                plainText += "X";//padding  
                n++; 
            }
            for(int i = 0; i<n-1; i+=2){
                vector<int> Pvec = {plainText[i]-'A',plainText[i+1]-'A'};  
                vector<int> Cvec = multiply(Pvec); 
                encrypted = encrypted + (char)(Cvec[0]+'A') + (char)(Cvec[1]+'A');
            }
            return encrypted;
        }
        string decrypt(string cipherText){
            string decrypted = ""; 
            int n = cipherText.length(); 
             if(n&1){
                cipherText += "X";//padding  
                n++; 
            }
            for(int i = 0; i<n-1; i+=2){
                vector<int> Cvec = {cipherText[i]-'A',cipherText[i+1]-'A'};  
                vector<int> Pvec = invertMultiply(Cvec); 
                decrypted = decrypted + (char)(Pvec[0]+'A') + (char)(Pvec[1]+'A');
            }
            return decrypted;
        }
};

int main(){
    string inputText; 
    cin >> inputText; 
    HillCipher HC; 
    cout << "Encrypted: " << HC.decrypt(inputText) << endl; 
}