#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <cstddef>

namespace learn {

    template <typename T>
    class Vector {
        private:
            T* data_ = nullptr;
            std::size_t size_ = 0;
            std::size_t capacity_ = 0;
        
        public:
            Vector() = default;

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
    };

}

#endif
