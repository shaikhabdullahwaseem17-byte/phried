QUVANTI LABS v2 — Complete Source Code & README




What even is this.   A   big    HUH


Okay so let me just talk to you like a person for a second, because most READMEs read like they were written by a legal department and a computer had a baby.



Quvanti Labs v2 is a quantitative finance research simulator I built from scratch in pure JavaScript — no Python, no R, no NumPy, no backend server, no cloud API calls, no subscription required. You open the page, you slide some sliders, you press a button, and within milliseconds it runs hundreds (or thousands) of simulated futures for an asset price and shows you exactly where that price is statistically likely to end up.



I built this because I kept running into two problems:


Every real quant finance tool I found was either behind a paywall, required installing Python environments and a dozen libraries, or was locked to some proprietary cloud platform that wanted my credit card.

The ones that were "free" were toy demos that used Math.random() raw — which is not normally distributed. That's just uniformly random. That's wrong. That's not how price movements actually model.


So I wrote this myself. Properly. From the maths up.



Who is this for?


Finance students who want to actually understand what Monte Carlo simulation does, not just run someone else's black box.
Quant researchers who want a clean, readable, copy-pasteable implementation of GBM and R/S analysis they can study or extend.
Developers building fintech tools who want a reference implementation they can actually read.
Anyone who's ever asked "what's the realistic range of outcomes for this investment over 1 year?" and wanted a real answer, not a guess.
What does it actually compute?
Let me walk through what happens when you press that RUN SIMULATION button, step by step.




Step 1 — You give it five numbers


