
def combinations(n, k):
    
    def generate(start, comb):
        if len(comb) == k:
            print(comb)
            return 

        for i in range(start, n + 1):

            comb.append(i);
            generate(i + 1, comb)
            comb.pop()

    generate(1,[])

combinations(4, 2)

