#include<iostream>
#include<string>
#include<sstream>
#include <vector>

std::string help =
R"("
# Methods of Optimization, BDZ3 by Mikhaylova Ekaterina #
  > find minimum point with e : | df/dx | < 0.1 and | df/dy | < 0.1
  > calculate value of function in minimum point
  > use methods: 
    1. gradient descent method
    2. steepest gradient descent method
    3. Newton's method
)";

double x_0 = 3;
double y_0 = 4;
double e = 0.1;
//.............................................................................
#define EXIT( message ) { std::cout << "\033[1;31mERROR: " << message << " \033[0m" << std::endl; exit(EXIT_FAILURE); }
#define WARNING( message ) { std::cout << "\033[1;33mWARNING: " << message << " \033[0m" << std::endl; }
#define INFO( message ) { std::cout << "\033[1;32mINFO: " << message << " \033[0m" << std::endl; }

struct PointValue {
    double x;
    double y;
    double f;
    PointValue( double _x, double _y, double _f ) { x = _x; y = _y; f = _f; }
};
//.............................................................................
// my goal function
double goalFunction( double x, double y ) {
    return x * x + x * y + 2 * y * y - 7.6 * x - 13.9 * y + 18.9;
}
double goalFunctionDerX( double x, double y ) {
    return 2 * x + y - 7.6;
}
double goalFunctionDerY( double x, double y ) {
    return x + 4 * y - 13.9;
}
double goalFunctionDer2X( double x, double y ) {
    return 2;
}
double goalFunctionDer2Y( double x, double y ) {
    return 4;
}
double goalFunctionDerXY( double x, double y ) {
    return 1;
}

//.............................................................................
// gradient descent method
void gradient() {

    double dfdx = goalFunctionDerX( x_0, y_0 );
    double dfdy = goalFunctionDerY( x_0, y_0 );

    double x_1 = x_0, y_1 = y_0;
    double f0 = goalFunction( x_0, y_0 );

    std::vector<PointValue> iter;
    iter.push_back( PointValue( x_0, y_0, f0 ) );

    while( abs( dfdx ) > e or abs( dfdy ) > e ) {
        x_1 = x_1 - e * dfdx;
        y_1 = y_1 - e * dfdy;

        dfdx = goalFunctionDerX( x_1, y_1 );
        dfdy = goalFunctionDerY( x_1, y_1 );

        f0 = goalFunction( x_1, y_1 );
        iter.push_back( PointValue( x_1, y_1, f0 ) );
    }
    double x_min = iter.back().x;
    double y_min = iter.back().y;
    double f_min = iter.back().f;

    std::stringstream ss;
    ss << "Gradient descent : Minimum point : ( " << x_min << "; " << y_min << " ); Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].x << "\t" <<
              "y_" << iter.size() - i << " = " << iter[ iter.size() - i ].y << "\t" <<
              "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].f << std::endl;
    }
    INFO( ss.str() );
}

//.............................................................................
// steepest gradient descent method analythic
void steepestGradient() {
    double x_1 = x_0;
    double y_1 = y_0;

    double dfdx = goalFunctionDerX( x_0, y_0 );
    double dfdy = goalFunctionDerY( x_0, y_0 );
    double l = ( dfdx * dfdx + dfdy * dfdy ) / ( 2 * ( pow( dfdx, 2 ) + dfdx * dfdy + pow( dfdy, 2 ) ) );

    double f0 = goalFunction( x_1, y_1 );

    std::vector<PointValue> iter;
    iter.push_back( PointValue( x_1, y_1, f0 ) );

    while( abs( dfdx ) > 0.1 || abs( dfdy ) > 0.1 ) {
        x_1 = x_1 - l * dfdx;
        y_1 = y_1 - l * dfdy;

        dfdx = goalFunctionDerX( x_1, y_1 );
        dfdy = goalFunctionDerY( x_1, y_1 );
        l = ( dfdx * dfdx + dfdy * dfdy ) / ( 2 * ( pow( dfdx, 2 ) + dfdx * dfdy + pow( dfdy, 2 ) ) );

        f0 = goalFunction( x_1, y_1 );
        iter.push_back( PointValue( x_1, y_1, f0 ) );
    }
    double x_min = iter.back().x;
    double y_min = iter.back().y;
    double f_min = iter.back().f;

    std::stringstream ss;
    ss << "Steepest gradient descent : Minimum point : ( " << x_min << "; " << y_min << " ); Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].x << "\t" <<
            "y_" << iter.size() - i << " = " << iter[ iter.size() - i ].y << "\t" <<
            "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].f << std::endl;
    }
    INFO( ss.str() );
}
//.............................................................................
// steepest gradient descent method one-dimensional minimization by bitwise search
double lFunction( double l, double x, double y ) {
    double dfx = goalFunctionDerX( x, y );
    double dfy = goalFunctionDerY( x, y );
    double k1 = l * l * ( dfx * dfx + dfx * dfy + dfy * dfy );
    double k2 = l * ( 7.6 * dfx + 13.9 * dfy - 2 * x * dfx - x * dfy - y * dfx - 4 * y * dfy );
    double k3 = goalFunction( x, y );

    return k1 + k2 + k3;
}
void changeStepSize( bool & mode, double & h ) {
    mode = !mode;
    h = h / 2;
}
double bitwiseSearch( double x, double y ) {
    double a = 0;
    double b = 10;
    double h = ( b - a ) / 4;
    double l = a;
    double f0 = lFunction( l, x, y );
    bool mode = true;

    while( h > 0.001 ) {
        double l1 = l + h;
        bool isOutOfRange = ( l1 > b );
        double tempL = b;
        if( !mode ) {
            l1 = l - h;
            isOutOfRange = l1 < a;
            tempL = a;
        }
        double f1 = lFunction( l1, x, y );
        if( isOutOfRange ) {
            changeStepSize( mode, h );
            l1 = tempL;
            f1 = lFunction( l1, x, y );
        }

        if( f1 > f0 ) changeStepSize( mode, h );
        l = l1;
        f0 = f1;
    }
    return l;
}
void steepestGradientBitwiseSearch() {
    double x0 = 3;
    double y0 = 4;
    double l = bitwiseSearch( x0, y0 );

    double f0 = goalFunction( x0, y0 );
    double dfx = goalFunctionDerX( x0, y0 );
    double dfy = goalFunctionDerY( x0, y0 );

    std::vector<PointValue> iter;
    iter.push_back( PointValue( x0, y0, f0 ) );

    while( abs( dfx ) > e or abs( dfy ) > e ) {
        x0 = x0 - l * dfx;
        y0 = y0 - l * dfy;

        l = bitwiseSearch( x0, y0 );

        f0 = goalFunction( x0, y0 );
        iter.push_back( PointValue( x0, y0, f0 ) );
        dfx = goalFunctionDerX( x0, y0 );
        dfy = goalFunctionDerY( x0, y0 );
    }
    double x_min = iter.back().x;
    double y_min = iter.back().y;
    double f_min = iter.back().f;

    std::stringstream ss;
    ss << "Steepest gradient descent with bitwise search: Minimum point : ( " << x_min 
        << "; " << y_min << " ); Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].x << "\t" <<
            "y_" << iter.size() - i << " = " << iter[ iter.size() - i ].y << "\t" <<
            "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].f << std::endl;
    }
    INFO( ss.str() );
}

