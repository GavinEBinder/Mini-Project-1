// C++ program to insert a node in AVL tree 
#include <iostream>
#include <vector>

using namespace std;

// An AVL tree node 

class Node {

  public: int key;
  unsigned int height;
  Node * left;
  Node * right;
  Node * parent;
  Node() {
    key = 0;
    height = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
  }
  Node(int val) {
    key = val;
    height = 0;
    parent = NULL;
    left = NULL;
    right = NULL;
  }
};

void inorder(Node * currentPtr);
Node * insert(Node * root, Node * element);
int add(Node * currentPtr);
int find(Node * currentPtr, int val);
Node * parent(Node * root, Node * node);
Node * minVal(Node * root);
Node * maxVal(Node * root);
int isLeaf(Node * node);
int hasOnlyLeftChild(Node * node);
int hasOnlyRightChild(Node * node);
Node * findNode(Node * currentPtr, int value);
Node * deleteNode(Node * root, int value);
int menu();
Node * avlinsert(Node * node, int key);
int height(Node * N);
int max(int a, int b);
Node * newNode(int key);
Node * rightRotate(Node * y);
Node * leftRotate(Node * x);
int getBalance(Node * N);
void preOrder(Node * root);
vector<int> rangeSearch(int low, int high, Node * root);
int computeHeight(Node * targetNode);
Node * next(Node * root, Node * N);
Node * leftDescendant(Node * N);
Node * rightAncestor(Node * root, Node * N);
Node* avlDelete(Node* root, int key);
void rebalanceRight(Node * node);
void rebalanceLeft(Node * node);
bool isUnbalanced(Node * root);
Node * rebalance(Node * node, int key);

void inorder(Node * currentPtr) {
  // Only traverse the node if it's not null.
  if (currentPtr != NULL) {
    inorder(currentPtr->left); // Go Left.
    cout << " " << currentPtr->key; // Print the root.
    inorder(currentPtr->right); // Go Right.
  }
}

Node * insert(Node * root, Node * element) {
  // Inserting into an empty tree.
  if (root == NULL) {
    element->height = 0;
    return element;
  } 
  else {
    // element inserted to the right.
    element->height++;
    //* element->parent = parent(root, element);
    if (element->key > root->key) {
      if (root->right != NULL)
      {
        root->right = insert(root->right, element);
      }
      // Place the node to the right of root.
      else
      {
        root->right = element;
        element->parent = parent(root, element);

      }
    }
    // element inserted to the left.
    else {
      if (root->left != NULL)
        {
          root->left = insert(root->left, element);
        }
      //Place the node to the left of root.
      else
        root->left = element;
        element->parent = parent(root, element);
    }
    //Return the root pointer of the tree.
    return root;
  }
}

int find(Node * currentPtr, int val) {
  // Check if there are nodes in the tree.
  if (currentPtr != NULL) {
    // Found the value at the root.
    if (currentPtr->key == val)
      return 1;
    // Search to the left.
    if (val < currentPtr->key)
      return find(currentPtr->left, val);
    // Or search to the right.
    else
      return find(currentPtr->right, val);
  } else
    return 0;
}

int add(Node * currentPtr) {
  if (currentPtr != NULL)
    return currentPtr->key + add(currentPtr->left) +
      add(currentPtr->right);
  else
    return 0;
}

// Returns the parent of the node pointed to by node in the tree rooted at
// root. If the node is the root of the tree, or the node doesn't exist in
// the tree, null will be returned.
Node * parent(Node * root, Node * node) {
  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;
  // The root is the direct parent of node.
  if (root -> left == node || root -> right == node)
    return root;
  // Look for node's parent in the left side of the tree.
  if (node -> key < root -> key)
    return parent(root -> left, node);
  // Look for node's parent in the right side of the tree.
  else if (node -> key > root -> key)
    return parent(root -> right, node);
  return NULL; // For any other cases.
}

