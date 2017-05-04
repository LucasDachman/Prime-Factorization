#include <iostream>
#include <ttmath-0.9.3/ttmath/ttmath.h>
#include <limits>
#include <vector>
#include <random>

using namespace std;

typedef ttmath::UInt<100> bint;

// Function Prototypes
bint factor(bint num);
bint gcd(bint a, bint b);
bint func(bint x, bint seed);
bint getRand();
bint diff(bint a, bint b);
void test();

// Global Variables
bint N;

int main(int argc, char * argv [] ) {
	
	if( argc < 2 ) {
		cout << "Usage: ./fact <number>" << endl;
		test();
		return 0;
	}
	
	N = argv[1];
	bint p;
	bint q;
	p = factor(N);
	q = N/p;
	printf("Prime factors of %s: %s, %s\n", N.ToString().c_str(), p.ToString().c_str(), q.ToString().c_str());
	return 0;
}

void test() {
	bint a = 2;
	bint b = 3;
	N = 12;
	cout << getRand().ToString()  << endl;
}
/*
bint factor(bint num) {

	bint seed;
	while(true) {	// only infinite when N is prime, maybe if N is > 27 digits
		seed = getRand();
		bint a = getRand();
		bint b = a;
		bint p;
		do {
			a = func(a, seed);
			b = func(func(b,seed),seed);
			p = gcd( diff(a,b), N);
			if( p > 1 &&  p != N)
				return p;
		} while( b != a);
	}
}
*/

bint factor(bint num) {
	
	bint p = N;
	bint seed;
	while(p==N) {
		seed = getRand();
		bint a = getRand();
		bint b = a;
		p = 1;
		while( p == 1 ) {
			a = func(a, seed);
			b = func(func(b,seed),seed);
			p = gcd( diff(a,b), N);
		} 
	}
	return p;
}

bint func(bint x, bint seed) {
	return (x*x + seed) % N;

}

bint diff(bint a, bint b) {
	bint num = a-b;
	if( num > a)
		return b - a;
	return num;
}

bint gcd(bint a, bint b) {

	bint remainder;
	while(b != 0) {
		remainder = a % b;
		a = b;
		b = remainder;
	}
	return a;	
}

bint getRand() {
	random_device rdev{};
	static default_random_engine e{rdev()};
	static uniform_int_distribution<int> d{0,9};
	int nlen = N.ToString().length();
	
	char cN [nlen+2];
	int i;
	for(i=0; i < nlen+2; i++) {
		cN[i] = '0'+ d(e); 	//random char from '0' to '9'
	}
	cN[i+2] = '\0';
	string randStr(cN);
	bint val = randStr;
	val %= N;
	return val;
	
}



