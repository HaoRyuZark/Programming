
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

    def insertion(self, key):
        
        root = self.root 

        if root.is_full(self.t): # has 2t - 1 children 
            root = self.split_root()

        self.insert_not_full(root, key)

    def split_child(self, u, i):
        
        t = self.t 
        full_node = u.children[i] # pointer to ith child 

        new_node = Node()
        new_node.is_leaf = full_node.is_leaf
        new_node.keys = full_node.keys[t:] # copying keys after the median 

        if not full_node.is_leaf:
            new_node.children = full_node.children[t:] # same as above but for the pointers 

        u.children.insert(i + 1, new_node) # inserting the new node's key and value reference in the parent 
        u.keys.insert(i, full_node.keys[t - 1]) # inserting the median 

        full_node.keys = full_node.keys[:t - 1] # adjusting keys to go only until one before the median 
        full_node.children = full_node.children[:t] # same here but for the children 

    
    def split_root(self):
        
        new_root = Node()
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
                i = i if key <= u.keys[i] else i + 1 # choosing between right and left for the new key 
            
            self.insert_not_full(u.children[i], key) # applying the algorithm again until the key can be inserted

        
    def deletion(self, key):
        pass
        
class Node:
    
    def __init__(self) -> None:
        self.is_leaf = False 
        self.keys = []
        self.children = []


    def is_full(self, t) -> bool:
        
        if len(self.keys) == 2*t - 1:
            return True 

        return False
