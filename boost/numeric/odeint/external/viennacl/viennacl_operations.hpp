/*
 [auto_generated]
 boost/numeric/odeint/external/viennacl_operations.hpp

 [begin_description]
 ViennaCL operations.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_OPERATIONS_HPP_INCLUDED

#include <viennacl/vector.hpp>

#ifdef VIENNACL_WITH_OPENCL
#  include <viennacl/generator/custom_operation.hpp>
#  include <boost/numeric/odeint/util/n_ary_helper.hpp>
#endif

namespace boost {
namespace numeric {
namespace odeint {


#ifdef VIENNACL_WITH_OPENCL
struct viennacl_operations
{

#define BOOST_ODEINT_GEN_BODY(n, unused) \
    template< BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), class T) > \
    void operator()( viennacl::vector<T0> &v0 \
        BOOST_ODEINT_ENUM_TRAILING_SHIFTED_BINARY_PARAMS(BOOST_PP_INC(n), \
            const viennacl::vector<T, > &v) \
    ) const { \
        using namespace viennacl; \
        BOOST_PP_REPEAT(BOOST_PP_INC(n), BOOST_ODEINT_GEN_BODY_1, ~) \
        BOOST_PP_REPEAT(n, BOOST_ODEINT_GEN_BODY_2, BOOST_PP_INC(n)) \
        static generator::custom_operation op( \
            sym_v0 = BOOST_PP_REPEAT(n, BOOST_ODEINT_GEN_BODY_3, ~) , \
            "scale_sum" #n \
        ); \
        ocl::enqueue( op( \
            BOOST_PP_ENUM_PARAMS(BOOST_PP_INC(n), v) , \
            BOOST_PP_ENUM_PARAMS(n, m_alpha) \
        ) ); \
    }
#define BOOST_ODEINT_GEN_BODY_1(z, n, unused) \
    static generator::symbolic_vector< n , T##n > sym_v##n ;
#define BOOST_ODEINT_GEN_BODY_2(z, n, max_n) \
    static generator::cpu_symbolic_scalar< BOOST_PP_ADD(n, max_n) , T##n > sym_a##n ;
#define BOOST_ODEINT_GEN_BODY_3(z, n, unused) \
    BOOST_PP_IF(n, +, BOOST_PP_EMPTY()) \
    sym_a##n * BOOST_PP_CAT(sym_v, BOOST_PP_INC(n))
BOOST_ODEINT_GEN_SCALE_SUM_OUTER((BOOST_ODEINT_GEN_BODY, ~))
#undef BOOST_ODEINT_GEN_BODY
#undef BOOST_ODEINT_GEN_BODY_1
#undef BOOST_ODEINT_GEN_BODY_2
#undef BOOST_ODEINT_GEN_BODY_3

};
#else
struct viennacl_operations : public default_operations {};
#endif


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VIENNACL_VIENNACL_OPERATIONS_HPP_INCLUDED
