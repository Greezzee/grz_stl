#include <stdlib.h>
#include <iostream>
#include <exception>
#include <string.h>
#include "String.h"

String::String() 
{
	_capacity = 0;
	_len = 0;
	_data = nullptr;
	Resize(0);
}
String::String(size_t len, char fill_elem = '\0')
{
	_capacity = 0;
	_len = 0;
	_data = nullptr;
	Resize(len);
	for (size_t i = 0; i < _len; i++)
		_data[i] = fill_elem;
}
String::String(const String& src)
{
	_capacity = 0;
	_len = 0;
	_data = nullptr;
	Resize(src.Lenght());
	for (size_t i = 0; i < _len; i++)
		(*this)[i] = src[i];
}
String::String(const char src[])
{
	_capacity = 0;
	_len = 0;
	_data = nullptr;
	Resize(strlen(src));
	for (size_t i = 0; i < _len; i++)
		(*this)[i] = src[i];
}
String::~String() 
{
	if (_data != nullptr)
		free(_data);
	_len = 0;
	_capacity = 0;
	_data = nullptr;
}

size_t String::Lenght()
{
	return _len;
}

size_t String::Lenght() const
{
	return _len;
}

void String::Resize(size_t new_size)
{
	if (new_size != 0) new_size++;

	if (new_size > _capacity || new_size < _len / 2) {
		char* new_data = (char*)realloc(_data, new_size * 2 * sizeof(char));
		if (new_data == nullptr && new_size != 0)
			throw std::overflow_error("Overflow at Resize()");
		_data = new_data;
		for (size_t i = _len; i < new_size * 2; i++)
			_data[i] = '\0';
		_capacity = new_size * 2;
	}

	if (new_size == 0) {
		_len = 0;
		_data = nullptr;
	}
	else
		_len = new_size - 1;
}

char* String::C_string()
{
	return _data;
}
char* String::C_string() const
{
	return _data;
}

String& String::operator=(const String& src)
{
	this->String::String();
	Resize(src.Lenght());
	for (size_t i = 0; i < Lenght(); i++)
		(*this)[i] = src[i];
	return *this;
}
String& String::operator=(const char src[])
{
	this->String::String();
	if (src != nullptr) {
		Resize(strlen(src));
		for (size_t i = 0; i < Lenght(); i++)
			(*this)[i] = src[i];
	}
	else
		Resize(0);
	return *this;
}
String& String::operator+=(const String& a)
{
	size_t old_len = Lenght();
	Resize(Lenght() + a.Lenght());
	for (size_t i = old_len; i < Lenght(); i++)
		(*this)[i] = a[i - old_len];
	return *this;
}
String& String::operator+=(const char a[])
{
	if (a != nullptr) {
		size_t old_len = Lenght();
		Resize(Lenght() + strlen(a));
		for (size_t i = old_len; i < Lenght(); i++)
			(*this)[i] = a[i - old_len];
	}
	return *this;
}
String& String::operator*=(const unsigned m)
{
	size_t old_len = Lenght();
	Resize(Lenght() * m);
	for (size_t i = 1; i < m; i++)
		for (size_t j = 0; j < old_len; j++)
			(*this)[i * old_len + j] = (*this)[j];
	return *this;
}

char& String::operator[](const unsigned index)
{
	if (index < 0 || index >= _len)
		throw std::out_of_range("Incorrect index");
	return _data[index];
}
char String::operator[](const unsigned index) const
{
	if (index < 0 || index >= _len)
		throw std::out_of_range("Incorrect index");
	return _data[index];
}

String operator+(const String& a, const String& b)
{
	String out(a.Lenght() + b.Lenght());
	for (size_t i = 0; i < a.Lenght(); i++)
		out[i] = a[i];
	for (size_t i = a.Lenght(); i < out.Lenght(); i++)
		out[i] = b[i - a.Lenght()];
	return out;
}
String operator+(const String& a, const char b[])
{
	String out(a.Lenght() + strlen(b));
	for (size_t i = 0; i < a.Lenght(); i++)
		out[i] = a[i];
	for (size_t i = a.Lenght(); i < out.Lenght(); i++)
		out[i] = b[i - a.Lenght()];
	return out;
}
String operator+(const char a[], const String& b)
{
	return b + a;
}

String operator*(const String& a, const unsigned b)
{
	String out = a;
	out *= b;
	return out;
}
String operator*(const unsigned a, const String& b)
{
	String out = b;
	out *= a;
	return out;
}

bool operator==(const String& a, const String& b)
{
	if (a.C_string() == nullptr && b.C_string() == nullptr)
		return true;
	else if (a.C_string() == nullptr || b.C_string() == nullptr)
		return false;
	return strcmp(a.C_string(), b.C_string()) == 0;
}

bool operator==(const String& a, const char b[])
{
	if (b == nullptr && a.C_string() == nullptr)
		return true;
	else if (b == nullptr || a.C_string() == nullptr)
		return false;
	return strcmp(a.C_string(), b) == 0;
}

bool operator==(const char b[], const String& a)
{
	if (b == nullptr && a.C_string() == nullptr)
		return true;
	else if (b == nullptr || a.C_string() == nullptr)
		return false;
	return strcmp(a.C_string(), b) == 0;
}

bool operator!=(const String& a, const String& b)
{
	return !(a == b);
}

bool operator!=(const String& a, const char b[])
{
	return !(a == b);
}

bool operator!=(const char b[], const String& a)
{
	return !(a == b);
}