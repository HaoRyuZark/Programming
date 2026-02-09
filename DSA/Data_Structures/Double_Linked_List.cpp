#include <cstddef>
#include <memory>
#include <iostream>
#include <ostream>

template<typename T>
class Node {

private:
    std::shared_ptr<Node<T>> next;
    std::shared_ptr<Node<T>> previous;
    T data;

public:
     
    explicit Node(T data): data(data), next(nullptr), previous(nullptr) {}
   
    Node(T data, std::shared_ptr<Node<T>> next, std::shared_ptr<Node<T>> previous): data(data), next(next), previous(previous) {}
    
    // Copy Constructor
    Node(const Node& other): 
        data(other.data), 
        next(other.next), // shared ownership
        previous(other.previous) // shared ownership
        {}

    // Move Constructor
    Node (Node&& other) noexcept: data(other.data), next(std::move(other.next)), previous(std::move(other.previous)) {}

    // Assignment operator
    Node& operator=(const Node& other) {
        if (this == &other) {return *this; }
     
        data = other.data;
        next = other.next;
        previous = other.previous;
        return *this;
    }
    
    // Move assignment 
    Node& operator=(Node&& other) noexcept {
        if (this == &other) {return *this; }
        
        data = other.data;
        next = std::move(other.next);
        previous = std::move(other.previous);

        return *this;
    }

    T get_data() const {
        return this->data;
    }

    std::shared_ptr<Node<T>> get_next() const {
        return this->next;
    }

    std::shared_ptr<Node<T>> get_previous() const {
        return this->previous;
    }

    void set_data(T data) {
        this->data = data;
    }

    void set_next(std::shared_ptr<Node<T>> next) {
        this->next = next; // shared ownership
    }

    void set_previous(std::shared_ptr<Node<T>> previous) {
        this->previous = previous; // shared ownership
    }
    
    bool operator==(Node<T>& other) { 
        return this->data == other.data;
    }

    friend std::ostream& operator<<(std::ostream& os, const Node<T>& node) {
        os << node.data;
        return os;
    }
};

template <typename T>
class Double_Linked_List {

private:

    std::shared_ptr<Node<T>> head;
    std::shared_ptr<Node<T>> tail;

    size_t len;

public:
    
    // Default Constructor
    Double_Linked_List(): head(nullptr), tail(nullptr), len(0) {}

    // Parameterized Constructor no pointers
    explicit Double_Linked_List(T data): head(std::make_shared<Node<T>>(Node<T>(data))), tail(head), len(1) {}
    
    // Copy constructor
    explicit Double_Linked_List(const Double_Linked_List<T>& other): head(other.head), tail(other.tail), len(other.len) {}

    // Move constructor 
    Double_Linked_List(Double_Linked_List<T>&& other): head(std::move(other.head)), tail(std::move(other.tail)), len(other.len) {}

    // Assigment Operator
    Double_Linked_List<T>& operator=(const Double_Linked_List<T>& other) {

        if (this == &other) return *this;

        head = other.head;
        tail = other.tail;
        len = other.len;

        return *this;
    }

    void append_at_the_start(T data) {
        
        if (this->head == nullptr) {
            this->head = std::make_shared<Node<T>>(Node<T>(data));
            this->tail = this->head;
            this->len++;
            return;
        };
        
        std::shared_ptr<Node<T>> temp = this->head;
        
        Node<T> node = Node<T>(data, temp, this->tail);

        this->head = std::make_shared<Node<T>>(node);
        temp->set_previous(this->head);
        this->tail->set_next(this->head);
        this->len++;
    }

    void append_at_the_end(T data) {

        if (this->head == nullptr) {
            this->head = std::make_shared<Node<T>>(Node<T>(data));
            this->tail = this->head;
            this->len++;
            return;
        };
        
        std::shared_ptr<Node<T>> temp = this->tail;
        
        Node<T> node = Node<T>(data, this->head, temp); 

        this->tail = std::make_shared<Node<T>>(node);
        temp->set_next(this->tail);
        this->head->set_previous(this->tail);

        this->len++;
    }

    void append_at_index(T data, size_t index) {

        if (index >= this->len) return;

        std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(Node<T>(data));

        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 

        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }
        
        std::shared_ptr<Node<T>> previous = dummy->get_previous(); 
        std::shared_ptr<Node<T>> next = dummy->get_next();

        previous->set_next(node);

        node->set_next(dummy);
        node->set_previous(previous);

        dummy->set_previous(node);

        this->len++;
    }

    void set_at_index(T data, size_t index) {
        
        if (index >= this->len) return;

        std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>(Node(data));

        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 

        if (this->head == nullptr) {
            
            this->head = std::make_shared<Node<T>>(Node<T>(data));
            this->tail = this->head;
            this->len++;
            return;
        }

        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }

        dummy->set_data(data); 
    }

    T get_at_index(size_t index) {

        if (index >= this->len) return T();
        
        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 
        
        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }

        return dummy->get_data();
    }

    T first() {
        return this->head->get_data();
    }

    T last() {
        return this->tail->get_data();
    }

    void remove_head() {

        if (this->head == nullptr) return;

        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
            this->len--;
            return;
        }

        std::shared_ptr<Node<T>> new_head = this->head->get_next();

        this->tail->set_next(new_head);
        new_head->set_previous(this->tail);
        this->head = new_head;
        this->len--; 
    }
    
    void remove_tail() {
        if (this->head == nullptr) return;
        
        if (this->head == this->tail) {
            this->head = nullptr;
            this->tail = nullptr;
            this->len--;
            return;
        }
        std::shared_ptr<Node<T>> dummy = this->tail;

        std::shared_ptr<Node<T>> new_tail = this->tail->get_previous();
        
        this->head->set_previous(new_tail);
        new_tail->set_next(this->head);
        this->tail = new_tail;
        this->len--;     
    }

    void remove_at_index(size_t index) {

        if (index >= this->len) return;

        if (index == 0) {
            remove_head();
            return;
        }

        if (index == this->len - 1) {
            remove_tail();
            return;
        }

        int pos= 0;
        std::shared_ptr<Node<T>> dummy = this->head; 

        while (pos < index) {
            pos++;
            dummy = dummy->get_next();
        }

        std::shared_ptr<Node<T>> prev = dummy->get_previous(); 
        std::shared_ptr<Node<T>> next = dummy->get_next(); 

        prev->set_next(next);
        next->set_previous(prev);
        this->len--;

    }

    bool operator==(const Double_Linked_List<T>& other) {

        if (this->len != other.len) return false;

        std::shared_ptr<Node<T>> dummy1 = this->head;
        std::shared_ptr<Node<T>> dummy2 = other.head;

        while (dummy1 != nullptr) {
            if (dummy1->get_data() != dummy2->get_data()) {
                return false;
            }
            dummy1 = dummy1->get_next();
            dummy2 = dummy2->get_next();
        }

        return true;
    }

};

int main() {

    Double_Linked_List<int> dbl;
    
    for(int i = 0; i < 10; i++) {
        dbl.append_at_the_end(i);
    }

    for(int i = 0; i < 10; i++) {
        std::cout << dbl.get_at_index(i) << std::endl;
    }

    std::cout << "After removal:" << std::endl;

    dbl.remove_at_index(2);

    for(int i = 0; i < 9; i++) {
        std::cout << dbl.get_at_index(i) << std::endl;
    }
    
    std::cout << "After insrtion:" << std::endl;

    dbl.append_at_index(42, 2);

    for(int i = 0; i < 10; i++) {
        std::cout << dbl.get_at_index(i) << std::endl;
    }


    return 0;
}
