- [x] exponential_distribution should assert that params are valid
- [x] make survival_rate.cpp cout ore useful
- [x] move .h impls to proper .cpp file and create Makefile

# Approach 1: Upper Bound

Compute an upper bound on $E[\text{\# of laps}]$ for any strategy, then show the strategy achieves it.
Challenge: Finding a tight upper bound is hard. The obvious bound $E[\text{\# of laps}] \leq \frac{S(l)}{1-S(l)}$ (the no-gate case) is too loose.

# Approach 2: Markov Decision Process (MDP)

Model this as an MDP where:
- State: $(t \mod (T_1+T_2), l)$ — position in gate cycle and remaining lifespan
- Action: wait time $w \in [0, l - 2/v]$
- Reward: +1 for each successful lap
Then prove the optimal policy matches the strategy. This is rigorous but potentially complex.
Advantage: MDP theory gives us tools (Bellman equations, policy iteration) to characterize optimal policies.

# Approach 3: Coupling Argument

Show that for any other strategy $\sigma'$, you can construct a coupling where the strategy $\sigma$ survives at least as many laps almost surely.
Idea: If $\sigma'$ waits less than $\sigma$ on some lap, show that any advantage $\sigma'$ gains is offset by disadvantages later.

# Approach 4: Memorylessness Exploitation

The exponential distribution is memoryless. This might simplify the analysis — the optimal strategy shouldn't depend on history, only on current state.
Key insight: After each reset, the particle gets a fresh lifespan independent of the past. So the optimal wait time should only depend on:
1. Current lifespan $l$
2. Current position in gate cycle $\Omega$

# MDP sketch
1. Define the state space: $(\Omega, l)$ where $\Omega \in (0, T_1]$ (position in ON window when lap starts) and $l \geq 0$ (lifespan).
2. Value function: Let $V(\Omega, l)$ = expected additional laps starting from state $(\Omega, l)$.
3. Bellman equation: 
$$V(\Omega, l) = \max_{w \geq 0} \mathbf{1}[w + 2/v \leq l \text{ and arrives in ON}] \cdot (1 + E[V(\Omega', l')])$$
4. Show the strategy is optimal: Prove that waiting until the end of the ON window maximizes the RHS.
The crux: You need to show that the benefit of better $\Omega'$ (closer to next ON window) outweighs any cost. The memorylessness of the exponential distribution might make this tractable — the expected future value $E[V(\Omega', l')]$ only depends on $\Omega'$, not on how much lifespan was "used up."