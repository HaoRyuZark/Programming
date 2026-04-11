'''
Union Find:

Graph/Tree like data struture which is used to store and get information about 
'groups'. 

The naive approach is to make an array of sets. This works perfectly but is slow.
The preferred approach is to represent the sets as numerical array entries. With the root 
being the representative.

The operations supported are 
    
    - find(x: element) -> representative of the group(parent)
    - union(x: element, y:element) -> root becomes child of the other root -> new combined group

Note that in the array used to store the 'tree' already all elements are considered to exist but 
in separate sets. We are just uniting them.

 Example (simplified):

 1 2 3 4 5

 -> union(3, 4)

 1 2 3 5
     |
     4

-> find(4) = 3

-> union(4, 5)

 1 2 3
     | \
     4  5
'''

class union_find:
    
    parent:list[int] # this can be a hashmap or whatever. For numbers a normal array is enougth

    # optionaly we can add a size array for the size of each set
    # optionaly the rank(depth of the deepest set) can be also be added.  

    def __init__(self, size) -> None:
        self.parent = list(range(size))
    
    def make_set(self, x):  # For the case we habdle the others as not initialized
        self.parent[x] = x

    def find(self, x):

        if self.parent[x] == x:  # representative found 
            return x

        else: 
            self.parent[x] = self.find(self.parent[x]) # optimized recursive call to traverse the the tree upwards
                                                       # and also set the middle elements of the chain as stand alone 
                                                       # children of the representative
                                                       
        
            return self.parent[x] 

    def union(self, x, y): # get both representatives and then set one as the children of the other

        self.parent[self.find(y)] = self.find(x) # the root of y becomes a children of the root of x
       


uf = union_find(10)
uf.union(3, 4)
print(uf.find(4))
uf.union(4,5)


