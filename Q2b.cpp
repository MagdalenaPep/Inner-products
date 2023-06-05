//Call necessary  libraries
#include <iostream>
#include <cmath>
#include <valarray>
#include <iomanip>
using namespace std;

//Create the function for inner product using Kahan Summation Algorithm, if the vectors are not the same size show error message.
long double inner_product_kahan(const valarray<long double>& u, const valarray<long double>& v) {
    if (u.size() != v.size()) {
        throw invalid_argument("Vectors must have the same size.");
    }
    //define  an empty variable c and sum
    long double sum = 0.;
    long double c = 0.;
    long double y;
    long double t;
    //iterate through the size of t calculating the product of each u and v and find the sum
    for (size_t i = 0; i < u.size(); ++i) {
        long double product = u[i] * v[i];
        y = product - c;
        t = sum + y;
        c = (t - sum) - y;
        sum = t;
    }
    //return the sum
    return sum;
}
//Test function on a vector U, size 1 000 000 with all values equal to 0.1
int main() {

//define the number of elements, the value of all elements  and the vector of size 1000000.
    const int element_num = 1000000; //Define the number of elements
    const long double value = 0.1; //Define the value of the elements
    valarray<long double> u(value, element_num); //Define u as a valleray of size 1000000 ech of value 0.1

    long double dot_product = inner_product_kahan(u, u);
    long double difference = dot_product - 1e4;//calculate diffrence u*u-10^4

//Display dot product and difference with 20 digits of accuracy
    cout << setprecision(20)<< "Dot product of u and u using Kahan summation: " << dot_product << endl;
    cout << setprecision(20)<< "Difference with Kahan summation : " << difference << endl;


/*
//Code that tests if the error message  works when given vectors of different lengths.
    valarray<long double> a = {1.0, 2.0}; //a valarray of size 2
    valarray<long double> b = {4.0, 5.0, 6.0}; //a valarray ofsize 3
    long double test_2 = inner_product_kahan(a, b);
    cout << "Test_2" << test_2 << endl;
    */
}

