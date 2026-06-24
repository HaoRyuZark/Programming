# SciPy

SciPy is a scientific computing library built on NumPy. It provides modules for optimization, integration, interpolation, eigenvalue problems, 
algebraic equations, signal processing, statistics, and more.

## Import

```python
import numpy as np
import scipy

# Import individual submodules (preferred)
from scipy import optimize, integrate, interpolate, linalg, stats, special
from scipy import fft, signal, sparse, spatial
```

---

## Optimization (`scipy.optimize`)

### Unconstrained Minimization

- `minimize(fun, x0, method=None, jac=None, hess=None, bounds=None, constraints=(), tol=None, options=None)`: finds the minimum of a scalar function of one or more variables.
  - `fun`: objective function. Signature `fun(x, *args) → float` where `x` is a 1D array.
  - `x0`: initial guess — 1D array or scalar.
  - `method`: optimization algorithm:
    - `'Nelder-Mead'`: derivative-free simplex method; robust but slow.
    - `'BFGS'`: quasi-Newton; efficient for smooth functions, uses gradient.
    - `'L-BFGS-B'`: limited-memory BFGS with optional bounds.
    - `'Powell'`: derivative-free direction-set method.
    - `'CG'`: conjugate gradient; good for large-scale unconstrained problems.
    - `'SLSQP'`: sequential least-squares; supports bounds and all constraint types.
    - `'trust-constr'`: trust-region; supports all constraint types.
  - `jac`: gradient of `fun`. Callable, or `'2-point'`/`'3-point'`/`'cs'` for finite-difference.
  - `hess`: Hessian (optional; used by Newton-type methods).
  - `bounds`: sequence of `(min, max)` pairs per variable. `None` = no bound.
  - `constraints`: dict or list of dicts with keys `'type'` (`'eq'` or `'ineq'`) and `'fun'`. Inequality constraints must satisfy `fun(x) >= 0`.
  - `tol`: termination tolerance.
  - `options`: solver-specific dict, e.g. `{'maxiter': 1000, 'disp': True}`.
  - Returns `OptimizeResult` with attributes `res.x`, `res.fun`, `res.success`, `res.message`, `res.nit`.

- `minimize_scalar(fun, bracket=None, bounds=None, method='brent', tol=None)`: minimizes a scalar function of a **single** variable.
  - `fun`: callable `f(x) → float`.
  - `bounds`: `(min, max)` pair — required for `method='bounded'`.
  - `method`: `'brent'` (default, no bounds), `'bounded'` (interval search), `'golden'`.

```python
from scipy.optimize import minimize, minimize_scalar
import numpy as np

# --- Scalar minimization ---
f = lambda x: (x - 3)**2 + 1

res = minimize_scalar(f, method='brent')
print("Minimum at x =", res.x)     # ≈ 3.0
print("Minimum value =", res.fun)  # ≈ 1.0

res_b = minimize_scalar(f, bounds=(0, 2), method='bounded')
print("Bounded minimum at x =", res_b.x)   # ≈ 2.0 (hit boundary)

# --- Multi-variable: Rosenbrock ---
def rosenbrock(x):
    return (1 - x[0])**2 + 100 * (x[1] - x[0]**2)**2

res = minimize(rosenbrock, x0=[0, 0], method='BFGS')
print("Solution:", res.x)          # ≈ [1, 1]
print("Converged:", res.success)
print("Iterations:", res.nit)

# --- With analytic gradient ---
def rosenbrock_grad(x):
    dfdx0 = -2*(1 - x[0]) - 400*x[0]*(x[1] - x[0]**2)
    dfdx1 = 200*(x[1] - x[0]**2)
    return np.array([dfdx0, dfdx1])

res = minimize(rosenbrock, x0=[0, 0], method='BFGS', jac=rosenbrock_grad)
print("With gradient:", res.x)
```

### Constrained Minimization

```python
from scipy.optimize import minimize

# Minimize f(x,y) = (x-1)² + (y-2.5)²
# Subject to: x - 2y + 2 >= 0,  -x - 2y + 6 >= 0,  -x + 2y + 2 >= 0
# With bounds: x >= 0, y >= 0
fun = lambda x: (x[0] - 1)**2 + (x[1] - 2.5)**2

constraints = (
    {'type': 'ineq', 'fun': lambda x:  x[0] - 2*x[1] + 2},
    {'type': 'ineq', 'fun': lambda x: -x[0] - 2*x[1] + 6},
    {'type': 'ineq', 'fun': lambda x: -x[0] + 2*x[1] + 2},
)
bounds = ((0, None), (0, None))

res = minimize(fun, x0=[2, 0], method='SLSQP',
               constraints=constraints, bounds=bounds)
print("Optimal x:", res.x)       # ≈ [1.4, 1.7]
print("Optimal value:", res.fun)

# Equality constraint: minimize x² + y² subject to x + y = 1
eq_con = {'type': 'eq', 'fun': lambda x: x[0] + x[1] - 1}
res = minimize(lambda x: x[0]**2 + x[1]**2, [0.5, 0.5],
               constraints=eq_con, method='SLSQP')
print("Min norm on x+y=1:", res.x)   # [0.5, 0.5]
```

### Root Finding

- `brentq(f, a, b, xtol=2e-12, rtol=8.9e-16, maxiter=100, full_output=False)`: Brent's method — guaranteed convergence in `[a, b]` as long as `f(a)` and `f(b)` have opposite signs.
  - `f`: callable.
  - `a`, `b`: bracket endpoints.

- `bisect(f, a, b, xtol=2e-12, maxiter=100)`: bisection — simpler and more robust than Brent but slower.

- `newton(func, x0, fprime=None, tol=1.48e-8, maxiter=50)`: Newton-Raphson (or secant method if `fprime` is `None`).
  - `fprime`: first derivative of `func`. If `None`, uses finite differences.

- `fsolve(func, x0, fprime=None, full_output=False)`: legacy interface for systems of equations `func(x) = 0`.

- `root(fun, x0, method='hybr', jac=None, tol=None, options=None)`: modern interface for systems of equations.
  - `method`: `'hybr'` (Powell hybrid, default), `'lm'` (Levenberg-Marquardt), `'broyden1'`, `'broyden2'`, `'anderson'`, `'krylov'`, `'df-sane'`.
  - `jac`: Jacobian callable, or `True` to use finite differences.

```python
from scipy.optimize import brentq, bisect, newton, root

# Scalar root: x³ - x - 2 = 0
f = lambda x: x**3 - x - 2
r = brentq(f, 1, 2)
print("Root (brentq):", r)             # ≈ 1.5214

r_bis = bisect(f, 1, 2)
print("Root (bisect):", r_bis)

r_nwt = newton(f, x0=1.5, fprime=lambda x: 3*x**2 - 1)
print("Root (Newton):", r_nwt)

# System: x² + y² = 1,  x - y = 0  →  solution: (±√2/2, ±√2/2)
def system(vars):
    x, y = vars
    return [x**2 + y**2 - 1, x - y]

sol = root(system, x0=[0.5, 0.5])
print("System root:", np.round(sol.x, 4))   # [0.7071, 0.7071]
print("Residual:", np.linalg.norm(sol.fun))  # ≈ 0
```

### Curve Fitting

- `curve_fit(f, xdata, ydata, p0=None, sigma=None, absolute_sigma=False, bounds=(-inf, inf), method=None, maxfev=None)`: non-linear least-squares fit of model `f(x, *params)` to data.
  - `f`: model function — first argument is the independent variable, remaining are parameters.
  - `xdata`, `ydata`: observed data arrays.
  - `p0`: initial parameter guess. Defaults to all ones if `None`.
  - `sigma`: uncertainties on `ydata` used to weight the fit.
  - `absolute_sigma`: if `True`, treat `sigma` as absolute rather than relative.
  - `bounds`: `(lower, upper)` bounds on parameters.
  - `maxfev`: maximum number of function evaluations.
  - Returns `(popt, pcov)` — optimal parameters and covariance matrix. Parameter uncertainties: `perr = np.sqrt(np.diag(pcov))`.

```python
from scipy.optimize import curve_fit
import numpy as np

rng = np.random.default_rng(42)

# Exponential decay model
def model(x, a, b, c):
    return a * np.exp(-b * x) + c

xdata = np.linspace(0, 5, 80)
ydata = model(xdata, 3.0, 0.8, 0.5) + 0.2 * rng.standard_normal(80)

popt, pcov = curve_fit(model, xdata, ydata, p0=[1, 1, 0])
perr = np.sqrt(np.diag(pcov))     # 1-sigma uncertainties
print("popt:", np.round(popt, 3))  # ≈ [3.0, 0.8, 0.5]
print("perr:", np.round(perr, 3))

# With bounds to prevent unphysical parameter values
popt_b, _ = curve_fit(model, xdata, ydata, p0=[1, 1, 0],
                       bounds=([0, 0, -1], [10, 5, 5]))

# Sinusoidal fit
def sine_model(x, A, omega, phi, offset):
    return A * np.sin(omega * x + phi) + offset

x = np.linspace(0, 4*np.pi, 200)
y = 3 * np.sin(2*x + 0.5) + 1 + 0.2 * rng.standard_normal(200)
popt_s, _ = curve_fit(sine_model, x, y, p0=[1, 1, 0, 0])
print("Sine fit [A, ω, φ, offset]:", np.round(popt_s, 3))
```

### Global Optimization

- `differential_evolution(func, bounds, strategy='best1bin', maxiter=1000, popsize=15, tol=0.01, mutation=(0.5, 1), recombination=0.7, seed=None, workers=1)`: stochastic global optimizer. Suitable for noisy, non-differentiable, multi-modal functions.
  - `func`: objective function.
  - `bounds`: sequence of `(min, max)` pairs per variable — **required**.
  - `strategy`: mutation strategy — `'best1bin'`, `'rand1bin'`, `'currenttobest1bin'`, etc.
  - `maxiter`: maximum number of generations.
  - `popsize`: population size = `popsize * len(bounds)`.
  - `seed`: random seed for reproducibility.
  - `workers`: `-1` to use all CPU cores (parallel evaluation).

