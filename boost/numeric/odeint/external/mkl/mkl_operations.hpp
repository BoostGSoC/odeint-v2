/*
 [auto_generated]
 boost/numeric/odeint/external/mkl/mkl_operations.hpp

 [begin_description]
 Wrapper classes for intel math kernel library types.
 Get a free, non-commercial download of MKL at
 http://software.intel.com/en-us/articles/non-commercial-software-download/
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_MKL_MKL_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_MKL_MKL_OPERATIONS_HPP_INCLUDED

#include <iostream>

#include <mkl_cblas.h>
#include <boost/numeric/odeint/algebra/default_operations.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>

/* exemplary example for writing bindings to the Intel MKL library
 * see test/mkl for how to use mkl with odeint
 * this is a quick and dirty implementation showing the general possibility.
 * It works only with containers based on double and sequential memory allocation.
 */

namespace boost {
namespace numeric {
namespace odeint {

/* only defined for doubles */
struct mkl_operations
{

#define BOOST_ODEINT_GEN_BODY(n) \
    const int _n = t0.size(); \
    if( &(t1[0]) != &(t0[0]) ) \
        cblas_dcopy( _n , &(t1[0]) , 1 , &(t0[0]) , 1 ); \
    cblas_dscal( _n , m_alpha0 , &(t0[0]) , 1 ); \
    BOOST_PP_REPEAT_FROM_TO(1, n, BOOST_ODEINT_GEN_BODY_, ~)
#define BOOST_ODEINT_GEN_BODY_(z, n, unused) \
    cblas_daxpy( _n , m_alpha##n , &(BOOST_PP_CAT(t, BOOST_PP_INC(n))[0]) , 1 , &(t0[0]) , 1 );
BOOST_ODEINT_GEN_SCALE_SUM(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY
#undef BOOST_ODEINT_GEN_BODY_

};

} // odeint
} // numeric
} // boost

#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_MKL_MKL_OPERATIONS_HPP_INCLUDED
