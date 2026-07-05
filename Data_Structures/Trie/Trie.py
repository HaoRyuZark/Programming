class Trie_Node: 
    
    is_end: bool
    children: dict[str, Trie_Node]

    def __init__(self) -> None:
        self.children = {}
        self.is_end = False
    
    def insert(self, s):

        # Start at the root
        node = self 

        # Iterate over the character in s
        for char in s: 
            
            # if the character is not found in the current hashmap, create a new Trie and add it to the hashmap
            if char not in node.children: 
                node.children[char] = Trie_Node()

            # Move to the next node in the trie
            node = node.children[char]   
        
        node.is_end = True #set the end

    def search(self, string):
        
        node = self

        for ch in string:

            if ch not in node.children:
                return None

            node = node.children[ch]

        return node if node.is_end else None


    def delete(self, target):
        
        def rec(node, target, idx) -> bool:

            # If we have reached the end of the target string, we mark the current node as not an end node and check if it has any children. 
            # If it doesn't have any children, we return True to indicate that this node can be deleted.  
            if idx == len(target):
                node.is_end = False
                return len(node.children) == 0
            
            else:

                # If we are not at the end of the target string, we recursively call the function on the child node 
                # corresponding to the current character in the target string.
                next_to_delete = rec(node.children[target[idx]], target, idx + 1)

               # Only if the child node can be deleted (i.e., it has no children and is not an end node), we delete the child node from the current node's children dictionary. 
                if next_to_delete:
                    del node.children[target[idx]]

                # Continue returning whether the current node can be deleted. 
                # A node can be deleted if it is not an end node and has no children.
                return next_to_delete and not node.is_end and len(node.children) == 0

        # delte only if the target string is found in the trie
        if self.search(target):
            rec(self, target, 0)

    
    def list_all(self):

        def rec(node, string, strings):
        
            if node.is_end:     # end found -> form string
                strings.append("".join(string))

            for ch, child in node.children.items():

                string.append(ch) # choose
                rec(child, string, strings) # call with new string
                string.pop()            # backtrack
    
    
        strings = []
        rec(self, [], strings)
        return strings


class Trie:
    
    root: Trie_Node

    def __init__(self) -> None:
        self.root = Trie_Node()

    def insert(self, s):
        self.root.insert(s)

    def search(self, string):
        return self.root.search(string)

    def delete(self, target):
        self.root.delete(target)

    def list_all(self):
        return self.root.list_all()



trie = Trie()

trie.insert("hello")
trie.insert("hell")
trie.insert("heaven")
trie.insert("goodbye")

print(trie.list_all())  # Output: ['hell', 'hello', 'heaven', 'goodbye']
trie.delete("hello")
print(trie.list_all())  # Output: ['hell', 'heaven', 'goodbye']
trie.search("hello")  # Output: None