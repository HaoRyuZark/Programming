pub struct Stack<T> {
    vec: Vec<T>,
}

pub struct Queue<T> {
    vec: Vec<T>,
}

impl<T> Queue<T> {
    pub fn new() -> Self {
        Self {
            vec: Vec::new(),
        }
    }

    pub fn enqueue(&mut self, val: T) {
        self.vec.push(val);
    }

    pub fn dequeue(&mut self) -> Option<T> {
        if self.vec.is_empty() {
            None
        } else {
            Some(self.vec.remove(0))
        }
    }

    pub fn len(&self) -> usize {
        self.vec.len()
    }

    pub fn peek(&self) -> Option<&T> {
        self.vec.first()
    }

    pub fn is_empty(&self) -> bool {
        self.vec.is_empty()
    }
}

impl<T> Stack<T> {
    pub fn new() -> Self {
        Self {
            vec: Vec::new(),
        }
    }

    pub fn push(&mut self, val: T) {
        self.vec.push(val);
    }

    pub fn pop(&mut self) -> Option<T> {
        self.vec.pop()
    }

    pub fn len(&self) -> usize {
        self.vec.len()
    }

    pub fn peek(&self) -> Option<&T> {
        self.vec.last()
    }

    pub fn is_empty(&self) -> bool {
        self.vec.is_empty()
    }
}
fn main() {

}