- `basinhopping(func, x0, niter=100, T=1.0, stepsize=0.5, minimizer_kwargs=None, seed=None)`: global optimizer via random perturbation + local minimization. Good for multi-modal landscapes with smooth basins.
  - `T`: temperature — controls acceptance of uphill steps.
  - `stepsize`: random displacement magnitude.
  - `minimizer_kwargs`: dict passed to `minimize` for each local search.

```python
from scipy.optimize import differential_evolution, basinhopping

def rastrigin(x):
    n = len(x)
    return 10*n + np.sum(x**2 - 10*np.cos(2*np.pi*x))

bounds = [(-5.12, 5.12), (-5.12, 5.12)]

# Differential evolution
res = differential_evolution(rastrigin, bounds, seed=42, maxiter=500, popsize=20)
print("DE global min:", res.fun)    # ≈ 0
print("At:", res.x)                 # ≈ [0, 0]

# Basin-hopping
res_bh = basinhopping(rastrigin, x0=[3, -2], niter=300,
                      minimizer_kwargs={"method": "L-BFGS-B", "bounds": bounds},
                      seed=42)
print("BH global min:", res_bh.fun)
```

### Linear Programming

- `linprog(c, A_ub=None, b_ub=None, A_eq=None, b_eq=None, bounds=(0, None), method='highs', options=None)`: minimizes `c @ x` subject to linear constraints.
  - `c`: objective coefficients (1D array). **Note**: minimizes, so negate `c` to maximize.
  - `A_ub`, `b_ub`: inequality constraints `A_ub @ x <= b_ub`.
  - `A_eq`, `b_eq`: equality constraints `A_eq @ x == b_eq`.
  - `bounds`: sequence of `(min, max)` pairs; default `(0, None)` (non-negative variables). Use `(None, None)` for unbounded.
  - `method`: `'highs'` (default), `'highs-ds'`, `'highs-ipm'`.

```python
from scipy.optimize import linprog

# Maximize x + 2y  (=> minimize -x - 2y)
# Subject to: x + y <= 4,  x - y <= 2,  x >= 0,  y >= 0
c    = [-1, -2]
A_ub = [[1, 1], [1, -1]]
b_ub = [4, 2]

res = linprog(c, A_ub=A_ub, b_ub=b_ub, bounds=[(0, None), (0, None)])
print("Optimal x:", res.x)         # [1, 3]
print("Max value:", -res.fun)      # 7
print("Status:", res.message)
```

---

## Integration (`scipy.integrate`)

### Single Integrals

- `quad(func, a, b, args=(), limit=50, epsabs=1.49e-8, epsrel=1.49e-8, full_output=False)`: adaptive quadrature for `∫_a^b f(x) dx`.
  - `func`: integrand `f(x)` or `f(x, *args)`.
  - `a`, `b`: integration limits. Use `np.inf` / `-np.inf` for improper integrals.
  - `args`: extra arguments forwarded to `func`.
  - `limit`: maximum number of adaptive sub-intervals.
  - `epsabs`, `epsrel`: absolute and relative error tolerances.
  - Returns `(result, abserr)`.

- `dblquad(func, a, b, gfun, hfun, args=(), epsabs=1.49e-8, epsrel=1.49e-8)`: double integral `∫_a^b ∫_{gfun(x)}^{hfun(x)} f(y, x) dy dx`.
  - `func`: integrand `f(y, x)` — **y is the inner variable**.
  - `gfun`, `hfun`: lower/upper y-bounds as constants or callables of x.

- `tplquad(func, a, b, gfun, hfun, qfun, rfun)`: triple integral. Inner limits are callables of outer variables.

- `nquad(func, ranges, args=None, opts=None)`: general n-dimensional quadrature. More flexible than nested `dblquad`/`tplquad`.
  - `ranges`: list of `[a, b]` pairs or callables returning bounds given outer variables.

- `simpson(y, x=None, dx=1.0, axis=-1)`: integrates `y` on a fixed grid using Simpson's composite rule.
  - `y`: array of function values.
  - `x`: sample coordinates (optional; uniform spacing `dx` if not given).

- `cumulative_trapezoid(y, x=None, dx=1.0, axis=-1, initial=None)`: cumulative integral via trapezoidal rule — returns array of same length when `initial` is set.
  - `initial`: value prepended to the output (set to `0` to start the anti-derivative from zero).

```python
from scipy.integrate import quad, dblquad, tplquad, nquad, simpson, cumulative_trapezoid
import numpy as np

# ∫₀¹ x² dx = 1/3
result, err = quad(lambda x: x**2, 0, 1)
print(f"∫₀¹ x² dx = {result:.6f} ± {err:.1e}")   # 0.333333

# Improper integral: ∫₀^∞ e^{-x} dx = 1
result, _ = quad(lambda x: np.exp(-x), 0, np.inf)
print("∫₀^∞ e^{-x} dx =", result)   # 1.0

# With extra parameter: ∫₀¹ x^n dx = 1/(n+1)
result, _ = quad(lambda x, n: x**n, 0, 1, args=(4,))
print("∫₀¹ x⁴ dx =", result)   # 0.2

# Double integral: ∫₀¹ ∫₀¹ x*y dy dx = 0.25
result, _ = dblquad(lambda y, x: x*y, 0, 1, 0, 1)
print("∫∫ x*y =", result)

# Triangular domain: ∫₀¹ ∫₀^x 1 dy dx = 0.5
result, _ = dblquad(lambda y, x: 1.0, 0, 1, 0, lambda x: x)
print("Triangle area =", result)   # 0.5

# Triple integral: ∫₀¹∫₀¹∫₀¹ x*y*z = 0.125
result, _ = tplquad(lambda z, y, x: x*y*z, 0, 1, 0, 1, 0, 1)
print("∫∫∫ x*y*z =", result)

# nquad — n-dimensional
result, _ = nquad(lambda y, x: x*y, [[0, 1], [0, 1]])
print("nquad result:", result)   # 0.25

# Simpson on a grid
x = np.linspace(0, np.pi, 1001)
result = simpson(np.sin(x), x=x)
print("∫₀^π sin(x) ≈", result)   # ≈ 2.0

# Cumulative integral (anti-derivative of cos = sin)
x = np.linspace(0, 2*np.pi, 500)
F = cumulative_trapezoid(np.cos(x), x, initial=0)
print("F(π/2) ≈", F[len(x)//4])   # ≈ 1.0 (= sin(π/2))
```

### Ordinary Differential Equations

- `solve_ivp(fun, t_span, y0, method='RK45', t_eval=None, dense_output=False, events=None, vectorized=False, args=None, rtol=1e-3, atol=1e-6)`: solves the IVP `dy/dt = f(t, y)`, `y(t0) = y0`.
  - `fun`: right-hand side `f(t, y)` — `y` is 1D, returns same-shape array.
  - `t_span`: `(t0, tf)`.
  - `y0`: initial state vector.
  - `method`:
    - `'RK45'`: explicit 4(5)-order Runge-Kutta — default, good for non-stiff problems.
    - `'RK23'`: explicit 2(3)-order — lower accuracy.
    - `'DOP853'`: explicit 8th-order — high accuracy.
    - `'Radau'`: implicit — best for stiff problems.
    - `'BDF'`: implicit multi-step — also stiff-friendly.
    - `'LSODA'`: auto-switches between stiff and non-stiff.
  - `t_eval`: times at which the solution is stored.
  - `dense_output`: if `True`, solution includes a callable interpolant `sol.sol(t)`.
  - `events`: callable or list of callables for event detection (zero-crossing stops).
  - `rtol`, `atol`: relative and absolute tolerances controlling step size.
  - Returns `OdeResult` with `sol.t`, `sol.y`, `sol.success`.

```python
from scipy.integrate import solve_ivp
import matplotlib.pyplot as plt

# 1st-order: dy/dt = -2y  →  y(t) = e^{-2t}
sol = solve_ivp(lambda t, y: -2*y, t_span=[0, 5], y0=[1.0],
                t_eval=np.linspace(0, 5, 200))
print("Max error vs exact:", np.max(np.abs(sol.y[0] - np.exp(-2*sol.t))))

# Lotka-Volterra predator-prey system
alpha, beta, delta, gamma = 1.0, 0.1, 0.075, 1.5
def lotka_volterra(t, z):
    x, y = z
    return [alpha*x - beta*x*y, delta*x*y - gamma*y]

sol = solve_ivp(lotka_volterra, [0, 60], [10, 5],
                t_eval=np.linspace(0, 60, 600))
plt.plot(sol.t, sol.y[0], label='Prey')
plt.plot(sol.t, sol.y[1], label='Predator')
plt.xlabel('t'); plt.legend(); plt.show()

# Stiff: van der Pol oscillator — use Radau or BDF
def van_der_pol(t, y, mu=1000):
    return [y[1], mu*(1 - y[0]**2)*y[1] - y[0]]

sol = solve_ivp(van_der_pol, [0, 3000], [2, 0],
                method='Radau', t_eval=np.linspace(0, 3000, 5000), rtol=1e-6)
print("Stiff ODE success:", sol.success)

# Dense output — continuous interpolant
sol_d = solve_ivp(lambda t, y: -2*y, [0, 5], [1.0], dense_output=True)
t_fine = np.linspace(0, 5, 1000)
y_fine = sol_d.sol(t_fine)   # evaluate at any t

# Event detection — find when y crosses zero
def zero_crossing(t, y): return y[0]
zero_crossing.terminal = False

sol_e = solve_ivp(lambda t, y: [np.cos(t)], [0, 10], [0.0],
                  events=zero_crossing, t_eval=np.linspace(0, 10, 500))
print("Zero crossings at t =", np.round(sol_e.t_events[0], 3))
```

---

## Interpolation (`scipy.interpolate`)

### 1D Interpolation

- `interp1d(x, y, kind='linear', bounds_error=True, fill_value=nan)`: returns a callable interpolating function. **Legacy** — prefer `CubicSpline` or `make_interp_spline` for new code.
  - `x`, `y`: data points; `x` must be monotonically increasing.
  - `kind`: `'linear'`, `'nearest'`, `'zero'`, `'slinear'`, `'quadratic'`, `'cubic'`, or integer spline degree.
  - `bounds_error`: if `False`, returns `fill_value` outside `x` range instead of raising.
  - `fill_value`: scalar or `'extrapolate'` for linear extrapolation.

