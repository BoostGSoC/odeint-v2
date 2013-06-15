/*
 [auto_generated]
 boost/numeric/odeint/algebra/fusion_algebra.hpp

 [begin_description]
 Algebra for boost::fusion sequences.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_HPP_INCLUDED

#include <algorithm>

#include <boost/numeric/odeint/config.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

#include <boost/fusion/container/vector.hpp>
#include <boost/fusion/algorithm/iteration/for_each.hpp>
#include <boost/fusion/view/zip_view.hpp>
#include <boost/fusion/functional/generation/make_fused.hpp>
#include <boost/fusion/algorithm/iteration/accumulate.hpp>

namespace boost {
namespace numeric {
namespace odeint {

namespace detail {

    template< class Value >
    struct fusion_maximum
    {
        template< class Fac1 , class Fac2 >
        Value operator()( Fac1 t1 , const Fac2 t2 ) const
        {
            using std::abs;
            Value a1 = abs( get_unit_value( t1 ) ) , a2 = abs( get_unit_value( t2 ) );
            return ( a1 < a2 ) ? a2 : a1 ;
        }

        typedef Value result_type;
    };
}

/* specialize this if the fundamental numeric type in your fusion sequence is
 * anything else but double (most likely not)
 */
template< typename Sequence >
struct fusion_traits {
    typedef double value_type;
};

struct fusion_algebra
{

#define BOOST_ODEINT_GEN_BODY(n) \
    BOOST_STATIC_ASSERT_MSG( BOOST_FUSION_INVOKE_MAX_ARITY >= n , \
        "Macro Parameter BOOST_FUSION_INVOKE_MAX_ARITY to small!" ); \
    BOOST_STATIC_ASSERT_MSG( BOOST_RESULT_OF_NUM_ARGS >= n , \
        "Macro Parameter BOOST_RESULT_OF_NUM_ARGS to small!" ); \
    typedef boost::fusion::vector< \
        BOOST_PP_ENUM_BINARY_PARAMS(n, S, & BOOST_PP_INTERCEPT) \
    > Sequences; \
    Sequences sequences( BOOST_PP_ENUM_PARAMS(n, s) ); \
    boost::fusion::for_each( \
        boost::fusion::zip_view< Sequences >( sequences ) , \
        boost::fusion::make_fused( op ) \
    );
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY

    template< class S >
    static typename fusion_traits< S >::value_type norm_inf( const S &s )
    {
        typedef typename fusion_traits< S >::value_type value_type;
        return boost::fusion::accumulate( s , static_cast<value_type>(0) ,
                                          detail::fusion_maximum<value_type>() );
    }

};



} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_FUSION_ALGEBRA_HPP_INCLUDED
