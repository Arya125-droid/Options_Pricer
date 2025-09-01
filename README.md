# Option Pricer Web App
Options are financial instruments that give you the right (not obligation) to buy or sell a stock at a certain price in the future.
But how much should this right cost today? That’s exactly what an option pricer tells you.

*An Option Pricer is a mathematical or computational tool that helps you calculate the fair value (price) of an option contract.*
This project is a full-stack application that demonstrates how to calculate European call and put option prices using the **Monte-Carlo Simulations**.

## What is Monte Carlo Simulation?
Monte Carlo simulation is a method of **estimating the probability of different outcomes by running lots of random simulations.**

Instead of solving complex equations directly, you let the computer **simulate many possible futures** and see what the average outcome looks like.


# Features
- Calculate Call & Put option prices via Monte-Carlo simulations.

- Lightweight C++ REST API running on port 18080.

- Responsive web UI for user input and result display.

- Cross-origin enabled so frontend can talk to backend.


# Requirements
- C++17 or later

- Boost

- ASIO (```brew install asio``` on macOS)

- ```g++``` (or ```clang++```)

# Building the Backend
1. Clone this repository and ```cd``` into it.
2. Compile the backend server:
<pre> g++ main.cpp option_pricer.cpp -o option_pricer_app -I . -I /opt/homebrew/include -std=c++17 -pthread </pre>
3. Run the backend server:
<pre> ./option_pricer_app </pre>
By default, the server starts on ```http://localhost:18080```.

# Backend API
- Endpoint: ```POST /price```
- Input JSON:
<pre>
    {
      "S": 100,
      "K": 105,
      "T": 1,
      "r": 0.05,
      "v": 0.2,
      "type": "call"
    }
 </pre>

# Future Improvements
- Add Google Login authentication (OAuth).

- More advanced pricing models (Binomial, Monte Carlo).

- Better styled frontend (Bootstrap/React).
