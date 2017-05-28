#include <cassert>
#include <cstdlib>
#include <cstddef>
#include <cstring>

template <typename T, size_t N>
class my_array{
 public:
    T& at(size_t index){
        assert (index < N && "Range check");
        return array_[index];
    }

    const T& at(size_t index) const{
        assert (index < N && "Range check");
        return array_[index];
    }

    T& operator[](size_t index){
        return array_[index];
    }

    const T& operator[](size_t index) const{
        return array_[index];
    }

    bool empty() const{
        return (N == 0);
    }

    size_t size() const{
        return N;
    }

    void fill(const T& val){
        for (size_t i = 0; i < N; i++)
            array_[i] = val;
    }

 private:
    T array_[N];
};


template <size_t N>
class my_array<bool, N>{
 private:
    class Proxy{
     public:
        Proxy(my_array<bool, N> *ptr, size_t ind) : ptr_(ptr), pos_(ind){}

        operator bool() const{
            return ptr_ -> get(pos_);
        }

        Proxy operator=(bool new_value){
            if (ptr_ -> get(pos_) != new_value)
                ptr_ -> array_[pos_ / 8] ^= (1 << (pos_ % 8));
            return *this;
        }

        Proxy operator=(Proxy a){
            operator=(bool(a));
            return *this;
        }

        my_array<bool, N> *ptr_;
        size_t pos_;
    };

 public:
    my_array(){
        memset(array_, 0, sizeof(array_));
    }

    Proxy at(size_t index){
        assert (index < N && "Range check");
        return getProxy(index);
    }

    bool at(size_t index) const{
        assert (index < N && "Range check");
        return get(index);
    }

    Proxy operator[](size_t index){
        return getProxy(index);
    }

    bool operator[](size_t index) const{
        return get(index);
    }

    bool empty() const{
        return (N != 0);
    }

    size_t size() const{
        return N;
    }

    void fill(const bool val){
        for (size_t i = 0; i < N; i++)
            if (get(i) != val)
                array_[i / 8] ^= 1 << (i % 8);
    }

 private:
    char array_[(N + 7) / 8];

    bool get(size_t index) const{
        return (array_[index / 8] >> (index % 8)) & 1;
    }

    Proxy getProxy(size_t index){
        return Proxy(this, index);
    }
};
