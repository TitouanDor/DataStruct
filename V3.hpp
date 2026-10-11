#ifndef V3_HPP
#define V3_HPP

template <class T>
class V3{
    public:
        V3() : x(0), y(0), z(0) {}

        V3(const V3 &other) : x(other.x), y(other.y), z(other.z) {}

        V3& operator=(const V3 &other){
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
            return *this;
        }

        ~V3();

        V3 operator+(const V3 &other){
            V3 result;
            result.x = this->x+other.x;
            result.y = this->y+other.y;
            result.z = this->z+other.z;
            return result;
        }

        V3& operator+=(const V3 &other){
            this->x += other.x;
            this->y += other.y;
            this->z += other.z;
            return *this;
        }

        bool operator==(const V3 &other){
            return (this->x == other.x && this->y == other.y && this->z == other.z);
        }

        bool operator||(const V3 &other){
            T ratio = this->x/other.x;
            return (this->y/other.y == ratio && this->z/other.z == ratio);
        }

        T operator^(const V3 &other){
            V3 result;
            result.x = this->y*other.z - this->z*other.y;
            result.y = this->z*other.x - this->x*other.z;
            result.z = this->x*other.y - this->y*other.x;
            return result;
        }

        T operator%(const V3 &other){
            V3 result;
            result.x = this->x*other.x;
            result.y = this->y*other.y;
            result.z = this->z*other.z;
            return result;
        }



    private:
        T x;
        T y;
        T z;
};







#endif