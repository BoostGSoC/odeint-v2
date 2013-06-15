/*
 [auto_generated]
 boost/numeric/odeint/algebra/range_algebra.hpp

 [begin_description]
 Default algebra, which works with the most state types, like vector< double >, boost::array< double >, boost::range.
 Internally is uses boost::range to obtain the begin and end iterator of the according sequence.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED

#include <algorithm>

#include <boost/range.hpp>
#include <boost/mpl/size_t.hpp>

#include <boost/numeric/odeint/algebra/detail/macros.hpp>
#include <boost/numeric/odeint/algebra/detail/for_each.hpp>
#include <boost/numeric/odeint/algebra/detail/norm_inf.hpp>
#include <boost/numeric/odeint/algebra/norm_result_type.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {

struct range_algebra
{

#define BOOST_ODEINT_GEN_BODY(n) \
    detail::for_each##n( \
        boost::begin( s0 ) , \
        boost::end( s0 ) \
        BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
        BOOST_ODEINT_ENUM_SHIFTED_UNARY_CALLS(n, boost::begin BOOST_PP_INTERCEPT, s) , \
        op );
BOOST_ODEINT_GEN_FOR_EACH(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY

    template< typename S >
    static typename norm_result_type<S>::type norm_inf( const S &s )
    {
        return detail::norm_inf( boost::begin( s ) , boost::end( s ) ,
                                 static_cast< typename norm_result_type<S>::type >( 0 ) );
    }

};

} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_RANGE_ALGEBRA_HPP_INCLUDED
