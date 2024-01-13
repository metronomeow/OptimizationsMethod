#include<iostream>
#include<string>
#include<sstream>
#include <vector>

std::string help =
R"("
# Methods of Optimization, BDZ2 by Mikhaylova Ekaterina #
  > Solve the one-dimensional minimization problem for a given function on a given segment with an accuracy of e = 0.001 : ( | f'(x*) | < e ) by methods:
    1. Midpoint method
    2. Chord method
    3. Newton's method (without modifications)
)";

double from = 0.1;
double to = 1.5;
double e = 0.001;
//.............................................................................
#define EXIT( message ) { std::cout << "\033[1;31mERROR: " << message << " \033[0m" << std::endl; exit(EXIT_FAILURE); }
#define WARNING( message ) { std::cout << "\033[1;33mWARNING: " << message << " \033[0m" << std::endl; }
#define INFO( message ) { std::cout << "\033[1;32mINFO: " << message << " \033[0m" << std::endl; }

//.............................................................................
// my goal function
double goalFunction( double x ) {
    return exp( 2 * x ) + 3.0 / x;
}

double goalFunctionDerivative1( double x ) {
    return 2*exp( 2 * x ) - 3.0 / ( x * x );
}

double goalFunctionDerivative2( double x ) {
    return 4 * exp( 2 * x ) + 6.0 / ( x * x * x );
}

//.............................................................................
// midpoint method
void midpoint( double & x_min, double & f_min ) {

    double a = from;
    double b = to;
    double c = ( a + b ) / 2;
    double fc = goalFunction( c );

    std::vector<std::pair<double, double>> iter;
    iter.push_back( std::pair<double, double>( c, fc ) );

    while( abs( goalFunctionDerivative1( c ) ) > e ) {
        double res = goalFunctionDerivative1( c );
        if( goalFunctionDerivative1( c ) < 0 ) {
            a = c;
            c = ( a + b ) / 2;
            fc = goalFunction( c );
            iter.push_back( std::pair<double, double>( c, fc ) );
        }
        else if( goalFunctionDerivative1( c ) > 0 ) {
            b = c;
            c = ( a + b ) / 2;
            fc = goalFunction( c );
            iter.push_back( std::pair<double, double>( c, fc ) );
        } 
        else break;
    }

    x_min = iter.back().first;
    f_min = iter.back().second;

    std::stringstream ss;
    ss << "Midpoint: Minimum x = " << x_min << "; Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].first << "\t"
           << "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].second << std::endl;
    }
    INFO( ss.str() );
}

//.............................................................................
// chord method
void chord( double & x_min, double & f_min ) {
    double a = from;
    double b = to;
    double c = a - goalFunctionDerivative1( a ) * ( ( b - a ) / ( goalFunctionDerivative1( b ) - goalFunctionDerivative1( a ) ) );
    double fc = goalFunction( c );

    std::vector<std::pair<double, double>> iter;
    iter.push_back( std::pair<double, double>( c, fc ) );

    while( abs( goalFunctionDerivative1( c ) ) > e ) {
        if( goalFunctionDerivative1( c ) > 0 ) {
            b = c;
            c = a - goalFunctionDerivative1( a ) * ( ( b - a ) / ( goalFunctionDerivative1( b ) - goalFunctionDerivative1( a ) ) );
            fc = goalFunction( c );
            iter.push_back( std::pair<double, double>( c, fc ) );
        }
        if( goalFunctionDerivative1( c ) < 0 ) {
            a = c;
            c = a - goalFunctionDerivative1( a ) * ( ( b - a ) / ( goalFunctionDerivative1( b ) - goalFunctionDerivative1( a ) ) );
            fc = goalFunction( c );
            iter.push_back( std::pair<double, double>( c, fc ) );
        }
    }
    x_min = iter.back().first;
    f_min = iter.back().second;

    std::stringstream ss;
    ss << "Chord: Minimum x = " << x_min << "; Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].first << "\t" 
           << "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].second << std::endl;
    }
    INFO( ss.str() );
}
//.............................................................................
// newton method without modification
void newton( double & x_min, double & f_min ) {

    double x0 = 0.1;
    double f0 = goalFunction( x0 );
    std::vector<std::pair<double, double>> iter;

    iter.push_back( std::pair<double, double>( x0, f0 ) );

    while( abs( goalFunctionDerivative1( x0 ) ) > e ) {
        x0 = x0 - goalFunctionDerivative1( x0 ) / goalFunctionDerivative2( x0 );
        double f0 = goalFunction( x0 );
        iter.push_back( std::pair<double, double>( x0, f0 ) );
    }
    x_min = iter.back().first;
    f_min = iter.back().second;

    std::stringstream ss;
    ss << "Newton: Minimum x = " << x_min << "; Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].first << "\t" 
           << "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].second << std::endl;
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
    midpoint( min, fmin );
    chord( min, fmin );
    newton( min, fmin );

    return EXIT_SUCCESS;
}