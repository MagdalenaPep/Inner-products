
//Call necessary  libraries
#include <iostream>
#include <cmath>
#include <valarray>
#include <iomanip>
using namespace std;

//From part A
//Create the function for inner product, if the vectors are not the same size show error message.
long double inner_product(const valarray<long double> u, const valarray<long double> v) {
    if (u.size() != v.size()) {
        throw invalid_argument("Vectors must have the same size.");
    }
    return (u * v).sum();
}

//From part B
//Create the function for inner product using Kahan Summation Algorithm, if the vectors are not the same size show error message.
long double inner_product_kahan(const valarray<long double>& u, const valarray<long double>& v) {
    if (u.size() != v.size()) {
        throw invalid_argument("Vectors must have the same size.");
    }
    long double sum = 0.;
    long double c = 0.;
    long double y;
    long double t;
    for (size_t i = 0; i < u.size(); ++i) {
        long double product = u[i] * v[i];
        y = product - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    return sum;
}

// Define a structure called WeightedNorm, which is a function object.
struct WeightedNorm {
    int m; // This is the member variable, it will be used as the power in the calculation.

    WeightedNorm(int m) : m(m) {}

    // Function call operator to calculate the weighted norm of a valarray<double> using the specified power m.
    long double operator()(const valarray<long double> u) const {
        long double sum = 0.0; // This variable will store the sum for the weighted norm calculation.

        // For loop iterates through all elements of u, raises the absolute value of them to the power of m, and adds the result to sum.
        for (int i = 0; i < u.size(); ++i) {
            sum += pow(abs(u[i]), m);
        }
        return pow(sum, 1.0 / m); // Returns the m-th root of sum.
    }
};

//Test function on a vector U, size 1 000 000 with all values equal to 0.1
int main() {
    const int element_num = 1000000;    // Define the number of elements in the valarray u3.
    valarray<long double> u(0.1, element_num); // Create a valarray of 1000000 elements  all equal to 0.1 the vector u is
    // a long double so we can use the previously defined ' inner_product' function.
    WeightedNorm l2(2);// Create a WeightedNorm object with the power m set to 2.
    long double l2_u = l2(u);  // Calculate the l2 weighted norm of the valarray u store to l2_u.
    long double l2_u_squared = pow(l2_u, 2);// Square the l2 norm of u.

    // Calculate the dot product of u3 and u3 using the inner_product function defined in part B to remove some floating point errors.
    long double dot_product3 =inner_product_kahan(u, u);

    // Output the calculated values.
    cout << setprecision(20)<< "Weighted norm l2(u): " << l2_u << endl;
    cout << setprecision(20)<< "Weighted norm l2(u)^2 " << l2_u_squared << endl;


    // Compare l2(u)^2 and the dot product of u and u using the code from part A .
    if (inner_product(u,u)== l2_u_squared) {
        cout << "l2(u)^2 is equal to the inner product u and u using the inner product function." << endl;
    } else {
        cout << "l2(u)^2 is not exactly equal to the inner product u and u using the inner product function." << endl;
    }


    // Compare l2(u)^2 and the dot product of u and u using the kahan inner product function form part B.
    if ( dot_product3 == l2_u_squared) {
        cout << "l2(u)^2 is equal to the inner product u and u using the kahan inner product function." << endl;
    } else {
        cout  << "l2(u)^2 is not exactly equal to the inner product u and u using the kahan inner product function." << endl;
    }
    //Since both The weighted norm l2(u)^2, Inner product of u and u output as approximately 1000 they must be approximately equal with a small error due to floating point inaccuracies
    //(0.000001 is the smallest difference for both variables to be equal)
    if (abs(dot_product3- l2_u_squared) <0.000000001) {
        cout << "l2(u)^2 is approximately equal to the inner product u*u with difference smaller than 0.000000001 using the kahan inner product function." << endl;
    } else {
        cout << "l2(u)^2 is not equal to the inner product u*u." << endl;
    }
    return 0;
}

