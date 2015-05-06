#ifndef ACTIVATION_FUNCTION
#define ACTIVATION_FUNCTION
#include <cmath>
#include <cstdlib>

/**
 * @brief abstract class for activation_function
 * @details 
 * @return void
 */
class activation_function
{
public:
    virtual ~activation_function();

    virtual double activate(double, double) = 0;
    virtual double activate(double) = 0;
    
    
};

class sigmoid: public activation_function {
public:
    /**
     * @brief activate sigmoid function
     * 
     * @param x  double
     * @return double
     */
    virtual double activate(double x) {
        return 1.0 / (1.0 + std::exp(-x));
    }

};

class binomial: public activation_function {

public:
    virtual double activate(double n, double p) {
        if(p < 0 || p > 1) return 0;
          
          int c = 0;
          double r;
          
          for(int i=0; i<n; ++i) {
            r = std::rand() / (RAND_MAX + 1.0);
            if (r < p) c++;
          }

      return c;

    }

};

class uniform: public activation_function{
public:

    virtual double activate(double min, double max) {
        return std::rand() / (RAND_MAX + 1.0) * (max - min) + min;

    }

    
};







#endif