/*
 [auto_generated]
 boost/numeric/odeint/algebra/detail/for_each.hpp

 [begin_description]
 Default for_each implementations.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED

#include <boost/numeric/odeint/util/n_ary_helper.hpp>

namespace boost {
namespace numeric {
namespace odeint {
namespace detail {

#define BOOST_ODEINT_GEN(z, n, unused) \
    template< BOOST_PP_ENUM_PARAMS(n, class Iterator) , class Operation > \
    inline void for_each##n( \
        Iterator0 first0 , Iterator0 last0 \
        BOOST_PP_COMMA_IF(BOOST_PP_DEC(n)) \
        BOOST_PP_ENUM_SHIFTED_BINARY_PARAMS(n, Iterator, first) , \
        Operation op ) \
    { \
        for( ; first0 != last0 ; ) \
            op( \
                BOOST_PP_ENUM_BINARY_PARAMS(n, *first, ++ BOOST_PP_INTERCEPT) \
            ); \
    }
BOOST_PP_REPEAT_FROM_TO(1, BOOST_ODEINT_N_ARY_MAX, BOOST_ODEINT_GEN, ~)
#undef BOOST_ODEINT_GEN

} // detail
} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DETAIL_FOR_EACH_HPP_INCLUDED
