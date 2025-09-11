
def permute(n):
    
    res = []
    def permute_rec(per):

        if len(per) == n:
            res.append(per.copy())
            return

        for i in range(1, n + 1):

            if i in per:
                continue

            per.append(i)
            permute_rec(per)
            per.pop()
    

    permute_rec([])
    

    print(f"Permutations: {len(res)}")
    print(res)

permute(5)

