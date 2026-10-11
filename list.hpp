#ifndef LIST_HPP
#define LIST_HPP

#include <filesystem>
#include <iostream>

#define FILE_NAME "list.hpp"
#define PATH std::filesystem::absolute(FILE_NAME)
#define NOT_FIND -1

template<class T>
class Element;

/**
 * A double linked list.
 *
 * The list owns all its nodes and is responsible for deleting them.
 */
template<class T>
class List{
    private:
        Element<T>* head; // Pointer to the first node of the list.

        int size; // Integer for the size of the list.

        /**
         * Logs a message and exits if a list is empty.
         * 
         * @param name name of the function context.
         *
         * @return void
         */
        void emptyListError(std::string name){
            std::cerr << PATH <<" [ERROR] : Empty list in " << name << std::endl;
            exit(EXIT_FAILURE);
        }

        /**
         * Logs a message and exits if an index is out of range.
         * 
         * @param name name of the function context.
         * @param index the index that was accessed.
         *
         * @return void
         */
        void outOfRangeError(std::string name, int index){
            std::cerr << PATH <<" [ERROR] : index out of range in " << name << std::endl;
            std::cerr << "\tindex : " << index << " list size : " << this->size <<std::endl;
            exit(EXIT_FAILURE);
        }
    public:

        /**
         * Constructs an empty list.
         */
        List() : size(0) {
            this->head = nullptr;
        }

        /**
         * Copy constructor.
         *
         * Creates a deep copy of the other list.
         * Each node is copied into a new node.
         *
         * @param other List to copy.
         */
        List(const List& other) : size(other.size) {
            this->head = other.head;
        }

        /**
         * Destructor.
         *
         * Deletes every node owned by the list.
         */
        ~List(){
            Element<T>* current = head;
            while (current != nullptr) {
                Element<T>* next = current->next;
                delete current;
                current = next;
            }
        }

        /**
         * Copy assignment operator.
         *
         * Deletes the current contents and creates a deep copy
         * of the other list.
         *
         * @param other List to copy.
         * @return Reference to this list.
         */
        List& operator=(const List& other){
            this->head = other.head;
            this->size = other.size;
            return *this;
        }
        
        /**
         * Provides access to the element stored at a given index.
         * 
         * This operator allows the object to be accessed using array syntax:
         * `container[index]`.
         *
         * @param index The zero-based index of the element to retrieve.
         * @return A reference to the Element<T> located at the specified index.
         *
         * @note Because this function returns a reference, the caller can both read
         *       and modify the returned element.
         */
        Element<T>& operator[](const int index){
            if(this->head == nullptr){
                this->emptyListError("List[int]");
            }

            if(index >= this->size){
                this->outOfRangeError("List[int]", index);
            }

            Element<T>* tmp = this->head;
            int i = 0;

            while(tmp->next != nullptr && i<index){
                tmp = tmp->next;
                ++i;
            }
            
            //useless but keep it in case
            if(i != index){
                this->outOfRangeError("List[int]", index);
            }

            return *tmp;
        }

        /**
         * Returns the number of elements currently stored in the list.
         *
         * @return The current length of the list.
         */
        int len(){
            return this->size;
        }

        /**
         * Adds a value at the end of the list.
         *
         * @param newValue Value to add.
         * @return Index of the newly added value.
         */
        int add(const T& newValue){
            int index = 1;
            Element<T>* el = new Element<T>(newValue);
            if(this->head == nullptr){
                this->head = el;
                return 0;
            }
            Element<T>* tmp = this->head;
            while(tmp->next != nullptr){
                tmp = tmp->next;
                ++index;
            }
            tmp->next = el;
            el->previous = tmp;
            ++(this->size);
            return index;
        }

        /**
         * Insert a value at the wanted index, if the index is out of range, add it to the end.
         * 
         * @param newValue Value to insert.
         * @param wantedIndex The zero-based index of the element to insert.
         * @return Index of the newly added value.
         */
        int insert(const T& newValue, int wantedIndex){
            int index = 1;
            Element<T>* el = new Element<T>(newValue);
            if(this->head == nullptr){
                this->head = el;
                ++(this->size);
                return 0;
            }

            Element<T>* tmp = this->head;

            if(wantedIndex == 0){
                this->head = el;
                el->next = tmp;
                ++(this->size);
                return 0;
            }

            while(tmp->next != nullptr && index < wantedIndex){
                tmp = tmp->next;
                ++index;
            }

            if(tmp->next){
                tmp->next->previous = el;
            }
            el->next = tmp->next;
            el->previous = tmp;
            tmp->next = el;
            ++(this->size);
            return index;
        }
        
