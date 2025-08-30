# Variables
def variables():
    a = "Hello"
    b = True
    c: tuple[float, float] = (2.5, 2.4) # tuple with type annotaitons
    d = [1,2,3]
    e = 'A'
    f = {1,4,6} # set 
    g = {"bibi": 1, "james": 2} # hahsmap
    
    print(10 + int(e)) # casting char to int
    
# F Strings
def f_strings(name: str) -> str:
    return f"Hello{name}"

# List and dict comprehension
def comprehension():
    a = [0 for _ in range(10)]
    b = {i for i in range(10)} 

# Error Handling
def error_handling():
    a = 10
    b = "Hello"

    try:
        print(a + a)
    except Exception as e:
        print("Sike")

def lists(a: list[int]):
    
    c = a[:-1] # copy the reversed list

