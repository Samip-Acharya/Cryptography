#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<vector> 
using namespace std; 

class PlayfairCipher{
    string key; 
    vector<vector<char>> matrix;
    public:
        PlayfairCipher(string key) {
            this->key=key;
            matrix.assign(5,vector<char>(5)); 
        } 
        string encrypt(string plainText){
            unordered_set<char>  st;
            unordered_map<char,pair<int,int>> mp;
            int row,col;
            row=col=0; 
            //fill key
            for(char ch : key){
                 if(ch == 'J' && st.count('I')){
                    mp[ch] = mp['i']; 
                    continue; 
                }
                if(ch == 'I' && st.count('J')){
                    mp[ch] = mp['J'];
                    continue; 
                }
                if(st.find(ch) == st.end()){
                    st.insert(ch);
                    matrix[row][col] = ch; 
                    mp[ch] = {row,col}; 
                    col++; 
                    if(col==5){
                        col=0;
                        row++; 
                    }
                }
            }
            //fill remaining letters
            for(char ch = 'A'; ch<='Z'; ch++){
                if(ch == 'J' && st.count('I')){
                    mp[ch] = mp['i']; 
                    continue; 
                }
                if(ch == 'I' && st.count('J')){
                    mp[ch] = mp['J'];
                    continue; 
                }
                if(st.find(ch) == st.end()){
                    st.insert(ch);
                    matrix[row][col] = ch; 
                    mp[ch] = {row,col}; 
                    col++; 
                    if(col==5){
                        col=0;
                        row++; 
                    }
                }
            }
            int n = plainText.length(); 
            //if same add x filler
            string plainText_ = "";
            plainText_ += plainText[0]; 
            for(int i = 1; i<n; i++){
                if(plainText[i] == plainText_.back()){
                    plainText_ += "X"; 
                }
                plainText_ += plainText[i];
            }
            n = plainText_.length();
            if(n&1){
                plainText_ += "X";
            }
            cout << plainText_ << endl;
            string encrypted = "";
            //process two letters at a time
            for(int i = 0; i<n-1; i+=2){
                char ch1 = plainText_[i];
                char ch2 = plainText_[i+1];
                char ch1_,ch2_; 
                //check same row;
                if(mp[ch1].first == mp[ch2].first){
                    ch1_ = matrix[mp[ch1].first][(mp[ch1].second + 1)%5]; 
                    ch2_ = matrix[mp[ch1].first][(mp[ch2].second + 1)%5]; 
                }
                //check same col;
                else if(mp[ch1].second == mp[ch2].second){
                    ch1_ = matrix[(mp[ch1].first+1)%5][mp[ch1].second]; 
                    ch2_ = matrix[(mp[ch2].first+1)%5][mp[ch1].second]; 
                }
                else{
                    ch1_ = matrix[mp[ch1].first][mp[ch2].second];
                    ch2_ = matrix[mp[ch2].first][mp[ch1].second];
                }
                encrypted += ch1_;
                encrypted += ch2_;  
            }
            return encrypted;
        }
};

int main(){
    PlayfairCipher PC("MONARCHY"); 
    cout << PC.encrypt("CIRCULAR")<<endl;
    return 0;
}