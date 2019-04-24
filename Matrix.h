#pragma once
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include<assert.h>
using namespace std;

template<typename T, size_t N>
class Matrix{
private:
	Matrix_silce<N> desc;
	vector<T> elems;
public:

	static constexpr size_t order = N;
	using value_type = T;
	using iterator = typename vector<T>::iterator;
	using const_interator = typename vector<T>::const_iterator;
	
	//Class constructors
	Matrix() = default;
	Matrix(Matrix&&) = default;
	Matrix& operator =(Marix&&) = default;
	Matrix(const Matrix&) = default;
	Matrix& operator=(const Matrix&) = default;

	//Class destructor
	~Matrix();

	template<typename U>
	Matrix(const Matrix_ref<U, N>&);
	template<typename U>
	Matrix& operator=(const Matrix_ref<U, N>&);

	//Size defining
	template<typename... Exts>
	explicit Matrix(Exts... exts);

	//Initialization from list
	Matrix(Matrix_initializer<T, N>);
	Matrix& operator+(const Matrix_ref<U, N>&);

	template<typename U>
	Matrix(initializer_list<U>) = delete;
	template<typename U>
	Matrix& operator=(initializer_list<U>) = delete;

	//Number of dimension
	static constexpr size_t order() { return N; }
	//Number of elements in n dimension
	size_t extent(size_t n) const { return desc.extens[n]; }
	//Sum of all elements
	size_t size() const { return elems.size(); }
	//Clip defing indexing
	const Matrix_slice<N>& descriptor() const { return desc; }

	//"Flat" access to elements
	T* data() { return elems.data(); }
	const T*data() const { return elems.data(); }



};

#endif // !1


