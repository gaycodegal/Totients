/*
 Steph Oro. This code is now in the public domain.
 Sieve of Eratosthenes sub-part unoptimized atm.
 */

#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

typedef long long tottype;

class Sieve {
public:
  // Constructor
  Sieve(int limit) : is_prime_(new bool[limit + 1]), get_phi_(new int[limit + 1]), limit_(limit), totient_sum_(0) {
    sieve();
    initPhi();
  }

  // Deletes information from stack when program ends.
  ~Sieve() {
    delete [] is_prime_;
    delete [] get_phi_;
  }

  // Accessor
  inline tottype totient_sum() const {
    return totient_sum_;
  }

  // Accessor
  inline double max_n_phi_n() const {
    return max_n_phi_n_;
  }
  
  // Accessor
  inline double max_n_phi_n_n() const {
    return max_n_phi_;
  }
  
  // Formats the totients into columns.
  void display_totients() const {
    const int max_totient_width = num_digits(max_totient_),
      primes_per_row = 80 / (max_totient_width + 1);
    int counter = 0;
    for (int i = 1; i <= limit_; i++){
      int prnt = get_phi_[i];
      bool chk = 1;
      if(chk){
	if (primes_per_row - limit_ >= 0) {
	  if (counter != 0) {
	    cout<< setw(num_digits(prnt) + 1);
	  }
	  cout << prnt;
	  counter ++;
	}
	else {
	  if(counter == 0) {
	    cout << setw(max_totient_width);
	  }
	  else {
	    cout<< setw(max_totient_width + 1);
	  }
	  cout << prnt;
	  counter++;
	  if (counter == primes_per_row){
	    cout << endl;
	    counter = 0;
	  }
	}
      }
    }
  }

private:
  bool * const is_prime_;
  int * const get_phi_;
  const int limit_;
  int max_prime_, max_n_phi_, max_totient_;
  double max_n_phi_n_;
  tottype totient_sum_;

  /*
   * Determines how many digits are in an integer.
   * Parameter: num
   * Return: count
   */
  int num_digits(int num) const {
    int count = 0;
    while (num >= 1) {
      num = num /10;
      count++;
    }
    return count;
  }

  /*
    Sieve of Eratosthenes
   */
  void sieve() {
    max_prime_ = 0;
    // TODO: write sieve algorithm
    for (int p = 0; p <= limit_; p++){
      is_prime_[p] = true;
    }
    for (int i = 2; i <= sqrt(limit_); i++){
      if (is_prime_[i] == true) {
	for (int j = i*2; j <= limit_; j+=i) {
	  is_prime_[j] = false;
	}
      }
    }
    for (int m = 0; m <= limit_; m++) {
      if(is_prime_[m] == true) {
	max_prime_ = m;
      }
    }
  }
  
  

  /*
    Totient Sieve
   */
  void initPhi() {
    max_totient_ = 0;
    for(int p = 0; p <= limit_; ++p){
      get_phi_[p] = p;
    }
    for (int i = 2; i <= limit_; ++i){
      if(is_prime_[i]){
	for (int j = i; j <= limit_; j += i) {
	  get_phi_[j] -= get_phi_[j] / i;
	}
      }
    }
    max_totient_ = 0;
    double temp_n_n;
    for (int m = 2; m <= limit_; ++m) {
      totient_sum_ += get_phi_[m];
      temp_n_n = (double)m/(double)get_phi_[m];
      if(temp_n_n > max_n_phi_n_) {
	max_n_phi_n_ = temp_n_n;
	max_n_phi_ = m;
      }
      if(get_phi_[m] > max_totient_) {
	max_totient_ = m;
      }
    }
  }
};


int main(int argc, char ** argv) {
  if(argc < 3){
    cout << "./sieve <number> display<y/n>" << endl;
    return 0;
  }
  string limit_str(argv[1]);
  int limit;
  istringstream iss(limit_str);
  if ( !(iss >> limit) ) {
    cerr << "Error: Input is not an integer." << endl;
    return 1;
  }
  if (limit < 2) {
    cerr << "Error: Input must be an integer >= 2." << endl;
    return 1;
  }

  cout << "************* " <<  "Totient Sieve (The Cooler One They Didn't Teach You)" <<
    " *************" << endl;


  Sieve sieved(limit);
  cout << endl << "Number of totients found: " << argv[1] << endl;
  cout << "Max n/phi(n): " << "n = " << sieved.max_n_phi_n_n() << endl;
  cout << "Farey Number: " << sieved.totient_sum() << endl;
  
  if(argv[2][0] == 'y'){
    cout << "phi(n) (phi(1) up to phi(" << limit << ")):" << endl;
    sieved.display_totients();
  }
  cout << endl;
  return 0;
}
