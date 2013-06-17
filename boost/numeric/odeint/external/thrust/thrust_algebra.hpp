/*
 [auto_generated]
 boost/numeric/odeint/external/thrust/thrust_algebra.hpp

 [begin_description]
 An algebra for thrusts device_vectors.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED


#include <thrust/device_vector.h>
#include <thrust/for_each.h>
#include <thrust/iterator/zip_iterator.h>

#include <boost/range.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {

namespace detail {

    // to use in thrust::reduce
    template< class Value >
    struct maximum
    {
        template< class Fac1 , class Fac2 >
        __host__ __device__
        Value operator()( const Fac1 t1 , const Fac2 t2 ) const
        {
            return ( abs( t1 ) < abs( t2 ) ) ? t2 : t1 ;
        }

        typedef Value result_type;
    };

}




/*
 * The const versions are needed for boost.range to work, i.e.
 * it allows you to do
 * for_each1( make_pair( vec1.begin() , vec1.begin() + 10 ) , op );
 */

struct thrust_algebra
{

#define BOOST_ODEINT_GEN_BODY(n) \
    BOOST_PP_IF(BOOST_PP_DEC(n) \
    , /* n > 1 */ \
        thrust::for_each( \
            thrust::make_zip_iterator( thrust::make_tuple( \
                BOOST_ODEINT_ENUM_UNARY_CALLS(n, boost::begin BOOST_PP_INTERCEPT, s) \
            ) ) , \
            thrust::make_zip_iterator( thrust::make_tuple( \
                BOOST_ODEINT_ENUM_UNARY_CALLS(n, boost::end BOOST_PP_INTERCEPT, s) \
            ) ) , op ); \
    , /* n = 1 */ \
        thrust::for_each( boost::begin(s0) , boost::end(s0) , op ); \
    )
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY

    template< class S >
    static typename S::value_type norm_inf( const S &s )
    {
        typedef typename S::value_type value_type;
        return thrust::reduce( boost::begin( s ) , boost::end( s ) ,
                               static_cast<value_type>(0) ,
                               detail::maximum<value_type>() );
    }

};


} // odeint
} // numeric
} // boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_THRUST_THRUST_ALGEBRA_HPP_INCLUDED
