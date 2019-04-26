#pragma once
#ifndef _MATRIX_H_
#define _MATRIX_H_

#include<assert.h>
using namespace std;

template<size_t N>
struct Matrix_slice {
	Matrix_slice() = default;

	Matrix_slice(size_t s, initializer_list<size_t> exts);
	Matrix_slice(size_t s, initializer_list<size_t> exts, initializer_list<size_t> strs);

	template<typename... Dims>
	Matrix_slice(Dims... dims);

	template<typename... Dims, typename = Enable_ifAll(Convertible<Dims, size_t>()...) >>
		size_t operator()(Dims... dims) const;

	size_t size;
	size_t start;
	array<size_t, N> extends;
	array<size_t, N> strides;
};
template<typename T, size_t N>
class Matrix{
private:
	Matrix_silce<N> desc;
	std::vector<T> elems;
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
	Matrix& operator=(const Matrix_ref<U, N>&);

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

	template<typename... Args>
		Enable_if<Matrix_impl::Requesting_element<Args...>(), T&>
		operator()(Args... args);
	template<typename... Args>
		Enable_if<Matrix_impl::Requesting_element<Args...>(), const T&>
		operator()(Args... args) const;
	template<typename... Args>
		Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<T, N>>
		operator()(const Args&... args);
	template<typename... Args>
		Enable_if<Matrix_impl::Requesting_slice<Args...>(), Matrix_ref<const T, N>>
		operator()(const Args&... args) const;

	//m[i] Row access
	Matrix_ref<T, N - 1> operator[](size_t i) { return row(i); }
	Matrix_ref<const T, N - 1> operator[](size_t i) const { return row(i); }

	//Row access
	Matrix_ref<T, N - 1> row(size_t n);
	Matrix_ref<const T, N - 1> row(size_t n) const;

	//Column access
	Matrix_ref<T, N - 1> col(size_t n);
	Matrix_ref<const T, N - 1> col(size_t n) const;

	//f(x) for every element x
	template<typename F>
	Matrix& apply(F f);

	//f(x, mx) for corresponding elements
	template<typename M, typename F>
	Matrix& apply(const M& m, F f);

	//Assigment with scalar
	Matrix& operator=(const T& value);

	//Scalar operations. 
	Matrix& operator+=(const T& value);
	Matrix operator+(const Matrix<T, N>&, const T&);
	
	Matrix& operator-=(const T& value);

	Matrix& operator*=(const T& value);
	Matrix<T, 2> operator*(const Matrix<T, 1>&, const Matrix<T, 1>&);

	Matrix& operator/=(const T& value);
	Matrix& operator%=(const T& value);

	//Matrix operations.
	template<typename M>
	Matrix& operator+=(const M& x);
	template<typename M>
	Matrix& operator-=(const M& x);

	T dot_product(const Matrix_ref<T, 1>&, const Matrix_ref<T, 1>&);
};

/*template<>
struct common_type<Quad, long double> {
	using type = Quad;
};*/
#endif // _MATRIX_H_