- `CubicSpline(x, y, bc_type='not-a-knot', extrapolate=True)`: piecewise cubic with continuous second derivative. Preferred over `interp1d(kind='cubic')`.
  - `bc_type`: boundary conditions — `'not-a-knot'` (default), `'natural'` (zero curvature), `'clamped'` (zero slope), `'periodic'`, or explicit `((order, value), (order, value))`.
  - Returns a callable; call `cs(x, n)` to evaluate the n-th derivative.

- `PchipInterpolator(x, y)`: piecewise cubic Hermite — monotone, never overshoots data extrema. Good for data with plateaus.

- `Akima1DInterpolator(x, y)`: Akima spline — handles outlier points more gracefully than cubic.

- `make_interp_spline(x, y, k=3, bc_t=None)`: B-spline interpolation of degree `k` (`1`=linear, `3`=cubic default).

```python
from scipy.interpolate import interp1d, CubicSpline, PchipInterpolator, Akima1DInterpolator
import numpy as np

x = np.array([0.0, 1.0, 2.0, 3.0, 4.0, 5.0])
y = x**2    # ground truth
x_fine = np.linspace(0, 5, 300)

# Linear (legacy)
f_lin = interp1d(x, y, kind='linear')
print("Linear at 2.5:", f_lin(2.5))     # 6.5 (midpoint of [4, 9])

# Cubic spline (preferred)
cs = CubicSpline(x, y)
print("CubicSpline at 2.5:", cs(2.5))           # ≈ 6.25
print("1st derivative at x=3:", cs(3, 1))       # ≈ 6.0 (y'=2x)
print("2nd derivative at x=3:", cs(3, 2))       # ≈ 2.0 (y''=2)

# Natural boundary: zero curvature at ends
cs_nat = CubicSpline(x, y, bc_type='natural')

# Extrapolation outside data range
f_ext = interp1d(x, y, kind='linear', fill_value='extrapolate', bounds_error=False)
print("Extrapolated at x=7:", f_ext(7))   # 25 + 2*(7-5) = 29? (linear ext)

# PCHIP — monotone, no overshoot
pchip = PchipInterpolator(x, y)
print("PCHIP at 2.5:", pchip(2.5))

# Akima
akima = Akima1DInterpolator(x, y)
print("Akima at 2.5:", akima(2.5))
```

### 2D / N-D Interpolation

- `griddata(points, values, xi, method='linear', fill_value=nan, rescale=False)`: interpolates **unstructured** scattered N-D data.
  - `points`: shape `(n, D)` — input data coordinates.
  - `values`: shape `(n,)` — values at those points.
  - `xi`: shape `(m, D)` or tuple of arrays — query coordinates.
  - `method`: `'nearest'`, `'linear'`, or `'cubic'`.
  - `fill_value`: value outside the convex hull of input points.

- `RBFInterpolator(y, d, neighbors=None, smoothing=0, kernel='thin_plate_spline', epsilon=None, degree=None)`: radial basis function interpolation for scattered N-D data.
  - `y`: data points, shape `(n, D)`.
  - `d`: values, shape `(n,)` or `(n, m)`.
  - `kernel`: `'linear'`, `'thin_plate_spline'`, `'cubic'`, `'quintic'`, `'multiquadric'`, `'inverse_multiquadric'`, `'gaussian'`.
  - `smoothing`: allow deviation from exact interpolation (regularization).
  - `neighbors`: use only the k nearest data points per query (faster).

- `RegularGridInterpolator(points, values, method='linear', bounds_error=True, fill_value=nan)`: fast interpolation on a **regular rectilinear grid**.
  - `points`: tuple of 1D coordinate arrays, one per dimension.
  - `values`: N-D array of values on the grid.
  - `method`: `'linear'`, `'nearest'`, `'slinear'`, `'cubic'`, `'quintic'`, `'pchip'`.

```python
from scipy.interpolate import griddata, RBFInterpolator, RegularGridInterpolator
import numpy as np

rng = np.random.default_rng(0)

# --- Scattered 2D data ---
pts = rng.uniform(-2, 2, (300, 2))
vals = np.sin(pts[:, 0]) * np.cos(pts[:, 1])

gx, gy = np.mgrid[-2:2:50j, -2:2:50j]
grid_z = griddata(pts, vals, (gx, gy), method='cubic')
print("griddata shape:", grid_z.shape)   # (50, 50)

# --- RBF ---
rbf = RBFInterpolator(pts, vals, kernel='thin_plate_spline')
xi = np.array([[0, 0], [1, 1], [-1, 0.5]])
print("RBF at queries:", np.round(rbf(xi), 4))

# --- Regular grid ---
xg = np.linspace(-2, 2, 30)
yg = np.linspace(-2, 2, 30)
X, Y = np.meshgrid(xg, yg, indexing='ij')
Z = np.sin(X) * np.cos(Y)

rgi = RegularGridInterpolator((xg, yg), Z, method='cubic',
                               bounds_error=False, fill_value=None)
query = np.array([[0.5, 0.5], [1.2, -0.8]])
print("RegularGrid result:", np.round(rgi(query), 4))
```

### Polynomial Interpolation

- `lagrange(x, w)`: Lagrange interpolating polynomial through `(x[i], w[i])`. Returns a `numpy.poly1d`. Numerically unstable for many points — prefer `BarycentricInterpolator`.

- `BarycentricInterpolator(xi, yi=None)`: numerically stable barycentric Lagrange interpolation.

- `KroghInterpolator(xi, yi)`: Hermite interpolation — matches function values **and** derivatives at data points.

```python
from scipy.interpolate import lagrange, BarycentricInterpolator, KroghInterpolator
import numpy as np

x = np.array([0.0, 1.0, 2.0, 3.0])
y = np.array([1.0, 2.0, 5.0, 10.0])

poly   = lagrange(x, y)
bary   = BarycentricInterpolator(x, y)
print("Lagrange at 1.5:", poly(1.5))
print("Barycentric at 1.5:", bary(1.5))

# Krogh: match value and derivative at each node
# Simulate sin: at x=0 → y=0, y'=1;  at x=π → y=0, y'=-1
xi = [0, 0, np.pi, np.pi]
yi = [0, 1, 0, -1]
krogh = KroghInterpolator(xi, yi)
print("Krogh at π/2:", krogh(np.pi/2))   # ≈ 1.0 (matches sin)
```

---

## Linear Algebra (`scipy.linalg`)

`scipy.linalg` is a superset of `numpy.linalg` — all NumPy functions are present, plus additional decompositions and solvers. Prefer `scipy.linalg` for scientific work.

### Basic Operations

- `linalg.det(a)`: determinant.
- `linalg.inv(a)`: matrix inverse. Raises `LinAlgError` if singular.
- `linalg.norm(a, ord=None, axis=None)`: matrix or vector norm.
- `linalg.matrix_rank(M, tol=None)`: effective rank via SVD.
- `linalg.trace(a, offset=0)`: sum along a diagonal.
- `linalg.expm(A)`: matrix exponential `e^A` — used in ODEs, Lie groups.
- `linalg.logm(A)`: matrix logarithm.
- `linalg.sqrtm(A)`: matrix square root `B` such that `B @ B = A`.
- `linalg.kron(a, b)`: Kronecker (tensor) product.
- `linalg.block_diag(*arrs)`: builds a block-diagonal matrix.
- `linalg.circulant(c)`: circulant matrix with first column `c`.
- `linalg.hadamard(n, dtype=int)`: Hadamard matrix of order `n` (must be power of 2).
- `linalg.companion(a)`: companion matrix of a polynomial.

### Decompositions

- `linalg.lu(a, permute_l=False)`: LU decomposition with partial pivoting. Returns `(P, L, U)` with `A = P @ L @ U`.
  - `permute_l`: if `True`, returns `(PL, U)` with `PL = P @ L`.

- `linalg.qr(a, mode='full')`: QR decomposition `A = Q @ R`.
  - `mode`: `'full'` (square Q), `'economic'` (thin Q), `'r'` (only R), `'raw'`.

- `linalg.svd(a, full_matrices=True, compute_uv=True)`: Singular Value Decomposition `A = U @ diag(s) @ Vh`.
  - `full_matrices`: if `False`, returns economy-size matrices.
  - `compute_uv`: if `False`, returns only singular values.

- `linalg.cholesky(a, lower=False)`: Cholesky decomposition for positive-definite `A`. Returns upper triangle `U` with `A = U.T @ U`, or lower with `A = L @ L.T`.

- `linalg.eig(a, b=None, left=False, right=True)`: eigenvalues/vectors of a general matrix. May return complex values.

- `linalg.eigh(a, b=None, lower=True, eigvals_only=False, subset_by_index=None, subset_by_value=None)`: eigenvalues/vectors of a **real symmetric** or **complex Hermitian** matrix. Always real, ascending order.
  - `subset_by_index`: `[il, iu]` — return only eigenvalues `il` to `iu`.
  - `subset_by_value`: `[vl, vu]` — return eigenvalues in `[vl, vu]`.

- `linalg.schur(a, output='real')`: Schur decomposition `A = Z T Z.H`.
- `linalg.hessenberg(a, calc_q=False)`: reduces to upper Hessenberg form.
- `linalg.polar(a, side='right')`: polar decomposition `A = U P` (unitary × positive-semidefinite).

### Solving Linear Systems

- `linalg.solve(a, b, assume_a='gen', lower=False)`: solves `A x = b`. Much more stable and faster than `inv(A) @ b`.
  - `assume_a`: hint — `'gen'` (general), `'sym'`, `'her'`, `'pos'` (positive-definite).

- `linalg.lstsq(a, b, cond=None)`: least-squares solution for over/under-determined systems. Returns `(x, residuals, rank, sv)`.

- `linalg.solve_triangular(a, b, lower=False, trans=0)`: solves `A x = b` for triangular `A` — much faster than general solve.
  - `lower`: `True` for lower triangular.
  - `trans`: `0` = `Ax=b`, `1` = `A.T x=b`, `2` = `A.H x=b`.

