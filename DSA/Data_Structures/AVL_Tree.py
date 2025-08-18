'''
AVL Trees:
    - self balancing binary seach Trees
    - perform fixes after insert and delete (height balanced)
    - guarantees specific time complexity for operations O(log n) -> search, insert, delete
    - height = number of nodes on the longest path from the root to a leaf
    - for any node, the height of its two subtrees differs by at most 1
    - balance factor = height of the left subtree - hight of the right subtree {-1, 0, 1}

Use cases:
    - lookup intensive applications


Operations:
    
    - Search: Binary Search
    
    - Insertion: During this operation if the tree becomes invalanced there are three types of rotations we can do:
        
        - Left Rotate: Here the right child (B) of the target node (A) becomes the parent and the left child of B the right 
          child of A

                        A                   B
                      /   \      left     /   \
                     X     B   ------>   A     z
                          / \           / \
                         Y   Z         X   Y
        
        - Right Rotate: Here the left child (A) of the target node (B) becomes the parent and the left child of A the right 
          child of B 

                        B                   A
                      /   \      right    /   \
                     A     Z   ------>   X     B  
                    / \                       / \
                   X   Y                      Y  Z
        
        - Double Rotation: This case happens when after a right or left rotation the tree is still invalanced. To solve this we have left-right and right-left Rotations
            
                        C                   C                  B
                      /   \      left     /   \     right    /   \
                     A     Z   ------>   B     Z   ----->   A     C
                    / \                 / \                / \   / \
                   W   B               A   Y              W   X Y   Z 
                      / \             / \ 
                     X   Y           W   X

   - Deletion: This operation at the start is just like the delete operation on a binary search tree. The only difference is that after the delete portion 
     we have to check that the tree is balanced like before and rotate respectively
'''

from typing import Optional


class Node:

    def __init__(self, key):
        
        self.key = key
        self.right = None
        self.left = None 
        self.height = 1

class AVL_Tree:

    def __init__(self):
        self.root = None
        
    
    def search(self, key):

        x = self.root

        while x is not None and key != x.key:

            if key < x.key:
                x = x.left
            else:
                x = x.right

        return x

    def get_height(self, node) -> int:
        return 0 if not node else node.height
    
    def get_balance_factor(self, node) -> int:
        return 0 if not node else (self.get_height(node.left) - self.get_height(node.right))
    
    def get_min_node(self, node):
        return node if not node or not node.left else self.get_min_node(node.left)
    
    '''

                        A                   B
                      /   \               /   \
                     X     B   ------>   A     z
                          / \           / \
                         Y   Z         X   Y
    
    '''    
    def left_rotate(self, node):

        b = node.right # pointer to the right subtree  ( A -> B )  
        y = b.left  # pointer to the left subtree   ( B -> Y  )

        b.left = node  #  set B as parent of A
        node.right = y #  set left child of B as child of A

        #Updating height
        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))         
        b.height = 1 + max(self.get_height(b.left), self.get_height(b.right))
    
        return b

    '''
                        B                   A
                      /   \               /   \
                     A     Z   ------>   X     B  
                    / \                       / \
                   X   Y                      Y  Z
        
    ''' 
    def right_rotate(self, node):

        a = node.left # pointer to the left subtree  ( B -> A )  
        y = a.right  # pointer to the right subtree   ( A -> Y  )

        a.right = node  #  set B as parent of A
        node.left = y #  set left child of B as child of A

        #Updating height
        node.height = 1 + max(self.get_height(node.left), self.get_height(node.right))         
        a.height = 1 + max(self.get_height(a.left), self.get_height(a.right))
    
        return a 


    def insert(self, root, key):
        
        # Recursive call struture for reaching the desired position
        if not root:
            return Node(key)

        elif key < root.key:
            root.left = self.insert(root.left, key)

        else:
            root.right = self.insert(root.right, key)
        
        # Updating the height
        root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))
        
        # Getting the balance factor
        # bf > 1 -> left Heavy
        # bf < -1 -> right heavy
        bf = self.get_balance_factor(root)
        
        # Left Heavy
        if bf > 1 and key < root.left.key:
            self.right_rotate(root)
        
        # Right heavy
        if bf < -1 and key > root.right.key:
            self.left_rotate(root)
        
        # Left heavy -> right heavy -> balanced
        if bf > 1 and key > root.left.key:
            root.left = self.left_rotate(root)
            return self.right_rotate(root)
       
        # Right heavy -> left heavy -> balanced
        if bf < -1 and key < root.right.key:
            root.right = self.right_rotate(root)
            return self.left_rotate(root)
        
        # No invalance after insertion
        return root

    def delete(self, root, key):

        if not root:
            return root

        elif key < root.key:
            root.left = self.delete(root.left, key)

        elif key > root.key:
            root.right = self.delete(root.right, key)

        else:

            if not root.left:
                temp = root.right
                root = None
                return temp
            
            elif not root.right:
                temp = root.right
                root = None
                return temp
            
            # Case Two children
            temp = self.get_min_node(root.right)
            root.key = temp.key
            root.right = self.delete(root.right, temp.key)
            
            root.height = 1 + max(self.get_height(root.left), self.get_height(root.right))

            bf = self.get_balance_factor(root)

            if bf > 1 and self.get_balance_factor(root.left) >= 0:
                return self.right_rotate(root)

            if bf < -1 and self.get_balance_factor(root.right) <= 0:
                return self.left_rotate(root)

            if bf > 1 and self.get_balance_factor(root.left) < 0:
                root.left = self.left_rotate(root.left)
                return self.right_rotate(root)

            if bf < -1 and self.get_balance_factor(root.right) > 0:
                root.right = self.right_rotate(root.right)
                return self.left_rotate(root)

            return root


