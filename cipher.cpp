#include<bits/stdc++.h>
#define COUNT 10

using namespace std;

struct Node
{
    char ch;
    struct Node* left;
    struct Node* right;

    Node(char c)
    {
        ch = c;
        left = NULL;
        right = NULL;
    }
};


char arr[] =  {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
int n = sizeof(arr) / sizeof(arr[0]);
vector<char> v(arr, arr + n);

char a[] = {'(','!',')','%','@','$','#','^','&','*','{','/','|',',','.','}',':','~','<','?','=','+','-','_','[',']'};
vector<char> p(a,a+n);

/* rotation of the vector p */
vector<char> rotatebyk(vector<char> s, int k)
{
    int n = s.size();
    k = k%n;
   vector<char> str ;
    for(int i=0;i<n;i++)
    {
        if(i<k)
        {
            str.push_back(s[n+i-k]);
        }
        else{
            str.push_back(s[i-k]);
        }
    }
    return str;
}


void inorder(Node* root)
{
    if(root)
    {
        inorder(root->left);
        cout<<root->ch<<" ";
        inorder(root->right);
    }
}

/* creating a tree of v */
Node* InsertNode(Node* root, char c)
{
    if (root == NULL) {
        root = new Node(c);
        return root;
    }
    if(c>root->ch)
    {
        root->right = InsertNode(root->right,c);
    }
    else
    {
        root->left = InsertNode(root->left,c);
    }
    return root;
}

/*Finding predecessor and successor */
void findPreSuc(Node* root, Node*& pre,Node*& suc,char key)
{
    // Base case
    if (root == NULL)  return ;

    // If key is present at root
    if (root->ch == key)
    {
        // the maximum value in left subtree is predecessor
        if (root->left != NULL)
        {
            Node* tmp = root->left;
            while (tmp->right)
                tmp = tmp->right;
            pre = tmp ;
        }
    if (root->right != NULL)
        {
            Node* tmp = root->right ;
            while (tmp->left)
                tmp = tmp->left ;
            suc = tmp ;
        }
        return ;
    }

    // If key is smaller than root's key, go to left subtree
    if (root->ch > key)
    {
        suc = root ;
        findPreSuc(root->left, pre, suc, key) ;
    }
    else // go to right subtree
    {
        pre = root ;
        findPreSuc(root->right, pre, suc, key) ;
    }
}


map<char,char> mp;
map<char,char> m;

void encryption(Node* root,string s)
{
    Node* pre = NULL;
    Node* suc = NULL;
    cout<<"Cipher Text"<<endl;
    for(int k=0;k<s.size();k++)
    {
          findPreSuc(root, pre, suc, s[k]);
          if(pre){
            cout<<mp[pre->ch];
          }else
          {
              cout<<">";
          }
    }

}
void decryption(Node* root, string s)
{
    Node* pre = NULL;
    Node* suc = NULL;
    cout<<"Plain Text"<<endl;
    for(int k=0;k<s.size();k++)
    {
          findPreSuc(root, pre, suc, m[s[k]]);
          if(suc){
            cout<<suc->ch;
          }else
          {
              cout<<'>';
          }
    }
}

vector<string> make_sentence(string s)
{
    string test = "";
    vector<string> ans;
    for(int i = 0; i<s.length(); ++i)
    {
        if(s[i] !=  ' ')
            test += s[i];

        else if(s[i] == ' ')
        {
            ans.push_back(test);
            test = "";
        }
    }
    return ans;
}


int main()
{
    int x;
    cout<<"Enter 1. to Encryption and  2. to Decryption  "<<endl;
    cin>>x;
    cout<<endl;

string s;
cout<<"Enter text: ";
cin>>s;

 cout<<"Enter key: ";
    int key;
    cin>>key;


    vector<char> r = rotatebyk(p,key);
   /* vector<string> str = make_sentence(text);
    for(int i=0;i<str.size();i++)
    {
        cout<<str[i]<<",";
    }
    //cout<<r.size()<<endl;*/

    for(int i=0;i<n;i++)
    {
        mp[v[i]] = r[i];
        m[r[i]] = v[i];
    }

    //int i=0;
    //while(i<n)
    //{
      //  cout<<r[i]<<" ";
      //  i++;
    //}
    //cout<<endl;
    Node* root = NULL;

    int j =0;
    while(j<r.size()){
        root = InsertNode(root,v[j]);
        j++;
    }
    //inorder(root);
    //cout<<endl;

    cout<<endl;

    if(x == 1){
    //for(int i=0;i<str.size();i++)
    encryption(root,s);
    }else{
    //for(int i=0;i<str.size();i++)
    decryption(root,s);
    }
    cout<<endl;
    return 0;
}


