#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>

template<typename T, typename Iter>
class range_enumerator;

template<typename T>
class drop_enumerator;

template<typename T, typename U, typename F>
class select_enumerator;

template<typename T, typename F>
class until_enumerator;

template<typename T>
class take_enumerator;

template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:
    virtual const T& operator*() const = 0;
    virtual enumerator& operator++() = 0;
    virtual operator bool() const = 0;

    auto drop(int count) {
        return drop_enumerator<T>(*this, count);
    }

    auto take(int count) {
        return take_enumerator<T>(*this, count);
    }

    template<typename U = T, typename F>
    auto select(F func) {
        return select_enumerator<U, T, F>(*this, func);
    }

    template<typename F>
    auto until(F func) {
        return until_enumerator<T, F>(*this, func);
    }

    auto until_eq(const T &val) {
        return until([&val](const T &elem) { return elem == val; });
    }

    template<typename F>
    auto where(F func) {
        return where_enumerator<T, F>(*this, func);
    }

    auto where_neq(const T &v) {
        return where([&v](const T& x) { return x != v; });
    }

    std::vector<T> to_vector() {
        std::vector<T> res;
        while (*this){
            res.push_back(**this);
            ++*this;
        }
        return res;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (*this){
            (*it)++ = **this;
            ++*this;
        }
    }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
 public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}

    const T& operator*() const override{
        return *begin_;
    }

    range_enumerator<T, Iter>& operator++() override{
        begin_++;
        return *this;
    }

    operator bool() const override{
        return begin_ != end_;
    }

 private:
    Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
    return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
 public:
    drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
        for (; parent_ && count > 0; --count)
            ++parent_;
    }

    const T& operator*() const override{
        return *parent_;
    }

    drop_enumerator<T>& operator++() override{
        ++parent_;
        return *this;
    }

    operator bool() const override{
        return parent_;
    }

 private:
    enumerator<T>& parent_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
 public:
    take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}

    const T& operator*() const override{
        return *parent_;
    }

    take_enumerator<T>& operator++() override{
        ++parent_;
        count_--;
        return *this;
    }

    operator bool() const override{
        return parent_ && count_ > 0;
    }

 private:
    enumerator<T>& parent_;
    int count_;
};


template<typename T, typename U, typename F>
class select_enumerator : public enumerator<T> {
 public:

    void update(){
        if (parent_)
            cache_ = func_(*parent_);
    }

    select_enumerator(enumerator<U> &parent, F func) : parent_(parent),
                                            func_(std::move(func)){
        update();
    }
    const T& operator*() const override{
        return cache_;
    }

    select_enumerator<T, U, F>& operator++() override{
        ++parent_;
        update();
        return *this;
    }

    operator bool() const override{
        return parent_;
    }

 private:
    enumerator<U> &parent_;
    F func_;
    T cache_;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
 public:
    void update(){
        if (parent_)
            is_ = predicate_(*parent_);
    }

    until_enumerator(enumerator<T> &parent, F predicate) : parent_(parent),
                                        predicate_(std::move(predicate)){
        update();
    }

    const T& operator*() const override{
        return *parent_;
    }

    until_enumerator<T, F>& operator++() override{
        ++parent_;
        update();
        return *this;
    }

    operator bool() const override{
        return parent_ && !is_;
    }

 private:
    enumerator<T> &parent_;
    F predicate_;
    bool is_;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
 public:

    void omit(){
        while (parent_ && !predicate_(*parent_))
            ++parent_;
    }

    where_enumerator(enumerator<T> &parent, F predicate) : parent_(parent),
                                        predicate_(std::move(predicate)){
        omit();
    }

    const T& operator*() const override{
        return *parent_;
    }

    where_enumerator<T, F>& operator++() override{
        ++parent_;
        omit();
        return *this;
    }

    operator bool() const override{
        return parent_;
    }

 private:
    enumerator<T> &parent_;
    F predicate_;
};


#endif