//.............................................................................
// newton method
void newton() {
    double Hesse[ 2 ][ 2 ];
    double x0 = x_0;
    double y0 = y_0;

    double dfx = goalFunctionDerX( x0, y0 );
    double dfy = goalFunctionDerY( x0, y0 );
    double discr = goalFunctionDer2X( x0, y0 ) * goalFunctionDer2Y( x0, y0 ) - goalFunctionDerXY( x0, y0 ) * goalFunctionDerXY( x0, y0 );
    Hesse[ 0 ][ 0 ] = goalFunctionDer2Y( x0, y0 ) / discr;
    Hesse[ 0 ][ 1 ] = 0 - goalFunctionDerXY( x0, y0 ) / discr;
    Hesse[ 1 ][ 0 ] = 0 - goalFunctionDerXY( x0, y0 ) / discr;
    Hesse[ 1 ][ 1 ] = goalFunctionDer2X( x0, y0 ) / discr;

    double f0 = goalFunction( x0, y0 );
    std::vector<PointValue> iter;
    iter.push_back( PointValue( x0, y0, f0 ) );

    while( abs( dfx ) > 0.1 || abs( dfy ) > 0.1 ) {
        x0 = x0 - ( Hesse[ 0 ][ 0 ] * dfx + Hesse[ 0 ][ 1 ] * dfy );
        y0 = y0 - ( Hesse[ 1 ][ 0 ] * dfx + Hesse[ 1 ][ 1 ] * dfy );

        dfx = goalFunctionDerX( x0, y0 );
        dfy = goalFunctionDerY( x0, y0 );
        discr = goalFunctionDer2X( x0, y0 ) * goalFunctionDer2Y( x0, y0 ) - goalFunctionDerXY( x0, y0 ) * goalFunctionDerXY( x0, y0 );
        Hesse[ 0 ][ 0 ] = goalFunctionDer2Y( x0, y0 ) / discr;
        Hesse[ 0 ][ 1 ] = 0 - goalFunctionDerXY( x0, y0 ) / discr;
        Hesse[ 1 ][ 0 ] = 0 - goalFunctionDerXY( x0, y0 ) / discr;
        Hesse[ 1 ][ 1 ] = goalFunctionDer2X( x0, y0 ) / discr;

        f0 = goalFunction( x0, y0 );
        iter.push_back( PointValue( x0, y0, f0 ) );
    }
    double x_min = iter.back().x;
    double y_min = iter.back().y;
    double f_min = iter.back().f;

    std::stringstream ss;
    ss << "Newton: Minimum point : ( " << x_min << "; " << y_min << " ); Minimum value of function = " << f_min << std::endl;
    for( int i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i) ;
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].x << "\t" <<
            "y_" << iter.size() - i << " = " << iter[ iter.size() - i ].y << "\t" <<
            "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].f << std::endl;
    }
    INFO( ss.str() );
}

//.............................................................................
int main( int ac, char * av[] ) {


    if( ac > 1 ) if( !strcmp( av[ 1 ], "--help" ) ) {
        std::cout << help;
        return EXIT_SUCCESS;
    }

    double min = 0, fmin = 0;
    gradient();
    steepestGradient();
    steepestGradientBitwiseSearch();
    newton();

    return EXIT_SUCCESS;
}