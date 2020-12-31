# AVL TREE
A short and intutive implementation of self balancing AVL tree that supports duplicate deletions and ith element can be directly accessed in logarithmic time.
As of now this only supports long long data type.
##Functuions intended for user intractions are.
###void insert(node* &root,ll val)
Takes tree's root and value to be inserted as argument and insert the value in the tree.
###void remove(node* &root,ll val)
Takes tree's root and value as argument and delete one of the instance of that object from the tree.
###ll at(node* root,ll index)
Takes tree's root as argument and the index(0 based) and returns the element that is present at that index(as in sorted list).