// Returns the parent of the node pointed to by node in the tree rooted at
// root. If the node is the root of the tree, or the node doesn't exist in
// the tree, null will be returned.
Node * findParent(Node * root, Node * node) {
  // Take care of NULL cases.
  if (root == NULL || root == node)
    return NULL;
  // The root is the direct parent of node.
  if (root->left == node || root->right == node)
    return root;
  // Look for node's parent in the left side of the tree.
  if (node->key < root->key)
    return parent(root->left, node);
  // Look for node's parent in the right side of the tree.
  else if (node->key > root->key)
    return parent(root->right, node);
  return NULL; // For any other cases.
}

// Returns a pointer to the node storing the minimum value in the tree
Node * minVal(Node * root) {
  // Root stores the minimal value.
  if (root->left == NULL)
    return root;
  // The left subtree of the root stores the minimal value.
  else
    return minVal(root->left);
}

// Returns a pointer to the node storing the maximum value in the tree
Node * maxVal(Node * root) {
  // Root stores the maximal value.
  if (root->right == NULL)
    return root;
  // The right subtree of the root stores the maximal value.
  else
    return maxVal(root->right);
}

// Returns 1 if node is a leaf node, 0 otherwise.
int isLeaf(Node * node) {
  return (node->left == NULL && node->right == NULL);
}

// Returns 1 iff node has a left child and no right child.
int hasOnlyLeftChild(Node * node) {
  return (node->left != NULL && node->right == NULL);
}

// Returns 1 iff node has a right child and no left child.
int hasOnlyRightChild(Node * node) {
  return (node->left == NULL && node->right != NULL);
}

// Returns a pointer to a node that stores value in it in the subtree
Node * findNode(Node * currentPtr, int value) {
  if (currentPtr == NULL) {
    return NULL;
  }
  // Found the value at the root.
  if (currentPtr->key == value) {
    return currentPtr;
  }
  if (value < currentPtr->key) {
    return findNode(currentPtr->left, value);
  } else {
    return findNode(currentPtr->right, value);
  }
}

Node * deleteNode(Node * root, int value) {
  Node * delnode, *newDelNode, *saveNode;
  Node * parent;
  int temp;
  delnode = findNode(root, value); 
  parent = findParent(root, delnode); 
  if (isLeaf(delnode)) {
    if (parent == NULL) {
      delete root;
      return NULL;
    }
    if (value < parent->key) {
      delete parent->left;
    }
    else {
      delete parent->right;
      parent->right = NULL;
    }
    return root;
  }
  if (hasOnlyLeftChild(delnode)) {
    if (parent == NULL) {
      saveNode = delnode->left;
      delete delnode;
      return saveNode;
    }
    if (value < parent->key) {
      saveNode = parent->left;
      parent->left = parent->left->left;
      delete saveNode;
    }
    else {
      saveNode = parent->right;
      parent->right = parent->right->left;
      delete saveNode;
    }
    return root;
  }
  if (hasOnlyRightChild(delnode)) {
    if (parent == NULL) {
      saveNode = delnode->right;
      delete delnode;
      return saveNode;
    }
    if (value < parent->key) {
      saveNode = parent->left;
      parent->left = parent->left->right;
      delete saveNode;
    }
    else {
      saveNode = parent->right;
      parent->right = parent->right->right;
      delete saveNode;
    }
    return root;
  }
  newDelNode = minVal(delnode->right);
  temp = newDelNode->key;
  deleteNode(root, temp);
  delnode->key = temp;
  return root;
}

// Prints out the menu of choices for the user and returns their choice.
int menu() {
  int ans;
  cout << "Here are your choices.\n";
  cout << "1. Insert an item into your tree.\n";
  cout << "2. Delete an item from your tree.\n";
  cout << "3. Search for an item in your tree.\n";
  cout << "4. Print the sum of the nodes. \n";
  cout << "5. Print the next element of the node with key x.\n";
  cout << "6. Print the elements between x, and y\n";
  cout << "7. Print the height of the tree with root x\n";
  cout << "8. Print the sum of the list of elements between x, and y\n";
  cout << "9. Print out an in-order traversal\n";
  cout << "0. Exit.\n";
  cin >> ans;
  return ans;
}

