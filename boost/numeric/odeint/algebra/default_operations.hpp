/*
 [auto_generated]
 boost/numeric/odeint/algebra/default_operations.hpp

 [begin_description]
 Default operations. They work with the default numerical types, like float, double, complex< double> ...
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_DEFAULT_OPERATIONS_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_DEFAULT_OPERATIONS_HPP_INCLUDED

#include <algorithm>

#include <boost/config.hpp>
#include <boost/array.hpp>

#include <boost/numeric/odeint/util/unit_helper.hpp>
#include <boost/numeric/odeint/util/n_ary_helper.hpp>


namespace boost {
namespace numeric {
namespace odeint {



/*
 * Notes:
 *
 * * the results structs are needed in order to work with fusion_algebra
 */
struct default_operations
{

    template< class Fac1 = double >
    struct scale
    {
        const Fac1 m_alpha1;

        scale( Fac1 alpha1 ) : m_alpha1( alpha1 ) { }

        template< class T1 >
        void operator()( T1 &t1 ) const
        {
            t1 *= m_alpha1;
        }

        typedef void result_type;
    };


#define BOOST_ODEINT_GEN_BODY(n) \
    t0 = BOOST_PP_REPEAT(n, BOOST_ODEINT_GEN_BODY_, ~) ;
#define BOOST_ODEINT_GEN_BODY_(z, n, unused) \
    BOOST_PP_IF(n, +, BOOST_PP_EMPTY()) \
    m_alpha##n * BOOST_PP_CAT(t, BOOST_PP_INC(n))
BOOST_ODEINT_GEN_SCALE_SUM(BOOST_ODEINT_GEN_BODY)
#undef BOOST_ODEINT_GEN_BODY
#undef BOOST_ODEINT_GEN_BODY_


    template< class Fac1 = double , class Fac2 = Fac1 >
    struct scale_sum_swap2
    {
        const Fac1 m_alpha1;
        const Fac2 m_alpha2;

        scale_sum_swap2( Fac1 alpha1 , Fac2 alpha2 ) : m_alpha1( alpha1 ) , m_alpha2( alpha2 ) { }

        template< class T1 , class T2 , class T3 >
        void operator()( T1 &t1 , T2 &t2 , const T3 &t3) const
        {
            const T1 tmp( t1 );
            t1 = m_alpha1 * t2 + m_alpha2 * t3;
            t2 = tmp;
        }

        typedef void result_type;
    };

    /*
     * for usage in for_each2
     *
     * Works with boost::units by eliminating the unit
     */
    template< class Fac1 = double >
    struct rel_error
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt ) { }


        template< class T1 , class T2 , class T3 >
        void operator()( T3 &t3 , const T1 &t1 , const T2 &t2 ) const
        {
            using std::abs;
            set_unit_value( t3 , abs( get_unit_value( t3 ) ) / ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( t1 ) ) + m_a_dxdt * abs( get_unit_value( t2 ) ) ) ) );
        }

        typedef void result_type;
    };


    /*
     * for usage in for_each3
     *
     * used in the controller for the rosenbrock4 method
     *
     * Works with boost::units by eliminating the unit
     */
    template< class Fac1 = double >
    struct default_rel_error
    {
        const Fac1 m_eps_abs , m_eps_rel ;

        default_rel_error( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) { }


        /*
         * xerr = xerr / ( eps_abs + eps_rel * max( x , x_old ) )
         */
        template< class T1 , class T2 , class T3 >
        void operator()( T3 &t3 , const T1 &t1 , const T2 &t2 ) const
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Fac1 x1 = abs( get_unit_value( t1 ) ) , x2 = abs( get_unit_value( t2 ) );
            set_unit_value( t3 , abs( get_unit_value( t3 ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( x1 , x2 ) ) );
        }

        typedef void result_type;
    };



    /*
     * for usage in reduce
     */

    template< class Value >
    struct maximum
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


    template< class Fac1 = double >
    struct rel_error_max
    {
        const Fac1 m_eps_abs , m_eps_rel;

        rel_error_max( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel )
        { }

        template< class Res , class T1 , class T2 , class T3 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( x_old ) , abs( x ) ) );
            return max BOOST_PREVENT_MACRO_SUBSTITUTION ( r , tmp );
        }
    };


    template< class Fac1 = double >
    struct rel_error_max2
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error_max2( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
        { }

        template< class Res , class T1 , class T2 , class T3 , class T4 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &dxdt_old , const T4 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( x_old ) ) + m_a_dxdt * abs( get_unit_value( dxdt_old ) ) ) );
            return max BOOST_PREVENT_MACRO_SUBSTITUTION ( r , tmp );
        }
    };




    template< class Fac1 = double >
    struct rel_error_l2
    {
        const Fac1 m_eps_abs , m_eps_rel;

        rel_error_l2( Fac1 eps_abs , Fac1 eps_rel )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel )
        { }

        template< class Res , class T1 , class T2 , class T3 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &x_err )
        {
            BOOST_USING_STD_MAX();
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) / ( m_eps_abs + m_eps_rel * max BOOST_PREVENT_MACRO_SUBSTITUTION ( abs( x_old ) , abs( x ) ) );
            return r + tmp * tmp;
        }
    };




    template< class Fac1 = double >
    struct rel_error_l2_2
    {
        const Fac1 m_eps_abs , m_eps_rel , m_a_x , m_a_dxdt;

        rel_error_l2_2( Fac1 eps_abs , Fac1 eps_rel , Fac1 a_x , Fac1 a_dxdt )
        : m_eps_abs( eps_abs ) , m_eps_rel( eps_rel ) , m_a_x( a_x ) , m_a_dxdt( a_dxdt )
        { }

        template< class Res , class T1 , class T2 , class T3 , class T4 >
        Res operator()( Res r , const T1 &x_old , const T2 &x , const T3 &dxdt_old , const T4 &x_err )
        {
            using std::abs;
            Res tmp = abs( get_unit_value( x_err ) ) /
                    ( m_eps_abs + m_eps_rel * ( m_a_x * abs( get_unit_value( x_old ) ) + m_a_dxdt * abs( get_unit_value( dxdt_old ) ) ) );
            return r + tmp * tmp;
        }
    };






};


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_ALGEBRA_DEFAULT_OPERATIONS_HPP_INCLUDED
