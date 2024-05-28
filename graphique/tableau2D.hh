#pragma once

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <limits>
#include <stdexcept>
#include <memory>

template <typename Type>
class tableau2D {
private:
    std::unique_ptr<Type[]> _data;
    int _col;
    int _ligne;

public:
    tableau2D() : _col(0), _ligne(0) {}

    tableau2D(int cols, int rows) {
        initTableau2D(cols, rows);
    }

    tableau2D(int cols, int rows, Type initVal) {
        initTableau2D(cols, rows, initVal);
    }

    tableau2D(int cols, int rows, void* pData) {
        initTableau2D(cols, rows, pData);
    }

    ~tableau2D() {
        effacer();
    }

    tableau2D(const tableau2D& other) {
        _col = other._col;
        _ligne = other._ligne;
        _data = std::make_unique<Type[]>(_col * _ligne);
        std::copy(other._data.get(), other._data.get() + _col * _ligne, _data.get());
    }

    tableau2D& operator=(const tableau2D& other) {
        if (this == &other) {
            return *this;
        }

        _col = other._col;
        _ligne = other._ligne;
        _data = std::make_unique<Type[]>(_col * _ligne);
        std::copy(other._data.get(), other._data.get() + _col * _ligne, _data.get());

        return *this;
    }

    void initTableau2D(int cols, int rows) {
        _col = cols;
        _ligne = rows;
        _data = std::make_unique<Type[]>(cols * rows);
    }

    void initTableau2D(int cols, int rows, Type initVal) {
        initTableau2D(cols, rows);
        std::fill(_data.get(), _data.get() + cols * rows, initVal);
    }

    void initTableau2D(int cols, int rows, void* pData) {
        _col = cols;
        _ligne = rows;
        _data.reset(static_cast<Type*>(pData));
    }

    void effacer() {
        _data.reset();
        _col = 0;
        _ligne = 0;
    }

    Type* getAddr(int col, int row) const {
        return &_data[calcInd(col, row)];
    }

    Type* getBaseAddr() const {
        return _data.get();
    }

    int getTaille() const {
        return _ligne * _col;
    }

    int getTailleEnOctet() const {
        return getTaille() * sizeof(Type);
    }

    const Type& get(int col, int row) const {
        return *getAddr(col, row);
    }

    const Type& get(int index) const {
        if (index >= _ligne * _col) {
            throw std::out_of_range("Index out of bounds");
        }
        return _data[index];
    }

    Type& at(int col, int row) {
        return _data[calcInd(col, row)];
    }

    void set(int col, int row, const Type& val) {
        *getAddr(col, row) = val;
    }

    void set(int index, const Type& val) {
        if (index >= _ligne * _col) {
            throw std::out_of_range("Index out of bounds");
        }
        _data[index] = val;
    }

    void getMinMax(Type& min, Type& max) const {
        max = min = _data[0];
        for (int i = 1; i < _ligne * _col; ++i) {
            if (_data[i] < min) {
                min = _data[i];
            }
            if (_data[i] > max) {
                max = _data[i];
            }
        }
    }

    void normaliser(Type minRange, Type maxRange) {
        Type min, max;
        getMinMax(min, max);

        if (max <= min) {
            return;
        }

        Type minMaxDelta = max - min;
        Type minMaxRange = maxRange - minRange;

        for (int i = 0; i < _ligne * _col; ++i) {
            _data[i] = ((_data[i] - min) / minMaxDelta) * minMaxRange + minRange;
        }
    }

    void print() const {
        for (int y = 0; y < _ligne; ++y) {
            std::cout << y << ": ";
            for (int x = 0; x < _col; ++x) {
                std::cout << static_cast<float>(_data[y * _col + x]) << " ";
            }
            std::cout << std::endl;
        }
    }

private:
    size_t calcInd(int col, int row) const {
        if (col < 0 || col >= _col || row < 0 || row >= _ligne) {
            throw std::out_of_range("Column or row out of bounds");
        }
        return row * _col + col;
    }

};