- `linalg.solve_banded(l_and_u, ab, b)`: solves a banded system efficiently.
  - `l_and_u`: `(l, u)` — number of lower and upper diagonals.
  - `ab`: banded matrix in the format returned by `linalg.banded`.

```python
from scipy import linalg
import numpy as np

A = np.array([[4., 2., 0.],
              [2., 5., 1.],
              [0., 1., 3.]])
b = np.array([1., 2., 3.])

# Basic
print("det:", linalg.det(A))
print("rank:", linalg.matrix_rank(A))
print("Frobenius norm:", linalg.norm(A, 'fro'))
print("expm:\n", np.round(linalg.expm(np.eye(2)*0.1), 4))
print("block_diag:\n", linalg.block_diag(np.eye(2), np.array([[3]])))

# LU
P, L, U = linalg.lu(A)
print("LU check:", np.allclose(P @ L @ U, A))

# QR
Q, R = linalg.qr(A)
print("QR check:", np.allclose(Q @ R, A))

# SVD (economy)
U_s, s, Vh = linalg.svd(A, full_matrices=False)
print("Singular values:", np.round(s, 4))
# Low-rank approx (keep top 2 singular values)
A_lr2 = (U_s[:, :2] * s[:2]) @ Vh[:2, :]
print("Rank-2 approx error:", np.linalg.norm(A - A_lr2))

# Cholesky (positive-definite A)
L_c = linalg.cholesky(A, lower=True)
print("Cholesky check:", np.allclose(L_c @ L_c.T, A))

# Eigh (symmetric → real eigenvalues)
vals, vecs = linalg.eigh(A)
print("Eigenvalues:", np.round(vals, 4))
# Two smallest
vals2, _ = linalg.eigh(A, subset_by_index=[0, 1])
print("Two smallest:", np.round(vals2, 4))

# Solve
x = linalg.solve(A, b)
print("Solve residual:", np.linalg.norm(A @ x - b))

# Least-squares
A_over = np.vstack([A, [1., 1., 1.]])
b_over = np.append(b, 2.)
x_ls, res, rank, sv = linalg.lstsq(A_over, b_over)
print("Least-squares x:", np.round(x_ls, 4))

# Triangular solve
R_tri = np.array([[3., 1.], [0., 2.]])
x_tri = linalg.solve_triangular(R_tri, [7., 4.], lower=False)
print("Triangular solve:", x_tri)   # [2, 2]
```

---

## Statistics (`scipy.stats`)

### Descriptive Statistics

- `stats.describe(a, axis=0, ddof=1)`: computes N, min/max, mean, variance, skewness, and kurtosis in one call. Returns a named tuple.
- `stats.skew(a, axis=0, bias=True)`: sample skewness.
- `stats.kurtosis(a, axis=0, fisher=True, bias=True)`: sample kurtosis. `fisher=True` returns **excess** kurtosis (normal distribution = 0).
- `stats.zscore(a, axis=0, ddof=0)`: standardized z-scores along an axis.
- `stats.iqr(x, rng=(25, 75), scale=1.0)`: interquartile range.
- `stats.sem(a, axis=0, ddof=1)`: standard error of the mean.
- `stats.mode(a, axis=0, keepdims=False)`: modal value and count.
- `stats.gmean(a, axis=0)`: geometric mean.
- `stats.hmean(a, axis=0)`: harmonic mean.
- `stats.trim_mean(a, proportiontocut)`: mean after trimming a fraction from each tail.
- `stats.variation(a, axis=0)`: coefficient of variation (std / mean).

```python
from scipy import stats
import numpy as np

rng = np.random.default_rng(0)
data = rng.normal(loc=5, scale=2, size=1000)

desc = stats.describe(data)
print("N:", desc.nobs)
print("Min/Max:", desc.minmax)
print("Mean:", round(desc.mean, 3))
print("Variance:", round(desc.variance, 3))
print("Skewness:", round(desc.skewness, 3))
print("Kurtosis:", round(desc.kurtosis, 3))

print("IQR:", round(stats.iqr(data), 3))
print("SEM:", round(stats.sem(data), 4))
print("Trim mean (5%):", round(stats.trim_mean(data, 0.05), 3))
print("CV:", round(stats.variation(data), 4))
```

### Probability Distributions

All distributions share a common interface. Continuous:
- `.pdf(x)` — probability density.
- `.cdf(x)` — cumulative distribution.
- `.sf(x)` — survival function `1 - CDF`.
- `.ppf(q)` — quantile / inverse CDF.
- `.isf(q)` — inverse survival function.
- `.rvs(size, random_state)` — random variates.
- `.stats(moments='mv')` — mean, variance (add `'sk'` for skewness, kurtosis).
- `.fit(data)` — MLE parameter estimation.
- `.interval(confidence)` — equal-tail confidence interval for that confidence level.
- `.expect(func, lb, ub)` — expected value of `func(X)`.

Discrete distributions replace `.pdf` with `.pmf`.

| Distribution | Class | Shape params |
|---|---|---|
| Normal | `stats.norm` | — |
| Student's t | `stats.t` | `df` |
| Chi-squared | `stats.chi2` | `df` |
| F | `stats.f` | `dfn`, `dfd` |
| Exponential | `stats.expon` | — |
| Uniform | `stats.uniform` | — |
| Beta | `stats.beta` | `a`, `b` |
| Gamma | `stats.gamma` | `a` |
| Log-normal | `stats.lognorm` | `s` |
| Weibull | `stats.weibull_min` | `c` |
| Cauchy | `stats.cauchy` | — |
| Laplace | `stats.laplace` | — |
| Binomial | `stats.binom` | `n`, `p` |
| Poisson | `stats.poisson` | `mu` |
| Geometric | `stats.geom` | `p` |
| Negative binomial | `stats.nbinom` | `n`, `p` |
| Hypergeometric | `stats.hypergeom` | `M`, `n`, `N` |

```python
from scipy import stats
import numpy as np

# --- Normal ---
dist = stats.norm(loc=0, scale=1)
print("PDF at 0:", dist.pdf(0))                   # 0.3989
print("CDF at 1.96:", round(dist.cdf(1.96), 4))  # 0.975
print("95th percentile:", dist.ppf(0.95))          # 1.6449
print("95% CI:", dist.interval(0.95))              # (-1.96, 1.96)

# MLE fit
samples = rng.normal(5, 2, 1000)
mu_fit, sigma_fit = stats.norm.fit(samples)
print(f"Fitted: μ={mu_fit:.3f}, σ={sigma_fit:.3f}")

# --- t-distribution ---
print("t critical (df=10):", stats.t(df=10).ppf(0.975))   # 2.228

# --- Chi-squared: P(χ²(10) <= 18.31) ---
print("Chi2 CDF:", round(stats.chi2.cdf(18.31, df=10), 3))  # ≈ 0.95

# --- Binomial ---
binom_dist = stats.binom(n=20, p=0.3)
print("P(X=6):", round(binom_dist.pmf(6), 4))
print("P(X<=6):", round(binom_dist.cdf(6), 4))
print("Mean/Std:", binom_dist.mean(), binom_dist.std())

# --- Poisson ---
pois = stats.poisson(mu=3.5)
print("P(X=4):", round(pois.pmf(4), 4))

# --- Kernel Density Estimation ---
kde = stats.gaussian_kde(samples, bw_method='scott')
x_grid = np.linspace(-2, 12, 200)
pdf_kde = kde(x_grid)
print("KDE peak near:", x_grid[np.argmax(pdf_kde)])   # ≈ 5

# Evaluate log-likelihood of new data under fitted KDE
log_lik = np.sum(kde.logpdf(samples[:20]))
print("Log-likelihood:", round(log_lik, 2))
```

### Hypothesis Tests

All test functions return `(statistic, pvalue)`. Reject H₀ when `pvalue < α`.

- `stats.ttest_1samp(a, popmean, alternative='two-sided')`: one-sample t-test — is the population mean equal to `popmean`?
- `stats.ttest_ind(a, b, equal_var=True, alternative='two-sided')`: independent two-sample t-test. Use `equal_var=False` for Welch's t-test.
- `stats.ttest_rel(a, b, alternative='two-sided')`: paired t-test.
- `stats.mannwhitneyu(x, y, alternative='two-sided')`: Mann-Whitney U — non-parametric alternative to independent t-test.
- `stats.wilcoxon(x, y=None, alternative='two-sided')`: Wilcoxon signed-rank — non-parametric paired test.
- `stats.kruskal(*args)`: Kruskal-Wallis H — non-parametric one-way ANOVA.
- `stats.f_oneway(*args)`: one-way ANOVA F-test.
- `stats.chi2_contingency(observed, correction=True)`: chi-squared test of independence. Returns `(chi2, p, dof, expected)`.
- `stats.ks_1samp(x, cdf, alternative='two-sided')`: one-sample KS goodness-of-fit test.
- `stats.ks_2samp(data1, data2, alternative='two-sided')`: two-sample KS test — do both samples come from the same distribution?
- `stats.shapiro(x)`: Shapiro-Wilk normality test (best for n < 5000).
- `stats.normaltest(a)`: D'Agostino-Pearson omnibus normality test.
- `stats.levene(*args, center='mean')`: Levene's test for homogeneity of variances.
- `stats.bartlett(*args)`: Bartlett's test for equal variances (assumes normality).
- `stats.fisher_exact(table, alternative='two-sided')`: Fisher's exact test for 2×2 contingency tables.

