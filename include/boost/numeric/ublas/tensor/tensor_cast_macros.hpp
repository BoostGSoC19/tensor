//  Copyright (c) 2019-2020
//  Mohammad Ashar Khan, ashar786khan@gmail.com
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  Google in producing this work
//  which started as a Google Summer of Code project.

#ifndef BOOST_UBLAS_TENSOR_CAST_MACRO
#define BOOST_UBLAS_TENSOR_CAST_MACRO

#include <boost/numeric/ublas/detail/config.hpp>


#include <boost/yap/yap.hpp>
#include <type_traits>
#include <vector>

namespace boost::numeric::ublas {
template <class T, class F, class A> class tensor;
}

/**
 * @brief This MACRO defines a casting function. It eagerly casts the tensor
 * from one to other data type.
 *
 */
#define BOOST_UBLAS_EAGER_TENSOR_CAST(func_name, cast_name)                    \
  template <class new_type, typename Tensor> decltype(auto) func_name(Tensor &e) {       \
    if constexpr (std::is_same<new_type, typename Tensor::value_type>::value)  \
      return e;                                                                \
    tensor<new_type, typename Tensor::layout_type,                             \
           typename storage_traits<                                            \
               typename Tensor::array_type>::template rebind<new_type>>        \
        result;                                                                \
    result.data_.resize(e.extents().product());                                \
    result.strides_ = e.strides();                                             \
    result.extents_ = e.extents();                                             \
    for (auto i = 0u; i < e.extents().product(); i++)                          \
      result.data_[i] = cast_name<new_type>(e.data_[i]);                       \
    return result;                                                             \
  }                                                                            \
  template <class new_type, typename Tensor> decltype(auto) func_name(Tensor &&e) {      \
    if constexpr (std::is_same<new_type, typename Tensor::value_type>::value)  \
      return std::forward<Tensor>(e);                                                                \
    tensor<new_type, typename Tensor::layout_type,                             \
           typename storage_traits<                                            \
               typename Tensor::array_type>::template rebind<new_type>>        \
        result;                                                                \
    result.data_.resize(e.extents().product());                                \
    result.strides_ = std::move(e.strides());                                  \
    result.extents_ = std::move(e.extents());                                  \
    for (auto i = 0u; i < result.extents_.product(); i++)                      \
      result.data_[i] = cast_name<new_type>(e.data_[i]);                       \
    return std::forward<Tensor>(result);                                                             \
  }

#endif
