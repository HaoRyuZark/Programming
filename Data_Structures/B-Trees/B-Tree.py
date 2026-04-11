
class B_Tree:
    
    def __init__(self, t) -> None:
        self.t = t 

    def search(self, u, key):
    
        i = 0 
        # linear scan to find the key
        while i < len(u.keys) and key > u.keys[i]: # as long as the key is greater
            i += 1

        if i < len(u.keys) and key == u.keys[i]: # if we are within the bound and the value of the keys are identical 
            return (u, i)

        if u.is_leaf:       # Not found
            return None 

        return self.search(u.children[i], key)

    def insertion(self, key): # Fix then insert approach
        
        root = self.root 

        if root.is_full(self.t): # has 2t - 1 children 
            root = self.split_root()

        self.insert_not_full(root, key)

    def split_child(self, u, i):
        
        t = self.t 
        
        full_node = u.children[i] # pointer to ith full child 

        new_node = Node()
        new_node.is_leaf = full_node.is_leaf
        new_node.keys = full_node.keys[t:]      # copying keys after the median 

        if not full_node.is_leaf:               # transfer children if not leaf
            new_node.children = full_node.children[t:] # same as above but for the pointers 

        u.children.insert(i + 1, new_node) # inserting the new node's key and value reference in the parent 
        u.keys.insert(i, full_node.keys[t - 1]) # inserting the median 

        full_node.keys = full_node.keys[:t - 1] # adjusting keys to go only until one before the median 
        full_node.children = full_node.children[:t] # same here but for the children 

    
    def split_root(self):
        
        new_root = Node()
        new_root.is_leaf = False
        new_root.children = [self.root]

        self.root = new_root

        self.split_child(new_root, 0) # splitting the full root
        
        return new_root
    
    def insert_not_full(self, u, key):
        
        i = 0       
        while i < len(u.keys) and key > u.keys[i]: # linear scan
            i += 1

        if u.is_leaf:               # can insert
            u.keys.insert(i, key)

        else:
            if u.children[i].is_full(): # if the target node is full
                
                self.split_child(u, i)          # split the node
                i = i if key <= u.keys[i] else i + 1 # choosing between left and right for continuing the algorithm
            
            self.insert_not_full(u.children[i], key) # applying the algorithm again until the key can be inserted


    def delete(self, u, key):
        
        i = 0       

        while i < len(u.keys) and key > u.keys[i]: # linear scan
            i += 1

        # Case 1
        if u.is_leaf:
            
            if i < len(u.keys) and key == u.keys[i]:
                u.keys.pop(i) 
            else:
                raise KeyError(f"{key} not fount")
            return 
        
        # Case 2
        if i < len(u.keys) and key == u.keys[i]:

            if len(u.children[i].keys) >= self.t:                       # Case 2a: The children has enough keys 
                pred_key = self.maximum(u.children[i])                  # getting key of the predecessor  
                self.delete(u.children[i], pred_key)                    # deleting the predecessor 
                u.keys[i] = pred_key                                    # updating the key

            elif len(u.children[i+1].keys) >= self.t:                   # Case 2b: the next child has enough keys 
                succ_key = self.minimum(u.children[i + 1])              # Same as above but with the successor
                self.delete(u.children[i + 1], succ_key)
                u.keys[i] = succ_key 

            else:                                                       # Case 2c: both children have t - 1 keys therefore, merge and then delete by recursion
                self.merge_children(u, i) 
                if self.root == u and not u.keys:
                    self.root = u.children[0] 
                self.delete(u.children[i], key)
        
        # Case 3: Key not found. Keep searching and ensure the next node has more than t keys
        else:
            
            if len(u.children[i].keys) >= self.t:                       # the next node has enough keys 
                self.delete(u.children[i], key)                         # continue recursion 
        
            elif self.has_sibling_with_t_keys(u, i):                    # Case 3a: 
                
                j = self.index_of_sibling_with_t_keys(u, i) 
                
                if j == i + 1:                                          # sibling with t >= keys to the right
                
                    u.children[i].keys.append(u.keys[i])                # give the ith key of u to the ith child (left one) 
                    u.keys[i] = u.children[j].keys.pop(0)               # replace the key by the first of the right sibling 

                    if not u.children[j].is_leaf:                       # if the ith child is not a leaf: tranfer the child
                        first_child = u.children[j].children.pop(0)     # take first child 
                        u.children[i].children.append(first_child)      # put it at the end of the right of the other child
                
                else:                                                   # sibling with t >= keys to the left 

                    u.children[i].keys.insert(0, u.keys[j])             # give ith key to the ith child (right one) 
                    u.keys[j] = u.children[j].keys.pop()                # replace the key by the last of the left sibling

                    if not u.children[j].is_leaf:                       # transfer last child
                        u.children[j].children.insert(0, u.children[j].children.pop())


                self.delete(u.children[i], key)                           # continue after adjusting the children nodes

            else: # No sibling has enough keys 

                if i > 0:
                    self.merge_children(u, i - 1) # merge with left
                    i = i - 1
                else:
                    self.merge_children(u, i) # merge with right  

                if self.root == u and not u.keys: # if the root has no keys 
                    self.root = u.children[0]     # adjust the height 

                self.delete(u.children[i], key)


    def merge_children(self, u, i):

        median_key = u.keys.pop(i)                          # geth ith key 
        
        u.children[i].keys.append(median_key)               # give it to the left child  
        sibling_keys = u.children[i + 1].keys               # get keys fron the right child 
        u.children[i].keys.extend(sibling_keys)             # append the keys 

        if not u.children[i].is_leaf:                       # if it not a leaf copy the children from the right to the left child 
            sibling_children = u.children[i + 1].children 
            u.children[i].children.extend(sibling_children) 

        u.children.pop(i + 1)                               # pop the right childs key
    
    def index_of_sibling_with_t_keys(self, u, i):

        if i > 0 and  len(u.children[i - 1].keys) >= self.t:
            return i - 1 
        if i < len(u.children[i + 1].keys) >= self.t:
            return i + 1 

        raise ValueError("No sibling")

    def has_sibling_with_t_keys(self, u, i):

        left = i > 0 and  len(u.children[i - 1].keys) >= self.t
        right = i < len(u.children) - 1 and i < len(u.children[i + 1].keys) >= self.t

        return left or right
    
    def minimum(self, u):
        while not u.is_leaf:
            u = u.children[0]
        return u.keys[0]
    
    def maximum(self, u):
        while not u.is_leaf:
            u = u.children[-1]
        return u.keys[-1]

class Node:
    
    def __init__(self) -> None:
        self.is_leaf = True 
        self.keys = []
        self.children = []


    def is_full(self, t) -> bool:
        
        if len(self.keys) == 2*t - 1:
            return True 

        return False

    
