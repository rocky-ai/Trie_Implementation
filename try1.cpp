#include <iostream>
#include <fstream>
#include <iterator>
#define MARKER '#'
#include <bits/stdc++.h>
using namespace std;

struct Trie
{
    bool isEndOfWord;
    map<char, Trie*> ma;
    string frequency;
};
Trie* getNewTrieNode()
{
    Trie* node = new Trie;
    node->isEndOfWord = false;
    return node;
}

void insert(Trie*& root, const string& str,
            const string& frequency)
{

    // If root is null
    if (root == NULL)
        root = getNewTrieNode();

    Trie* temp = root;
    for (int i = 0; i < str.length(); i++)
    {
        char x = str[i];

        // Make a new node if there is no path
        if (temp->ma.find(x) == temp->ma.end())
            temp->ma[x] = getNewTrieNode();

        temp = temp->ma[x];
    }

    // Mark end of word and store the meaning
    temp->isEndOfWord = true;
    temp->frequency = frequency;
}
string getFrequency(Trie* root, const string& word)
{

    // If root is null i.e. the dictionary is empty
    if (root == NULL)
        return "";

    Trie* temp = root;

    // Search a word in the Trie
    for (int i = 0; i < word.length(); i++)
    {
        temp = temp->ma[word[i]];
        if (temp == NULL)
            return "";
    }

    // If it is the end of a valid word stored
    // before then return its meaning
    if (temp->isEndOfWord)
        return temp->frequency;
    return "";
}
int main()
{
    ifstream ip("temp.csv");
    if(!ip.is_open()) std::cout << "ERdf" << '\n';
    string name;
    string freq;
    Trie* root = NULL;
    while(ip.good())
    {
        getline(ip,name,',');
        getline(ip,freq,'\n');
        insert(root, name,freq);
    }
    string query;
    cout<<"Enter the word you want to search ";
    cin>>query;
    string f = getFrequency(root,query);
    if (f.length() == 0){
     cout<<"NO";
    }
    else{
        cout<<"YES "<<f;
    }
    FILE *fp = fopen("tree.txt", "w");
    if (fp == NULL)
    {
        puts("Could not open file");
        return 0;
    }

    fclose(fp);
    cout << endl;
}
