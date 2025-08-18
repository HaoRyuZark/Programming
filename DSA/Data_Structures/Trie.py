class Trie: 
    
    is_end: bool
    children: dict[str, Trie]

    def __init__(self) -> None:
        self.children = {}
    
    def insert(self, s):
        
        node = self # Start at the root
        
        for ch in s: # Iterate over the character in s

            if ch not in node.children: # if the character is not found
                node.children[ch] = Trie()    # create a new Trie

            node = node.children[ch]   # move to the next trie
        
        node.is_end = True #set the end

    def search(self, s):
        
        node = self

        for ch in s:

            if ch not in node.children:
                return None
            node = node.children[ch]

        return node if node.is_end else None
    
    def delete(self, s):
        
        def rec(node, s, i):
            
            if i == len(s):
                node.is_end = False
                return len(node.children) == 0
            
            else:
                next_to_delete = rec(node.children[s[i]], s, i + 1)
                
                if next_to_delete:
                    del node.children[s[i]]

                return next_to_delete and not node.is_end and len(node.children) == 0

        if self.search(s):
            rec(self, s, 0)

    
    def list_all(self):

        def rec(node, string, strings):
        
            if node.is_end:     # end found -> form string
                strings.append("".join(string))

            for ch in string:

                string.append(ch) # choose
                rec(node.children[ch], string, strings) # call with new string
                string.pop()            # backtrack
    
    
        strings = []
        rec(self, [], strings)
        return strings


