 

class lexicon  
{  
    private:  
    class Node  
    {  
        public:  
        std::string key;  
        Node* left=nullptr;  
        Node* right=nullptr;  
        int freq=1; 
    };  

    Node* root;  
    public:  

    lexicon():root(nullptr){}  

    ~lexicon(){purge(root);}  
    
    void purge(Node* root)  
    {  
        if(root==nullptr)  
            return;  
        purge(root->left);  
        purge(root->right);  
        delete root;  
    }  
    Node* createNode(const std::string &s)  
    {  
        Node* newNode = new Node();  
        newNode->key=s;  
        newNode->left=newNode->right=nullptr;  
        newNode->freq = 1;  
        return newNode;  
    }  
 
    void insert(const std::string &s)  
    {  
        if(root==nullptr)  
        {  
            root=createNode(s);  
        }else if(insert(root,s)){}  
    }  
    bool insert(Node* t, const std::string &s)  
    {  
        if(s<t->key)  
        {  
            if(t->left==nullptr)  
            {  
                t->left=createNode(s);  
                return true;  
            }else  
                return insert(t->left,s);  
        }else if(s>t->key)  
        {  
            if(t->right==nullptr)  
            {  
                t->right=createNode(s);  
                return true;  
            }else  
                return insert(t->right,s);  
        }else  
        {  
        ++(t->freq);  
        return false;  
        }  
    }  
    int lookup(const std::string &s) const  
    {  
        return lookup(root,s);  
    }  
    Node* minVal(Node* root)  
    {  
        Node* temp = root;  
        while(temp->left!=nullptr)  
            temp= temp->left;  
        return temp;  
    }  
    void remove(const std::string & s)  
    {  
        root=remove(root,s);  
    }  
    Node* remove(Node* root, const std::string &s)  
    {  
        if(root==nullptr)  
            return root;  
        if(s<root->key)  
            root->left=remove(root->left,s);  
        else if(s>root->key)  
            root->right=remove(root->right,s);  
        else   
        {  
            if(root->left==nullptr)  
            {  
                Node* temp= root->right;  
                delete root;  
                return temp;  
            }  
            if(root->right==nullptr)  
            {  
                Node* temp = root->left;  
                delete root;  
                return temp;  
            }  
        Node* temp = minVal(root->left);  
        root->key=temp->key;  
        root->freq=temp->freq;  
        root->left=remove(root->left,temp->key);  
    }  
    return root;  
    }

    int lookup(Node* root, const std::string& s) const  
    {  
    
        if(root==nullptr)  
            return 0;  
        if(s==root->key)  
            return root->freq;  
        else if(s<root->key)  
            return lookup(root->left,s);  
        else if(s>root->key)  
            return lookup(root->right,s);  
    } 

    void Inorder()const  
    {  
        Inorder(root);  
    }  
    void Inorder(Node* root)const  
    {  
        if(root==nullptr)  
            return;  
        Inorder(root->left);  
        cout<<root->key<<" "<<root->freq<<endl;  
        Inorder(root->right);  
    }  
    
    void replace(const string &s1, const string &s2)  
    {  
        
        if(lookup(s1)==0)  
            return;  
        else  
        {  
            int s1_freq=0;  
            Node*node_1=search_string(s1);  
            s1_freq=node_1->freq;  
            remove(s1);  
            if(lookup(s2)==0) 
            {  
                insert(s2);  
                
                search_string(s2)->freq=s1_freq;  
            }else  
                search_string(s2)->freq+=s1_freq;  
        }  
        
    }  
    friend ostream& operator<<(ostream& stream, const lexicon& l)  
    {  
        l.Inorder(l.root);  
        stream<<"";  
        return stream;  
    }  
    Node* search_string(const std::string &s)  
    {  
        return search_string(root,s);  
    }  
    Node* search_string(Node* root,const std::string &s)  
    {  
        if(root==nullptr || s==root->key)  
            return root;  
        else if(s<root->key)  
            return search_string(root->left,s);  
        else if(s>root->key)  
            return search_string(root->right,s);  
    }  
int getLevelUtil(Node* root  ,const string& data, int level) const  
{   
    if (root == nullptr)   
        return 0;   
    if (root -> key == data)   
        return level;   
    int downlevel = getLevelUtil(root -> left,    
                                 data, level + 1);   
    if (downlevel != 0)   
        return downlevel;   
    downlevel = getLevelUtil(root->right,    
                             data, level + 1);   
    return downlevel;   
}   
int depth( const string &s) const  
{   
    return getLevelUtil(root, s, 1);   
}   
void print()  
{  
    cout<<root->key<<endl;  
}     
   
};

#include <iostream>  
#include <string>  
#include <list>
#include <array>
#include <vector>
#include <algorithm>
using namespace std; 
