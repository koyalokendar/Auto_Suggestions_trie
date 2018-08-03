#include<bits/stdc++.h>
#include<fstream>
#include<string>
#define CHAR_TO_INDEX(c) ((int)c - (int)'a')
using namespace std;
const int ALPHABET_SIZE =26;
int calc(string s);
struct TrieNode
{
    struct TrieNode *children[ALPHABET_SIZE];
    bool isEndOfWord;
    //string res;
};

struct TrieNode *getNode(void)
{
    struct TrieNode *pNode =  new TrieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

void insert(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;
    int i;
    for ( i = 0; i < key.length() /*&& key[i]!='('*/; i++)
    {
        int index =CHAR_TO_INDEX(key[i]);
        if (!pCrawl->children[index])
            pCrawl->children[index] = getNode();

        pCrawl = pCrawl->children[index];
    }
    pCrawl->isEndOfWord = true;
    //int n=key.length();
    //pCrawl->res=key.substr(i,n-i);
}
bool search(struct TrieNode *root, string key)
{
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < key.length(); i++)
    {
        int index = CHAR_TO_INDEX(key[i]);
        if (!pCrawl->children[index])
            return false;

        pCrawl = pCrawl->children[index];
    }

    if(pCrawl != NULL && pCrawl->isEndOfWord)
	{
		return true;
	}
}
bool isLastNode(struct TrieNode* root)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return 0;
    return 1;
}
void suggestionsRec(struct TrieNode* root, vector<char> currPrefix)
{
    if (root->isEndOfWord)
    {
        for(int i=0;i<currPrefix.size();i++)cout<<currPrefix[i];
        cout << endl;
    }
    if (isLastNode(root))
        return;
 
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (root->children[i])
        {
            currPrefix.push_back(97 + i);
            suggestionsRec(root->children[i], currPrefix);
            currPrefix.pop_back();
        }
    }
}
int printAutoSuggestions(TrieNode* root, const vector<char> query)
{
    struct TrieNode* pCrawl = root;
    int level;
    int n = query.size();
    for (level = 0; level < n; level++)
    {
        int index = CHAR_TO_INDEX(query[level]);
        if (!pCrawl->children[index])
            return 0;
 
        pCrawl = pCrawl->children[index];
    }
    bool isWord = (pCrawl->isEndOfWord == true);
    bool isLast = isLastNode(pCrawl);
    if (isWord && isLast)
    {
        for(int i=0;i<query.size();i++)cout<<query[i];
        return -1;
    }
    if (!isLast)
    {
        vector<char>prefix = query;
        suggestionsRec(pCrawl, prefix);
        return 1;
    }
}
string getlower(string s)
{
	for(int i=0;i<s.length();i++)
	{
		s[i]=tolower(s[i]);
	}
	return s;
}
int main()
{
    struct TrieNode *root = getNode();
    char words[20];
	FILE *inf = fopen("dictionary.txt", "r");
	int i=0;
	while (!feof(inf) && i<3000)
	{
		fgets(words, 30 , inf);
		cout<<words;
		words[strlen(words) - 1] = '\0';
		insert(root, words);
		i++;
	}
	string inp;
	vector<char>s;
	cin>>inp;
	for(int i=0;i<inp.length();i++)s.push_back(inp[i]);
    //cout<<search(root,s);
    cout<<endl;
    int comp = printAutoSuggestions(root, s);
    if (comp == -1)
        cout << "No other strings found with this prefix\n";
 
    else if (comp == 0)
        cout << "No string found with this prefix\n";
    return 0;
}
