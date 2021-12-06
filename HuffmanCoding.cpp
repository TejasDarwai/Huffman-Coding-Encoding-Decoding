/******************************************************************************* 
                         
                            Huffman Algorithm
                           Encoding - Decoding

*******************************************************************************/


#include<bits/stdc++.h>

using namespace std;

class HuffTree{
    public:
    int val;
    char letter;
    HuffTree *left;
    HuffTree *right;

    HuffTree(int val, char ch){
        this->val = val;
        this->letter=ch;
        this->left = NULL;
        this->right = NULL;
    }
};

vector<pair<int, char > > frequency (string s){
    map<char, int>mp;
    for(int i=0; i<s.size(); i++){
        mp[s[i]]++;
    }
    vector<pair<int, char > > v;
    for(int i=0; i<s.size(); i++){
        if(mp[s[i]]!=0){
            v.push_back(make_pair(mp[s[i]], s[i]));
            mp[s[i]]=0;
        }
    }
    
    return v;
}

class Compare{
    public:
    bool operator() (HuffTree* a, HuffTree* b){
        if(a->val > b->val){
            return true;
        }
        else{
            return false;
        }
    }
};

void print(priority_queue<HuffTree*, vector<HuffTree*>, Compare> q){
    while(q.size()){
        cout<<q.top()->letter<<" "<<q.top()->val<<endl;
        q.pop();
    }
}

HuffTree *makeTree(vector<pair<int, char> > &frq){  
    priority_queue<HuffTree*, vector<HuffTree*>, Compare> q;
    for(int i=0; i<frq.size(); i++){
        q.push(new HuffTree(frq[i].first, frq[i].second));
    }
    //print(q);
    while(q.size()>1){
        HuffTree *left = q.top();
        q.pop();
        HuffTree *right = q.top();
        q.pop();
        HuffTree *nd = new HuffTree(left->val+right->val, '~');
        nd->left = left;
        nd->right = right;
        q.push(nd);
    }
    return q.top();
}

void InOrder(HuffTree *tree){
    if(tree){
        InOrder(tree->left);
        cout<<tree->val<<endl;
        InOrder(tree->right);
    }
}

void getValues(HuffTree *root, string s, map<char, string>& vtr){
    if(!root){
        return;
    }
    if(root->letter!='~'){
        vtr[root->letter]=s;
        return;
    }
    else{
        getValues(root->left,s+"0",vtr);
        getValues(root->right,s+"1",vtr);
    }
}

string decode(HuffTree *tree, string s, int &i){
    string str="";
    while(i<=s.size()){
    if(tree->letter!='~'){
        str+=tree->letter; 
        return str;
    }
    else if(s[i]=='0'){
        if(tree->left){
            tree=tree->left;
            i++;
        }
        else{
            return str;
        }
    }
    else if(s[i]=='1'){
        if(tree->right){
            tree=tree->right;
            i++;
        }
        else{
            return str;
        }
    }
    }
    return "";
}



int main(){
    string s;
    string resultant="";
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<endl;
    cout<<"               -----------------------------------------------------"<<endl;
    cout<<"               -                                                   -"<<endl;
    cout<<"               -        Huffman Algorithm Encoding - Decoding      -"<<endl;
    cout<<"               -                                                   -"<<endl;
    cout<<"               -----------------------------------------------------"<<endl;
    cout<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    cout<<endl;
    cout<<"                             Enter Data"<<endl;
    cout<<endl;
    cout<<"==>>";
    getline(cin, s);
    cout<<endl;
    vector<pair<int, char> > frq = frequency(s);
    sort(frq.begin(), frq.end());

    cout<<"Elements Frequency"<<"==>>"<<endl;
    for(int i=0; i<frq.size(); i++){
        cout<<frq[i].first<<" "<<frq[i].second<<endl;
    }
    cout<<endl;

    map<char, string> vtr;
    HuffTree *tree = makeTree(frq);
    //InOrder(tree);
    getValues(tree, "",vtr);

    cout<<"Corresponding Binary Codes Formed"<<"==>>"<<endl;
    for(auto &pr:vtr){
        cout<<pr.first<<" "<<pr.second<<endl;
    }
    cout<<endl;
    for(int i=0; i<s.size(); i++){
        char temp = s[i];
        resultant+=vtr[temp];
    }
    cout<<"Encoded Data"<<"==>>"<<endl;
    cout<<resultant<<endl;
    cout<<endl;
    string original=""; 
    for(int i=0; i<resultant.size();){
        original+=decode(tree, resultant, i); 
    }
    cout<<endl;
    cout<<"Decoded Data"<<"==>>"<<endl;
    cout<<original<<endl;
    cout<<endl;
    cout<<"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
    return 0;
}