        /**
         * Remove an element at the given index. 
         * 
         * @param index The zero-based index of the element to remove. 
         * @return 0 if success.
         */
        int remove(int index = 0){
            if(index < 0){
                index+= this->size;
            }

            if(index >= this->size){
                this->outOfRangeError("List.remove(int)", index);
            }

            if(this->head == nullptr){
                this->emptyListError("List.remove(int)");
            }

            if(index == 0){
                this->head = this->head->next;
                --(this->size);
                return 0;
            }

            Element<T>* tmp = this->head;
            int i = 0;
            while(tmp->next != nullptr && i<index){
                tmp = tmp->next;
                ++i;
            }

            if(tmp->next){
                tmp->next->previous = tmp->previous;
            }
            tmp->previous->next = tmp->next;
            delete tmp;
            --(this->size);
            return 0;
        }

        /**
         * Delete the first Element of the list.
         * 
         * @param element the element to delete.
         * @return Index of the element deleted.
         */
        int del(const T& element){
            if(this->head == nullptr){
                this->emptyListError("List.remove(int)");
            }

            if(this->head->value == element){
                this->head = this->head->next;
                --(this->size);
                return 0;
            }

            int index = 0;
            Element<T>* tmp = this->head;

            while(tmp->next != nullptr && tmp->value != element){
                tmp = tmp->next;
                ++index;
            }
            if(tmp->next){
                tmp->next->previous = tmp->previous;
            }
            tmp->previous->next = tmp->next;
            delete tmp;
            --(this->size);
            return index;
        }

        /**
         * Find the first index of the given element.
         * 
         * @param element The element to search for.
         * @return Index of the element
         */
        int find(const T& element){
            if(this->head == nullptr){
                return NOT_FIND;
            }

            if(this->head->value == element){
                return 0;
            }

            int index = 0;
            Element<T>* tmp = this->head;

            while(tmp != nullptr && tmp->value != element){
                tmp = tmp->next;
                ++index;
            }
            if(tmp == nullptr){
                return NOT_FIND;
            }
            return index;
        }

        /**
         * Count the number of occurence of a given element
         * 
         * @param element The element to search for.
         * @return The number of occurence of the given element
         */
        int occure(const T& element){
            int counter = 0;
            Element<T>* tmp = this->head;
            while(tmp != nullptr){
                if(tmp->value == element){
                    ++counter;
                }
                tmp = tmp->next;
            }
            return counter;
        }

        /**
         * Outputs the complete list.
         *
         * Example:
         * List<int> list;
         * list.add(10);
         * list.add(20);
         * std::cout << list; // [10,20]
         */
        friend std::ostream& operator<<(std::ostream& os, const List& list) {
            os << "[";

            const Element<T>* tmp = list.head;
            bool first = true;

            while (tmp != nullptr) {
                if (!first) {
                    os << ",";
                }

                os << *tmp;
                first = false;
                tmp = tmp->next;
            }

            os << "]";

            return os;
        }
};


/**
 * A node of the linked list.
 *
 * Each Element stores:
 * - one value of type T;
 * - a pointer to the next Element.
 * - a pointer to the previous Element
 */
template<class T>               
class Element{
    private:

        Element* next; // Pointer to the next node in the list.

        Element* previous; // Pointer to the previous node in the list.

        T value; // The value stored by this node. It is stored by value so every node owns its own copy.

        friend class List<T>; // List<T> can access private members of Element<T>.

    public:

        /**
         * Constructs an empty node.
         *
         * The value is default-constructed and next and previous is initialized to nullptr.
         */
        Element() : value(T()), next(nullptr), previous(nullptr) {}

        /**
         * Copy constructor.
         *
         * Copies only the value.
         * The new node is not attached to the original node's list.
         *
         * @param other Node to copy.
         */
        Element(const Element& other) : value(other.value), next(other.next), previous(other.previous) {}

        /**
         * Constructs a node containing newValue.
         *
         * @param newValue Value to store in the node.
         */
        Element(T newValue) : value(newValue), next(nullptr), previous(nullptr) {}

        /**
         * Destructor.
         *
         * The node does not delete next.
         * The List class is responsible for deleting all nodes.
         */
        ~Element() = default;

        /**
         * Copy assignment operator.
         *
         * Copies the value but does not copy the next pointer.
         * Copying next would connect two independent lists together.
         *
         * @param other Node to copy.
         * @return Reference to this node.
         */
        Element& operator=(const Element& other){
            this->value = other.value;
            this->next = other.next;
            this->previous = other.previous;
            return *this;
        }

        /**
         * Outputs the value stored in an Element.
         *
         * Example:
         * Element<int> element(42);
         * std::cout << element; // 42
         */
        friend ostream& operator<<(ostream &os, const Element& el){
            os  << el.value;
            return os;
        }
};

#endif //LIST_HPP