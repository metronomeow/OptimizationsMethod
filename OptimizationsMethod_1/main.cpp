#include<iostream>
#include<string>
#include<sstream>
#include <vector>

std::string help =
R"("
# Methods of Optimization, BDZ1 by Mikhaylova Ekaterina #
  > Solve the one-dimensional minimization problem for a given function on a given segment with an accuracy of e = 0.001 by methods:
    1. brute force method
    2. dichotomy method
    3. Golden ratio method
    4. Bitwise search method
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

//.............................................................................
//  brute force method
void bruteForce( double & x_min, double & f_min ) {

    int n = ( to - from ) / e + 1; //num of iteration
    double h = ( to - from ) / n;  //step

    x_min = from;                  //x coordinate when function is minimum
    f_min = goalFunction( x_min ); //minimum


    for( int i = 1; i < n; i++ ) {
        double x = from + h * i;
        double f2 = goalFunction( x );
        if( f2 < f_min ) {
            x_min = x;
            f_min = f2;
        }
    }
    std::stringstream ss;
    ss << "Brute Force: Minimum x = " << x_min << "; Minimum value of function = " << f_min;
    INFO( ss.str() );
}

//.............................................................................
void dichotomyCalculating( double & x, double & f, double begin, double end ) {
    x = (end + begin) / 2;
    f = goalFunction( x );
}
//.............................................................................
// dichotomy method
void dichotomy( double x_min, double f_min ) {

    double beginning = from;
    double ending = to;
    double x1 = 0;
    double x2 = 0;
    double f1 = 0;
    double f2 = 0;
    std::vector<std::pair<double, double>> iter;
    dichotomyCalculating( x_min, f_min, beginning, ending );

    for( size_t i = 0;; i++ ) {
        if( e > abs( ending - beginning ) / 2 ) break;
        dichotomyCalculating( x1, f1, beginning, (beginning + ending) / 2 );
        dichotomyCalculating( x2, f2, (beginning + ending) / 2, ending );
        if( f1 < f2 ) {
            ending = (beginning + ending) / 2;
            iter.push_back( std::pair<double, double>( x1, f1 ) );
            continue;
        }
        else {
            beginning = ( beginning + ending ) / 2;
            iter.push_back( std::pair<double, double>( x2, f2 ) );
            continue;
        }
        //EXIT( "Cannot find minimum of the goal function by dichotomy method!" );
    }

    x_min = iter.back().first;
    f_min = iter.back().second;
    std::stringstream ss;
    ss << "Dichotomy: Minimum x = " << x_min << "; Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[ iter.size() - i ].first << "\t" 
           << "f_" << iter.size() - i << " = " << iter[ iter.size() - i ].second << std::endl;
    }
    INFO( ss.str() );
}

//.............................................................................
// golden ratio method

void goldenRatio( double & x_min, double & f_min ) {

    std::vector<std::pair<double, double>> iter;
    double a = from;
    double b = to;
    double t = ( sqrt( 5 ) - 1 ) / 2;

    while( true ) {
        double c = a + ( 1 - t ) * ( b - a );
        double d = a + t * ( b - a );
        double fc = goalFunction( c );
        double fd = goalFunction( d );

        double xi = ( c + d ) / 2;
        double fi = goalFunction( xi );

        if( abs( a - b ) < e ) {
            x_min = xi;
            f_min = fi;
            break;
        }

        iter.push_back( std::pair<double, double>( xi, fi ) );
        if( fc > fd ) {
            a = c; c = d; d = a + t * ( b - a );
        }
        if( fc < fd ) {
            b = d; d = c; c = a + ( 1 - t ) * ( b - a );
        }
    }

    std::stringstream ss;
    ss << "Golden ratio: Minimum x = " << x_min << "; Minimum value of function = " << f_min << std::endl;
    for( size_t i = 1; i < 4; i ++ ) {
        int dif = int( iter.size() - i );
        if( dif < 0 ) break;
        ss << "x_" << iter.size() - i << " = " << iter[iter.size() - i].first << "\t" 
           << "f_" << iter.size() - i << " = " << iter[iter.size() - i].second << std::endl;
    }
    INFO( ss.str() );
}

//.............................................................................
// bitwise search method

void changeStepSize( bool & mode, double & h ) {
    mode = !mode;
    h = h / 2;
}
void bitwiseSearch( double & x_min, double & f_min ) {
    double a = from;
    double b = to;

    double h = ( b - a ) / 4;
    double x0 = a;
    double f0 = goalFunction( x0 );
    std::vector<std::pair<double, double>> iter;
    iter.push_back( std::pair<double, double>( x0, f0 ) );
    bool mode = true;

    while( h > e ) {
        double x1 = x0 + h;
        bool isOutOfRange = ( x1 > b );
        double tempX = b;
        if( !mode ) {
            x1 = x0 - h;
            isOutOfRange = ( x1 < a );
            tempX = a;
        }
        double f1 = goalFunction( x1 );
        if( isOutOfRange ) {
            changeStepSize( mode, h );
            x1 = tempX;
            f1 = goalFunction( x1 );
        }
        if( f1 > f0 ) changeStepSize( mode, h );

        x0 = x1;
        f0 = f1;
        iter.push_back( std::pair<double, double>( x1, f1 ) );
    }
    x_min = iter.back().first;
    f_min = iter.back().second;

    std::stringstream ss;
    ss << "Bitwise search: Minimum x = " << x_min << "; Minimum value of function = " << f_min << std::endl;
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
    bruteForce( min, fmin );
    dichotomy( min, fmin );
    goldenRatio( min, fmin );
    bitwiseSearch( min, fmin );

    return EXIT_SUCCESS;
}