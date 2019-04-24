#include "Matrix.h"

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
Matrix<T, N>&::Matrix operator=(const Matrix_ref<U, N>&x) 
{
	static_assert(Convertible<U,T>(),"Matrix's constructor: incompatible elements types";

	desc = x.desc;
	elems.assign(x.begin(), x.end());
	return *this;
}

