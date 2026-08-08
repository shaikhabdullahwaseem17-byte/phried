/**
 * Quvanti Labs v2 — GBM Stochastic Engine
 * Geometric Brownian Motion path generator using Box-Muller transform.
 * Pure, dependency-free, fully open-source compliant.
 */

/**
 * Box-Muller Transform
 * Converts two independent uniform random variables [0,1)
 * into a standard normally-distributed random variable Z ~ N(0,1).
 * @returns {number} - A sample from the standard normal distribution
 */
export function boxMuller() {
  let u = 0;
  let v = 0;
  // Guard against log(0) by ensuring strict positivity
  while (u === 0) u = Math.random();
  while (v === 0) v = Math.random();
  return Math.sqrt(-2.0 * Math.log(u)) * Math.cos(2.0 * Math.PI * v);
}

/**
 * Geometric Brownian Motion Path Generator
 *
 * Models asset price dynamics under the risk-neutral measure:
 *   dS = S * (μ dt + σ √dt Z)
 * where Z ~ N(0,1) via Box-Muller transform.
 *
 * @param {number} S0    - Initial asset price (e.g., 100.00)
 * @param {number} mu    - Drift coefficient (annualized, e.g., 0.08 = 8%)
 * @param {number} sigma - Volatility metric (annualized, e.g., 0.20 = 20%)
 * @param {number} T     - Time horizon in fractions of a year (e.g., 0.5 = 6 months)
 * @param {number} steps - Total discrete step count (e.g., 252 for daily steps over 1yr)
 * @returns {number[]}   - Array of simulated asset prices [S0, S1, ..., S_steps]
 */
export function generateGBMPath(S0, mu, sigma, T, steps) {
  if (S0 <= 0)
    throw new RangeError("Initial price S0 must be strictly positive.");
  if (sigma < 0)
    throw new RangeError("Volatility sigma must be non-negative.");
  if (steps < 1)
    throw new RangeError("Step count must be at least 1.");

  const dt     = T / steps;
  const sqrtDt = Math.sqrt(dt);
  const path   = new Array(steps + 1);
  path[0]      = S0;

  let S = S0;
  for (let i = 1; i <= steps; i++) {
    const Z = boxMuller();
    // Log-normal exact discretization (Itô's Lemma corrected form):
    // S(t+dt) = S(t) * exp((μ - σ²/2)dt + σ√dt·Z)
    S = S * Math.exp(
      (mu - 0.5 * sigma * sigma) * dt +
      sigma * sqrtDt * Z
    );
    // Floor at machine epsilon to prevent degenerate zero-price states
    path[i] = Math.max(S, 1e-10);
  }

  return path;
}

/**
 * Returns a single terminal (final) price from one GBM simulation.
 * Lightweight variant used when full path storage is unnecessary.
 *
 * @param {number} S0
 * @param {number} mu
 * @param {number} sigma
 * @param {number} T
 * @param {number} steps
 * @returns {number} - Terminal asset price
 */
export function generateGBMTerminalPrice(S0, mu, sigma, T, steps) {
  const dt     = T / steps;
  const sqrtDt = Math.sqrt(dt);
  let S = S0;
  for (let i = 0; i < steps; i++) {
    const Z = boxMuller();
    S = S * Math.exp(
      (mu - 0.5 * sigma * sigma) * dt +
      sigma * sqrtDt * Z
    );
    S = Math.max(S, 1e-10);
  }
  return S;
}

