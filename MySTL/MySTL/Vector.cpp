#include <stdlib.h>
#include <iostream>
#include <exception>

#include "Vector.h"

template <typename T>
Vector<T>::Vector()
{
	_capacity = 0;
	_size = 0;
	_data = nullptr;
	Resize(0);
}

template <typename T>
Vector<T>::Vector(const Vector& src)
{
	_capacity = 0;
	_size = 0;
	_data = nullptr;
	Resize(src.Size());
	for (int i = 0; i < _size; i++)
		_data[i] = src[i];
}

template <typename T>
Vector<T>::Vector(size_t size)
{
	_capacity = 0;
	_size = 0;
	_data = nullptr;
	Resize(size);
}

template <typename T>
Vector<T>::Vector(size_t size, T fill_elem)
{
	_capacity = 0;
	_size = 0;
	_data = nullptr;
	Resize(size);
	for (int i = 0; i < _size; i++)
		_data[i] = fill_elem;
}

template <typename T>
Vector<T>::~Vector()
{
	if (_data != nullptr)
		free(_data);
	_data = nullptr;
	_size = 0;
	_capacity = 0;
}

template <typename T>
void Vector<T>::Resize(size_t new_size)
{
	if (new_size > _capacity || new_size < _size / 2) {
		T* new_data = (T*)realloc(_data, new_size * 2 * sizeof(T));
		if (new_data == nullptr && new_size != 0)
			throw std::overflow_error("Overflow at Resize()");
		_data = new_data;
		_capacity = new_size * 2;
	}
	_size = new_size;
}

template <typename T>
void Vector<T>::Push_back(T elem)
{
	Resize(_size + 1);
	(*this)[_size - 1] = elem;
}

template <typename T>
void Vector<T>::Insert(Vector& src, size_t pos)
{
	Vector<T> buffer = *this;
	Resize(Size() + src.Size());
	for (int i = 0; i < pos; i++)
		(*this)[i] = buffer[i];
	for (int i = 0; i < src.Size(); i++)
		(*this)[pos + i] = src[i];
	for (int i = 0; i < buffer.Size() - pos; i++)
		(*this)[pos + src.Size() + i] = buffer[pos + i];
}

template <typename T>
T Vector<T>::Pop_back()
{
	T out = (*this)[_size - 1];
	Resize(_size - 1);
	return out;
}

template <typename T>
T Vector<T>::RemoveElem(int pos)
{
	T out = (*this)[pos];
	for (int i = pos; i < Size() - 1; i--)
		(*this)[i] = (*this)[i + 1];
	return out;
}

template <typename T>
void Vector<T>::Slice(int start_pos, int end_pos)
{
	if (end_pos < start_pos)
		throw std::out_of_range("Negative slice distance");

	Vector<T> buffer = *this;
	Resize(end_pos - start_pos);

	for (int i = 0; i < Size(); i++)
		(*this)[i] = buffer[start_pos + i];
}

template <typename T>
T* Vector<T>::Begin()
{
	return _data;
}

template <typename T>
size_t Vector<T>::Size()
{
	return _size;
}

template <typename T>
T* Vector<T>::End()
{
	return _data + _size;
}

template <typename T>
T* Vector<T>::Begin() const
{
	return _data;
}

template <typename T>
T* Vector<T>::End() const
{
	return _data + _size;
}
template <typename T>
size_t Vector<T>::Size() const
{
	return _size;
}


template <typename T>
T& Vector<T>::operator[] (const unsigned index)
{
	if (index < 0 || index >= _size)
		throw std::out_of_range("Incorrect index");
	return _data[index];
}

template <typename T>
T Vector<T>::operator[] (const unsigned index) const
{
	if (index < 0 || index >= _size)
		throw std::out_of_range("Incorrect index");
	return _data[index];
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& src)
{
	Resize(src.Size());
	for (int i = 0; i < Size(); i++)
		(*this)[i] = src[i];
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator+= (const Vector<T>& src)
{
	size_t old_size = Size();
	Resize(Size() + src.Size());
	for (int i = old_size; i < Size(); i++)
		(*this)[i] = src[i - old_size];
	return *this;
}

template <typename T>
Vector<T>& Vector<T>::operator*= (const unsigned num)
{
	size_t old_size = Size();
	Resize(Size() * num);
	for (int i = 1; i < num; i++)
		for (int j = 0; j < old_size; j++)
			(*this)[i * old_size + j] = (*this)[j];
	return *this;
}

template <typename T>
Vector<T> operator+ (const Vector<T>& a, const Vector<T>& b)
{
	Vector<T> out(a.Size() + b.Size());
	for (int i = 0; i < a.Size(); i++)
		out[i] = a[i];
	for (int i = a.Size(); i < out.Size(); i++)
		out[i] = b[i - a.Size()];
	return out;
}

template <typename T>
Vector<T> operator* (const Vector<T>& a, const unsigned num)
{
	Vector<T> out = a;
	out *= num;
	return out;
}

template <typename T>
bool operator==(const Vector<T>& a, const Vector<T>& b)
{
	if (a.Size() != b.Size())
		return false;
	for (int i = 0; i < a.Size(); i++)
		if (a[i] != b[i])
			return false;
	return true;
}

template <typename T>
bool operator!=(const Vector<T>& a, const Vector<T>& b)
{
	return !(a == b);
}