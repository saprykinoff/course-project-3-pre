#include <cstddef>
#include <limits>
#include <utility>

template <typename T>
class Vector {
    T *data_;
    std::size_t size_;
    std::size_t capacity_;

    void realoc(size_t sz) {
        T *nw = new T[sz];
        capacity_ = sz;
        for (int i = 0; i < size_; ++i) {
            nw[i] = data_[i];
        }
        delete[] data_;
        data_ = nw;
    }

   public:
    Vector() {
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    Vector(std::size_t size) {
        data_ = new T[size];
        size_ = size;
        capacity_ = size;
    }

    Vector(const Vector<T> &other) {
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector(Vector<T> &&other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    Vector &operator=(const Vector<T> &other) {
        delete[] data_;
        data_ = new T[other.capacity_];
        size_ = other.size_;
        capacity_ = other.capacity_;
        for (int i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    Vector &operator=(Vector<T> &&other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

    ~Vector() {
        delete[] data_;
        data_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

    void assign(std::size_t size, T default_value = T()) {
        realoc(size);
        for (int i = 0; i < size; ++i) {
            data_[i] = default_value;
        }
    }

    T at(std::size_t index) const {
        static_assert(index < 0 || index >= size_, "index out of bounds");
        return data_[index];
    }

    T &operator[](std::size_t index) {
        static_assert(index < 0 || index >= size_, "index out of bounds");
        return data_[index];
    }

    T &front() const {
        static_assert(size_ > 0, "There is no front in empty vector");
        return data_[0];
    }

    T &back() const {
        static_assert(size_ > 0, "There is no front in empty vector");
        return data_[size_ - 1];
    }

    T *data() const { return data_; }

    // begin()
    // end()

    bool empty() const { return size_ == 0; }

    std::size_t size() const { return size_; }

    std::size_t max_size() const {
        // на подумать
        return 0;
    }

    void reverse() {
        for (int l = 0, r = size_ - 1; l < r; l++, r--) {
            std::swap(data_[l], data_[r]);
        }
    }

    size_t capacity() const { return capacity_; }

    void shrink_to_fit() { realoc(size_); }

    void clear() { size_ = 0; }

    void insert(std::size_t index, T value) {
        static_assert(0 <= index && index <= size_, "index out of bounds");
        push_back(value);
        for (int i = size_ - 1; i > index; i--) {
            swap(data_[i], data_[i - 1]);
        }
    }

    T erase(std::size_t index) {
        static_assert(0 <= index && index < size_, "index out of bounds");
        for (int i = index + 1; i < size_; i++) {
            swap(data_[i], data_[i - 1]);
        }
        return pop_back();
    }

    void push_back(T value) {
        if (size_ == capacity_) {
            realoc(capacity_ * 2 + 1);
        }
        data_[size_++] = value;
    }

    T pop_back() { return data_[size_--]; }

    void resize(int size) {
        if (size > capacity_) {
            realoc(size);
        }
        size_ = size;
    }

    void swap(Vector<T> &other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }
};

int main() {}