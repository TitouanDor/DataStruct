#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <iostream>
#include <stdexcept>

/**
 * @brief A dynamically allocated, fixed-size mathematical vector.
 *
 * @tparam T The type of each vector component, for example float or double.
 *
 * Supports element access, copy operations, vector addition/subtraction,  scalar multiplication/division, equality comparison, and output formatting.
 */
template <class T>
class Vector {
    private:
        T* data; // Pointer to the underlying array
        size_t size; // Size of the vector
    
    public:

        /**
         * @brief Constructs an empty vector.
         *
         * The vector has no allocated storage and a size of 0.
         */
        Vector() : data(nullptr), size(0) {}

        /**
         * @brief Constructs a copy of another vector.
         *
         * @param other The vector to copy.
         */
        Vector(const Vector& other) : size(other.size) {
            this->data = new T[this->size];
            for (size_t i = 0; i < this->size; ++i) {
                this->data[i] = other.data[i];
            }
        }

        /**
         * @brief Constructs a vector with a given number of components.
         *
         * All components are value-initialized, which means they are set to 0 for numeric types.
         *
         * @param size The number of components to allocate.
         */
        Vector(size_t size) : data(new T[size]()), size(size) {}

        /**
         * @brief Destroys the vector and releases its allocated memory.
         */
        ~Vector() {
            delete[] this->data;
        }

        /**
         * @brief Provides access to a component of the vector.
         *
         * Supports negative indices: a negative index is counted from the end of the vector, similar to Python indexing. For example, -1 refers to the last component.
         *
         * @param index The zero-based index of the component, or a negative index counted from the end of the vector.
         * @return A reference to the component at the specified index.
         *
         * @throws std::out_of_range If the resulting index is outside the vector.
         */
        T& operator[](long long index) const{
            if (index < 0) {
                index += static_cast<long long>(size);
            }

            if (index < 0 || index >= static_cast<long long>(size)) {
                throw std::out_of_range("Vector::operator[]: index out of range");
            }

            return data[static_cast<size_t>(index)];
        }

        /**
         * @brief Assigns the contents of another vector to this vector.
         *
         * Performs a deep copy: this vector receives its own copy of the other vector's data.
         *
         * @param other The vector whose contents will be copied.
         * @return A reference to this vector.
         */
        Vector& operator=(const Vector& other) {
            if (this == &other) {
                return *this;
            }

            T* newData = new T[other.size];

            for (size_t i = 0; i < other.size; ++i) {
                newData[i] = other.data[i];
            }

            delete[] data;

            this->data = newData;
            this->size = other.size;

            return *this;
        }

        /**
         * @brief Adds this vector to another vector.
         *
         * @param other The vector to add.
         * @return A new vector containing the component-wise sum.
         *
         * @throws std::out_of_range If the two vectors have different sizes.
         */
        Vector operator+(const Vector& other){
            if(this->size != other.size){
                throw std::out_of_range("ERROR : Vector operator+: Trying to add 2 vector of different dimention");
            }

            Vector result = Vector(this->size);
            for (size_t i = 0; i < this->size; ++i) {
                result[i] = this->data[i] + other.data[i];
            }

            return result;
        }

        /**
         * @brief Adds another vector to this vector in place.
         *
         * @param other The vector to add.
         * @return A reference to this vector after the addition.
         *
         * @throws std::out_of_range If the two vectors have different sizes.
         */
        Vector& operator+=(const Vector& other){
            if(this->size != other.size){
                throw std::out_of_range("ERROR : Vector operator+=: Trying to add 2 vector of different dimention");
            }

            for (size_t i = 0; i < this->size; ++i) {
                this->data[i] = this->data[i] + other.data[i];
            }

            return *this;
        }