```python
from scipy import stats
import numpy as np

rng = np.random.default_rng(0)
a = rng.normal(0, 1, 30)
b = rng.normal(0.5, 1, 30)

# One-sample t-test
stat, p = stats.ttest_1samp(a, popmean=0)
print(f"One-sample t: stat={stat:.3f}, p={p:.3f}")

# Independent t-test
stat, p = stats.ttest_ind(a, b)
print(f"Independent t: stat={stat:.3f}, p={p:.3f}")

# Welch (unequal variances)
stat, p = stats.ttest_ind(a, b, equal_var=False)
print(f"Welch t: stat={stat:.3f}, p={p:.3f}")

# Paired t-test
pre  = rng.normal(100, 10, 25)
post = pre - rng.normal(5, 2, 25)
stat, p = stats.ttest_rel(pre, post, alternative='greater')
print(f"Paired t: stat={stat:.3f}, p={p:.4f}")

# Non-parametric
stat, p = stats.mannwhitneyu(a, b, alternative='two-sided')
print(f"Mann-Whitney: stat={stat:.1f}, p={p:.3f}")

# ANOVA across 3 groups
g1 = rng.normal(0, 1, 30)
g2 = rng.normal(1, 1, 30)
g3 = rng.normal(2, 1, 30)
F, p = stats.f_oneway(g1, g2, g3)
print(f"ANOVA: F={F:.3f}, p={p:.4e}")

# Chi-squared contingency
obs = np.array([[10, 20], [30, 40]])
chi2, p, dof, exp = stats.chi2_contingency(obs)
print(f"Chi2={chi2:.3f}, p={p:.3f}, dof={dof}")

# Normality tests
stat, p = stats.shapiro(a)
print(f"Shapiro-Wilk: stat={stat:.4f}, p={p:.4f}")
stat, p = stats.normaltest(a)
print(f"D'Agostino: stat={stat:.3f}, p={p:.3f}")

# KS test against normal distribution
stat, p = stats.ks_1samp(a, stats.norm.cdf)
print(f"KS normality: stat={stat:.3f}, p={p:.3f}")
```

### Correlation & Linear Regression

- `stats.pearsonr(x, y, alternative='two-sided')`: Pearson correlation coefficient and p-value.
- `stats.spearmanr(a, b=None, axis=0, alternative='two-sided')`: Spearman rank correlation.
- `stats.kendalltau(x, y, alternative='two-sided')`: Kendall's tau.
- `stats.pointbiserialr(x, y)`: point-biserial (binary vs continuous).
- `stats.linregress(x, y, alternative='two-sided')`: simple linear regression `y = slope*x + intercept`. Returns `(slope, intercept, rvalue, pvalue, stderr)`.

```python
x = rng.normal(0, 1, 50)
y = 2*x + rng.normal(0, 0.5, 50)

r, p    = stats.pearsonr(x, y)
rho, ps = stats.spearmanr(x, y)
tau, pk = stats.kendalltau(x, y)
print(f"Pearson r={r:.4f}, Spearman ρ={rho:.4f}, Kendall τ={tau:.4f}")

reg = stats.linregress(x, y)
print(f"slope={reg.slope:.3f}, intercept={reg.intercept:.3f}")
print(f"R²={reg.rvalue**2:.4f}, p={reg.pvalue:.2e}")
print(f"Std error of slope: {reg.stderr:.4f}")
```

### Bootstrap Confidence Intervals

- `stats.bootstrap(data, statistic, n_resamples=9999, confidence_level=0.95, method='BCa', random_state=None)`: non-parametric bootstrap CI.
  - `data`: tuple of sample arrays.
  - `statistic`: callable `f(*data) → scalar`.
  - `method`: `'percentile'`, `'basic'`, `'BCa'` (bias-corrected, recommended).

```python
from scipy.stats import bootstrap

data = (rng.normal(5, 2, 100),)

# CI for the mean
res = bootstrap(data, np.mean, n_resamples=9999, method='BCa', random_state=42)
print(f"95% CI for mean: ({res.confidence_interval.low:.3f}, {res.confidence_interval.high:.3f})")

# CI for the median
res_med = bootstrap(data, np.median, n_resamples=9999, method='BCa', random_state=42)
print(f"95% CI for median: ({res_med.confidence_interval.low:.3f}, {res_med.confidence_interval.high:.3f})")

# CI for correlation between two samples
xy = (rng.normal(0, 1, 50), rng.normal(0, 1, 50))
res_corr = bootstrap(xy, stats.pearsonr, n_resamples=9999, method='BCa',
                     random_state=42, paired=True)
print(f"95% CI for Pearson r: ({res_corr.confidence_interval.low:.3f}, {res_corr.confidence_interval.high:.3f})")
```

---

## Special Functions (`scipy.special`)

- `special.gamma(z)`: Gamma function `Γ(z)`. For positive integers: `Γ(n) = (n-1)!`.
- `special.gammaln(z)`: `log|Γ(z)|` — numerically stable for large `z`.
- `special.factorial(n, exact=False)`: factorial. `exact=True` for arbitrary-precision integers.
- `special.comb(n, k, exact=False, repetition=False)`: binomial coefficient `C(n,k)`.
- `special.perm(n, k, exact=False)`: permutations `P(n,k)`.
- `special.beta(a, b)`: Beta function `B(a,b) = Γ(a)Γ(b)/Γ(a+b)`.
- `special.betainc(a, b, x)`: regularized incomplete Beta function — CDF of Beta distribution.
- `special.erf(z)`: error function `(2/√π) ∫₀^z e^{-t²} dt`. Relates to normal CDF: `P(X < x) = 0.5(1 + erf(x/√2))`.
- `special.erfc(z)`: complementary error function `1 - erf(z)`.
- `special.erfinv(y)`: inverse error function.
- `special.expit(x)`: logistic sigmoid `σ(x) = 1/(1 + e^{-x})`.
- `special.logit(x)`: logit `log(x/(1-x))`.
- `special.log_softmax(x)`: numerically stable `log(softmax(x))`.
- `special.softmax(x, axis=None)`: softmax `e^x / Σ e^x`.
- `special.logsumexp(a, axis=None, b=None, keepdims=False)`: numerically stable `log(Σ exp(a))`.
- `special.jv(v, z)` / `special.jn(n, z)`: Bessel function of the first kind, order `v`.
- `special.yv(v, z)`: Bessel function of the second kind.
- `special.iv(v, z)` / `special.kv(v, z)`: modified Bessel functions (first and second kind).
- `special.legendre(n)`: Legendre polynomial `P_n(x)` (returns `poly1d`).
- `special.hermite(n)`: physicist's Hermite polynomial `H_n(x)`.
- `special.chebyt(n)` / `special.chebyu(n)`: Chebyshev polynomials of the first/second kind.
- `special.zeta(x, q=None)`: Riemann zeta `ζ(x)` or Hurwitz zeta `ζ(x,q)`.
- `special.xlogy(x, y)`: `x * log(y)`, returning `0` when `x = 0` (avoids `0 * -inf`).
- `special.entr(x)`: `-x * log(x)` element-wise (entropy contribution).
- `special.rel_entr(x, y)`: `x * log(x/y)` element-wise (KL contribution).

```python
from scipy import special
import numpy as np

# Gamma & combinatorics
print("Γ(5):", special.gamma(5))                    # 24.0 = 4!
print("Γ(0.5):", round(special.gamma(0.5), 4))      # √π ≈ 1.7725
print("log Γ(1000):", special.gammaln(1000))
print("10!:", special.factorial(10, exact=True))     # 3628800
print("C(10,3):", special.comb(10, 3, exact=True))   # 120

# Error function & normal CDF
print("erf(1):", round(special.erf(1), 4))           # 0.8427
print("P(Z < 1.96):", round(0.5*(1 + special.erf(1.96/np.sqrt(2))), 4))  # 0.975

# Logistic functions
x = np.array([-2, -1, 0, 1, 2])
print("Sigmoid:", np.round(special.expit(x), 4))     # [0.119, 0.269, 0.5, 0.731, 0.881]

# Numerically stable log-sum-exp
logits = np.array([1000.0, 1001.0, 1002.0])
print("logsumexp:", special.logsumexp(logits))        # ≈ 1002.408

# Softmax
log_p = special.log_softmax(np.array([2.0, 1.0, 0.1]))
print("Softmax:", np.round(np.exp(log_p), 4))         # [0.659, 0.242, 0.099]

# Bessel functions
x = np.linspace(0, 10, 200)
j0 = special.jv(0, x)
print("First zero of J₀ ≈", x[np.argmin(np.abs(j0))])   # ≈ 2.4048

# Orthogonal polynomials
P2 = special.legendre(2)
print("P₂(0):", P2(0))    # -0.5   (= (3·0 - 1)/2)
print("P₂(1):", P2(1))    # 1.0

H2 = special.hermite(2)
print("H₂(1):", H2(1))    # 2  (= 4·1² - 2)

# Safe KL divergence using xlogy
p = np.array([0.4, 0.4, 0.2, 0.0])
q = np.array([0.3, 0.4, 0.2, 0.1])
kl = np.sum(special.xlogy(p, p) - special.xlogy(p, q))   # Σ p log(p/q)
print("KL(p||q):", round(kl, 4))
```

---

## Fourier Analysis (`scipy.fft`)

- `fft.fft(x, n=None, axis=-1, norm=None)`: 1D Discrete Fourier Transform.
  - `x`: input array (real or complex).
  - `n`: transform length. Pads with zeros if `n > len(x)`, truncates if smaller.
  - `axis`: axis along which to compute (default last).
  - `norm`: `None` (unnormalized), `'ortho'` (unitary, symmetric), `'forward'` (divide by `n`).

- `fft.ifft(x, n=None, axis=-1, norm=None)`: inverse DFT.

- `fft.rfft(x, n=None, axis=-1, norm=None)`: DFT of **real** input — returns only non-redundant first `n//2 + 1` complex coefficients. Preferred over `fft` for real signals.

- `fft.irfft(x, n=None, axis=-1, norm=None)`: inverse of `rfft`. Specify `n` for odd-length output.

- `fft.fft2(x, s=None, axes=(-2, -1), norm=None)`: 2D DFT.
- `fft.ifft2(x, s=None, axes=(-2, -1), norm=None)`: inverse 2D DFT.
- `fft.fftn(x, s=None, axes=None, norm=None)`: N-D DFT.

- `fft.fftfreq(n, d=1.0)`: DFT sample frequencies for a signal of length `n` with sample spacing `d`.
  - Output range: `[-0.5/d, 0.5/d)`. For `d = 1/fs`, frequencies are in Hz.

- `fft.rfftfreq(n, d=1.0)`: non-negative frequencies only (for `rfft` output).

- `fft.fftshift(x, axes=None)`: shifts the zero-frequency component to the array centre.
- `fft.ifftshift(x, axes=None)`: inverse of `fftshift`.
- `fft.next_fast_len(target)`: returns the smallest efficient FFT length `>= target` (highly composite number).

