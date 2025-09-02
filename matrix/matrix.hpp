#pragma once
#include <iostream>
#include <initializer_list>
#include <algorithm>
using namespace std;

template<typename T, std::size_t Rows = 4, std::size_t Cols = 4>
class Matrix{
    private:
        T elements[Rows][Cols];
        // Matrix( const Matrix& ) = default;
    public:
        Matrix() {
            for (std::size_t i = 0; i < Rows; ++i) {
                for (std::size_t j = 0; j < Cols; ++j) {
                    elements[i][j] = T();
                }
            }
        }

        Matrix( std::initializer_list<std::initializer_list<T>> list ){
            std::size_t r = 0;
            for (const auto& row : list) {
                if (r >= Rows) break;
                std::size_t count = std::min<std::size_t>(row.size(), Cols);
                std::copy_n(row.begin(), count, elements[r]);
                for (std::size_t c = count; c < Cols; c++) {
                    elements[r][c] = T();
                }
                r++;
            }
            // reszta
            for (; r < Rows; ++r) {
                for (std::size_t c = 0; c < Cols; c++) {
                    elements[r][c] = T();
                }
            }
        }
        friend std::ostream& operator<<(std::ostream& os, const Matrix<T, Rows, Cols>& M){
            for (std::size_t i = 0; i < Rows; i++) {
                for (std::size_t j = 0; j < Cols; j++) {
                    os << M.elements[i][j];
                    if (j + 1 < Cols) {
                        os << ' ';
                    }
                }
                if (i + 1 < Rows) {
                    os << '\n';
                }
                os << '\n';
            }
            return os;
        }
        T* operator[](std::size_t row) {
            return elements[row];
        }
        const T* operator[](std::size_t row) const {
            return elements[row];
        }

        Matrix<T, Rows, Cols> operator+(const Matrix<T, Rows, Cols>& other) const {
            Matrix<T, Rows, Cols> result;
            for (std::size_t i = 0; i < Rows; i++) {
                for (std::size_t j = 0; j < Cols; j++) {
                    result.elements[i][j] = elements[i][j] + other.elements[i][j];
                }
            }
            return result;
        }

        Matrix<T, Rows, Cols> operator-(const Matrix<T, Rows, Cols>& other) const {
            Matrix<T, Rows, Cols> result;
            for (std::size_t i = 0; i < Rows; i++) {
                for (std::size_t j = 0; j < Cols; j++) {
                    result.elements[i][j] = elements[i][j] - other.elements[i][j];
                }
            }
            return result;
        }

        Matrix<T, Cols, Rows> transpose() const {
            Matrix<T, Cols, Rows> transposed;
            for (std::size_t i = 0; i < Rows; i++) {
                for (std::size_t j = 0; j < Cols; j++) {
                    transposed[j][i] = elements[i][j];
                }
            }
            return transposed;
        }
};
