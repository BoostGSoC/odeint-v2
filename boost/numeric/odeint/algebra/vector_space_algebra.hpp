/*
 [auto_generated]
 boost/numeric/odeint/algebra/vector_space_algebra.hpp

 [begin_description]
 An algebra for types which have vector space semantics, hence types on which the operators +,-,* are well defined.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_VECTOR_SPACE_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_VECTOR_SPACE_ALGEBRA_HPP_INCLUDED

#include <complex>

#include <boost/type_traits/remove_reference.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>


namespace boost {
namespace numeric {
namespace odeint {

/*
 * This class template has to be overload in order to call vector_space_algebra::norm_inf
 */
template< class State > struct vector_space_norm_inf;

/*
 * Example: instantiation for sole doubles and complex
 */
template<>
struct vector_space_norm_inf< double >
{
    typedef double result_type;
    double operator()( double x ) const
    {
        using std::abs;
        return abs(x);
    }
};

template<>
struct vector_space_norm_inf< float >
{
    typedef float result_type;
    result_type operator()( float x ) const
    {
        using std::abs;
        return abs(x);
    }
};

template< typename T >
struct vector_space_norm_inf< std::complex<T> >
{
    typedef T result_type;
    result_type operator()( std::complex<T> x ) const
    {
        using std::abs;
        return abs( x );
    }
};

struct vector_space_algebra
{
    // ToDo : build checks, that the +-*/ operators are well defined
#define BOOST_ODEINT_GEN_BODY(n) \
    op( BOOST_PP_ENUM_PARAMS(n, s) );
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY

    template< class S >
    static typename boost::numeric::odeint::vector_space_norm_inf< S >::result_type norm_inf( const S &s )
    {
        boost::numeric::odeint::vector_space_norm_inf< S > n;
        return n( s );
    }
};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_VECTOR_SPACE_ALGEBRA_HPP_INCLUDED