```python
from scipy import fft
import numpy as np

fs  = 1000            # sampling frequency (Hz)
t   = np.arange(0, 1.0, 1/fs)   # 1 s, 1000 points
rng = np.random.default_rng(0)

# Signal: 50 Hz + 120 Hz + noise
x = (np.sin(2*np.pi*50*t) +
     0.5*np.sin(2*np.pi*120*t) +
     0.1*rng.standard_normal(len(t)))

# rfft — efficient for real signals
n_fft = fft.next_fast_len(len(t))
X     = fft.rfft(x, n=n_fft)
freq  = fft.rfftfreq(n_fft, d=1/fs)
mag   = np.abs(X) * 2 / len(t)    # normalize to single-sided amplitude

# Dominant frequencies
top = np.argsort(mag)[-3:][::-1]
print("Top frequencies (Hz):", np.round(freq[top], 1))  # [50, 120, ...]

# Reconstruct signal
x_rec = fft.irfft(X, n=len(t))
print("Reconstruction error:", np.max(np.abs(x - x_rec)))  # ≈ 0

# Low-pass filter via FFT (brick-wall, not recommended in practice)
X_filt = X.copy()
X_filt[freq > 80] = 0
x_lp = fft.irfft(X_filt, n=len(t))

# Power spectral density
psd = np.abs(X)**2 / (fs * len(t))
print("PSD at 50 Hz:", round(psd[50], 4))

# 2D FFT — frequency domain of an image
image = np.zeros((64, 64))
image[20:44, 20:44] = 1.0
F2 = fft.fft2(image)
F2_shift = fft.fftshift(F2)
magnitude_spectrum = np.log1p(np.abs(F2_shift))
image_rec = np.real(fft.ifft2(F2))
print("2D reconstruction error:", np.max(np.abs(image - image_rec)))  # ≈ 0

# Phase and magnitude extraction
magnitude = np.abs(X)
phase     = np.angle(X)
print("Phase range (rad): [{:.3f}, {:.3f}]".format(phase.min(), phase.max()))
```

---

## Signal Processing (`scipy.signal`)

### Filter Design & Application

- `signal.butter(N, Wn, btype='low', analog=False, output='ba', fs=None)`: Butterworth filter.
  - `N`: filter order — higher = sharper rolloff, more ringing.
  - `Wn`: critical frequency or frequencies. In Hz if `fs` is given; otherwise fraction of Nyquist.
  - `btype`: `'low'`, `'high'`, `'band'`, `'bandstop'`.
  - `output`: `'ba'` (b/a coefficients), `'sos'` (second-order sections, **recommended**), `'zpk'`.

- `signal.sosfiltfilt(sos, x, axis=-1)`: zero-phase forward-backward SOS filter — no phase distortion. Recommended for offline processing.
- `signal.sosfilt(sos, x, axis=-1)`: causal (one-pass) SOS filter — introduces phase delay.
- `signal.filtfilt(b, a, x, axis=-1)`: zero-phase filter using `(b, a)` coefficients.
- `signal.lfilter(b, a, x, axis=-1)`: causal filter using `(b, a)`.

- `signal.firwin(numtaps, cutoff, window='hamming', pass_zero=True, fs=None)`: FIR filter via window method.
  - `numtaps`: number of taps (filter length — must be odd for highpass/bandstop).
  - `cutoff`: cutoff frequency or list of frequencies.
  - `pass_zero`: `True` for lowpass, `False` for highpass.

- `signal.iirfilter(N, Wn, btype='band', ftype='butter', output='ba', fs=None)`: general IIR design.
  - `ftype`: `'butter'`, `'cheby1'`, `'cheby2'`, `'ellip'`, `'bessel'`.

- `signal.freqz(b, a=1, worN=512, fs=2*pi)`: frequency response of a digital filter.
  - Returns `(frequencies, H)` — complex frequency response.

### Spectral Analysis

- `signal.welch(x, fs=1.0, window='hann', nperseg=None, noverlap=None, nfft=None, scaling='density')`: Welch's averaged PSD estimate — reduces variance by averaging overlapping periodograms.
  - Returns `(freqs, Pxx)`.

- `signal.spectrogram(x, fs=1.0, window='hann', nperseg=None, noverlap=None, nfft=None, scaling='density')`: short-time Fourier transform magnitude.
  - Returns `(freqs, times, Sxx)`.

- `signal.periodogram(x, fs=1.0, window='boxcar', nfft=None, scaling='density')`: simple (non-averaged) periodogram.

- `signal.stft(x, fs=1.0, window='hann', nperseg=256, noverlap=None, nfft=None)`: short-time Fourier transform (returns complex values).
  - Returns `(freqs, times, Zxx)`.

- `signal.istft(Zxx, fs=1.0, window='hann', nperseg=None, noverlap=None, nfft=None)`: inverse STFT.

### Convolution & Correlation

- `signal.convolve(in1, in2, mode='full', method='auto')`: N-D convolution.
  - `mode`: `'full'`, `'same'` (same size as `in1`), `'valid'` (only fully overlapping).
  - `method`: `'auto'` (chooses fastest), `'direct'`, `'fft'`.

- `signal.correlate(in1, in2, mode='full', method='auto')`: cross-correlation.

- `signal.fftconvolve(in1, in2, mode='full', axes=None)`: FFT-based convolution — faster than direct for large arrays.

### Peak Detection

- `signal.find_peaks(x, height=None, threshold=None, distance=None, prominence=None, width=None, wlen=None, rel_height=0.5)`: finds all local maxima satisfying the given constraints.
  - `height`: minimum peak height (scalar or `(min, max)`).
  - `distance`: minimum horizontal distance between peaks (samples).
  - `prominence`: minimum peak prominence.
  - `width`: minimum peak width (samples).
  - Returns `(indices, properties_dict)`.

- `signal.peak_prominences(x, peaks, wlen=None)`: computes prominence of each peak.
- `signal.peak_widths(x, peaks, rel_height=0.5)`: computes width of each peak.
- `signal.argrelmax(data, order=1, axis=0)`: indices of relative maxima (simpler but less featured than `find_peaks`).

```python
from scipy import signal
import numpy as np

fs = 1000    # Hz
t  = np.linspace(0, 1, fs, endpoint=False)
x  = (np.sin(2*np.pi*5*t) +
      np.sin(2*np.pi*50*t) +
      np.sin(2*np.pi*200*t))

# --- Butterworth low-pass at 80 Hz ---
sos_lp = signal.butter(8, 80, btype='low', output='sos', fs=fs)
x_lp = signal.sosfiltfilt(sos_lp, x)    # zero-phase

# --- Bandpass: 40–100 Hz ---
sos_bp = signal.butter(4, [40, 100], btype='band', output='sos', fs=fs)
x_bp = signal.sosfiltfilt(sos_bp, x)

# --- FIR highpass at 150 Hz ---
b_fir = signal.firwin(101, 150, pass_zero=False, fs=fs)
x_hp = signal.filtfilt(b_fir, 1.0, x)

# --- Frequency response ---
w, H = signal.freqz(b_fir, worN=1024, fs=fs)
print("Stopband attenuation at 50 Hz:", round(20*np.log10(np.abs(H[50])), 1), "dB")

# --- Welch PSD ---
freqs, Pxx = signal.welch(x, fs=fs, nperseg=256, noverlap=128)
print("PSD peak at (Hz):", freqs[np.argmax(Pxx)])

# --- Spectrogram ---
f_sg, t_sg, Sxx = signal.spectrogram(x, fs=fs, nperseg=64, noverlap=48)
print("Spectrogram shape:", Sxx.shape)

# --- STFT round-trip ---
f_st, t_st, Zxx = signal.stft(x, fs=fs, nperseg=128)
_, x_rec = signal.istft(Zxx, fs=fs, nperseg=128)
print("STFT round-trip error:", np.max(np.abs(x[:len(x_rec)] - x_rec)))

# --- Peak detection ---
rng = np.random.default_rng(42)
noisy = np.sin(2*np.pi*5*t) + 0.2*rng.standard_normal(len(t))
peaks, props = signal.find_peaks(noisy, height=0.5, distance=fs//12,
                                  prominence=0.3, width=5)
print(f"Found {len(peaks)} peaks")
proms, _, _ = signal.peak_prominences(noisy, peaks)
widths, _, _, _ = signal.peak_widths(noisy, peaks, rel_height=0.5)
print("Prominences:", np.round(proms[:3], 3))
print("Widths (samples):", np.round(widths[:3], 1))

# --- Convolution: polynomial multiplication via convolution ---
p1 = np.array([1, 2, 1])   # (x+1)²
p2 = np.array([1, -1])     # (x-1)
print("Product polynomial:", signal.convolve(p1, p2))   # [1, 1, -1, -1]
```

---

## Sparse Matrices (`scipy.sparse`)

Sparse matrices store only non-zero elements, providing large memory and speed savings when most values are zero (e.g., adjacency matrices, finite-difference/element operators).

### Storage Formats

- `sparse.csr_array(arg, shape=None, dtype=None)` / `csr_matrix(...)`: **Compressed Sparse Row** — efficient row slicing and matrix-vector products. Default for most computations.
- `sparse.csc_array(...)` / `csc_matrix(...)`: **Compressed Sparse Column** — efficient column slicing and `A.T @ x`.
- `sparse.coo_array(...)` / `coo_matrix(...)`: **Coordinate** — best for construction. Not efficient for arithmetic.
- `sparse.lil_array(shape, dtype)` / `lil_matrix(...)`: **List of Lists** — best for element-by-element construction.
- `sparse.dia_array(...)` / `dia_matrix(...)`: **Diagonal** — efficient for diagonal/banded matrices.
- `sparse.bsr_array(...)`: **Block Sparse Row** — efficient for block-structured problems.

Common attributes and methods (all formats):
- `.nnz`: number of stored non-zero elements.
- `.shape`, `.dtype`, `.T`.
- `.toarray()` / `.todense()`: convert to dense NumPy array.
- `.tocsr()`, `.tocsc()`, `.tocoo()`: convert between formats.
- `@` operator: sparse matrix-vector and matrix-matrix product.

### Sparse Linear Solvers (`scipy.sparse.linalg`)