//Inserts a given node to the tree
Node * avlinsert(Node * node, int key) 
{

  

  if (node == NULL)

    return (newNode(key));

  if (key < node->key)

    node->left = avlinsert(node->left, key);

  else if (key > node->key)

    node->right = avlinsert(node->right, key);

  else  

    return node; 

  node->height = 1 + max(height(node->left), height(node->right));


  if(isUnbalanced(node))
  {
    return rebalance(node, key);
  }

  return rebalance(node,key);

  
  return node;
}

//Used to find the height of a given node
int height(Node * N) {

  if (N == NULL)

    return 0;

  return N->height;
}

//Finds the max of two node values
int max(int a, int b) {

  return (a > b) ? a : b;
}

//Used to create new node using a given key
Node * newNode(int key) {

  Node * node = new Node();

  node->key = key;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;  

  return (node);
}

//Conducts the right rotate 
Node * rightRotate(Node * y) {

  Node * x = y->left;
  Node * T2 = x->right; 

  x->right = y;
  y->left = T2;

  y->height = max(height(y->left), height(y->right)) + 1;

  x->height = max(height(x->left), height(x->right)) + 1;

  return x;
}

//Conducts the left rotate 
Node * leftRotate(Node * x) {

  Node * y = x->right;
  Node * T2 = y->left; 

  y->left = x;
  x->right = T2; 

  x->height = max(height(x->left), height(x->right)) + 1;

  y->height = max(height(y->left), height(y->right)) + 1; 

  return y;
}

// Get Balance factor of a working node 

int getBalance(Node * N) {

  if (N == NULL)

    return 0;

  return height(N->left) - height(N->right);
}


//Return vector of node values between a range
vector<int> rangeSearch(int low, int high, Node * root)
{

  vector<int> myVect;
  Node * temp = findNode(root, low);

  while(temp->key <= high)
  {

    myVect.push_back(temp->key);

    temp = next(root, temp);    

    if(temp == NULL)
    break;
    

  }

  return myVect;



}

//Finds the height of the node 
int computeHeight(Node * targetNode)
{

  return targetNode->height;

}

//Find the next biggest node
Node * next(Node * root, Node * N)
{

  if(N->right != NULL)
  {

    return leftDescendant(N->right);

  }
  else
  {

    return rightAncestor(root, N);

  }

  

}

//Return leftDescendant of working node
Node * leftDescendant(Node * N)
{

  if(N->left == NULL)
  {

    return N;

  }
  else
  {
    return leftDescendant(N->left);
  }

}

//Return rightAncestor of working node
Node * rightAncestor(Node * root, Node * N)
{
  if(parent(root,N) == NULL){
    return NULL;
  }
  if(N->key < parent(root,N)->key)
  {
    if(parent(root, N) == NULL)
    {

      return N;

    }

    return parent(root,N);
  }
  else
  {
    return rightAncestor(root, parent(root, N));
  }

}

//Delete the given node and then reblance if necessary
Node* avlDelete(Node* root, int key) {
    if (root == NULL) {
        return root;
    }
    if (key < root->key) {
        root->left = avlDelete(root->left, key);
    }
    else if (key > root->key) {
        root->right = avlDelete(root->right, key);
    }
    else {
        if (root->left == NULL || root->right == NULL) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == NULL) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            delete temp;
        }
        else {
            Node* temp = minVal(root->right);
            root->key = temp->key;
            root->right = avlDelete(root->right, temp->key);
        }
    }
    if (root == NULL) {
        return root;
    }
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);
    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rightRotate(root);
    }
    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0) {
        return leftRotate(root);
    }
    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