S₀ — The starting price of whatever asset you're modelling. Could be a stock, a crypto, a commodity. Doesn't matter. It's just a number.
μ (mu) — The drift. Think of this as the annualized expected return. If you think the stock goes up 10% per year on average, set this to 10%. You can set it negative if you're modelling a declining asset.
σ (sigma) — The volatility. This is the annualized standard deviation of returns. A calm utility stock might be 15%. A meme coin might be 120%. This controls how "wild" the paths look.
T — Time horizon in trading days. 252 = one year (that's the market convention, not calendar days). 126 = six months. You get the idea.
N — How many simulated futures to compute. I cap it at 2,000 because your browser only has one thread and I don't want to freeze your tab. But even 500 gives solid statistical distributions.
Step 2 — The GBM engine fires up
This is where the real maths lives. Geometric Brownian Motion is the standard model for asset price dynamics under the assumption that log-returns are normally distributed. The exact formula I implemented is:


code


S(t + Δt) = S(t) × exp( (μ − σ²/2) × Δt  +  σ × √Δt × Z )
Where Z is a sample from the standard normal distribution N(0,1). Notice the (μ − σ²/2) term — that's the Itô correction. A lot of basic implementations get this wrong and just use μ × Δt. The Itô correction accounts for the fact that you're working in log-space, and without it your expected value drifts. I got it right.

For Z, I used the Box-Muller transform instead of Math.random() directly. The reason is that Math.random() gives you a uniform distribution between 0 and 1. Price movements are not uniformly distributed. They cluster around the mean and have thin but real tails (normal distribution). Box-Muller takes two uniform random numbers and mathematically transforms them into a proper Gaussian sample. It's a beautiful little algorithm:



javascript


Z = sqrt(-2 × ln(U₁)) × cos(2π × U₂)
Where U₁ and U₂ are two independent uniform random draws. The result is exactly N(0,1). This is the right way to do it.

I also floor the price at 1e-10 to prevent degenerate zero-or-negative prices. In theory GBM can never hit zero, but floating point arithmetic can drift into very small territory in extreme volatility scenarios.

Step 3 — The Monte Carlo matrix runs
The orchestrator runs N iterations of the GBM engine. For the first 80 paths, it stores the entire price path — every step from start to finish — because those are what get drawn on the canvas chart. For paths 81 through 2,000, it only stores the final price (the terminal value). This is a deliberate memory optimization — storing 2,000 full paths of 252 steps each would be ~2 million floats in memory, which is unnecessary when all we actually need for statistics is the last price.

Step 4 — Sorting and percentile computation
Once all N simulations are done, the engine sorts all terminal prices from lowest to highest. Then it computes percentiles using linear interpolation — not rounding to the nearest index, which would be imprecise for small N. Linear interpolation gives you a smooth estimate between adjacent ranks.





The three key outputs are:



P05 — The 5th percentile. This is the "downside risk tail." In plain English: in 95% of simulated futures, the price ends up above this number. It's your floor estimate, your worst realistic case (not worst possible — just statistically rare territory).


P50 — The 50th percentile (median). This is where half the simulations end up above and half below. It's the most honest "central expectation" — better than the mean actually, because the mean of a log-normal distribution is pulled upward by the long right tail.


P95 — The 95th percentile. The upside horizon. In 95% of simulations the price stays below this. It's your optimistic-but-realistic ceiling.
These three numbers give you a proper probabilistic range, not a single point estimate. That's the whole point.






Step 5 — Hurst Exponent Analysis


After the Monte Carlo runs, the engine picks the simulated path whose terminal price is closest to P50 (the most "median" path) and runs it through the Rescaled Range (R/S) algorithm to compute the Hurst Exponent.

The Hurst Exponent (H) is a measure of long-range memory in a time series. It was developed by hydrologist Harold Edwin Hurst in the 1950s while studying the Nile River — he wanted to know if floods and droughts clustered or alternated. The same mathematics applies to financial time series.


H ≈ 0.50 → Pure random walk. No memory. Yesterday's return tells you nothing about tomorrow's. This is the Efficient Market Hypothesis.
H > 0.55 → Persistent / trending. The series has "momentum." A positive return makes a positive return more likely in the near future. Long-range dependence.
H < 0.45 → Anti-persistent / mean-reverting. The series resists trends. A big move up is more likely to be followed by a correction.
How it's computed: I convert the price path to log-returns, then evaluate the Rescaled Range statistic (R/S) at multiple scale lengths using geometric spacing. R/S at scale n is: compute the cumulative deviation from the mean, take its range (max minus min), divide by the standard deviation. Do this for many different n values. Plot log(R/S) against log(n). The slope of that line, fitted via OLS linear regression, is your H estimate.

The OLS fitting is done in maybe 20 lines of straightforward algebra — no library needed. Sum of products, divide, done.









The file structure
code


/quanti-labs-v2/
│
├── page.jsx                  ← The entire UI. React component, ~750 lines.
│
└── engine/
    ├── gbm.js                ← Geometric Brownian Motion engine
    ├── hurst.js              ← Hurst Exponent / R/S analysis engine
    └── monteCarlo.js         ← Monte Carlo orchestrator + histogram builder
Four files. That's the whole thing. No configuration files, no build scripts beyond what Next.js already provides, no .env files with secret keys, no database schema migrations. Just four JavaScript files doing real quantitative finance maths.







How to run it

Since this is built inside the Quvanti platform (which runs Next.js under the hood), you just navigate to:




/quanti-labs-v2
And it's live. No install step, no npm install, no environment variables, no API keys. The entire computation happens client-side in your browser the moment you press RUN.





If you're pulling the engine files out to use standalone:



(javascript)


// In any JS project — no dependencies needed
import { generateGBMPath, generateGBMTerminalPrice, boxMuller } from './engine/gbm.js';
import { calculateHurst } from './engine/hurst.js';
import { runMonteCarlo, buildHistogram } from './engine/monteCarlo.js';

// Run a quick simulation
const results = runMonteCarlo({
  S0: 100,       // $100 starting price
  mu: 0.08,      // 8% annual drift
  sigma: 0.20,   // 20% annual volatility
  daysT: 252,    // 1 year
  iterations: 1000,
  pathSample: 80,
}, console.log, (pct) => console.log(`${pct}%`));

console.log(`P05: $${results.p5.toFixed(2)}`);
console.log(`P50: $${results.p50.toFixed(2)}`);
console.log(`P95: $${results.p95.toFixed(2)}`);
console.log(`Hurst H = ${results.hurstResult?.hurst.toFixed(4)}`);
The engines are pure ES modules with zero external imports. They'll work in any modern browser, Node.js, Deno, or Bun environment without modification.







Design decisions I made and why


Why canvas for the path chart instead of a charting library? Because drawing 50+ overlapping semi-transparent lines with custom glow effects and dynamic Y-scaling is the kind of thing that kills most charting library renderers. They're built for clean bar charts and line charts with 10-20 series. The raw Canvas2D API is 10x faster for this use case and gives me pixel-level control. The histogram uses Recharts because that is the right tool for a single-series bar chart.

Why store only 80 full paths and terminal-only for the rest? Memory. A full path at 252 steps is an array of 253 floats. At 2,000 iterations, full storage is 506,000 floats ≈ 4MB just for the simulation data. Keeping only 80 full paths (for visualization) and 1,920 terminal prices reduces that to ~20,000 floats. The statistical outputs (P05, P50, P95) only need the terminal prices anyway — you don't need the full path history to compute percentiles.




Why not use Web Workers for the computation? I honestly considered it. For 2,000 iterations at 252 steps each, the computation takes roughly 50-200ms on a modern machine — well within the "this doesn't feel laggy" threshold. The setTimeout(..., 30) trick I use (deferring computation by one frame) lets the UI update the "RUNNING..." button state before the blocking computation starts. If iterations were pushed to 50,000+, Workers would become essential. At 2,000, it's engineering overkill that adds complexity for no user-visible benefit.





Why 252 trading days = 1 year? This is the standard convention in quantitative finance. US markets are open roughly 252 days per year (365 calendar days minus weekends minus holidays). Using trading days rather than calendar days is important because price volatility is a trading phenomenon — prices don't move on days when markets are closed. If you modelled on 365 days, your σ would be systematically underestimated.




Why the Itô correction term (μ − σ²/2)? This is one of the most commonly misunderstood details in GBM implementations. If you model S(t+dt) = S(t) × exp(μ × dt + σ × Z × √dt) without the -σ²/2 correction, the expected value of your simulated prices is S0 × exp(μ × T) — which sounds right! But in log-space, the log-return has a bias. Itô's Lemma shows that for a log-normal process, the correct drift in log-space is (μ - σ²/2), not μ. The -σ²/2 term (Jensen's inequality correction) ensures the ensemble mean of the simulated terminal prices equals the theoretical expectation. Without it, your P50 estimates are systematically high at high volatility.




Limitations (I want to be honest here)
GBM is a model, not reality. Real asset prices have fat tails (more extreme events than GBM predicts), volatility clustering (volatility isn't constant — it tends to be high when it's been high), jumps (gaps at market open, news events), and correlation structures (assets don't move independently). GBM assumes none of that. It's the simplest useful model, not the best model.




The Hurst Exponent estimate is from a single path. I run R/S analysis on the single path closest to P50, which is a GBM path. Since GBM is by construction a random walk (H = 0.5 theoretically), the H estimate you get here is reflecting the random fluctuations in one finite path, not some deep truth about the underlying asset. In a real research context, you'd compute H from historical market data, not from a simulated path. The H here is illustrative — it shows you the algorithm working and gives you a feel for what different H values mean.




Browser-based computation is single-threaded. The main JavaScript thread blocks while computing. At 2,000 iterations, this is imperceptible. At 10,000+ it would freeze the UI noticeably. This is a deliberate design choice (simplicity over scalability) for a research/education tool.






No persistence. Results disappear when you close the tab. There's no "save simulation" feature, no export to CSV, no history. This is v2 — maybe v3 gets that


---sign off---
  8/8//2026
  