- `spla.spsolve(A, b)`: direct solve `A x = b` for sparse `A` (CSC or CSR).
- `spla.spsolve_triangular(A, b, lower=True)`: triangular sparse solve.
- `spla.cg(A, b, tol=1e-5, maxiter=None)`: Conjugate Gradient — symmetric positive-definite `A`.
- `spla.cgs(A, b, tol=1e-5)`: Conjugate Gradient Squared.
- `spla.gmres(A, b, tol=1e-5, restart=None, maxiter=None)`: GMRES — general non-symmetric `A`.
- `spla.bicgstab(A, b, tol=1e-5)`: BiCGSTAB — general, often faster than GMRES.
- `spla.minres(A, b, tol=1e-5)`: MINRES — symmetric (possibly indefinite) `A`.
- `spla.eigs(A, k=6, which='LM', M=None, sigma=None)`: `k` eigenvalues of sparse `A` (ARPACK). `which`: `'LM'` (largest magnitude), `'SM'` (smallest), `'LR'`/`'SR'` (real part), etc.
- `spla.eigsh(A, k=6, which='LM', M=None)`: eigenvalues of sparse **symmetric** `A`.
- `spla.svds(A, k=6, which='LM')`: `k` largest singular values.
- `spla.norm(x, ord=None)`: sparse matrix norm.
- `spla.LinearOperator(shape, matvec)`: defines a matrix implicitly via a matrix-vector product function — avoids forming `A` explicitly.

```python
from scipy import sparse
from scipy.sparse import linalg as spla
import numpy as np

# --- COO construction ---
row  = np.array([0, 1, 2, 0])
col  = np.array([0, 1, 2, 2])
data = np.array([4., 3., 2., 1.])
A_coo = sparse.coo_array((data, (row, col)), shape=(3, 3))
print("Dense:\n", A_coo.toarray())

# --- LIL: incremental construction ---
A_lil = sparse.lil_array((100, 100))
for i in range(100):
    A_lil[i, i] = 2.
    if i > 0: A_lil[i, i-1] = -1.
    if i < 99: A_lil[i, i+1] = -1.
A_csr = A_lil.tocsr()
print("Tridiagonal nnz:", A_csr.nnz)   # 298

# --- diags: most efficient for banded matrices ---
n = 200
diags_data = [-np.ones(n-1), 2*np.ones(n), -np.ones(n-1)]
offsets     = [-1, 0, 1]
A_diag = sparse.diags(diags_data, offsets, shape=(n, n), format='csr')

b = np.ones(n)

# --- Direct sparse solve ---
x = spla.spsolve(A_diag, b)
print("Direct solve residual:", np.linalg.norm(A_diag @ x - b))

# --- Iterative: Conjugate Gradient ---
x_cg, info = spla.cg(A_diag, b, tol=1e-10)
print("CG converged:", info == 0, "  residual:", np.linalg.norm(A_diag @ x_cg - b))

# --- GMRES (non-symmetric) ---
A_ns = A_diag + sparse.diags([0.5*np.ones(n-1)], [1], shape=(n,n), format='csr')
x_gm, info = spla.gmres(A_ns, b, tol=1e-10)
print("GMRES converged:", info == 0)

# --- Eigenvalues of large sparse matrix ---
vals, vecs = spla.eigsh(A_diag, k=6, which='SM')   # 6 smallest
print("6 smallest eigenvalues:", np.round(vals, 4))

# --- LinearOperator (matrix-free) ---
def matvec(v):   # circulant shift + scale
    return 2*v - np.roll(v, 1) - np.roll(v, -1)

A_op = spla.LinearOperator((n, n), matvec=matvec)
x_op, _ = spla.cg(A_op, b, tol=1e-10)
print("Matrix-free CG converged")
```

---

## Spatial Algorithms (`scipy.spatial`)

### KD-Tree

- `spatial.KDTree(data, leafsize=10, compact_nodes=True, balanced_tree=True)`: kd-tree for Euclidean nearest-neighbour queries.
  - `data`: shape `(n, k)` — n points in k-D space.
  - `leafsize`: points per leaf (affects build/query time trade-off).

- `KDTree.query(x, k=1, workers=1, distance_upper_bound=inf)`: finds `k` nearest neighbours of query points `x`. Returns `(distances, indices)`.

- `KDTree.query_ball_point(x, r, workers=1)`: returns all indices within radius `r` of each query point.

- `KDTree.query_ball_tree(other, r)`: all pairs between two trees within distance `r`.

- `KDTree.count_neighbors(other, r)`: counts neighbour pairs within distance `r`.

- `spatial.cKDTree`: C implementation — same API, significantly faster for large datasets.

### Geometric Algorithms

- `spatial.ConvexHull(points, incremental=False)`: convex hull.
  - `.vertices`: indices of hull vertices.
  - `.simplices`: indices of hull facets.
  - `.area`: surface area (perimeter in 2D).
  - `.volume`: enclosed volume (area in 2D).

- `spatial.Delaunay(points, furthest_site=False)`: Delaunay triangulation.
  - `.find_simplex(xi)`: finds the simplex containing each query point (`-1` if outside).
  - `.simplices`: triangle indices.
  - `.neighbors`: neighbor simplex indices.

- `spatial.Voronoi(points, furthest_site=False)`: Voronoi diagram.
  - `.vertices`: Voronoi vertex coordinates.
  - `.ridge_vertices`: pairs of Voronoi vertices forming ridges.
  - `.regions`: lists of vertex indices per region.

### Distance Computations

- `spatial.distance.cdist(XA, XB, metric='euclidean', **kwargs)`: all pairwise distances between rows of `XA` (shape `(mA, k)`) and `XB` (shape `(mB, k)`). Returns `(mA, mB)`.
  - `metric`: `'euclidean'`, `'cityblock'`, `'cosine'`, `'minkowski'`, `'hamming'`, `'jaccard'`, `'chebyshev'`, `'correlation'`, `'mahalanobis'`, etc.

- `spatial.distance.pdist(X, metric='euclidean', **kwargs)`: condensed pairwise distances within `X`.

- `spatial.distance.squareform(X)`: converts between condensed (1D) and square (2D) distance matrices.

```python
from scipy import spatial
from scipy.spatial.distance import cdist, pdist, squareform
import numpy as np

rng = np.random.default_rng(0)
pts = rng.uniform(0, 10, (200, 2))

# --- KDTree ---
tree = spatial.KDTree(pts)

# 5 nearest neighbours of a query point
dists, idxs = tree.query([[5.0, 5.0]], k=5)
print("NN distances:", np.round(dists, 3))

# All points within radius r
neighbours = tree.query_ball_point([[5, 5]], r=1.5)
print(f"Points within r=1.5: {len(neighbours[0])}")

# --- Convex Hull ---
hull = spatial.ConvexHull(pts)
print("Hull vertices:", len(hull.vertices))
print("Hull area (perimeter in 2D):", round(hull.area, 2))
print("Hull volume (area in 2D):", round(hull.volume, 2))

# --- Delaunay ---
tri = spatial.Delaunay(pts)
test = np.array([[5, 5], [20, 20]])
inside = tri.find_simplex(test) >= 0
print("Inside hull:", inside)   # [True, False]

# --- Distance matrices ---
A = rng.uniform(0, 5, (6, 2))
B = rng.uniform(0, 5, (4, 2))
D_AB = cdist(A, B, metric='euclidean')
print("cdist shape:", D_AB.shape)   # (6, 4)

D_cos = cdist(A, B, metric='cosine')
print("Cosine distance range: [{:.3f}, {:.3f}]".format(D_cos.min(), D_cos.max()))

# Condensed pairwise and square form
cond = pdist(A)
sq   = squareform(cond)
print("Square form diagonal (should be 0):", sq.diagonal())

# Mahalanobis (accounts for correlation structure)
cov_data = rng.multivariate_normal([0, 0], [[2, 1], [1, 2]], 200)
VI = np.linalg.inv(np.cov(cov_data.T))
D_maha = cdist(A, B, metric='mahalanobis', VI=VI)
print("Mahalanobis shape:", D_maha.shape)
```

---

## Information Theory (`scipy.stats` & `scipy.special`)

- `stats.entropy(pk, qk=None, base=None, axis=0)`: Shannon entropy `H(p)` or KL divergence `D_KL(p||q)`.
  - `pk`: probability distribution. Normalised automatically if it does not sum to 1.
  - `qk`: if provided, computes `D_KL(pk || qk)` instead of entropy.
  - `base`: logarithm base. `None` = natural log (nats), `2` = bits.

- `special.entr(x)`: element-wise entropy contribution `-x * log(x)`, returning `0` for `x = 0`.

- `special.rel_entr(x, y)`: element-wise KL contribution `x * log(x/y)`. Returns `0` when `x = 0`, `+∞` when `y = 0` and `x ≠ 0`.

- `special.kl_div(x, y)`: `x * log(x/y) - x + y` — alternative divergence form.

```python
from scipy import stats, special
import numpy as np

# --- Shannon entropy ---
uniform = np.array([0.25, 0.25, 0.25, 0.25])
print("H(uniform) in nats:", round(stats.entropy(uniform), 4))        # ln(4) ≈ 1.386
print("H(uniform) in bits:", round(stats.entropy(uniform, base=2), 4)) # 2.0

peaked = np.array([0.9, 0.05, 0.04, 0.01])
print("H(peaked) in bits:", round(stats.entropy(peaked, base=2), 4))   # < 2

# --- KL divergence ---
p = np.array([0.4, 0.4, 0.2])
q = np.array([0.3, 0.4, 0.3])
kl_pq = stats.entropy(p, q)
kl_qp = stats.entropy(q, p)
print(f"KL(p||q) = {kl_pq:.4f}")    # asymmetric
print(f"KL(q||p) = {kl_qp:.4f}")

# --- Jensen-Shannon divergence (symmetric, in [0, ln2]) ---
m = 0.5 * (p + q)
jsd = 0.5 * stats.entropy(p, m) + 0.5 * stats.entropy(q, m)
print(f"JSD(p, q) = {jsd:.4f}")

# --- Cross-entropy H(p, q) = H(p) + KL(p||q) ---
cross_ent = stats.entropy(p) + kl_pq
print(f"Cross-entropy H(p,q) = {cross_ent:.4f}")

# --- Mutual Information (discrete) ---
# Joint distribution P(X, Y)
joint = np.array([[0.1, 0.4],
                  [0.4, 0.1]])
px  = joint.sum(axis=1)    # P(X)
py  = joint.sum(axis=0)    # P(Y)
H_X  = stats.entropy(px)
H_Y  = stats.entropy(py)
H_XY = stats.entropy(joint.ravel())
MI   = H_X + H_Y - H_XY
print(f"Mutual information I(X;Y) = {MI:.4f} nats")

# --- Element-wise operations ---
x = np.array([0.5, 0.3, 0.2, 0.0])
y = np.array([0.4, 0.4, 0.1, 0.1])
print("entr(x):", np.round(special.entr(x), 4))          # -x*log(x)
print("rel_entr(x,y):", np.round(special.rel_entr(x, y), 4))

# Safe KL using xlogy: Σ p log(p/q) = Σ p log(p) - Σ p log(q)
kl_safe = np.sum(special.xlogy(x, x) - special.xlogy(x, y))
print(f"KL via xlogy = {kl_safe:.4f}")
```