//Rebalances a target node
Node * rebalance(Node * node, int key)
{

  int balance = getBalance(node); 

  if (balance > 1 && key < node->left->key)
  {

    return rightRotate(node);
  }
  // Right Right Case 

  if (balance < -1 && key > node->right->key)
  {
    return leftRotate(node);
  }
  // Left Right Case 

  if (balance > 1 && key > node->left->key)
  {

    rebalanceLeft(node);

    return rightRotate(node);

  }

  // Right Left Case 

  if (balance < -1 && key < node->right->key)
  {


    rebalanceRight(node);

    return leftRotate(node);

  }


  return node;

}

//Determines whether or not a node is balanced
bool isUnbalanced(Node * root)
{

  if(root == NULL)
  {

    return false;

  }

  int leftNodeHeight = height(root->left);
  int rightNodeHeight = height(root->right);

  if(abs(leftNodeHeight - rightNodeHeight) > 1)
  {
    return true;
  }

  return isUnbalanced(root->left) || isUnbalanced(root->right);

}

//rebalances the right of a target node
void rebalanceRight(Node * node)
{

  node->right = rightRotate(node->right);

}

//rebalances the left of a target node 
void rebalanceLeft(Node * node)
{

 node->left = leftRotate(node->left); 
  

}

int main() 
{

  Node * root = NULL;

  Node * tempNode;
  int done = 0, ans = 1, val;
  int low, high, sum = 0;
  ans = menu();
  while (ans != 0) {
    switch (ans) {
    case 1:
      // Get value to insert.
      cout << "What value would you like to insert?\n";
      cin >> val;
      // Insert the value.
      root = avlinsert(root, val);

      break;
    case 2:
      cout << "What value would you like to delete?\n";
      cin >> val;
      if (!find(root, val)) {
        cout << "Sorry that value isn't in the tree to delete.\n";
      } else {
        //root = deleteNode(root, val);
        avlDelete(root, val);
      }
      break;
    case 3:
      cout << "What value would you like to search for?\n";
      cin >> val;
      if (find(root, val)) {
        cout << " Found" << val << "in the tree.\n";
      } else {
        cout << " Did not find %d in the tree.\n";
      }
      break;
    case 4:
      cout << "The sum of the nodes in your tree is" << add(root) << "\n";
      break;
    case 5:
      cout << "What is the target node?\n";
      cin >> val;

      if (!find(root, val)) {
        cout << "Node does not exist";
      } else {
        Node * temp = next(root, findNode(root, val));
        cout << "The value of the next node is " << temp->key;
      }
      break;
    case 6:
      int low, high;
      cout << "What are the low and high?" << std::endl;
      cin >> low >> high;

      if (find(root, low) && find(root, high)) {
        vector < int > vectDisp = rangeSearch(low, high, root);
        cout << endl;
        for (int x: vectDisp) {
          cout << x << " ";
        }
        cout << endl;
      } else {
        cout << "One or two values does not exist" << std::endl;
      }
      break;
    case 7:
      cout << "What is the target node?\n";
      cin >> val;

      if (!find(root, val)) {
        cout << "The node does not exist" << std::endl;
      } else {
        cout << "The height of the target node is " << computeHeight(findNode(root, val)) << std::endl;
      }
      break;
    case 8:
      cout << "What are the two values?" << std::endl;
      cin >> low >> high;

      if (find(root, low) & find(root, high)) {
        vector < int > vectDisp = rangeSearch(low, high, root);
        for (int x: vectDisp) {
          sum += x;
        }
        cout << "Sum between " << low << " and " << high << " is " << sum << endl;
      } else {
        cout << "One or two values does not exist" << std::endl;
      }
      break;
    case 9:
      // Print the resulting tree.
      cout << "Here is an inorder traversal of your tree: ";
      inorder(root);
      cout << "\n";
      break;
    case 0:
      std::cout << "exit" << std::endl;
      break;
    default:
      std::cout << "Invalid Input" << std::endl;
      break;
    };

    // See if they want to insert more nodes.
    ans = menu();
  }

  return 0;
}