
"""
Generating all words 
"""

def generate_words():

    alphabet = ['o', 'p', 't', 'r']
    count = 0 # expected 1.364
    
    for i in range(1,6): 
        count += generate(i, "", alphabet)
    
    print(count)

"""
Will return the number of words 
"""
def generate(length, word, alphabet):
   
    # Recursive case, a word of len x was generated
    if len(word) == length:
       print(word)
       return 1 
    
    count = 0
    
    # Take a different letter and keep counting
    for c in alphabet:
       count += generate(length, word + c, alphabet)
    
    return count

def count_words():
    
    letters = ['o', 'p', 't', 'r']
    count = 0

    def count_rec(oc, tc, pc, rc, word):
        nonlocal count

        # stop condition
        if len(word) == 5:
            if oc == 2 and tc == 2 and pc + rc == 1:
                count += 1
                print(word)
            return

        for c in letters:
            if c == 'o' and oc < 2:
                count_rec(oc + 1, tc, pc, rc, word + 'o')
            elif c == 't' and tc < 2:
                count_rec(oc, tc + 1, pc, rc, word + 't')
            elif c == 'p' and pc < 1:
                count_rec(oc, tc, pc + 1, rc, word + 'p')
            elif c == 'r' and rc < 1:
                count_rec(oc, tc, pc, rc + 1, word + 'r')

    count_rec(0, 0, 0, 0, "")
    print("Total:", count)

"""
Generating Words by brute force
"""
def print_all_words():
  
  le = ['o', 'p', 't', 'r']
  count = 0

  for i in range(0,4):
    for j in range(0,4):
      for k in range(0,4):
        for l in range(0,4):
          for o in range(0,4):
            word = le[i] + le[j] + le[k] + le[l] + le[o] 
            count += check_word(word)
  
  print(count) # expected 60

def check_word(word):
  
  o = 0
  t = 0

  for c in word:
    if c == 'o':
      o += 1
    if c == 't':
      t += 1
  
  if t == 2 and o == 2:
    print(word)
    return 1
  return 0

generate_words()