        /**
         * @brief Subtracts another vector from this vector.
         *
         * @param other The vector to subtract.
         * @return A new vector containing the component-wise difference.
         *
         * @throws std::out_of_range If the two vectors have different sizes.
         */
        Vector operator-(const Vector& other){
            if(this->size != other.size){
                throw std::out_of_range("ERROR : Vector operator-: Trying to substract 2 vector of different dimention");
            }

            Vector result = Vector(this->size);
            for (size_t i = 0; i < this->size; ++i) {
                result[i] = this->data[i] - other.data[i];
            }

            return result;
        }

        /**
         * @brief Subtracts another vector from this vector in place.
         *
         * @param other The vector to subtract.
         * @return A reference to this vector after the subtraction.
         *
         * @throws std::out_of_range If the two vectors have different sizes.
         */
        Vector& operator-=(const Vector& other){
            if(this->size != other.size){
                throw std::out_of_range("ERROR : Vector operator-=: Trying to substract 2 vector of different dimention");
            }

            for (size_t i = 0; i < this->size; ++i) {
                this->data[i] = this->data[i] - other.data[i];
            }

            return *this;
        }

        /**
         * @brief Multiplies every component of the vector by a scalar.
         *
         * @param lambda The scalar multiplier.
         * @return A new vector containing the scaled components.
         */
        Vector operator*(const T lambda){
            Vector result = Vector(this->size);

            for(size_t i = 0; i < this->size; ++i){
                result.data[i] = this->data[i]*lambda;
            }

            return result;
        }

        /**
         * @brief Multiplies every component of this vector by a scalar in place.
         *
         * @param lambda The scalar multiplier.
         * @return A reference to this vector after scaling.
         */
        Vector& operator*=(const T lambda){
            for(size_t i = 0; i < this->size; ++i){
                this->data[i] = this->data[i]*lambda;
            }

            return *this;
        }

        /**
         * @brief Divides every component of the vector by a scalar.
         *
         * @param lambda The scalar divisor.
         * @return A new vector containing the divided components.
         */
        Vector operator/(const T lambda){
            Vector result = Vector(this->size);

            for(size_t i = 0; i < this->size; ++i){
                result.data[i] = this->data[i]/lambda;
            }

            return result;
        }

        /**
         * @brief Divides every component of this vector by a scalar in place.
         *
         * @param lambda The scalar divisor.
         * @return A reference to this vector after division.
         */
        Vector& operator/=(const T lambda){
            for(size_t i = 0; i < this->size; ++i){
                this->data[i] = this->data[i]/lambda;
            }

            return *this;
        }

        /**
         * @brief Checks whether two vectors are equal.
         *
         * Two vectors are equal if they have the same size and all corresponding components are equal.
         *
         * @param other The vector to compare with.
         * @return true If both vectors are equal.
         * @return false If the vectors differ in size or in any component.
         */
        bool operator==(const Vector& other) const {
            if(this->size != other.size){
                return false;
            }

            for(size_t i = 0;i < this->size;++i){
                if(this->data[i] != other.data[i]){
                    return false;
                }
            }

            return true;
        }

        /**
         * @brief Checks whether all components of the vector are zero.
         *
         * @return true If every component equals 0.0f.
         * @return false If at least one component is non-zero.
         */
        bool isNull() const {
            bool result = true;
            for(size_t i = 0; (i < this->size) && result; ++i){
                result = this->data[i] == T{};
            }

            return result;
        }

        /**
         * @brief Returns the number of components in the vector.
         *
         * @return The size of the vector.
         */
        size_t getSize() const {
            return size;
        }

        /**
         * @brief Writes a human-readable representation of the vector to an output stream.
         *
         * The output has the form: `Vector(a,b,c)`.
         *
         * @param os The output stream to write to.
         * @param vect The vector to write.
         * @return A reference to the output stream.
         */
       friend std::ostream& operator<<(std::ostream& os, const Vector& vect){
            os << "Vector(";

            for (size_t i = 0; i < vect.size; ++i) {
                os << vect.data[i];
                if(i+1 != vect.size){
                    os << ",";
                }
            }

            os << ")";
            return os;
        }
};

#endif // VECTOR_HPP