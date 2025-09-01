#include "option_pricer.h"
#include <cmath>
#include <vector>
#include <random>
#include <numeric>
#include <algorithm> // For std::max

/**
 * Generates a random number from a standard normal distribution.
 * This is the source of randomness for our simulation.
 * We use the high-quality Mersenne Twister engine for this.
 * @return A double drawn from N(0, 1).
 */
double generateGaussian() {
    // A high-quality random number generator
    static std::mt19937 generator(std::random_device{}()); 
    // Standard normal distribution (mean=0.0, stddev=1.0)
    static std::normal_distribution<double> distribution(0.0, 1.0); 
    return distribution(generator);
}

/**
 * Prices a European option using the Monte Carlo method.
 * @param params The OptionInput struct containing all required parameters.
 * @return The estimated price of the option.
 */
double monteCarloPricer(const OptionInput& params) {
    double S = params.S;
    double K = params.K;
    double T = params.T;
    double r = params.r;
    double v = params.v;
    long num_sims = params.num_sims;

    double total_payoff = 0.0;

    // Run the simulation for the specified number of paths
    for (long i = 0; i < num_sims; ++i) {
        // Generate a random path using the Geometric Brownian Motion formula
        double Z = generateGaussian();
        double ST = S * std::exp((r - 0.5 * v * v) * T + v * std::sqrt(T) * Z);

        double payoff = 0.0;

        // Calculate the payoff for the option type
        if (params.type == OptionInput::CALL) {
            payoff = std::max(ST - K, 0.0);
        } else { // PUT
            payoff = std::max(K - ST, 0.0);
        }

        total_payoff += payoff;
    }

    // Calculate the average payoff
    double average_payoff = total_payoff / num_sims;

    // Discount the average payoff back to its present value
    return average_payoff * std::exp(-r * T);
}
