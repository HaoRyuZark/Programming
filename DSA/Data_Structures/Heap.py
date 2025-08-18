from typing import Optional, List, DefaultDict

def swap(a: int, b: int):
    temp = a
    a = b
    b = temp

class Heap:
    
    arr: list[int]

    def __init__(self) -> None:
       self.arr = []
    
    def get_index(self, val: int) -> int:
        return self.arr.index(val)

    def get_parent(self, i: int) -> int:
        return i - 1 // 2

    def get_left_child(self, i: int) -> int:
        return 2 * i + 1

    def get_right_child(self, i: int) -> int:
        return 2  * i + 2
    
    def shift_down(self):
        
        val_index = 0;
        min_child = min(self.arr[self.get_left_child(val_index)], self.arr[self.get_right_child(val_index)])
        min_index = self.arr.index(min_child)

        while self.arr[val_index] > self.arr[min_index]:

            swap(self.arr[val_index], self.arr[min_index])

            val_index = min_index
            min_child = min(self.arr[self.get_left_child(val_index)], self.arr[self.get_right_child(val_index)])
            min_index = self.arr.index(min_child)

    
    def shift_up(self):
        
        val_index = len(self.arr) - 1
        parent_index = self.get_parent(val_index)

        while val_index != 0 and self.arr[val_index] < self.arr[parent_index]:

            swap(self.arr[val_index], self.arr[parent_index])

            val_index = parent_index
            parent_index = self.get_parent(val_index)


    def enqueue(self, val: int):

        self.arr.append(val)

        self.shift_up()


    def extract_min(self) -> Optional[int]:
         
        if len(self.arr) == 0:
            return None

        res = self.arr[0]
        swap(self.arr[0], self.arr[len(self.arr)])
        self.arr.pop()

        self.shift_down()
        return res





