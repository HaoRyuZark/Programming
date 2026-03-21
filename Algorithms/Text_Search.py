
def longest_prefix_suffix_table(pattern: str) -> list[int]:

    pattern_len = len(pattern)
    
    i = 1 
    j = 0
    
    res = [0 for _ in range(0,pattern_len)]

    while i <= pattern_len - 1:

        if pattern[i] == pattern[j]:

            j += 1
            res[i] = j 
            i += 1

        else:

            if j != 0:
                j = res[j - 1]
            else:
                i += 1

    return res

def knp_text_search(text:str, pattern:str) -> list[int]:

    res = []
    text_len = len(text) 
    pattern_len = len(pattern)
    
    if pattern_len > text_len:
        return res 

    table = longest_prefix_suffix_table(pattern)

    i = 0 
    j = 0

    while i <= text_len:
        
        while pattern[j] == text[i]:

            j += 1 
            i += 1

        if j == pattern_len:
            res.append(i - pattern_len)
            j = table[j - 1]

        elif i < text_len and text[i] != pattern[j]:
            
            if j == 0:
                i += 1
            else:
                j = table[j - 1]
            

    return res


def bad_character_heuristic(pattern: str) -> list[int]:

    table = [-1 for i in range(0, 256)]

    for i in range(0, len(pattern)):
        
        table[ord(pattern[i])] = i
    
    return table


def good_suffix_heuristic(pattern: str) -> list[int]:
    return [] 

def booyer_moore_text_search(text: str, pattern: str) -> list[int]:
    
    res = []
    text_len = len(text)
    pattern_len = len(pattern)
    
    if pattern_len > text_len:
        return res
    
    last_table =bad_character_heuristic(pattern)
    
    i = 0 

    while i <= text_len - pattern_len: 

        j = pattern_len - 1

        while j >= 0 and text[i + j] == pattern[j]:
            j -= 1

        if j < 0:
           
            res.append(i)
            i += (pattern_len - last_table[ord(text[i + pattern_len])]) if i + pattern_len < text_len else 1

        else:
   
            i += max(1, j - last_table[ord(text[i + j])])
    
    return res
  



