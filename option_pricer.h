#ifndef OPTION_PRICER_H
#define OPTION_PRICER_H

// To hold all necessary inputs for the options pricing model
struct OptionInput {
    double S;      // Current stock price
    double K;      // Strike price
    double T;      // Time to expiration in years
    double r;      // Risk-free interest rate
    double v;      // Volatility of the underlying stock
    long num_sims; // Number of simulations for Monte Carlo
    enum OptionType { CALL, PUT } type; // Option type
};

// This is the main function that wilol be called by web API
// It takes the option parameters and returns the calculated price
double monteCarloPricer(const OptionInput& params);

#endif