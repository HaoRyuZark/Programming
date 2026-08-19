# SymPy

**SymPy** stands for Symbolic Python. It is a library for computer algebra that manipulates mathematical expressions as symbols
rather than numbers, enabling exact analytical results and avoiding floating-point rounding errors.

The documentation is at [SymPy Docs](https://docs.sympy.org/).

---

## Import

```python
import sympy as sp

# Or import commonly used names directly
from sympy import symbols, Symbol, sqrt, pi, E, oo, I, Rational
```

---

## Symbols & Assumptions

**Symbols** are the building blocks of SymPy expressions — symbolic placeholders for unknowns or variables. Assumptions
constrain the symbol's domain, which affects simplification and solving behaviour.

- `sp.Symbol(name, **assumptions)`: creates a single symbolic variable.
  - `name`: string identifier for the symbol.
  - `**assumptions`: keyword flags constraining the symbol — see table below.

- `sp.symbols(names, **assumptions)`: creates multiple symbols at once from a space- or comma-separated string.
  - `names`: string of names, e.g. `'x y z'`, or a sequence pattern like `'x:5'`.
  - `**assumptions`: same flags applied to all created symbols.

**Common assumptions:**

| Assumption | Meaning |
|------------|---------|
| `real=True` | Symbol is real-valued |
| `positive=True` | Symbol is strictly positive (implies `real=True`) |
| `negative=True` | Symbol is strictly negative |
| `nonnegative=True` | Symbol is ≥ 0 |
| `integer=True` | Symbol is an integer |
| `rational=True` | Symbol is rational |
| `complex=True` | Symbol is complex (default) |
| `finite=True` | Symbol is finite |
| `commutative=False` | Symbol does not commute (for matrix algebra) |

```python
x = sp.Symbol("x")
y = sp.Symbol("y", real=True)
n = sp.Symbol("n", integer=True, positive=True)

x, y, z = sp.symbols("x y z")
a, b, c = sp.symbols("a b c", real=True, positive=True)
x0, x1, x2, x3, x4 = sp.symbols("x:5")         # range shorthand

# Checking assumptions — returns True, False, or None (unknown)
print(y.is_real)         # True
print(n.is_positive)     # True
print(x.is_real)         # None
```

---

## Data Types & Constants

SymPy provides exact numeric types that avoid floating-point errors.

- `sp.Integer(n)`: wraps a Python int in SymPy's type system.

- `sp.Rational(p, q)`: exact fraction $\frac{p}{q}$.
  - `p`: numerator.
  - `q`: denominator.

- `sp.Float(num, precision)`: arbitrary-precision float.
  - `num`: numeric value (string or number).
  - `precision`: number of significant digits.

**Built-in constants:**

| Constant | Description |
|----------|-------------|
| `sp.pi` | π = 3.14159… |
| `sp.E` | Euler's number e = 2.71828… |
| `sp.oo` | Infinity ∞ |
| `sp.I` | Imaginary unit i = √(−1) |
| `sp.nan` | Not a Number |
| `sp.GoldenRatio` | φ = (1 + √5) / 2 |
| `sp.EulerGamma` | Euler–Mascheroni constant γ ≈ 0.5772 |

```python
# Exact types — no rounding errors
print(sp.Rational(1, 3))          # 1/3
print(sp.Rational(1, 3) * 3)      # 1  (exact)
print(1/3 * 3)                     # 0.9999... (floating-point error)

r = sp.Rational(22, 7)             # exact approximation of π
f = sp.Float("3.14159265", 50)     # 50 significant digits

# Constants in expressions
expr = sp.E ** (sp.I * sp.pi) + 1  # Euler's identity e^(iπ) + 1
print(sp.simplify(expr))            # 0

print(sp.oo + 1)       # oo
print(1 / sp.oo)       # 0
print(sp.oo > 1e100)   # True
```

---

## Basic Operations & Arithmetic

Standard Python operators work on SymPy objects and return symbolic results.

```python
x, y = sp.symbols("x y")

# Arithmetic operators
expr1 = x + y
expr2 = x * y
expr3 = x ** 2 + 2*x + 1
expr4 = (x + 1) / (x - 1)
expr5 = sp.sqrt(x)                  # = x**(sp.Rational(1, 2))

# Built-in elementary functions
print(sp.Abs(x))                    # |x|
print(sp.sign(x))                   # sign function
print(sp.ceiling(x))                # ⌈x⌉
print(sp.floor(x))                  # ⌊x⌋
print(sp.sqrt(8))                   # 2*sqrt(2) — simplified automatically
print(sp.cbrt(x))                   # x**(1/3)
print(sp.root(x, 4))                # x**(1/4)
print(sp.log(x))                    # natural log ln(x)
print(sp.log(x, 10))                # log base 10
print(sp.exp(x))                    # e^x

# Relational objects — returns symbolic Boolean, NOT Python bool
eq  = sp.Eq(x**2, 4)               # x² = 4 (equation object for solve())
neq = sp.Ne(x, 0)
lt  = sp.Lt(x, 5)
gt  = sp.Gt(x, 0)
```

---

## Simplification & Manipulation

These functions transform expressions into equivalent forms.

- `sp.simplify(expr)`: applies a sequence of simplification rules. General-purpose but slow; prefer specialised functions below when you know the target form.

- `sp.expand(expr, **hints)`: distributes products and powers over addition.
  - `trig=True`: also expands trigonometric identities.
  - `log=True`: expands logarithms using log rules.
  - `complex=True`: expands using complex number rules.

- `sp.factor(expr, **kwargs)`: factors a polynomial into irreducible factors over the rationals.
  - `deep=True`: also factors sub-expressions.
  - `extension`: algebraic extension to factor over (e.g. `sp.sqrt(2)`).

- `sp.collect(expr, syms)`: collects terms by powers of a symbol or list of symbols.
  - `syms`: symbol or list of symbols to collect by.

- `sp.cancel(expr)`: puts a rational expression in standard form $p/q$ with `gcd(p, q) = 1`.

- `sp.apart(expr, x=None)`: partial fraction decomposition.
  - `x`: variable to decompose with respect to.

- `sp.radsimp(expr)`: rationalises the denominator (removes roots from the denominator).

- `sp.powsimp(expr, force=False)`: simplifies expressions with powers.
  - `force=True`: combines powers even without assumptions on variables.

- `sp.logcombine(expr, force=False)`: combines separate logarithm terms into a single log.

- `sp.trigsimp(expr)`: simplifies trigonometric expressions using identities.

- `sp.nsimplify(expr, constants=[], tolerance=None)`: finds a simple symbolic form matching a float value.
  - `constants`: list of constants to try (e.g. `[sp.pi, sp.E]`).
  - `tolerance`: maximum allowed error.

```python
x, y = sp.symbols("x y")

# expand
print(sp.expand((x + y)**3))               # x³ + 3x²y + 3xy² + y³
print(sp.expand((x+1)*(x-1)))              # x² - 1
print(sp.expand(sp.sin(x + y), trig=True)) # sin(x)cos(y) + cos(x)sin(y)
print(sp.expand(sp.log(x**2 * y), log=True))  # 2*log(x) + log(y)

# factor
print(sp.factor(x**2 - 1))                # (x-1)*(x+1)
print(sp.factor(x**3 - x**2 + x - 1))    # (x-1)*(x²+1)

# collect
expr = x*y + x**2*y + x*y**2
print(sp.collect(expr, x))                # x*(y + y²) + x²*y

# cancel
print(sp.cancel((x**2 - 1) / (x - 1)))   # x + 1

# apart
print(sp.apart(1 / (x**2 - 1), x))       # -1/(2*(x+1)) + 1/(2*(x-1))

# trigsimp
print(sp.trigsimp(sp.sin(x)**2 + sp.cos(x)**2))  # 1
print(sp.trigsimp(2*sp.sin(x)*sp.cos(x)))        # sin(2x)

# nsimplify — recognise symbolic form of a float
print(sp.nsimplify(3.14159265, [sp.pi]))   # pi
print(sp.nsimplify(0.333333))              # 1/3
```

---

## Substitution & Evaluation

- `expr.subs(old, new)`: replaces `old` with `new` in the expression.
  - `old`: symbol, sub-expression, or list of `(old, new)` pairs for simultaneous substitution.
  - `new`: replacement value or expression.

- `expr.evalf(n=15, subs=None)`: evaluates the expression to an `n`-digit floating-point number.
  - `n`: number of significant digits (default 15).
  - `subs`: dict of substitutions to apply before evaluating.

- `sp.N(expr, n=15)`: shorthand alias for `evalf`.

- `sp.lambdify(args, expr, modules='numpy')`: compiles a SymPy expression into a fast callable.
  - `args`: symbol or tuple of symbols used as function arguments.
  - `expr`: SymPy expression to convert.
  - `modules`: numeric backend — `'numpy'`, `'scipy'`, `'math'`, or a custom dict.

```python
import numpy as np
x, y = sp.symbols("x y")
expr = x**2 + 2*x + 1

# Single substitution
print(expr.subs(x, 3))               # 16
print(expr.subs(x, y + 1))           # (y+1)² + 2(y+1) + 1

# Simultaneous substitution with a list
expr2 = x**2 + y**2
print(expr2.subs([(x, 3), (y, 4)]))  # 25

# High-precision evaluation
print(sp.pi.evalf())                  # 3.14159265358979
print(sp.pi.evalf(50))               # 50 digits of π
print(sp.E.evalf(100))               # 100 digits of e

# Evaluate with substitution in one step
f = sp.sin(x) + sp.cos(x)
print(f.evalf(subs={x: 1.0}))        # 1.38177329...

# lambdify — vectorised NumPy speed
f_num = sp.lambdify(x, sp.sin(x) + x**2, modules="numpy")
print(f_num(np.array([0, 1, 2])))    # array of numeric results

g_num = sp.lambdify((x, y), x**2 + y**2, modules="numpy")
print(g_num(3, 4))                   # 25.0
```

---

## Expression Inspection

Useful for introspecting the structure of a SymPy expression tree.

- `expr.args`: tuple of top-level operands.
- `expr.free_symbols`: set of all unbound symbols in the expression.
- `expr.func`: the outermost function class of the expression.
- `sp.count_ops(expr)`: counts the number of operations.
- `sp.degree(expr, x)`: degree of a polynomial in `x`.
- `sp.Poly(expr, *gens)`: wraps an expression as a polynomial object with explicit coefficient tracking.
  - `gens`: generator variables.
- `sp.srepr(expr)`: full internal tree representation as a string.

```python
x, y = sp.symbols("x y")
expr = x**2 + 2*x*y + y**2

print(expr.args)             # (x², 2*x*y, y²)
print(expr.free_symbols)     # {x, y}
print(expr.func)             # <class 'sympy.core.add.Add'>

print(sp.degree(x**3 + x, x))    # 3
print(sp.srepr(x + 1))           # Add(Symbol('x'), Integer(1))

p = sp.Poly(x**3 - 2*x + 1, x)
print(p.coeffs())            # [1, 0, -2, 1]
print(p.degree())            # 3
print(p.nth(0))              # 1  (constant term)
```

---

## Solving Equations

- `sp.solve(f, *symbols, **flags)`: solves equations and systems symbolically.
  - `f`: expression (assumed = 0), `Eq` object, or list for systems.
  - `*symbols`: symbol(s) to solve for. Solves for all free symbols if omitted.
  - `dict=True`: returns a list of dicts `{symbol: solution}`.
  - `set=True`: returns a tuple `(symbols, set_of_solutions)`.

- `sp.solveset(f, symbol=None, domain=sp.S.Complexes)`: rigorous solver returning a SymPy `Set`.
  - `f`: expression (= 0) or `Eq` object.
  - `symbol`: the variable to solve for.
  - `domain`: `sp.S.Reals`, `sp.S.Complexes`, `sp.S.Integers`.

- `sp.linsolve(system, *symbols)`: solves systems of linear equations.
  - `system`: list of expressions/equations, or an augmented matrix.

- `sp.nonlinsolve(system, *symbols)`: solves systems of nonlinear equations.

- `sp.nsolve(f, x, x0, tol=None)`: numerical solver using Newton's method.
  - `x`: variable or tuple of variables.
  - `x0`: initial guess (scalar or column vector for systems).

```python
x, y = sp.symbols("x y")

# Single variable equation (expression assumed = 0)
print(sp.solve(x**2 - 4, x))            # [-2, 2]
print(sp.solve(x**3 - x, x))            # [-1, 0, 1]

# Using Eq object
print(sp.solve(sp.Eq(x**2, 9), x))      # [-3, 3]

# System of equations
sol = sp.solve([x + y - 3, x - y - 1], [x, y])
print(sol)                               # {x: 2, y: 1}

# solveset — returns a Set
print(sp.solveset(x**2 - 4, x, domain=sp.S.Reals))       # {-2, 2}
print(sp.solveset(sp.sin(x), x, domain=sp.S.Reals))      # ImageSet over integers
print(sp.solveset(x**2 + 1, x, domain=sp.S.Reals))       # EmptySet

# linsolve — linear systems
sol = sp.linsolve([x + y - 2, 2*x - y - 1], x, y)
print(sol)                               # {(1, 1)}

# Augmented matrix form
M = sp.Matrix([[1, 1, 2], [2, -1, 1]])
print(sp.linsolve(M, x, y))             # {(1, 1)}

# nsolve — numerical root finding
print(sp.nsolve(x**3 - x - 1, x, 1))   # 1.32472...

# nsolve for systems
sol = sp.nsolve([x**2 + y**2 - 5, x - y - 1], [x, y], [1, 1])
print(sol)                               # matrix with solution
```

---

## Solving Inequalities

- `sp.solve_univariate_inequality(expr, x, relational=False, domain=sp.S.Reals)`: solves a single-variable inequality.
  - `expr`: relational expression, e.g. `x**2 > 1`.
  - `x`: the variable.
  - `relational=False`: returns a `Set`; `True` returns a relational expression.

- `sp.reduce_inequalities(ineqs, symbols=[])`: reduces a system of inequalities to a simpler form.
  - `ineqs`: list of inequality expressions.

```python
x = sp.Symbol("x", real=True)

# x² > 1
sol = sp.solve_univariate_inequality(x**2 > 1, x, relational=False)
print(sol)                   # (-oo, -1) ∪ (1, oo)

# x² - x < 6
sol = sp.solve_univariate_inequality(x**2 - x < 6, x)
print(sol)                   # -2 < x ∧ x < 3

# System of inequalities
sol = sp.reduce_inequalities([x >= 0, x**2 <= 4], x)
print(sol)                   # 0 <= x <= 2
```

---

## Trigonometry

SymPy returns exact values for common angles and knows all standard identities.

```python
x, y = sp.symbols("x y", real=True)

# Standard trig functions
print(sp.sin(x), sp.cos(x), sp.tan(x))
print(sp.cot(x), sp.sec(x), sp.csc(x))

# Inverse trig
print(sp.asin(x), sp.acos(x), sp.atan(x))
print(sp.atan2(y, x))               # atan(y/x) with correct quadrant

# Hyperbolic
print(sp.sinh(x), sp.cosh(x), sp.tanh(x))
print(sp.asinh(x), sp.acosh(x), sp.atanh(x))

# Exact values at special angles
print(sp.sin(sp.pi / 6))            # 1/2
print(sp.cos(sp.pi / 4))            # sqrt(2)/2
print(sp.tan(sp.pi / 3))            # sqrt(3)
print(sp.sin(sp.pi))                # 0

# Expand using identities
print(sp.expand_trig(sp.sin(x + y)))     # sin(x)cos(y) + cos(x)sin(y)
print(sp.expand_trig(sp.cos(2*x)))       # 2*cos²(x) - 1
print(sp.expand_trig(sp.tan(2*x)))       # 2*tan(x)/(1 - tan²(x))

# Simplify using identities
print(sp.trigsimp(sp.sin(x)**2 + sp.cos(x)**2))  # 1
print(sp.trigsimp(2*sp.sin(x)*sp.cos(x)))        # sin(2x)

# Rewrite in terms of exponentials (Euler's formula)
print(sp.rewrite(sp.cos(x), sp.exp))    # exp(I*x)/2 + exp(-I*x)/2
print(sp.sin(x).rewrite(sp.cos))        # cos(x - π/2)
print(sp.tan(x).rewrite(sp.sin))        # sin(x)/sin(π/2 - x)
```

---

## Simplifying Expressions (Advanced)

Specialised simplification functions for particular expression types.

- `sp.simplify(expr)`: general-purpose simplification.
- `sp.trigsimp(expr)`: trig identities.
- `sp.powsimp(expr, force=False)`: power rule combinations.
- `sp.radsimp(expr)`: rationalise denominator.
- `sp.logcombine(expr, force=False)`: merge log terms.
- `sp.fu(expr)`: applies Fu's algorithm — a systematic set of trig simplification rules (often more powerful than `trigsimp`).
- `sp.combsimp(expr)`: simplifies combinatorial expressions (factorials, binomials).
- `sp.gammasimp(expr)`: simplifies gamma function expressions.

```python
x, n = sp.symbols("x n", positive=True)

# Combining logs
expr = sp.log(x) + sp.log(n)
print(sp.logcombine(expr, force=True))  # log(x*n)

# Simplifying powers
expr = sp.sqrt(x) * x**sp.Rational(3, 2)
print(sp.powsimp(expr))               # x²

# Rationalise denominator
print(sp.radsimp(1 / (1 + sp.sqrt(2))))  # -1 + sqrt(2)

# Combinatorial simplification
print(sp.combsimp(sp.factorial(n) / sp.factorial(n - 1)))  # n

# Fu's algorithm — advanced trig
from sympy import sin, cos
print(sp.fu(sin(x)**4 - cos(x)**4))   # -cos(2x)
```

---

## Calculus – Derivatives

- `sp.diff(expr, *args)`: differentiates an expression.
  - `expr`: expression to differentiate.
  - `*args`: variable, or `(variable, n)` for the n-th derivative. Chain multiple variables for partial derivatives.

- `expr.diff(*args)`: method form, equivalent to `sp.diff`.

- `sp.Derivative(expr, *args)`: unevaluated (lazy) derivative for display or deferred computation.

```python
x, y = sp.symbols("x y")

# First derivatives of common functions
print(sp.diff(x**3 + 2*x, x))        # 3x² + 2
print(sp.diff(sp.sin(x), x))         # cos(x)
print(sp.diff(sp.exp(x), x))         # e^x
print(sp.diff(sp.log(x), x))         # 1/x
print(sp.diff(sp.atan(x), x))        # 1/(x² + 1)

# Higher-order derivatives
print(sp.diff(x**5, x, 3))           # 60x²  (third derivative)
print(sp.diff(x**5, (x, 3)))         # same — tuple syntax

# Partial derivatives
f = x**2 * y + y**3
print(sp.diff(f, x))                 # 2xy
print(sp.diff(f, y))                 # x² + 3y²
print(sp.diff(f, x, y))              # 2x  (∂²f/∂x∂y)
print(sp.diff(f, x, 2))              # 2y  (∂²f/∂x²)

# Method form
print((x**3 + sp.sin(x)).diff(x))    # 3x² + cos(x)
print((x**3).diff(x, 2))             # 6x

# Unevaluated derivative (for display or later .doit())
d = sp.Derivative(sp.sin(x), x)
print(d)                             # Derivative(sin(x), x)
print(d.doit())                      # cos(x)
```

---

## Calculus – Integrals

- `sp.integrate(expr, *args)`: computes the integral of an expression.
  - `expr`: expression to integrate.
  - For **indefinite** integrals: pass the variable — `integrate(f, x)`.
  - For **definite** integrals: pass a tuple `(x, a, b)` — `integrate(f, (x, a, b))`.
  - For **multiple** integrals: chain tuples — `integrate(f, (x, a, b), (y, c, d))`.

- `sp.Integral(expr, *args)`: unevaluated (lazy) integral for display or deferred computation.

> No constant of integration is added to indefinite integrals.

```python
x, y = sp.symbols("x y")

# Indefinite integrals
print(sp.integrate(x**2, x))                         # x³/3
print(sp.integrate(sp.sin(x), x))                    # -cos(x)
print(sp.integrate(sp.exp(x), x))                    # e^x
print(sp.integrate(1 / x, x))                        # log(x)
print(sp.integrate(1 / (1 + x**2), x))               # atan(x)
print(sp.integrate(sp.log(x), x))                     # x*log(x) - x

# Definite integrals
print(sp.integrate(x**2, (x, 0, 1)))                 # 1/3
print(sp.integrate(sp.sin(x), (x, 0, sp.pi)))        # 2
print(sp.integrate(sp.exp(-x), (x, 0, sp.oo)))       # 1
print(sp.integrate(sp.exp(-x**2), (x, -sp.oo, sp.oo)))  # sqrt(pi)  (Gaussian)

# Double integral ∫₀¹ ∫₀¹ x*y dx dy
print(sp.integrate(x * y, (x, 0, 1), (y, 0, 1)))    # 1/4

# Unevaluated form
I = sp.Integral(sp.sin(x) / x, (x, 0, sp.oo))
print(I)          # Integral(sin(x)/x, (x, 0, oo))
print(I.doit())   # pi/2

# Non-elementary antiderivative — returned in terms of special functions
print(sp.integrate(sp.exp(-x**2), x))   # sqrt(pi)*erf(x)/2
```

---

## Limits & Series

- `sp.limit(expr, x, x0, dir='+')`: computes the limit of an expression.
  - `expr`: expression to evaluate.
  - `x`: variable approaching the limit point.
  - `x0`: limit point — number, symbol, `sp.oo`, or `-sp.oo`.
  - `dir`: direction — `'+'` (from right), `'-'` (from left), `'+-'` (two-sided).

- `sp.Limit(expr, x, x0, dir='+')`: unevaluated limit.

- `sp.series(expr, x=None, x0=0, n=6, dir='+')`: Taylor/Laurent series expansion around `x0`.
  - `x`: expansion variable.
  - `x0`: expansion point (default 0).
  - `n`: order of truncation — includes terms up to but not including `O(x^n)`.

- `expr.removeO()`: strips the big-O remainder from a series result.

```python
x = sp.Symbol("x")

# Standard limits
print(sp.limit(sp.sin(x) / x, x, 0))                   # 1
print(sp.limit((1 + 1/x)**x, x, sp.oo))                # E
print(sp.limit(1/x, x, 0, dir='+'))                    # oo
print(sp.limit(1/x, x, 0, dir='-'))                    # -oo
print(sp.limit((x**2 - 1)/(x - 1), x, 1))             # 2 (L'Hôpital applied automatically)

# Taylor series for sin(x) around 0, up to O(x⁷)
s = sp.series(sp.sin(x), x, 0, 7)
print(s)            # x - x³/6 + x⁵/120 + O(x⁷)
print(s.removeO())  # x - x³/6 + x⁵/120

# Taylor series around a different point
print(sp.series(sp.exp(x), x, 1, 4))   # around x=1, 4 terms

# Laurent series (pole at x=0)
print(sp.series(1/sp.sin(x), x, 0, 4))  # 1/x + x/6 + 7x³/360 + O(x⁵)

# Extract specific coefficients
s = sp.series(sp.cos(x), x, 0, 8)
print(s.coeff(x, 0))     # 1
print(s.coeff(x, 2))     # -1/2
print(s.coeff(x, 4))     # 1/24
```

---

## Differential Equations

- `sp.dsolve(ode, func=None, hint='default', ics=None)`: solves ordinary differential equations.
  - `ode`: ODE expression equal to zero, built using `sp.Function` and `.diff()`.
  - `func`: the unknown function, e.g. `f(x)`.
  - `hint`: solver method — `'default'`, `'separable'`, `'1st_linear'`, `'nth_linear_constant_coeff_homogeneous'`, etc. Use `sp.classify_ode(ode, f(x))` to list valid hints.
  - `ics`: dict of initial/boundary conditions, e.g. `{f(0): 1, f(x).diff(x).subs(x, 0): 0}`.

- `sp.Function(name)`: declares an undefined function symbol for use in ODEs.

- `sp.checkodesol(ode, sol)`: verifies a solution satisfies the ODE. Returns `(True, 0)` if correct.

```python
x = sp.Symbol("x")
f = sp.Function("f")

# First-order ODE: f'(x) = f(x)
ode = f(x).diff(x) - f(x)
sol = sp.dsolve(ode, f(x))
print(sol)                    # f(x) = C1*exp(x)

# With initial condition f(0) = 2
sol_ic = sp.dsolve(ode, f(x), ics={f(0): 2})
print(sol_ic)                 # f(x) = 2*exp(x)

# Second-order ODE: f''(x) + f(x) = 0 (simple harmonic oscillator)
ode2 = f(x).diff(x, 2) + f(x)
sol2 = sp.dsolve(ode2, f(x))
print(sol2)                   # f(x) = C1*sin(x) + C2*cos(x)

# With boundary conditions f(0) = 0, f'(0) = 1
sol2_ic = sp.dsolve(ode2, f(x), ics={f(0): 0, f(x).diff(x).subs(x, 0): 1})
print(sol2_ic)                # f(x) = sin(x)

# Verify the solution
print(sp.checkodesol(ode, sol))   # (True, 0)

# Non-homogeneous ODE: f'' - 3f' + 2f = x
ode3 = f(x).diff(x, 2) - 3*f(x).diff(x) + 2*f(x) - x
print(sp.dsolve(ode3, f(x)))

# List available solver hints for an ODE
print(sp.classify_ode(ode, f(x)))
```

---

## Linear Algebra

- `sp.Matrix(rows)`: creates a symbolic matrix from a 2D list.
- `sp.eye(n)`: n×n identity matrix.
- `sp.zeros(n, m)`: n×m zero matrix.
- `sp.ones(n, m)`: n×m matrix of ones.
- `sp.diag(*args)`: block-diagonal matrix.

**Matrix methods:**

| Method | Description |
|--------|-------------|
| `M.T` | Transpose |
| `M.inv()` | Inverse |
| `M.det()` | Determinant |
| `M.rank()` | Rank |
| `M.trace()` | Trace |
| `M.norm()` | Frobenius norm |
| `M.nullspace()` | List of null-space basis vectors |
| `M.columnspace()` | List of column-space basis vectors |
| `M.rref()` | Reduced row echelon form: returns `(matrix, pivot_cols)` |
| `M.eigenvals()` | Dict `{eigenvalue: algebraic_multiplicity}` |
| `M.eigenvects()` | List of `(eigenvalue, multiplicity, [eigenvectors])` |
| `M.diagonalize()` | Returns `(P, D)` where `M = P·D·P⁻¹` |
| `M.cholesky()` | Cholesky decomposition (positive-definite M) |
| `M.LUdecomposition()` | Returns `(L, U, perm)` |
| `M.QRdecomposition()` | Returns `(Q, R)` |
| `M.singular_values()` | List of singular values |
| `M.solve(b)` | Solve `M·x = b` |
| `M.dot(v)` | Dot product |
| `M.cross(v)` | Cross product (3D vectors) |

```python
x = sp.Symbol("x")

A = sp.Matrix([[1, 2], [3, 4]])
B = sp.Matrix([[x, 1], [0, x]])

# Basic operations
print(A + A)            # element-wise addition
print(A * A)            # matrix multiplication
print(2 * A)            # scalar multiplication
print(A.T)              # transpose
print(A.det())          # -2
print(A.inv())          # [[−2, 1], [3/2, −1/2]]
print(A.trace())        # 5
print(A.rank())         # 2

# Solve A·x = b
b = sp.Matrix([1, 2])
print(A.solve(b))       # solution vector

# Eigenvalues and eigenvectors
print(A.eigenvals())    # {3-sqrt(5): 1, 3+sqrt(5): 1}
for val, mult, vecs in A.eigenvects():
    print(f"λ={val}, multiplicity={mult}, vectors={vecs}")

# Diagonalization: A = P·D·P⁻¹
P, D = A.diagonalize()
print(sp.simplify(P * D * P.inv() - A))  # zero matrix

# RREF
M = sp.Matrix([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
rref, pivots = M.rref()
print(rref)             # reduced row echelon form
print(pivots)           # (0, 1) — pivot column indices

# Null space
print(M.nullspace())    # [Matrix([1, -2, 1])]

# LU decomposition
L, U, perm = A.LUdecomposition()

# Symbolic matrix
M2 = sp.Matrix([[1, x], [x, 1]])
print(M2.det())         # 1 - x²
print(M2.eigenvals())   # {1-x: 1, 1+x: 1}
```

---

## Number Theory & Combinatorics

```python
import sympy as sp

n, k = sp.symbols("n k", integer=True, nonneg=True)
x = sp.Symbol("x")

# Primality & factoring
print(sp.isprime(17))              # True
print(sp.factorint(360))           # {2: 3, 3: 2, 5: 1}  →  2³·3²·5
print(sp.primefactors(360))        # [2, 3, 5]
print(sp.divisors(12))             # [1, 2, 3, 4, 6, 12]
print(sp.divisor_count(12))        # 6
print(sp.nextprime(10))            # 11
print(sp.prevprime(10))            # 7
list(sp.primerange(10, 30))        # [11, 13, 17, 19, 23, 29]

# GCD & LCM (work symbolically too)
print(sp.gcd(12, 18))              # 6
print(sp.lcm(12, 18))              # 36
print(sp.gcd(x**2 - 1, x - 1))    # x - 1

# Modular arithmetic
print(sp.mod_inverse(3, 11))       # 4  (3·4 ≡ 1 mod 11)
print(sp.totient(12))              # 4  (Euler's φ(12))
print(sp.n_order(2, 7))            # 3  (multiplicative order of 2 mod 7)

# Combinatorics
print(sp.factorial(10))            # 3628800
print(sp.binomial(10, 3))          # 120  C(10,3)
print(sp.catalan(5))               # 42
print(sp.fibonacci(10))            # 55
print(sp.lucas(10))                # 123

# Symbolic combinatorics
print(sp.binomial(n, k))                      # binomial(n, k)
print(sp.expand_func(sp.binomial(n, 3)))      # n*(n-1)*(n-2)/6
print(sp.combsimp(sp.factorial(n) / sp.factorial(n - 2)))  # n*(n-1)
```

---

## Set Theory

SymPy has a full symbolic set library supporting finite sets, intervals, and compound sets.

```python
from sympy import (FiniteSet, Interval, Union, Intersection,
                   Complement, ProductSet, ImageSet, S, Lambda, oo)

x = sp.Symbol("x", real=True)
n = sp.Symbol("n", integer=True)

# Finite sets
A = FiniteSet(1, 2, 3, 4, 5)
B = FiniteSet(3, 4, 5, 6, 7)

print(A | B)                    # {1, 2, 3, 4, 5, 6, 7}  (union)
print(A & B)                    # {3, 4, 5}  (intersection)
print(A - B)                    # {1, 2}  (difference)
print(A ^ B)                    # {1, 2, 6, 7}  (symmetric difference)
print(3 in A)                   # True
print(A.is_subset(A | B))       # True

# Intervals
I1 = Interval(0, 5)                      # [0, 5]  closed
I2 = Interval(3, 8, left_open=True)      # (3, 8]
I3 = Interval.open(1, 4)                 # (1, 4)
I4 = Interval.Ropen(0, 1)               # [0, 1)
I5 = Interval.Lopen(0, 1)               # (0, 1]

print(I1 & I2)                  # (3, 5]
print(I1 | I2)                  # [0, 8]
print(2.5 in I1)                # True

# Special built-in sets
print(S.Reals)                  # ℝ
print(S.Integers)               # ℤ
print(S.Naturals)               # ℕ (positive integers)
print(S.Naturals0)              # ℕ₀ (non-negative integers)
print(S.Rationals)              # ℚ
print(S.Complexes)              # ℂ
print(S.EmptySet)               # ∅

# ImageSet — set defined by a function applied to another set
evens = ImageSet(Lambda(n, 2*n), S.Integers)  # all even integers
print(4 in evens)               # True
print(3 in evens)               # False

# Cartesian product
C = ProductSet(FiniteSet(1, 2), FiniteSet("a", "b"))
print(list(C))                  # all (element, element) pairs
```

---

## Logic & Boolean Algebra

- `sp.And(*args)`, `sp.Or(*args)`, `sp.Not(arg)`, `sp.Xor(*args)`: Boolean connectives.
- `sp.Implies(p, q)`: logical implication p → q.
- `sp.Equivalent(p, q)`: logical equivalence p ↔ q.
- `sp.satisfiable(expr)`: checks satisfiability; returns a satisfying assignment or `False`.
- `sp.to_cnf(expr)` / `sp.to_dnf(expr)`: converts to conjunctive / disjunctive normal form.

```python
from sympy.logic.boolalg import And, Or, Not, Xor, Implies, to_cnf, to_dnf
from sympy.logic.inference import satisfiable
from sympy.abc import p, q, r

# Build boolean expressions
expr = And(p, Or(q, r))
print(expr)                      # p & (q | r)
print(Not(expr))                 # ~p | (~q & ~r)
print(Implies(p, q))             # Implies(p, q)

# Evaluate with specific truth values
print(expr.subs([(p, True), (q, False), (r, True)]))  # True

# Normal forms
print(to_cnf(p | (q & r)))       # (p | q) & (p | r)
print(to_dnf(p & (q | r)))       # (p & q) | (p & r)

# Satisfiability
print(satisfiable(p & Not(p)))   # False  (contradiction)
print(satisfiable(p | Not(p)))   # {p: True}  (tautology)
print(satisfiable(p & q))        # {p: True, q: True}
```

---

## Piecewise Functions

- `sp.Piecewise(*args)`: creates a piecewise-defined function.
  - `*args`: pairs of `(expression, condition)`. The last condition is typically `True` as the catch-all default.

```python
x = sp.Symbol("x", real=True)

# f(x) = −x for x < 0, x² for 0 ≤ x < 2, 4 for x ≥ 2
f = sp.Piecewise(
    (-x,    x < 0),
    (x**2,  x < 2),
    (4,     True)      # default case
)

print(f.subs(x, -3))   # 3
print(f.subs(x, 1))    # 1
print(f.subs(x, 5))    # 4

# Differentiate piece-by-piece
print(sp.diff(f, x))   # Piecewise((-1, x<0), (2x, x<2), (0, True))

# Integrate piece-by-piece
print(sp.integrate(f, (x, -1, 3)))

# Built-in step and delta functions
H = sp.Heaviside(x)
print(H.subs(x, -1))   # 0
print(H.subs(x, 1))    # 1
print(H.subs(x, 0))    # 1/2  (H(0) = 1/2 by convention)

delta = sp.DiracDelta(x)
print(sp.integrate(delta, (x, -sp.oo, sp.oo)))   # 1
```

---

## Summation & Products

- `sp.summation(f, (n, a, b))`: evaluates $\sum_{n=a}^{b} f(n)$ symbolically.
  - `f`: summand expression.
  - `(n, a, b)`: index variable and bounds (`sp.oo` allowed).

- `sp.Sum(f, (n, a, b))`: unevaluated (lazy) sum for display or manipulation.

- `sp.product(f, (n, a, b))`: evaluates $\prod_{n=a}^{b} f(n)$.

- `sp.Product(f, (n, a, b))`: unevaluated product.

```python
n, k = sp.symbols("n k", integer=True, positive=True)
x = sp.Symbol("x")

# Finite sums
print(sp.summation(n, (n, 1, 10)))            # 55
print(sp.summation(n**2, (n, 1, 10)))         # 385
print(sp.summation(n**2, (n, 1, k)))          # k*(k+1)*(2k+1)/6

# Infinite series — closed forms
print(sp.summation(1/n**2, (n, 1, sp.oo)))    # pi²/6  (Basel problem)
print(sp.summation(x**n / sp.factorial(n), (n, 0, sp.oo)))   # exp(x)

# Products
print(sp.product(n, (n, 1, 5)))               # 120  (= 5!)
print(sp.product(1 - 1/n**2, (n, 2, sp.oo))) # 1/2

# Unevaluated form
S = sp.Sum(n**2, (n, 1, k))
print(S)           # Sum(n², (n, 1, k))
print(S.doit())    # k*(k+1)*(2k+1)/6

# Double sum
print(sp.summation(n*k, (n, 1, 3), (k, 1, 3)))  # 36
```

---

## Special Functions

```python
x, n = sp.symbols("x n")

# Error function
print(sp.erf(x))                        # erf(x)
print(sp.erfc(x))                       # 1 - erf(x)
print(sp.erf(0))                        # 0
print(sp.erf(sp.oo))                    # 1

# Gamma and relatives
print(sp.gamma(n))                      # Γ(n) — generalises factorial: Γ(n+1) = n!
print(sp.gamma(sp.Rational(1, 2)))      # sqrt(pi)
print(sp.factorial2(7))                 # 7!! = 7·5·3·1 = 105
print(sp.beta(x, n))                    # B(x,n) = Γ(x)Γ(n)/Γ(x+n)
print(sp.digamma(x))                    # ψ(x) = Γ'(x)/Γ(x)

# Bessel functions
print(sp.besselj(n, x))                 # J_n(x)  first kind
print(sp.bessely(n, x))                 # Y_n(x)  second kind
print(sp.besseli(n, x))                 # I_n(x)  modified first kind
print(sp.besselk(n, x))                 # K_n(x)  modified second kind

# Orthogonal polynomials
print(sp.legendre(3, x))                # P_3(x) = (5x³ - 3x)/2
print(sp.chebyshevt(3, x))             # T_3(x) = 4x³ - 3x

# Riemann zeta function
print(sp.zeta(2))                       # π²/6
print(sp.zeta(4))                       # π⁴/90

# Hypergeometric
print(sp.hyper([1, 1], [2], x))        # ₂F₁(1,1;2;x) = -log(1-x)/x
```

---

## Transforms

- `sp.laplace_transform(f, t, s, noconds=True)`: Laplace transform $\mathcal{L}\{f(t)\} = F(s)$.
  - `noconds=True`: suppresses the convergence condition in the return value.
- `sp.inverse_laplace_transform(F, s, t)`: inverse Laplace transform.
- `sp.fourier_transform(f, x, k)`: Fourier transform.
- `sp.inverse_fourier_transform(F, k, x)`: inverse Fourier transform.

```python
t, s = sp.symbols("t s", positive=True)
x, k = sp.symbols("x k", real=True)

# Laplace transforms
print(sp.laplace_transform(sp.exp(-t), t, s, noconds=True))    # 1/(s+1)
print(sp.laplace_transform(sp.sin(t), t, s, noconds=True))     # 1/(s²+1)
print(sp.laplace_transform(t**3, t, s, noconds=True))          # 6/s⁴
print(sp.laplace_transform(t*sp.exp(-2*t), t, s, noconds=True))  # 1/(s+2)²

# Inverse Laplace
print(sp.inverse_laplace_transform(1/(s+1), s, t))    # exp(-t)*Heaviside(t)
print(sp.inverse_laplace_transform(s/(s**2+1), s, t)) # cos(t)*Heaviside(t)

# Fourier transform
f = sp.exp(-x**2)
print(sp.fourier_transform(f, x, k))   # sqrt(pi)*exp(-pi²k²)

# Inverse Fourier
F = sp.fourier_transform(sp.exp(-x**2), x, k)
print(sp.inverse_fourier_transform(F, k, x))   # exp(-x²)
```

---

## Probability & Statistics (`sympy.stats`)

SymPy can work with probability distributions symbolically, computing exact PDFs, CDFs, and expectations.

- `Normal(name, mean, std)`: normal distribution N(μ, σ).
- `Exponential(name, rate)`: exponential distribution with rate λ.
- `Uniform(name, left, right)`: uniform distribution on [a, b].
- `Binomial(name, n, p)`: binomial distribution B(n, p).
- `Poisson(name, lam)`: Poisson distribution with rate λ.
- `E(expr, condition=None)`: expected value.
- `variance(X)`: variance.
- `P(condition, given=None)`: probability of a condition (or conditional probability).
- `density(X)(x)`: probability density / mass function evaluated at `x`.
- `cdf(X)(x)`: cumulative distribution function evaluated at `x`.

```python
from sympy.stats import (Normal, Exponential, Uniform, Binomial, Poisson,
                          E, variance, std, P, density, cdf)

x, mu, sigma = sp.symbols("x mu sigma", real=True, positive=True)

# Standard normal N(0, 1)
X = Normal("X", 0, 1)
print(E(X))                           # 0
print(variance(X))                    # 1
print(density(X)(x))                  # sqrt(2)*exp(-x²/2)/(2*sqrt(pi))
print(cdf(X)(x))                      # erf(sqrt(2)*x/2)/2 + 1/2

# Probabilities
print(P(X > 0))                       # 1/2
print(P(X > 1).evalf())               # 0.158655...  (right tail)

# Conditional probability
print(P(X > 1, X > 0))               # P(X > 1 | X > 0)

# Parametric normal N(μ, σ)
Y = Normal("Y", mu, sigma)
print(E(Y))                           # mu
print(variance(Y))                    # sigma²

# Exponential with rate λ = 1/2
T = Exponential("T", sp.Rational(1, 2))
print(E(T))                           # 2
print(density(T)(x))                  # exp(-x/2)/2  for x ≥ 0

# Uniform U(0, 1)
U = Uniform("U", 0, 1)
print(E(U))                           # 1/2
print(variance(U))                    # 1/12

# Binomial B(10, 1/2)
B = Binomial("B", 10, sp.Rational(1, 2))
print(E(B))                           # 5
print(variance(B))                    # 5/2

# Poisson with λ = 3
N = Poisson("N", 3)
print(E(N))                           # 3
print(density(N)(x))                  # 3**x * exp(-3) / factorial(x)
```

---

## Numerical Mathematics

- `expr.evalf(n=15, subs=None)`: evaluates to an `n`-digit float.
- `sp.N(expr, n=15)`: alias for `evalf`.
- `sp.lambdify(args, expr, modules)`: compiles to a fast callable (see Substitution & Evaluation).
- `sp.nsolve(f, x, x0)`: numerical Newton-method root finding.
- `sp.Integral(...).evalf()`: numerically evaluates a definite integral that has no closed form.

```python
import numpy as np
x = sp.Symbol("x")

# Arbitrary-precision arithmetic
print(sp.pi.evalf(100))          # 100 digits of π
print(sp.E.evalf(100))           # 100 digits of e
print(sp.sqrt(2).evalf(50))      # 50 digits of √2
print(sp.zeta(3).evalf(30))      # Apéry's constant to 30 digits

# lambdify — NumPy-speed evaluation over arrays
f_sym = sp.sin(x**2) + sp.exp(-x)
f_num = sp.lambdify(x, f_sym, modules="numpy")
xs = np.linspace(0, 5, 1000)
ys = f_num(xs)                   # vectorised — no Python loop

# Rotation matrix evaluated numerically
A_sym = sp.Matrix([[sp.cos(x), -sp.sin(x)], [sp.sin(x), sp.cos(x)]])
A_num = sp.lambdify(x, A_sym, modules="numpy")
print(A_num(np.pi / 4))          # 2×2 NumPy array

# Numerical root finding
print(sp.nsolve(sp.cos(x) - x, x, 1))     # 0.739085...  (Dottie number)
print(sp.nsolve(sp.exp(x) + x, x, -1))    # -0.567143...

# Numerical integration when no closed form exists
I = sp.Integral(sp.sin(x) / (1 + x**3), (x, 0, sp.oo))
print(I.evalf())                 # numeric result
```

---

## Printing & Output Formatting

- `sp.pprint(expr, use_unicode=True)`: pretty-prints with 2D math notation in the terminal.
- `sp.latex(expr)`: returns a LaTeX string of the expression.
- `sp.mathml(expr)`: returns a MathML representation.
- `sp.init_printing(use_unicode=True)`: configures default rendering for the session (essential in Jupyter).

```python
x = sp.Symbol("x")

expr = sp.Integral(sp.sqrt(1/x), x)

sp.pprint(expr)
# ⌠
# ⎮   1
# ⎮  ─── dx
# ⎮  √x
# ⌡

print(sp.latex(expr))
# \int \frac{1}{\sqrt{x}}\, dx

print(sp.latex(sp.Matrix([[1, 2], [3, 4]])))
# \left[\begin{matrix}1 & 2\\3 & 4\end{matrix}\right]

print(sp.latex(sp.Rational(1, 3)))    # \frac{1}{3}

# In Jupyter — run once at the start of the notebook
sp.init_printing()

# Inspect the internal expression tree
print(sp.srepr(x**2 + 1))
# Add(Pow(Symbol('x'), Integer(2)), Integer(1))
```

---

## Plotting

SymPy provides a built-in plotting module that wraps Matplotlib.

- `sp.plot(*args, show=True, **kwargs)`: plots one or more expressions over an interval.
  - `*args`: `expr` alone (uses default range), or `(expr, (x, a, b))` pairs.
  - `show`: displays the plot immediately if `True`.
  - `xlabel`, `ylabel`, `title`, `legend`: labels.

- `sp.plot_parametric(expr_x, expr_y, range, **kwargs)`: 2D parametric plot.

- `sp.plot3d(expr, range_x, range_y, **kwargs)`: 3D surface plot.

- `sp.plot3d_parametric_line(x_e, y_e, z_e, range, **kwargs)`: 3D parametric curve.

```python
x, t = sp.symbols("x t", real=True)

# Single function
sp.plot(x**2, (x, -5, 5), title="Parabola", ylabel="y")

# Multiple functions on one axes
sp.plot(
    sp.sin(x), sp.cos(x),
    (x, -2*sp.pi, 2*sp.pi),
    legend=True, title="sin vs cos"
)

# Combine two separately created plots
p1 = sp.plot(sp.sin(x), show=False)
p2 = sp.plot(sp.cos(x), show=False)
p1.extend(p2)
p1.show()

# Parametric plot — circle
sp.plot_parametric(sp.cos(t), sp.sin(t), (t, 0, 2*sp.pi), title="Circle")

# 3D surface
sp.plot3d(sp.sin(x) * sp.cos(t), (x, -3, 3), (t, -3, 3))

# Change line colour
p = sp.plot(x**2, (x, -2, 2), show=False)
p[0].line_color = "red"
p.show()
```

