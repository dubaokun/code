double foo();
float * bar();

const auto a = foo();       // a: const double
const auto & b = foo();     // b: const double&
volatile auto * c = bar();  // c: volatile float*

auto d = a;                 // d: double
auto & e = a;               // e: const double &
auto f = c;                 // f: float *
volatile auto & g = c;      // g: volatile float * &
