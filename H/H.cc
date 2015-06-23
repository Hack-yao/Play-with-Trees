#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<int> xml;

map<string, int> string_hashing;

void readXML() {
    char c;
    string word;
    bool flag = true;
    int hashing_count = 0;
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\n') continue;
        else if (c == '<') word = "";
        else if (c == '>') {
            int k;
            if (word == "/")
                k = -1;
            else {
                if (string_hashing.find(word) == string_hashing.end()) {
                    ++ hashing_count;
                    string_hashing[word] = hashing_count;
                    k = hashing_count;
                }
                else 
                    k = string_hashing[word];
            }
            xml.push_back(k);
            flag = true;
        }
        else if (c == '/') {
            word = "/";
            flag = false;
        }
        else if (flag) word += c;
    }
}

struct TreeNode {
    int tag;
    int id;
    int size;
    vector<int> child;
};

#define MAXN    15000+100

TreeNode XMLTree[MAXN];

int ptr;
int level;
int total;

bool cmp(const int A, const int B) {
    return XMLTree[A].tag <= XMLTree[B].tag;
}

int buildXMLTree() {
    ++ total; int x = total;
    XMLTree[x].tag = xml[ptr]; ++ ptr;
    XMLTree[x].id = total;
    XMLTree[x].child.clear();
    XMLTree[x].size = 1;
    while (xml[ptr] != -1) {
        int y = buildXMLTree();
        XMLTree[x].child.push_back(y);
        XMLTree[x].size += XMLTree[y].size;
    }
    ++ ptr;
    sort(XMLTree[x].child.begin(), XMLTree[x].child.end(), cmp);
    return x;
}

vector<int> ans;

int root_text, root_query;

bool check(int rootA, int rootB) {
    if (XMLTree[rootB].child.empty()) return true;
    int j = 0;
    int n = XMLTree[rootA].child.size();
    int m = XMLTree[rootB].child.size();
    for (int i = 0; i < m; ++ i) {
        while (j < n && XMLTree[XMLTree[rootA].child[j]].tag != XMLTree[XMLTree[rootB].child[i]].tag) ++ j;
        if (j == n) return false;
        if (!check(XMLTree[rootA].child[j], XMLTree[rootB].child[i])) return false;
    }
    return true;
}

void dfs(int x) {
    if (XMLTree[x].size < XMLTree[root_query].size) return;
    if (XMLTree[x].tag == XMLTree[root_query].tag && check(x, root_query))
        ans.push_back(XMLTree[x].id);
    for (int i = 0; i < XMLTree[x].child.size(); ++ i)
        dfs(XMLTree[x].child[i]);
}

int main() {
    readXML();
    total = ptr = 0;
    root_text = buildXMLTree();
    root_query = buildXMLTree();
    /*
    cout << ptr << endl;
    cout << xml.size() << endl;
    for (int i = 0; i < xml.size(); ++ i)
        cout << xml[i] << endl;
    ans.clear();
    */
    dfs(root_text);


    sort(ans.begin(), ans.end());

    printf("%d\n", (int)ans.size());
    for (int i = 0; i < ans.size(); ++ i)
        printf("%d\n", ans[i]);
    return 0;
}