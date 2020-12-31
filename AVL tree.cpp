 /*
    Created by Ezio112
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vll;
#define inf ll(10e16)
#define mod ll(10e5+7)
#define ff first
#define ss second
struct node{
    ll data,size;
    node* left,*right;
    node(ll val)
    {
        data=val;
        size=1;
        left=right=nullptr;
    }
};
inline void rotate_right(node* &root)
{
    node *temp=root;
    root=root->left;
    node* temp2=root->right;
    root->right=temp;
    temp->left=temp2;
 
    ll left_size(0),right_size(0);
    if(root->right->left)
        left_size=root->right->left->size;
    if(root->right->right)
        right_size=root->right->right->size;
 
    root->right->size=left_size+right_size+1;
    right_size=left_size=0;
 
    if(root->left)
        left_size=root->left->size;
    if(root->right)
        right_size=root->right->size;
    root->size=left_size+right_size+1;
}
inline void rotate_left(node* &root)
{
    node* temp=root;
    root=root->right;
    node* temp2=root->left;
    root->left=temp;
    temp->right=temp2;
 
    ll left_size(0),right_size(0);
    if(root->left->left)
        left_size=root->left->left->size;
    if(root->left->right)
        right_size=root->left->right->size;
    root->left->size=left_size+right_size+1;
    right_size=left_size=0;
 
    if(root->left)
        left_size=root->left->size;
    if(root->right)
        right_size=root->right->size;
    root->size=left_size+right_size+1;
}
inline bool is_leaf(node* &root)
{
    return (!root->left && !root->right);
}
void balance(node* &root)
{
    ll left_size(0),right_size(0);
    if(root->left)
        left_size=root->left->size;
    if(root->right)
        right_size=root->right->size;
    if(abs(left_size-right_size)<=1)
        return ;
 
    if(left_size>right_size)
    {
        ll left_of_left(0),right_of_left(0);
        if(root->left->left)
            left_of_left=root->left->left->size;
        if(root->left->right)
            right_of_left=root->left->right->size;
        if(left_of_left>right_of_left)
        {
            rotate_right(root);
        }
        else
        {
            rotate_left(root->left);
            rotate_right(root);
        }
    }
    else if(left_size<right_size)
    {
        ll left_of_right(0),right_of_right(0);
        if(root->right->left)
            left_of_right=root->right->left->size;
        if(root->right->right)
            right_of_right=root->right->right->size;
        if(right_of_right>left_of_right)
        {
            rotate_left(root);
        }
        else
        {
            rotate_right(root->right);
            rotate_left(root);
        }
    }
    return ;
}
void insert(node* &root,ll val)
{
    if(!root)
        root=new node(val);
    else if(root->data>=val)
    {
        insert(root->left,val);
        root->size++;
        balance(root);
    }
    else
    {
        insert(root->right,val);
        root->size++;
        balance(root);
    }
    return;
}
node* left_max(node* root)
{
    if(!root->right)
        return root;
    return left_max(root->right);
}
void remove(node* &root,ll val)
{
    if(root->data>val)
    {
        remove(root->left,val);
        --root->size;
        balance(root);
    }
    else if(root->data<val)
    {
        remove(root->right,val);
        --root->size;
        balance(root);
    }
    else{
        if(is_leaf(root))
        {
            delete(root);
            root=nullptr;
        }
        else if(!root->right)
        {
            node* temp=root->left;
            delete(root);
            root=temp;
        }
        else if(!root->left)
        {
            node* temp=root->right;
            delete(root);
            root=temp;
        }
        else
        {
            node* temp=left_max(root->left);
            root->data=temp->data;
            remove(root->left,root->data);
            --root->size;
            balance(root);
        }
    }
}
void inorder(node* root)
{
    if(!root)  return;
    inorder(root->left);
    cout<<root->data<<"->"<<root->size<<" ";
    inorder(root->right);
}
ll at(node* root,ll index)
{
    ll left_size=0;
    if(root->left)
        left_size=root->left->size;
    if(left_size==index)
        return root->data;
    if(left_size>index)
        return at(root->left,index);
 
    return at(root->right,index-left_size-1);
}
int main()
{
        ll n,k;
        cin>>n>>k;
        node* tree=nullptr;
        vector<ll> vec(n);
 
        for(ll &x:vec)
            cin>>x;
 
        for(ll i=0;i<k;++i)
        {
            insert(tree,vec[i]);
        }
 
        for(ll i=k;i<n;++i)
        {
            cout<<at(tree,(k-1)/2)<<" ";
            remove(tree,vec[i-k]);
            insert(tree,vec[i]);
        }
        cout<<at(tree,(k-1)/2);
    return 0;
}