---

## Clustering (`scipy.cluster`)

SciPy provides two clustering submodules: `scipy.cluster.vq` for vector quantization (k-means) and `scipy.cluster.hierarchy` for agglomerative hierarchical clustering.

```python
from scipy.cluster import vq, hierarchy
```

### Vector Quantization (`scipy.cluster.vq`)

- `vq.whiten(obs, check_finite=True)`: normalizes each feature by its standard deviation so all features have unit variance before clustering — strongly recommended as a preprocessing step.
  - `obs`: shape `(n, k)` — n observations, k features.

- `vq.kmeans(obs, k_or_guess, iter=10, thresh=1e-5, check_finite=True)`: runs k-means and returns the final codebook (centroids) and distortion.
  - `obs`: whitened observation array, shape `(n, k)`.
  - `k_or_guess`: number of clusters (int) or initial centroid array of shape `(k, k_features)`.
  - `iter`: number of times k-means is run; best result returned.
  - `thresh`: convergence threshold on distortion change.
  - Returns `(codebook, distortion)` — `codebook` has shape `(k, k_features)`.

- `vq.kmeans2(data, k, iter=10, minit='random', missing='warn', check_finite=True)`: extended k-means with more control over initialisation.
  - `minit`: initialisation method — `'random'` (random data points), `'points'` (random observations), `'++' ` (k-means++ seeding, recommended), `'matrix'` (use `k` as initial centroid matrix).
  - `missing`: action when a cluster becomes empty — `'warn'` or `'raise'`.
  - Returns `(centroid, label)` — `label` is the cluster index for every observation.

- `vq.vq(obs, code_book, check_finite=True)`: assigns each observation in `obs` to the nearest centroid in `code_book`.
  - Returns `(code, dist)` — cluster index and distance to the nearest centroid for each observation.

```python
from scipy.cluster import vq
import numpy as np

rng = np.random.default_rng(42)

# Generate 3 Gaussian clusters
c1 = rng.normal([0, 0],   1.0, (100, 2))
c2 = rng.normal([6, 0],   1.0, (100, 2))
c3 = rng.normal([3, 5],   1.0, (100, 2))
data = np.vstack([c1, c2, c3])

# Whiten features (standardise by std)
whitened = vq.whiten(data)

# k-means (basic)
codebook, distortion = vq.kmeans(whitened, 3, iter=20)
print("Distortion:", round(distortion, 4))
print("Centroids (whitened):\n", np.round(codebook, 3))

# Assign labels
labels, dists = vq.vq(whitened, codebook)
print("Label counts:", np.bincount(labels))   # ≈ [100, 100, 100]

# kmeans2 with k-means++ initialisation
centroids, labels2 = vq.kmeans2(whitened, 3, iter=20, minit='++')
print("kmeans2 label counts:", np.bincount(labels2))

# Elbow method — choose k by distortion
distortions = []
for k in range(1, 7):
    _, d = vq.kmeans(whitened, k, iter=10)
    distortions.append(d)
print("Distortions for k=1..6:", [round(d, 3) for d in distortions])
```

### Hierarchical Clustering (`scipy.cluster.hierarchy`)

- `hierarchy.linkage(y, method='single', metric='euclidean', optimal_ordering=False)`: performs agglomerative hierarchical clustering.
  - `y`: condensed distance matrix (from `pdist`) **or** observation matrix (shape `(n, k)`).
  - `method`: linkage criterion:
    - `'single'`: minimum pairwise distance (chaining effect).
    - `'complete'`: maximum pairwise distance (compact clusters).
    - `'average'`: UPGMA — mean pairwise distance.
    - `'weighted'`: WPGMA.
    - `'centroid'`: UPGMC — distance between centroids.
    - `'median'`: WPGMC.
    - `'ward'`: minimises within-cluster variance — usually best for compact clusters.
  - `metric`: any metric accepted by `pdist` (used only when `y` is an observation matrix).
  - `optimal_ordering`: if `True`, reorders the linkage matrix to minimise distances between adjacent leaves.
  - Returns a linkage matrix `Z` of shape `(n-1, 4)`: `[cluster_i, cluster_j, distance, n_members]`.

- `hierarchy.dendrogram(Z, p=30, truncate_mode=None, color_threshold=None, labels=None, orientation='top', show_leaf_counts=True, ax=None, no_plot=False)`: plots the dendrogram.
  - `truncate_mode`: `'lastp'` (show only last `p` merges) or `'level'` (cut at depth `p`).
  - `color_threshold`: distance at which branch colours change; `None` uses 70% of max distance.
  - `no_plot`: if `True`, returns cluster structure without drawing.
  - Returns a dict with `'icoord'`, `'dcoord'`, `'ivl'` (leaf labels), `'color_list'`.

- `hierarchy.fcluster(Z, t, criterion='inconsistent', depth=2, R=None, monocrit=None)`: forms flat clusters from a linkage matrix.
  - `t`: threshold — interpretation depends on `criterion`.
  - `criterion`:
    - `'inconsistent'`: cut where inconsistency coefficient exceeds `t`.
    - `'distance'`: cut at distance `t` (most intuitive — merges below `t` are in same cluster).
    - `'maxclust'`: form exactly `t` clusters.
    - `'monocrit'`: custom monotonic criterion array.
  - Returns a label array of shape `(n,)`.

- `hierarchy.fclusterdata(X, t, criterion='inconsistent', metric='euclidean', depth=2, method='single', R=None)`: convenience wrapper — runs `pdist`, `linkage`, and `fcluster` in one call.

- `hierarchy.cut_tree(Z, n_clusters=None, height=None)`: cuts the dendrogram to form a given number of flat clusters or at specified heights. More flexible than `fcluster`.
  - Returns shape `(n, len(n_clusters))` — a column per cut.

- `hierarchy.inconsistent(Z, d=2)`: computes the inconsistency coefficient for each merge — how different the merge distance is from the mean of the `d` levels below it.
  - Returns array of shape `(n-1, 4)`: `[mean, std, count, inconsistency]`.

- `hierarchy.cophenet(Z, Y=None)`: computes the cophenetic correlation coefficient — measures how faithfully the dendrogram preserves original pairwise distances. Higher is better (max 1.0).

- `hierarchy.maxdists(Z)`: maximum distance within each cluster for every merge step.

- `hierarchy.leaders(Z, T)`: returns the root nodes (leaders) of each flat cluster `T` in the linkage tree.

- `hierarchy.is_valid_linkage(Z)` / `hierarchy.is_valid_im(R)`: validates a linkage/inconsistency matrix.

```python
from scipy.cluster import hierarchy
from scipy.spatial.distance import pdist
import numpy as np
import matplotlib.pyplot as plt

rng = np.random.default_rng(42)

# Three compact clusters
c1 = rng.normal([0, 0],  0.5, (30, 2))
c2 = rng.normal([5, 0],  0.5, (30, 2))
c3 = rng.normal([2.5, 4], 0.5, (30, 2))
X  = np.vstack([c1, c2, c3])

# Condensed distance matrix
Y = pdist(X, metric='euclidean')

# Linkage — Ward minimises within-cluster variance
Z = hierarchy.linkage(Y, method='ward')
print("Linkage matrix shape:", Z.shape)   # (89, 4) for 90 points

# Cophenetic correlation — how well dendrogram preserves distances
c, coph_dists = hierarchy.cophenet(Z, Y)
print(f"Cophenetic correlation: {c:.4f}")   # > 0.9 is good

# Inconsistency coefficients
incon = hierarchy.inconsistent(Z, d=3)
print("Max inconsistency:", round(incon[:, 3].max(), 4))

# Flat clusters by distance threshold
labels_dist = hierarchy.fcluster(Z, t=2.0, criterion='distance')
print("Clusters (distance cut):", np.bincount(labels_dist)[1:])

# Flat clusters — exactly 3 clusters
labels_k = hierarchy.fcluster(Z, t=3, criterion='maxclust')
print("Clusters (k=3):", np.bincount(labels_k)[1:])   # ≈ [30, 30, 30]

# cut_tree — multiple cuts at once
cuts = hierarchy.cut_tree(Z, n_clusters=[2, 3, 4])
print("Cut shapes:", cuts.shape)   # (90, 3)

# Dendrogram (truncated for readability)
fig, ax = plt.subplots(figsize=(10, 4))
hierarchy.dendrogram(Z, truncate_mode='lastp', p=12,
                     color_threshold=2.0, ax=ax, leaf_rotation=45)
ax.set_title("Ward Linkage Dendrogram (last 12 merges)")
plt.tight_layout()
plt.show()

# fclusterdata — one-shot convenience
labels_fc = hierarchy.fclusterdata(X, t=3, criterion='maxclust',
                                   metric='euclidean', method='ward')
print("fclusterdata labels:", np.bincount(labels_fc)[1:])

# Compare methods — cophenetic correlation for each linkage type
for method in ['single', 'complete', 'average', 'ward']:
    Z_m = hierarchy.linkage(Y, method=method)
    c_m, _ = hierarchy.cophenet(Z_m, Y)
    print(f"  {method:10s}: cophenetic r = {c_m:.4f}")
```
