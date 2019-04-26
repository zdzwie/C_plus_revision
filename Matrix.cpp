#include "Matrix.h"

template<size_t N>
template<typename... Dims>
size_t Matrix_slice<N>::operator()(Dims... dims) const {
	static_assert(size_of...(Dims) == N, "");

	size_t args[N]{ size_t(dims)... };
	return inner_product(args, args + N, strides.begin(), size_t(0));
}



template<typename T, size_t N>
template<typename... Exts>
Matrix<T, N>::Matrix(Exts... exts) : desc{exts...}, elems(desc.size){}

template<typename T, size_t N>
Matrix<T, N>::Matrix(Matrix_initializer er<T, N> init) {
	desc.extens = Matrix_impl::derrive_extens(init);
	elems.reserve(desc.size);
	Matrix_impl::insert_flat(init, elems);
	assert(elems.size() == desc.size);
}
template<typename T, size_t N>
template<typename U>
Matrix<T, N>::Matrix(const Matrix_ref<U, N>&x) : desc{ x.desc }, elems{ x.begin(),x.end() 
{
 static_assert(Convertible<U,T>(),"Matrix's constructor: incompatible elements types";
}

template<typename T, size_t N>
template<typename U>
Matrix<T, N>& Matrix<T,N>::operator=(const Matrix_ref<U, N>&x)
{
	static_assert(Convertible<U,T>(),"Matrix's constructor: incompatible elements types";

	desc = x.desc;
	elems.assign(x.begin(), x.end());
	return *this;
}

template<typename T, size_t N>
template<typename F>
Matrix<T,N>& Matrix<T,N>::apply(F f) {
	for (auto& x : elems)f(x);
	return *this;
}

template<typename T, size_t N>
Matrix<T,N>&Matrix<T,N>::operator+=(const T& val) {
	return apply([&](T& a) {a += val; };)
}

template<typename T, size_t N>
Matrix<T,N> Matrix<T,N>::operator+(const Matrix<T,N>&m, const T& val) {
	Matrix<T,N> res = m;
	res += val;
	return res;
}

template<typename T, size_t N>
template<typename M>
Enable_if<Matrix_type<M>(),Matrix<T,N>&>
Matrix<T,N>::operator+=(const M& m) {
	static_assert(m.oder() == N,"+=:mismatched Matrix dimensions");
	assert(same_extens(desc, m.descriptor()));

	return apply(m,[]T& a, Value_type<M> &b) { a += b; });
}

template<typename T, siz e_t N>
template<typename M, typename F>
Enable_if<Matrix_type<M>(),Matrix<T,N>&> Matrix<T,N>::apply(M& m, F f)
{
	assert(same_extents(desc,m.descriptor())); 
	for (auto i = begin(), j = m.begin(); i != end(); ++i, ++j)
		f(∗i,∗j);
	return ∗this;
}

template<typename T, typename T2, size_t N, typename RT=Matrix<Common_type<Value_type<T>,Value_type<T2>>,N>
Matrix<RT,N> operator+(const Matrix<T,N>& a, const Matrix <T2,N>& b) {
	Matrix<RT, N> res = a;
	res += b;
	return res;
}

template<typename T>
Matrix<T,2> Matrix<T,2>::operator*(const Matrix<T,1>& u, const Matrix<T,1>& v) {
	const size_t n = u.extent(0);
	const size_t m = v.extent(0);
	Matrix<T, 2> res(n, m);
	for (size_t i = 0; i != n; ++i)
		for (size_t j = 0; j != m; ++j)
			res(i, j) = u[i] * v[j];
	return res;
}

template<typename T>
T Matrix<T,1>::dot_product(const Matrix_ref<T,1>& a, const Matrix_ref<T,1>& b)
{
	return inner_product(a.begin(),a.end(),b.begin(),0.0);
}



