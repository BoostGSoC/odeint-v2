/*
 [auto_generated]
 boost/numeric/odeint/external/thrust/thrust_operations.hpp

 [begin_description]
 Operations of thrust zipped iterators. Is the counterpart of the thrust_algebra.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

#include <thrust/tuple.h>
#include <thrust/iterator/zip_iterator.h>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

struct thrust_operations
{

    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum_swap2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum_swap2( const Fac1 alpha1 , const Fac2 alpha2 )
        : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            typename thrust::tuple_element<0,Tuple>::type tmp = thrust::get<0>(t);
            thrust::get<0>(t) = m_alpha1 * thrust::get<1>(t) + m_alpha2 * thrust::get<2>(t);
            thrust::get<1>(t) = tmp;
        }
    };


#define BOOST_ODEINT_GEN_BODY(n, unused) \
    template< class Tuple > \
    __host__ __device__ \
    void operator()( Tuple t ) const \
    { thrust::get<0>(t) = BOOST_PP_REPEAT(n, BOOST_ODEINT_GEN_BODY_, ~) ; }
#define BOOST_ODEINT_GEN_BODY_(z, n, unused) \
    BOOST_PP_IF(n, +, BOOST_PP_EMPTY()) \
    m_alpha##n * thrust::get<BOOST_PP_INC(n)>(t)
BOOST_ODEINT_GEN_SCALE_SUM_OUTER((BOOST_ODEINT_GEN_BODY, ~))
#undef BOOST_ODEINT_GEN_BODY
#undef BOOST_ODEINT_GEN_BODY_


    template< class Fac1 = double >
    struct rel_error
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error( const Fac1 eps_abs , const Fac1 eps_rel , const Fac1 a_x , const Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }


        template< class Tuple >
        __host__ __device__
        void operator()( Tuple t ) const
        {
            using std::abs;
            thrust::get< 0 >( t ) = abs( thrust::get< 0 >( t ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( thrust::get< 1 >( t ) + m_a_dxdt * abs( thrust::get< 2 >( t ) ) ) ) );
        }

        typedef void result_type;
    };


};

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_OPERATIONS_HPP_INCLUDED
