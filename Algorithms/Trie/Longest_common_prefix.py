class Trie:

    def __init__(self):
        self.children = {}
        self.is_end = False

    def insert(self, target):
        node = self
        for ch in target:
            if ch not in node.children:
                node.children[ch] = Trie()
            node = node.children[ch]
        node.is_end = True


def longest_common_prefix(strs):
    lcp = ""

    trie = Trie()

    for s in strs:
        trie.insert(s)

    node = trie

    while not node.is_end:
        keys = list(node.children.keys())

        if len(keys) != 1:
            break

        ch = keys[0]
        lcp += ch
        node = node.children[ch]

    return lcp


print(longest_common_prefix(["flower", "flow", "flight"]))  # Output: "fl"
print(longest_common_prefix(["ab", "abc", "abcd"]))         # Output: "ab"
