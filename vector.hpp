#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>
#include <limits>
#include <new>
#include <stdexcept>

namespace learn {

    template <typename T>
    class Vector {
        private:
            T* data_ = nullptr;
            std::size_t size_ = 0;
            std::size_t capacity_ = 0;

            static T* allocate(std::size_t count) {
                if (count == 0) {
                    return nullptr;
                }

                return static_cast<T*>(::operator new(count * sizeof(T), std::align_val_t{alignof(T)}));
            }

            static void deallocate(T* pointer) noexcept {
                if (pointer == nullptr) {
                    return;
                }

                ::operator delete(pointer, std::align_val_t{alignof(T)});
            }

            static void end_objects(T* pointer, std::size_t count) {
                while (count > 0) {
                    --count;
                    pointer[count].~T();
                }
            }
        
        public:
            Vector() = default;

            ~Vector() {
                end_objects(data_, size_);
                deallocate(data_);
            }

            Vector(const Vector&) = delete;
            Vector& operator=(const Vector&) = delete;
            Vector(Vector&&) = delete;
            Vector& operator=(Vector&&) = delete;

            std::size_t size() const noexcept {
                return size_;
            }

            std::size_t capacity() const noexcept {
                return capacity_;
            }

            bool empty() const noexcept {
                return size_ == 0;
            }

            T* data() noexcept {
                return data_;
            }

            const T* data() const noexcept {
                return data_;
            }

            static  constexpr std::size_t max_size() noexcept {
                return std::numeric_limits<std::size_t>::max() / sizeof(T);
            }

            void reserve(std::size_t requested) {
                if (requested <= capacity_) {
                    return;
                }

                if (requested > max_size()) {
                    throw std::length_error("learn::Vector::reserve");
                }

                T* fresh = allocate(requested);
                deallocate(data_);
                data_ = fresh;
                capacity_ = requested;
            }

            void push_back(const T& value) {
                if (size_ == capacity_) {
                    throw std::logic_error("learn::Vector::push_back");
                }

                ::new (static_cast<void*>(data_ + size_)) T(value);
                ++size_;
            }
    };

}

#endif
