//Call necessary  libraries
#include <iostream>
#include <valarray>
#include <iomanip>
using namespace std;


//Create the function for inner product, if the vectors are not the same size show error message.
long double inner_product(const valarray<long double> u, const valarray<long double> v) {
    if (u.size() != v.size()) {
        throw invalid_argument("Vectors must have the same size.");
    }
    return (u * v).sum();
}
//Test function on a vector U, size 1 000 000 with all values equal to 0.1
int main() {

    const int element_num = 1000000; //Define the number of elements
    const long double value = 0.1; //Define the value of the elements
    valarray<long double> u(value, element_num); //Define u as a valleray of size 1000000 ech of value 0.1

    long double dot_product = inner_product(u, u); //calculate dot product
    long double difference = dot_product - 1e4;

    /*
//Code that tests if the error message  works when given vectors of different lengths.
    valarray<long double> a = {1.0, 2.0}; //a valarray of size 2
    valarray<long double> b = {4.0, 5.0, 6.0} //a valarray of size 3
    long double test = inner_product(a, b);
    cout << "Test" << test << endl;
*/
//output results to 20 digits of accuracy
    cout << setprecision(20) << "Dot product of u and u:   " << dot_product << endl;
     cout << setprecision(20)<<"Difference:                " << difference << endl;
}