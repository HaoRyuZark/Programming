# Scikit-Learn

Scikit-learn is the standard Python machine learning library. It provides a unified API for supervised learning (regression, classification), unsupervised learning 
(clustering, dimensionality reduction), model selection, and preprocessing.

## Import

```python
import numpy as np
import pandas as pd
from sklearn import ...
```

---

## Estimator API

Every scikit-learn object follows the same interface:

- `.fit(X, y=None)`: trains the model on data `X` (and labels `y` for supervised models). Always returns `self`.
- `.predict(X)`: returns predicted labels or values for `X`.
- `.predict_proba(X)`: returns class probabilities (classifiers that support it).
- `.transform(X)`: applies a learned transformation (preprocessors, decomposers).
- `.fit_transform(X, y=None)`: equivalent to `.fit(X).transform(X)` but often more efficient.
- `.score(X, y)`: returns the default performance metric (R² for regressors, accuracy for classifiers).
- `.get_params(deep=True)`: returns a dict of the estimator's parameters.
- `.set_params(**params)`: sets parameters and returns `self`.
- `.inverse_transform(X)`: reverses a transformation (where supported).

> **Convention**: capital `X` denotes the feature matrix (shape `(n_samples, n_features)`); lowercase `y` denotes the target vector (shape `(n_samples,)`).

---

## Datasets & Data Loading

### Built-in Toy Datasets

- `load_iris(return_X_y=False, as_frame=False)`: 150 samples, 4 features, 3 classes (flower species).
- `load_digits(n_class=10, return_X_y=False)`: 1797 samples, 64 features, handwritten digit images.
- `load_wine(return_X_y=False)`: 178 samples, 13 features, 3 classes (wine origin).
- `load_breast_cancer(return_X_y=False)`: 569 samples, 30 features, binary classification.
- `load_diabetes(return_X_y=False)`: 442 samples, 10 features, continuous regression target.
- `load_boston()`: **deprecated** — do not use.

All `load_*` functions return a `Bunch` object with:
- `.data`: feature matrix (NumPy array).
- `.target`: target vector.
- `.feature_names`: list of feature names.
- `.target_names`: list of class names (classifiers only).
- `.DESCR`: dataset description string.
- Pass `return_X_y=True` to get `(X, y)` directly.
- Pass `as_frame=True` to get a pandas DataFrame.

### Synthetic Dataset Generators

- `make_classification(n_samples=100, n_features=20, n_informative=2, n_redundant=2, n_classes=2, class_sep=1.0, random_state=None)`: generates a random classification dataset.
  - `n_informative`: features with actual predictive power.
  - `n_redundant`: features that are linear combinations of informative ones.
  - `class_sep`: larger = easier classification.

- `make_regression(n_samples=100, n_features=100, n_informative=10, noise=0.0, random_state=None)`: generates a regression dataset.
  - `noise`: Gaussian noise standard deviation added to targets.

- `make_blobs(n_samples=100, n_features=2, centers=3, cluster_std=1.0, random_state=None)`: isotropic Gaussians; good for clustering experiments.

- `make_moons(n_samples=100, noise=0.1, random_state=None)`: two interleaving half-circles.

- `make_circles(n_samples=100, noise=0.05, factor=0.8, random_state=None)`: concentric circles.

```python
from sklearn.datasets import (load_iris, load_diabetes, load_breast_cancer,
                               make_classification, make_regression,
                               make_blobs, make_moons)

# Toy datasets
X, y = load_iris(return_X_y=True)
print("Iris shape:", X.shape, y.shape)   # (150, 4) (150,)

df_iris = load_iris(as_frame=True)
print(df_iris.frame.head())

# Synthetic classification
X_clf, y_clf = make_classification(n_samples=1000, n_features=20,
                                    n_informative=5, n_redundant=5,
                                    n_classes=3, random_state=42)

# Synthetic regression
X_reg, y_reg = make_regression(n_samples=500, n_features=15,
                                n_informative=8, noise=10.0, random_state=42)

# Clustering / non-linear data
X_blobs, y_blobs = make_blobs(n_samples=300, centers=4, cluster_std=0.8, random_state=0)
X_moons, y_moons = make_moons(n_samples=300, noise=0.1, random_state=0)
```

### Train/Test Split

- `train_test_split(*arrays, test_size=None, train_size=None, random_state=None, shuffle=True, stratify=None)`: splits arrays into random train and test subsets.
  - `*arrays`: any number of arrays with the same first dimension (X, y, weights, …).
  - `test_size`: fraction (0–1) or absolute integer count.
  - `train_size`: alternative to `test_size`; both can be set.
  - `random_state`: seed for reproducibility.
  - `shuffle`: if `False`, splits without shuffling.
  - `stratify`: array-like — splits preserve the class proportion of `stratify` in both sets.

```python
from sklearn.model_selection import train_test_split

X_train, X_test, y_train, y_test = train_test_split(
    X_clf, y_clf, test_size=0.2, random_state=42, stratify=y_clf
)
print("Train:", X_train.shape, "Test:", X_test.shape)
```

---

## Preprocessing (`sklearn.preprocessing`)

### Scalers

- `StandardScaler(copy=True, with_mean=True, with_std=True)`: standardises features to zero mean and unit variance (z-score). Sensitive to outliers.
  - `.mean_`, `.scale_`: learned statistics.

- `MinMaxScaler(feature_range=(0, 1), copy=True)`: scales each feature to a given range (default [0, 1]). Sensitive to outliers.
  - `.data_min_`, `.data_max_`, `.data_range_`.

- `RobustScaler(quantile_range=(25.0, 75.0), with_centering=True, with_scaling=True)`: uses median and IQR — robust to outliers.

- `MaxAbsScaler()`: scales by the maximum absolute value; preserves sparsity, does not centre.

- `Normalizer(norm='l2')`: scales **each sample** (row) to unit norm. Does not touch columns.
  - `norm`: `'l1'`, `'l2'`, `'max'`.

- `QuantileTransformer(n_quantiles=1000, output_distribution='uniform', random_state=None)`: maps features to a uniform or normal distribution using empirical quantiles. Very robust to outliers.
  - `output_distribution`: `'uniform'` or `'normal'`.

- `PowerTransformer(method='yeo-johnson', standardize=True)`: applies a power transform to make data more Gaussian-like. Box-Cox requires positive data; Yeo-Johnson works for any values.

> **Rule of thumb**: use `StandardScaler` as default, `RobustScaler` with many outliers, `QuantileTransformer` / `PowerTransformer` when normality is required (e.g., linear models).

### Encoders

- `OneHotEncoder(categories='auto', drop=None, sparse_output=True, handle_unknown='error', dtype=float)`: encodes categorical features as binary indicator columns.
  - `drop`: `None`, `'first'` (avoids multicollinearity), or `'if_binary'`.
  - `handle_unknown`: `'error'` or `'ignore'` (sets unknown categories to all zeros).
  - `.categories_`: list of arrays with the categories per feature.

- `OrdinalEncoder(categories='auto', handle_unknown='error', unknown_value=None)`: encodes categorical features as integers `0, 1, …, n-1`.

- `LabelEncoder()`: encodes **target labels** (1D) as integers. Not for features.

- `LabelBinarizer(neg_label=0, pos_label=1, sparse_output=False)`: binarizes labels for multi-class problems (one-vs-rest).

### Imputation

- `SimpleImputer(missing_values=nan, strategy='mean', fill_value=None, add_indicator=False)`: fills in missing values.
  - `strategy`: `'mean'`, `'median'`, `'most_frequent'`, `'constant'` (uses `fill_value`).
  - `add_indicator`: if `True`, appends a binary column for each feature that had missing values.

- `KNNImputer(n_neighbors=5, weights='uniform', metric='nan_euclidean')`: imputes using the mean of k nearest neighbours.

- `IterativeImputer(estimator=None, max_iter=10, random_state=None)`: multivariate imputation modelling each feature with missing values as a function of all others. Experimental.

### Feature Construction

- `PolynomialFeatures(degree=2, interaction_only=False, include_bias=True)`: generates polynomial and interaction features.
  - `interaction_only`: if `True`, only produces interaction terms (no `x²`, `y²`).
  - `include_bias`: if `True`, adds a column of ones.
  - `.get_feature_names_out()`: returns names of generated features.

- `FunctionTransformer(func=None, inverse_func=None, validate=False, kw_args=None)`: wraps an arbitrary function as a transformer. Useful in pipelines.

- `Binarizer(threshold=0.0)`: maps features to `0` or `1` based on a threshold.

- `KBinsDiscretizer(n_bins=5, encode='onehot', strategy='quantile', dtype=None)`: discretises continuous features into bins.
  - `strategy`: `'uniform'`, `'quantile'`, `'kmeans'`.
  - `encode`: `'onehot'`, `'onehot-dense'`, `'ordinal'`.

### ColumnTransformer

- `ColumnTransformer(transformers, remainder='drop', sparse_threshold=0.3, n_jobs=None, transformer_weights=None, verbose_feature_names_out=True)`: applies different transformers to different columns.
  - `transformers`: list of `(name, transformer, columns)` triples. `columns` can be a list of indices, names, or a boolean mask.
  - `remainder`: what to do with untransformed columns — `'drop'`, `'passthrough'`, or a transformer.

```python
from sklearn.preprocessing import (StandardScaler, MinMaxScaler, RobustScaler,
                                    OneHotEncoder, OrdinalEncoder, LabelEncoder,
                                    PolynomialFeatures, PowerTransformer,
                                    QuantileTransformer, Normalizer)
from sklearn.impute import SimpleImputer, KNNImputer
from sklearn.compose import ColumnTransformer
import numpy as np

# --- Scalers ---
X = np.array([[1.0, 100.0], [2.0, 200.0], [3.0, 300.0], [100.0, 10.0]])

ss = StandardScaler()
X_std = ss.fit_transform(X)
print("Mean after StandardScaler:", X_std.mean(axis=0))  # ≈ [0, 0]
print("Std after StandardScaler:", X_std.std(axis=0))    # ≈ [1, 1]
print("Learned mean:", ss.mean_)

mm = MinMaxScaler(feature_range=(0, 1))
X_mm = mm.fit_transform(X)
print("MinMax range:", X_mm.min(axis=0), X_mm.max(axis=0))

rb = RobustScaler()
X_rb = rb.fit_transform(X)   # robust to the outlier at row 3

# --- Encoders ---
cats = np.array([['cat'], ['dog'], ['cat'], ['bird'], ['dog']])
enc = OneHotEncoder(sparse_output=False)
X_enc = enc.fit_transform(cats)
print("One-hot categories:", enc.categories_)
print("Encoded:\n", X_enc)

ord_enc = OrdinalEncoder()
X_ord = ord_enc.fit_transform(cats)
print("Ordinal:", X_ord.ravel())

le = LabelEncoder()
y_enc = le.fit_transform(['cat', 'dog', 'bird', 'cat'])
print("Labels:", y_enc)                # [1, 2, 0, 1]
print("Classes:", le.classes_)         # ['bird', 'cat', 'dog']

# --- Imputation ---
X_nan = np.array([[1., 2.], [np.nan, 4.], [5., np.nan], [7., 8.]])
imputer = SimpleImputer(strategy='mean')
X_imp = imputer.fit_transform(X_nan)
print("Imputed:\n", X_imp)

knn_imp = KNNImputer(n_neighbors=2)
X_knn = knn_imp.fit_transform(X_nan)

# --- Polynomial features ---
poly = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly.fit_transform(np.array([[1., 2.], [3., 4.]]))
print("Poly feature names:", poly.get_feature_names_out())

# --- ColumnTransformer ---
import pandas as pd
df = pd.DataFrame({
    'age':    [25., 30., np.nan, 45.],
    'salary': [50000., 60000., 70000., 80000.],
    'dept':   ['eng', 'hr', 'eng', 'fin']
})

ct = ColumnTransformer([
    ('num_scale', StandardScaler(), ['age', 'salary']),
    ('cat_enc',   OneHotEncoder(handle_unknown='ignore'), ['dept']),
], remainder='drop')

# Note: fit on training data only, then transform train and test
X_ct = ct.fit_transform(df)
print("ColumnTransformer output shape:", X_ct.shape)   # (4, 7): 2 scaled + 3 OHE + 2 imputed
```

---

## Pipelines (`sklearn.pipeline`)

A `Pipeline` chains preprocessing steps and a final estimator. Only the last step can be an estimator; all others must be transformers (implement `fit` and `transform`).

- `Pipeline(steps, memory=None, verbose=False)`: constructs a pipeline.
  - `steps`: list of `(name, estimator)` tuples. Names must be unique and contain no `__`.
  - `memory`: path or `joblib.Memory` object for caching fitted transformers.
  - Accessing steps: `pipe['name']` or `pipe.named_steps['name']`.
  - Parameters follow the `step__param` naming convention.

- `make_pipeline(*steps, memory=None, verbose=False)`: convenience constructor that auto-names steps from their class names (lowercase).

- `Pipeline.fit(X, y=None)`: calls `fit_transform` on all but the last step, then `fit` on the last.
- `Pipeline.predict(X)`: calls `transform` on all but the last step, then `predict`.
- `Pipeline.score(X, y)`: calls `transform`, then `score` on the final estimator.
- `Pipeline.set_params(**params)`: sets parameters using `step__param` notation.

```python
from sklearn.pipeline import Pipeline, make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.linear_model import LogisticRegression, Ridge
from sklearn.neighbors import KNeighborsRegressor
from sklearn.decomposition import PCA
from sklearn.model_selection import train_test_split
from sklearn.datasets import load_iris, load_diabetes

# --- Simple pipeline ---
X, y = load_iris(return_X_y=True)
X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

pipe = Pipeline([
    ('scaler', StandardScaler()),
    ('clf',    LogisticRegression(max_iter=200, C=1.0))
])
pipe.fit(X_train, y_train)
print("Test accuracy:", pipe.score(X_test, y_test))

# Access intermediate output
X_scaled = pipe[:-1].transform(X_test)   # apply all but last step

# Change parameters after creation
pipe.set_params(clf__C=0.1)

# make_pipeline — auto-names steps
pipe2 = make_pipeline(StandardScaler(), PCA(n_components=2), LogisticRegression())
pipe2.fit(X_train, y_train)

# --- Regression pipeline ---
X_r, y_r = load_diabetes(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X_r, y_r, test_size=0.2, random_state=42)

pipe_reg = Pipeline([
    ('scaler', StandardScaler()),
    ('model',  KNeighborsRegressor(n_neighbors=5))
])
pipe_reg.fit(X_tr, y_tr)
print("KNN R²:", round(pipe_reg.score(X_te, y_te), 4))
print("All params:", pipe_reg.get_params())
# step params: 'model__n_neighbors', 'scaler__with_mean', etc.
```

---

## Model Selection & Cross-Validation

### Cross-Validation

- `cross_val_score(estimator, X, y=None, scoring=None, cv=5, n_jobs=None)`: evaluates an estimator using k-fold cross-validation.
  - `scoring`: metric string (`'accuracy'`, `'f1'`, `'r2'`, `'neg_mean_squared_error'`, …). See the scoring glossary for full list.
  - `cv`: number of folds (int), or a CV splitter object.
  - `n_jobs`: parallel jobs (`-1` = all cores).
  - Returns array of scores for each fold.

- `cross_validate(estimator, X, y=None, scoring=None, cv=5, return_train_score=False, n_jobs=None)`: like `cross_val_score` but also reports fit and score times and optionally train scores.

- `cross_val_predict(estimator, X, y=None, cv=5, method='predict', n_jobs=None)`: generates out-of-fold predictions — useful for stacking and diagnostic plots.

### CV Splitters

- `KFold(n_splits=5, shuffle=False, random_state=None)`: basic k-fold.
- `StratifiedKFold(n_splits=5, shuffle=False, random_state=None)`: preserves class proportions in each fold.
- `RepeatedKFold(n_splits=5, n_repeats=10, random_state=None)`: repeats k-fold multiple times for more stable estimates.
- `RepeatedStratifiedKFold(n_splits=5, n_repeats=10, random_state=None)`: stratified + repeated.
- `ShuffleSplit(n_splits=10, test_size=0.1, random_state=None)`: random train/test splits (not exhaustive).
- `StratifiedShuffleSplit(n_splits=10, test_size=0.1, random_state=None)`: stratified random splits.
- `LeaveOneOut()`: leave-one-out CV. Expensive for large datasets.
- `GroupKFold(n_splits=5)`: ensures that the same group does not appear in both train and test.
- `TimeSeriesSplit(n_splits=5, gap=0, max_train_size=None)`: sequential splits for time series — test always follows train.

### Hyperparameter Tuning

- `GridSearchCV(estimator, param_grid, scoring=None, cv=5, refit=True, return_train_score=False, n_jobs=None, verbose=0)`: exhaustive search over a parameter grid.
  - `param_grid`: dict or list of dicts with parameter names as keys and lists of values. For pipelines, use `step__param`.
  - `refit`: if `True` (default), retrains the best estimator on the full dataset.
  - After fitting: `.best_params_`, `.best_estimator_`, `.best_score_`, `.cv_results_`.

- `RandomizedSearchCV(estimator, param_distributions, n_iter=10, scoring=None, cv=5, refit=True, random_state=None, n_jobs=None)`: samples `n_iter` parameter combinations at random. Efficient for large search spaces.
  - `param_distributions`: dict mapping parameter names to distributions or lists. Use `scipy.stats` distributions (e.g., `stats.randint(1, 11)`).

- `HalvingGridSearchCV(estimator, param_grid, factor=3, resource='n_samples', cv=5)`: successive halving — starts with all candidates on a small budget, progressively allocates more to the best. Much faster than GridSearch.

- `HalvingRandomSearchCV(estimator, param_distributions, n_candidates='exhaust', factor=3, resource='n_samples')`: random search with successive halving.

```python
from sklearn.model_selection import (cross_val_score, cross_validate, cross_val_predict,
                                      KFold, StratifiedKFold, TimeSeriesSplit,
                                      GridSearchCV, RandomizedSearchCV)
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.neighbors import KNeighborsClassifier, KNeighborsRegressor
from sklearn.datasets import load_iris, load_diabetes
from scipy.stats import randint, uniform
import pandas as pd
import numpy as np

X, y = load_iris(return_X_y=True)

# --- Cross-val score ---
pipe = Pipeline([('scaler', StandardScaler()), ('clf', KNeighborsClassifier())])
scores = cross_val_score(pipe, X, y, cv=5, scoring='accuracy')
print(f"5-fold accuracy: {scores.mean():.4f} ± {scores.std():.4f}")

# Multiple metrics
cv_res = cross_validate(pipe, X, y, cv=5,
                         scoring=['accuracy', 'f1_macro'],
                         return_train_score=True)
print("Test accuracy:", cv_res['test_accuracy'].mean())
print("Train accuracy:", cv_res['train_accuracy'].mean())

# Out-of-fold predictions (for diagnostic plots)
y_oof = cross_val_predict(pipe, X, y, cv=5, method='predict_proba')
print("OOF proba shape:", y_oof.shape)   # (150, 3)

# --- Stratified k-fold ---
skf = StratifiedKFold(n_splits=5, shuffle=True, random_state=42)
for fold, (tr, te) in enumerate(skf.split(X, y)):
    print(f"Fold {fold}: train={len(tr)}, test={len(te)}")

# --- GridSearchCV ---
X_r, y_r = load_diabetes(return_X_y=True)

pipe_r = Pipeline([
    ('scaler', StandardScaler()),
    ('model',  KNeighborsRegressor())
])
param_grid = {
    'model__n_neighbors': [3, 5, 7, 9, 11],
    'model__weights':     ['uniform', 'distance'],
    'scaler__with_std':   [True, False],
}
grid = GridSearchCV(pipe_r, param_grid, cv=5, scoring='r2',
                    refit=True, n_jobs=-1)
grid.fit(X_r, y_r)
print("Best params:", grid.best_params_)
print("Best CV R²:", round(grid.best_score_, 4))

# Full results as DataFrame
df_cv = pd.DataFrame(grid.cv_results_)
print(df_cv[['params', 'mean_test_score', 'std_test_score']].head())

# Use best estimator on new data
y_pred_best = grid.best_estimator_.predict(X_r[:5])

# --- RandomizedSearchCV ---
from sklearn.ensemble import RandomForestRegressor

param_dist = {
    'n_estimators':   randint(50, 300),
    'max_depth':      [None, 5, 10, 20],
    'max_features':   uniform(0.1, 0.9),
    'min_samples_split': randint(2, 20),
}
rnd = RandomizedSearchCV(RandomForestRegressor(random_state=0), param_dist,
                          n_iter=30, cv=5, scoring='r2',
                          n_jobs=-1, random_state=42)
rnd.fit(X_r, y_r)
print("RandomSearch best R²:", round(rnd.best_score_, 4))
```

---

## Linear Models (`sklearn.linear_model`)

### Regression

- `LinearRegression(fit_intercept=True, copy_X=True, n_jobs=None, positive=False)`: ordinary least-squares regression. No regularisation.
  - `.coef_`: weight vector.
  - `.intercept_`: bias term.

- `Ridge(alpha=1.0, fit_intercept=True, solver='auto', max_iter=None, tol=1e-4)`: L2-regularised OLS. Shrinks coefficients, never sets them to zero.
  - `alpha`: regularisation strength. Larger = more shrinkage.

- `Lasso(alpha=1.0, fit_intercept=True, max_iter=1000, tol=1e-4, selection='cyclic')`: L1-regularised OLS. Produces sparse models by driving some coefficients to exactly zero.

- `ElasticNet(alpha=1.0, l1_ratio=0.5, fit_intercept=True, max_iter=1000)`: combines L1 and L2. `l1_ratio=1` = Lasso; `l1_ratio=0` = Ridge.

- `RidgeCV(alphas=(0.1, 1.0, 10.0), cv=None, scoring=None)`: Ridge with built-in cross-validation over `alphas`. Very fast for a large grid.

- `LassoCV(alphas=None, cv=5, max_iter=1000, n_jobs=None)`: Lasso with built-in CV.

- `BayesianRidge(max_iter=300, tol=1e-3, alpha_1=1e-6, lambda_1=1e-6)`: Bayesian regularisation; estimates uncertainty in predictions.

- `HuberRegressor(epsilon=1.35, alpha=0.0001, max_iter=100)`: robust to outliers; uses Huber loss.

- `SGDRegressor(loss='squared_error', penalty='l2', alpha=0.0001, learning_rate='invscaling', max_iter=1000, random_state=None)`: stochastic gradient descent — scales to very large datasets.

### Classification

- `LogisticRegression(penalty='l2', C=1.0, solver='lbfgs', max_iter=100, multi_class='auto', class_weight=None, random_state=None)`: logistic regression for binary and multi-class classification.
  - `penalty`: `'l1'`, `'l2'` (default), `'elasticnet'`, `None`.
  - `C`: inverse of regularisation strength (larger C = less regularisation).
  - `solver`: `'lbfgs'` (default), `'liblinear'`, `'saga'`, `'sag'`, `'newton-cg'`. Use `'saga'` for L1 + large datasets.
  - `class_weight`: `None` or `'balanced'` or dict. `'balanced'` adjusts for class imbalance.
  - `.coef_`, `.intercept_`, `.classes_`.

- `SGDClassifier(loss='hinge', penalty='l2', alpha=0.0001, max_iter=1000, random_state=None)`: linear classifier via SGD. `loss='hinge'` = linear SVM; `loss='log_loss'` = logistic regression.
  - Scales to very large datasets.

- `RidgeClassifier(alpha=1.0, class_weight=None)`: ridge regression adapted for classification.

- `Perceptron(penalty=None, alpha=0.0001, max_iter=1000, random_state=None)`: classic single-layer perceptron.

- `PassiveAggressiveClassifier(C=1.0, max_iter=1000)`: online learning — good for streaming data.

```python
from sklearn.linear_model import (LinearRegression, Ridge, Lasso, ElasticNet,
                                   RidgeCV, LassoCV, HuberRegressor,
                                   LogisticRegression, SGDClassifier, RidgeClassifier)
from sklearn.datasets import load_diabetes, load_breast_cancer
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.metrics import r2_score, mean_squared_error, accuracy_score
import numpy as np

X_r, y_r = load_diabetes(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X_r, y_r, test_size=0.2, random_state=42)

# --- OLS ---
lr = make_pipeline(StandardScaler(), LinearRegression())
lr.fit(X_tr, y_tr)
print("OLS R²:", round(lr.score(X_te, y_te), 4))

# --- Ridge ---
ridge = make_pipeline(StandardScaler(), Ridge(alpha=1.0))
ridge.fit(X_tr, y_tr)
print("Ridge R²:", round(ridge.score(X_te, y_te), 4))

# RidgeCV — finds best alpha automatically
ridge_cv = make_pipeline(StandardScaler(), RidgeCV(alphas=np.logspace(-3, 3, 50), cv=5))
ridge_cv.fit(X_tr, y_tr)
print("Best alpha (RidgeCV):", ridge_cv['ridgecv'].alpha_)

# --- Lasso ---
lasso = make_pipeline(StandardScaler(), Lasso(alpha=0.1))
lasso.fit(X_tr, y_tr)
print("Lasso R²:", round(lasso.score(X_te, y_te), 4))
n_zero = np.sum(lasso['lasso'].coef_ == 0)
print(f"Lasso: {n_zero} of {X_r.shape[1]} features zeroed out")

# LassoCV — cross-validates alpha
lasso_cv = make_pipeline(StandardScaler(), LassoCV(cv=5, max_iter=5000))
lasso_cv.fit(X_tr, y_tr)
print("LassoCV best alpha:", round(lasso_cv['lassocv'].alpha_, 5))

# --- ElasticNet ---
en = make_pipeline(StandardScaler(), ElasticNet(alpha=0.1, l1_ratio=0.5))
en.fit(X_tr, y_tr)
print("ElasticNet R²:", round(en.score(X_te, y_te), 4))

# --- Huber (robust) ---
huber = make_pipeline(StandardScaler(), HuberRegressor(epsilon=1.35))
huber.fit(X_tr, y_tr)

# --- Classification ---
X_c, y_c = load_breast_cancer(return_X_y=True)
Xc_tr, Xc_te, yc_tr, yc_te = train_test_split(X_c, y_c, test_size=0.2,
                                                stratify=y_c, random_state=42)

log_reg = make_pipeline(StandardScaler(),
                         LogisticRegression(C=1.0, solver='lbfgs', max_iter=1000))
log_reg.fit(Xc_tr, yc_tr)
print("Logistic regression accuracy:", round(log_reg.score(Xc_te, yc_te), 4))
print("Coefficients shape:", log_reg['logisticregression'].coef_.shape)

# Probabilities
y_proba = log_reg.predict_proba(Xc_te)
print("Predicted probabilities (first 3):\n", y_proba[:3].round(3))

# class_weight='balanced' for imbalanced data
lr_bal = make_pipeline(StandardScaler(),
                        LogisticRegression(class_weight='balanced', max_iter=1000))
lr_bal.fit(Xc_tr, yc_tr)
```

---

## Support Vector Machines (`sklearn.svm`)

- `SVC(C=1.0, kernel='rbf', degree=3, gamma='scale', coef0=0.0, probability=False, class_weight=None, random_state=None)`: Support Vector Classifier.
  - `C`: regularisation — smaller = wider margin, more misclassification allowed.
  - `kernel`: `'linear'`, `'rbf'` (default), `'poly'`, `'sigmoid'`, `'precomputed'`.
  - `degree`: degree for polynomial kernel.
  - `gamma`: kernel coefficient for `'rbf'`, `'poly'`, `'sigmoid'`. `'scale'` = `1/(n_features * X.var())`; `'auto'` = `1/n_features`.
  - `probability`: if `True`, enables `predict_proba` (adds training overhead via cross-validation).
  - `.support_vectors_`: array of support vectors.

- `LinearSVC(C=1.0, penalty='l2', loss='squared_hinge', dual=True, max_iter=1000, class_weight=None)`: linear SVM via `liblinear`. Faster than `SVC(kernel='linear')` for large datasets.

- `SVR(kernel='rbf', C=1.0, epsilon=0.1, gamma='scale', degree=3)`: Support Vector Regressor.
  - `epsilon`: tube width — no penalty for errors within `epsilon` of the prediction.

- `LinearSVR(C=1.0, epsilon=0.0, max_iter=1000)`: linear SVR via `liblinear`.

- `NuSVC(nu=0.5, kernel='rbf', degree=3, gamma='scale')`: SVC with `nu` controlling the fraction of support vectors instead of `C`.

```python
from sklearn.svm import SVC, LinearSVC, SVR, LinearSVR
from sklearn.datasets import load_iris, load_diabetes
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
import numpy as np

X, y = load_iris(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, random_state=42)

# --- SVC with RBF kernel (default) ---
svc = make_pipeline(StandardScaler(), SVC(C=1.0, kernel='rbf', gamma='scale'))
svc.fit(X_tr, y_tr)
print("SVC (RBF) accuracy:", round(svc.score(X_te, y_te), 4))

# With probabilities
svc_prob = make_pipeline(StandardScaler(),
                          SVC(C=1.0, kernel='rbf', probability=True, random_state=42))
svc_prob.fit(X_tr, y_tr)
proba = svc_prob.predict_proba(X_te[:5])
print("SVC probabilities:\n", proba.round(3))

# --- Linear SVC (faster for large datasets) ---
lsvc = make_pipeline(StandardScaler(), LinearSVC(C=1.0, max_iter=5000))
lsvc.fit(X_tr, y_tr)
print("LinearSVC accuracy:", round(lsvc.score(X_te, y_te), 4))

# --- SVR ---
X_r, y_r = load_diabetes(return_X_y=True)
X_tr_r, X_te_r, y_tr_r, y_te_r = train_test_split(X_r, y_r, test_size=0.2, random_state=42)

svr = make_pipeline(StandardScaler(), SVR(C=10.0, epsilon=0.1, kernel='rbf'))
svr.fit(X_tr_r, y_tr_r)
print("SVR R²:", round(svr.score(X_te_r, y_te_r), 4))

# Support vectors
print("Number of support vectors:", svc['svc'].support_vectors_.shape[0])
```

---

## Decision Trees (`sklearn.tree`)

- `DecisionTreeClassifier(criterion='gini', max_depth=None, min_samples_split=2, min_samples_leaf=1, max_features=None, class_weight=None, random_state=None)`: CART decision tree for classification.
  - `criterion`: split quality measure — `'gini'` (default) or `'entropy'` (information gain).
  - `max_depth`: maximum tree depth. `None` = grow until leaves are pure (risk of overfitting).
  - `min_samples_split`: minimum samples required to split a node.
  - `min_samples_leaf`: minimum samples required in a leaf.
  - `max_features`: number/fraction of features considered per split. `'sqrt'`, `'log2'`, int, float, `None`.
  - `class_weight`: `None`, `'balanced'`, or dict.
  - `.feature_importances_`: impurity-based feature importances.

- `DecisionTreeRegressor(criterion='squared_error', max_depth=None, min_samples_split=2, min_samples_leaf=1, max_features=None, random_state=None)`: CART decision tree for regression.
  - `criterion`: `'squared_error'` (MSE), `'friedman_mse'`, `'absolute_error'`, `'poisson'`.

- `export_text(decision_tree, feature_names=None, max_depth=None)`: prints the tree as text.
- `plot_tree(decision_tree, feature_names=None, class_names=None, filled=True, ax=None)`: visualises the tree.

```python
from sklearn.tree import DecisionTreeClassifier, DecisionTreeRegressor, export_text, plot_tree
from sklearn.datasets import load_iris, load_diabetes
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
import matplotlib.pyplot as plt
import numpy as np

X, y = load_iris(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, random_state=42)
feat_names = load_iris().feature_names
class_names = load_iris().target_names

# --- Classifier ---
dt = DecisionTreeClassifier(max_depth=3, criterion='gini', random_state=42)
dt.fit(X_tr, y_tr)
print("DT accuracy:", round(dt.score(X_te, y_te), 4))
print("Feature importances:", np.round(dt.feature_importances_, 3))

# Text representation
print(export_text(dt, feature_names=list(feat_names)))

# Visualise (requires matplotlib)
fig, ax = plt.subplots(figsize=(14, 6))
plot_tree(dt, feature_names=feat_names, class_names=class_names,
          filled=True, ax=ax)
plt.show()

# --- Pruning: cost-complexity path ---
path = dt.cost_complexity_pruning_path(X_tr, y_tr)
alphas = path.ccp_alphas
print("Pruning alphas:", np.round(alphas[:5], 6))

# Find best alpha via cross-validation
from sklearn.model_selection import cross_val_score
best_alpha, best_score = 0, 0
for a in alphas[:-1]:
    dt_a = DecisionTreeClassifier(ccp_alpha=a, random_state=42)
    s = cross_val_score(dt_a, X_tr, y_tr, cv=5).mean()
    if s > best_score:
        best_score, best_alpha = s, a
print(f"Best alpha: {best_alpha:.5f}, CV score: {best_score:.4f}")

# --- Regressor ---
X_r, y_r = load_diabetes(return_X_y=True)
X_tr_r, X_te_r, y_tr_r, y_te_r = train_test_split(X_r, y_r, test_size=0.2, random_state=42)
dt_r = DecisionTreeRegressor(max_depth=4, min_samples_leaf=5, random_state=42)
dt_r.fit(X_tr_r, y_tr_r)
print("DT Regressor R²:", round(dt_r.score(X_te_r, y_te_r), 4))
```

---

## Nearest Neighbours (`sklearn.neighbors`)

- `KNeighborsClassifier(n_neighbors=5, weights='uniform', algorithm='auto', leaf_size=30, p=2, metric='minkowski', n_jobs=None)`: k-nearest-neighbour classifier.
  - `weights`: `'uniform'` (all neighbours equal) or `'distance'` (closer = more weight).
  - `algorithm`: `'auto'`, `'ball_tree'`, `'kd_tree'`, `'brute'`.
  - `p`: power of the Minkowski metric (`p=2` = Euclidean, `p=1` = Manhattan).
  - `metric`: any `scipy.spatial.distance` metric string.

- `KNeighborsRegressor(n_neighbors=5, weights='uniform', algorithm='auto', leaf_size=30, p=2, metric='minkowski', n_jobs=None)`: k-NN regressor (predicts the average of the k nearest neighbours' targets).

- `RadiusNeighborsClassifier(radius=1.0, weights='uniform', algorithm='auto', outlier_label=None)`: classifies using all neighbours within a fixed radius.

- `NearestNeighbors(n_neighbors=5, radius=1.0, algorithm='auto', leaf_size=30, metric='minkowski')`: unsupervised nearest-neighbour lookup (not a classifier).
  - `.fit(X)`: builds the index.
  - `.kneighbors(X, n_neighbors=None, return_distance=True)`: returns distances and indices of nearest neighbours.
  - `.radius_neighbors(X, radius=None)`: returns all neighbours within a radius.

```python
from sklearn.neighbors import KNeighborsClassifier, KNeighborsRegressor, NearestNeighbors
from sklearn.datasets import load_iris, load_diabetes
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
import numpy as np

X, y = load_iris(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, random_state=42)

# --- KNN Classifier ---
knn = make_pipeline(StandardScaler(), KNeighborsClassifier(n_neighbors=5, weights='distance'))
knn.fit(X_tr, y_tr)
print("KNN accuracy:", round(knn.score(X_te, y_te), 4))

# Tune k via cross-validation
k_scores = {k: cross_val_score(make_pipeline(StandardScaler(),
                                               KNeighborsClassifier(n_neighbors=k)),
                                X, y, cv=5).mean()
            for k in range(1, 21)}
best_k = max(k_scores, key=k_scores.get)
print(f"Best k={best_k}, score={k_scores[best_k]:.4f}")

# --- KNN Regressor ---
X_r, y_r = load_diabetes(return_X_y=True)
X_tr_r, X_te_r, y_tr_r, y_te_r = train_test_split(X_r, y_r, test_size=0.2, random_state=42)

knn_r = make_pipeline(StandardScaler(), KNeighborsRegressor(n_neighbors=7))
knn_r.fit(X_tr_r, y_tr_r)
print("KNN Regressor R²:", round(knn_r.score(X_te_r, y_te_r), 4))

# --- Unsupervised nearest-neighbour lookup ---
nn = NearestNeighbors(n_neighbors=3, algorithm='ball_tree')
nn.fit(StandardScaler().fit_transform(X))
distances, indices = nn.kneighbors(X[:5])
print("NN distances (first 5 samples):\n", distances.round(3))
print("NN indices:\n", indices)
```

---

## Ensemble Methods (`sklearn.ensemble`)

### Bagging

- `BaggingClassifier(estimator=None, n_estimators=10, max_samples=1.0, max_features=1.0, bootstrap=True, bootstrap_features=False, oob_score=False, random_state=None, n_jobs=None)`: trains `n_estimators` copies of `estimator` on random subsets.
  - `estimator`: base estimator (default `DecisionTreeClassifier`).
  - `max_samples`, `max_features`: fraction or count of samples/features per estimator.
  - `bootstrap`: if `True`, samples with replacement.
  - `oob_score`: if `True`, estimates out-of-bag score (uses samples not drawn).

- `BaggingRegressor`: regressor equivalent of `BaggingClassifier`.

### Random Forest

- `RandomForestClassifier(n_estimators=100, criterion='gini', max_depth=None, min_samples_split=2, min_samples_leaf=1, max_features='sqrt', bootstrap=True, oob_score=False, class_weight=None, random_state=None, n_jobs=None)`: ensemble of decision trees trained on bootstrap samples with random feature subsets at each split.
  - `max_features`: `'sqrt'` (default, recommended), `'log2'`, int, float.
  - `oob_score`: out-of-bag accuracy estimate without a separate validation set.
  - `.feature_importances_`: mean decrease in impurity across trees.

- `RandomForestRegressor(n_estimators=100, criterion='squared_error', max_depth=None, max_features=1.0, bootstrap=True, oob_score=False, random_state=None, n_jobs=None)`: same, for regression.

- `ExtraTreesClassifier` / `ExtraTreesRegressor`: like Random Forest but splits are chosen randomly rather than optimally — faster, often similar accuracy.

### Boosting

- `GradientBoostingClassifier(loss='log_loss', learning_rate=0.1, n_estimators=100, max_depth=3, subsample=1.0, min_samples_split=2, min_samples_leaf=1, max_features=None, random_state=None)`: gradient boosting with decision trees.
  - `learning_rate`: shrinks each tree's contribution (trade-off with `n_estimators`).
  - `subsample`: fraction of samples per tree (< 1 = stochastic gradient boosting).

- `HistGradientBoostingClassifier(max_iter=100, learning_rate=0.1, max_depth=None, l2_regularization=0.0, max_bins=255, random_state=None)`: histogram-based gradient boosting. **Much faster** than `GradientBoosting` on large datasets. Natively handles NaN values.

- `HistGradientBoostingRegressor(...)`: histogram-based regressor.

- `AdaBoostClassifier(estimator=None, n_estimators=50, learning_rate=1.0, algorithm='SAMME', random_state=None)`: AdaBoost — reweights misclassified samples for each new estimator.

- `AdaBoostRegressor(estimator=None, n_estimators=50, learning_rate=1.0, loss='linear', random_state=None)`: AdaBoost for regression.

### Voting & Stacking

- `VotingClassifier(estimators, voting='hard', weights=None, n_jobs=None, flatten_transform=True)`: combines predictions by majority vote (`'hard'`) or averaged probabilities (`'soft'`).

- `VotingRegressor(estimators, weights=None, n_jobs=None)`: averages regressor predictions.

- `StackingClassifier(estimators, final_estimator=None, cv=5, stack_method='auto', n_jobs=None, passthrough=False)`: trains a meta-learner on cross-validated predictions of base estimators.
  - `stack_method`: `'auto'` (tries `predict_proba`, then `decision_function`, then `predict`).
  - `passthrough`: if `True`, also passes original features to the meta-learner.

- `StackingRegressor(estimators, final_estimator=None, cv=5, n_jobs=None, passthrough=False)`: regression stacking.

```python
from sklearn.ensemble import (RandomForestClassifier, RandomForestRegressor,
                               GradientBoostingClassifier, HistGradientBoostingClassifier,
                               AdaBoostClassifier, BaggingClassifier,
                               ExtraTreesClassifier, VotingClassifier, StackingClassifier)
from sklearn.linear_model import LogisticRegression
from sklearn.tree import DecisionTreeClassifier
from sklearn.svm import SVC
from sklearn.datasets import load_breast_cancer, load_diabetes
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
import numpy as np

X, y = load_breast_cancer(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)

# --- Random Forest ---
rf = RandomForestClassifier(n_estimators=200, max_depth=None, max_features='sqrt',
                             oob_score=True, random_state=42, n_jobs=-1)
rf.fit(X_tr, y_tr)
print("RF accuracy:", round(rf.score(X_te, y_te), 4))
print("OOB score:", round(rf.oob_score_, 4))
# Feature importances
feat_imp = rf.feature_importances_
top5 = np.argsort(feat_imp)[-5:][::-1]
print("Top 5 features:", top5, feat_imp[top5].round(3))

# --- Gradient Boosting ---
gb = GradientBoostingClassifier(n_estimators=200, learning_rate=0.05,
                                  max_depth=3, subsample=0.8, random_state=42)
gb.fit(X_tr, y_tr)
print("GBT accuracy:", round(gb.score(X_te, y_te), 4))

# --- Histogram GBT (fast, handles NaN) ---
hgb = HistGradientBoostingClassifier(max_iter=200, learning_rate=0.05, max_depth=4,
                                       l2_regularization=0.01, random_state=42)
hgb.fit(X_tr, y_tr)
print("HistGBT accuracy:", round(hgb.score(X_te, y_te), 4))

# --- AdaBoost ---
ada = AdaBoostClassifier(estimator=DecisionTreeClassifier(max_depth=2),
                          n_estimators=100, learning_rate=0.5, random_state=42)
ada.fit(X_tr, y_tr)
print("AdaBoost accuracy:", round(ada.score(X_te, y_te), 4))

# --- Voting ---
vote = VotingClassifier(
    estimators=[
        ('lr',  make_pipeline(StandardScaler(), LogisticRegression(max_iter=1000))),
        ('rf',  RandomForestClassifier(n_estimators=100, random_state=42)),
        ('hgb', HistGradientBoostingClassifier(max_iter=100, random_state=42)),
    ],
    voting='soft'
)
vote.fit(X_tr, y_tr)
print("Voting accuracy:", round(vote.score(X_te, y_te), 4))

# --- Stacking ---
stack = StackingClassifier(
    estimators=[
        ('rf',  RandomForestClassifier(n_estimators=100, random_state=42)),
        ('svc', make_pipeline(StandardScaler(), SVC(probability=True, random_state=42))),
    ],
    final_estimator=LogisticRegression(),
    cv=5, stack_method='predict_proba'
)
stack.fit(X_tr, y_tr)
print("Stacking accuracy:", round(stack.score(X_te, y_te), 4))
```

---

## Neural Networks (`sklearn.neural_network`)

- `MLPClassifier(hidden_layer_sizes=(100,), activation='relu', solver='adam', alpha=0.0001, batch_size='auto', learning_rate='constant', learning_rate_init=0.001, max_iter=200, shuffle=True, random_state=None, early_stopping=False, validation_fraction=0.1, n_iter_no_change=10, tol=1e-4)`: multi-layer perceptron classifier.
  - `hidden_layer_sizes`: tuple giving the number of neurons in each hidden layer, e.g. `(100, 50)` = two hidden layers.
  - `activation`: `'relu'` (default), `'tanh'`, `'logistic'` (sigmoid), `'identity'`.
  - `solver`: `'adam'` (default, good for large data), `'sgd'`, `'lbfgs'` (good for small data).
  - `alpha`: L2 regularisation term.
  - `early_stopping`: if `True`, uses `validation_fraction` for early stopping.
  - `.loss_curve_`: list of training loss per iteration.
  - `.best_validation_score_`: best validation score when `early_stopping=True`.
  - `.n_iter_`: number of iterations run.

- `MLPRegressor(hidden_layer_sizes=(100,), activation='relu', solver='adam', alpha=0.0001, max_iter=200, early_stopping=False, random_state=None)`: MLP for regression.

> **Note**: Scikit-learn's MLP does not support GPU, convolutional layers, or advanced architectures. Use PyTorch or TensorFlow/Keras for deep learning.

```python
from sklearn.neural_network import MLPClassifier, MLPRegressor
from sklearn.datasets import load_digits, load_diabetes
from sklearn.model_selection import train_test_split
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
import numpy as np
import matplotlib.pyplot as plt

# --- Classifier ---
X, y = load_digits(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, random_state=42)

mlp = make_pipeline(
    StandardScaler(),
    MLPClassifier(hidden_layer_sizes=(256, 128), activation='relu', solver='adam',
                  alpha=1e-4, learning_rate_init=0.001, max_iter=300,
                  early_stopping=True, validation_fraction=0.1, random_state=42)
)
mlp.fit(X_tr, y_tr)
print("MLP Digits accuracy:", round(mlp.score(X_te, y_te), 4))

# Training curve
loss = mlp['mlpclassifier'].loss_curve_
plt.plot(loss)
plt.xlabel('Iteration'); plt.ylabel('Loss'); plt.title('MLP Training Loss')
plt.show()

# --- Regressor ---
X_r, y_r = load_diabetes(return_X_y=True)
X_tr_r, X_te_r, y_tr_r, y_te_r = train_test_split(X_r, y_r, test_size=0.2, random_state=42)

mlp_r = make_pipeline(
    StandardScaler(),
    MLPRegressor(hidden_layer_sizes=(128, 64), activation='relu', solver='adam',
                  alpha=1e-3, max_iter=500, early_stopping=True, random_state=42)
)
mlp_r.fit(X_tr_r, y_tr_r)
print("MLP Regressor R²:", round(mlp_r.score(X_te_r, y_te_r), 4))
print("Iterations run:", mlp_r['mlpregressor'].n_iter_)
```

---

## Clustering (`sklearn.cluster`)

Clustering is unsupervised — only `X` is given to `.fit()`.

- `KMeans(n_clusters=8, init='k-means++', n_init=10, max_iter=300, tol=1e-4, random_state=None, algorithm='lloyd')`: k-means clustering.
  - `init`: centroid initialisation — `'k-means++'` (smart, default) or `'random'`.
  - `n_init`: number of times to run with different centroid seeds.
  - `.labels_`: cluster label for each sample.
  - `.cluster_centers_`: centroid coordinates.
  - `.inertia_`: sum of squared distances to nearest centroid.
  - `.n_iter_`: number of iterations run.

- `MiniBatchKMeans(n_clusters=8, batch_size=1024, init='k-means++', n_init=3, max_iter=100, random_state=None)`: approximate k-means for large datasets — much faster, slightly less accurate.

- `DBSCAN(eps=0.5, min_samples=5, metric='euclidean', algorithm='auto', leaf_size=30, n_jobs=None)`: density-based clustering — discovers clusters of arbitrary shape. Points in low-density regions are labelled as noise (`-1`).
  - `eps`: maximum distance between neighbours.
  - `min_samples`: minimum samples in a neighbourhood to form a core point.

- `AgglomerativeClustering(n_clusters=2, linkage='ward', metric='euclidean', connectivity=None)`: hierarchical agglomerative clustering.
  - `linkage`: `'ward'` (minimises variance, default), `'complete'`, `'average'`, `'single'`.

- `SpectralClustering(n_clusters=8, affinity='rbf', gamma=1.0, n_init=10, random_state=None, n_jobs=None)`: clusters the graph Laplacian. Good for non-convex clusters.

- `GaussianMixture(n_components=1, covariance_type='full', max_iter=100, tol=1e-3, n_init=1, random_state=None)`: generative probabilistic model for soft cluster assignments.
  - `covariance_type`: `'full'`, `'tied'`, `'diag'`, `'spherical'`.
  - `.predict(X)`: hard cluster assignments.
  - `.predict_proba(X)`: soft (probabilistic) assignments.
  - `.bic(X)` / `.aic(X)`: information criteria for model selection.

- `MeanShift(bandwidth=None, seeds=None, bin_seeding=False, cluster_all=True, n_jobs=None)`: finds cluster centres by shifting towards the densest region. Does not require specifying the number of clusters.

- `Birch(threshold=0.5, branching_factor=50, n_clusters=3)`: efficient for very large datasets; builds a compact tree.

```python
from sklearn.cluster import (KMeans, MiniBatchKMeans, DBSCAN,
                               AgglomerativeClustering, SpectralClustering,
                               GaussianMixture, MeanShift)
from sklearn.datasets import make_blobs, make_moons
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import silhouette_score, adjusted_rand_score
import numpy as np
import matplotlib.pyplot as plt

rng = np.random.default_rng(0)

# --- K-Means ---
X_blob, y_true = make_blobs(n_samples=500, centers=4, cluster_std=0.8, random_state=0)
X_scaled = StandardScaler().fit_transform(X_blob)

km = KMeans(n_clusters=4, init='k-means++', n_init=10, random_state=42)
km.fit(X_scaled)
labels = km.labels_
print("K-Means inertia:", round(km.inertia_, 2))
print("ARI vs true labels:", round(adjusted_rand_score(y_true, labels), 4))
print("Silhouette score:", round(silhouette_score(X_scaled, labels), 4))

# Elbow method — find optimal k
inertias = []
k_range = range(1, 11)
for k in k_range:
    km_k = KMeans(n_clusters=k, n_init=5, random_state=42).fit(X_scaled)
    inertias.append(km_k.inertia_)
plt.plot(k_range, inertias, 'bx-')
plt.xlabel('k'); plt.ylabel('Inertia'); plt.title('Elbow Method')
plt.show()

# --- DBSCAN ---
X_moons, _ = make_moons(n_samples=300, noise=0.08, random_state=0)
X_moons_sc = StandardScaler().fit_transform(X_moons)

db = DBSCAN(eps=0.2, min_samples=5)
db_labels = db.fit_predict(X_moons_sc)
n_clusters = len(set(db_labels)) - (1 if -1 in db_labels else 0)
n_noise    = np.sum(db_labels == -1)
print(f"DBSCAN: {n_clusters} clusters, {n_noise} noise points")
print("DBSCAN Silhouette:", round(silhouette_score(X_moons_sc, db_labels), 4))

# --- Agglomerative ---
agg = AgglomerativeClustering(n_clusters=4, linkage='ward')
agg_labels = agg.fit_predict(X_scaled)
print("Agglomerative ARI:", round(adjusted_rand_score(y_true, agg_labels), 4))

# --- Gaussian Mixture ---
gm = GaussianMixture(n_components=4, covariance_type='full', n_init=3, random_state=42)
gm.fit(X_scaled)
gm_labels = gm.predict(X_scaled)
gm_proba  = gm.predict_proba(X_scaled)

print("GMM BIC:", round(gm.bic(X_scaled), 1))
print("GMM ARI:", round(adjusted_rand_score(y_true, gm_labels), 4))

# Select number of components via BIC
bics = [GaussianMixture(n_components=k, random_state=0).fit(X_scaled).bic(X_scaled)
        for k in range(1, 8)]
print("Best n_components:", np.argmin(bics) + 1)

# --- MiniBatch K-Means (large scale) ---
mbkm = MiniBatchKMeans(n_clusters=4, batch_size=128, n_init=3, random_state=42)
mbkm.fit(X_scaled)
print("MiniBatch ARI:", round(adjusted_rand_score(y_true, mbkm.labels_), 4))
```

---

## Dimensionality Reduction (`sklearn.decomposition` & `sklearn.manifold`)

### Linear Methods

- `PCA(n_components=None, whiten=False, svd_solver='auto', random_state=None)`: Principal Component Analysis — projects data onto the directions of maximum variance.
  - `n_components`: number of components to keep, or a float in `(0, 1)` specifying the minimum explained variance ratio.
  - `whiten`: if `True`, each component is scaled to unit variance.
  - `.explained_variance_ratio_`: fraction of variance explained by each component.
  - `.components_`: principal axes (shape `(n_components, n_features)`).
  - `.singular_values_`: singular values of the centred data matrix.
  - `transform(X)` / `inverse_transform(X_t)`: project and reconstruct.

- `TruncatedSVD(n_components=2, algorithm='randomized', random_state=None)`: SVD-based decomposition that works with **sparse matrices**. Equivalent to PCA but without mean-centring.

- `FastICA(n_components=None, algorithm='parallel', max_iter=200, random_state=None)`: Independent Component Analysis — separates a multivariate signal into additive independent components.

- `NMF(n_components=None, init='nndsvda', solver='cd', max_iter=200, random_state=None)`: Non-negative Matrix Factorisation — `X ≈ W @ H` with all non-negative. Good for text and image data.

### Manifold Learning (Non-linear)

- `TSNE(n_components=2, perplexity=30.0, learning_rate='auto', n_iter=1000, metric='euclidean', random_state=None)`: t-SNE — reveals local cluster structure. **Only for visualisation** — `transform` not supported.
  - `perplexity`: effective number of neighbours (typically 5–50).

- `UMAP`: not in scikit-learn — install separately with `pip install umap-learn`.

- `MDS(n_components=2, metric=True, n_init=4, max_iter=300, random_state=None)`: Multidimensional Scaling — preserves pairwise distances.

- `Isomap(n_neighbors=5, n_components=2, metric='minkowski', n_jobs=None)`: geodesic distance manifold learning.

- `LocallyLinearEmbedding(n_neighbors=5, n_components=2, method='standard', random_state=None)`: LLE.

```python
from sklearn.decomposition import PCA, TruncatedSVD, FastICA, NMF
from sklearn.manifold import TSNE, MDS, Isomap
from sklearn.datasets import load_digits, load_iris
from sklearn.preprocessing import StandardScaler
import numpy as np
import matplotlib.pyplot as plt

X_d, y_d = load_digits(return_X_y=True)
X_d_sc = StandardScaler().fit_transform(X_d)

# --- PCA ---
pca = PCA(n_components=0.95, svd_solver='full')   # keep 95% of variance
X_pca = pca.fit_transform(X_d_sc)
print(f"PCA: {pca.n_components_} components explain 95% of variance")
print("Explained var ratio (first 5):", pca.explained_variance_ratio_[:5].round(3))

# Fixed number of components
pca2 = PCA(n_components=2)
X_2d = pca2.fit_transform(X_d_sc)
print("2D PCA shape:", X_2d.shape)

# Reconstruction error
X_rec = pca2.inverse_transform(X_2d)
print("Reconstruction MSE:", np.mean((X_d_sc - X_rec)**2).round(4))

# Scree plot
pca_full = PCA().fit(X_d_sc)
cumvar = np.cumsum(pca_full.explained_variance_ratio_)
n_95 = np.searchsorted(cumvar, 0.95) + 1
plt.plot(cumvar); plt.axhline(0.95, color='r', linestyle='--')
plt.xlabel('n_components'); plt.ylabel('Cumulative explained variance')
plt.title('Scree Plot')
plt.show()

# --- TruncatedSVD (for sparse input) ---
from scipy.sparse import csr_matrix
X_sp = csr_matrix(X_d)
svd = TruncatedSVD(n_components=50, random_state=42)
X_svd = svd.fit_transform(X_sp)
print("TruncatedSVD explained var:", svd.explained_variance_ratio_.sum().round(3))

# --- NMF (requires non-negative data) ---
from sklearn.preprocessing import MinMaxScaler
X_nn = MinMaxScaler().fit_transform(X_d)
nmf = NMF(n_components=16, init='nndsvda', random_state=42, max_iter=500)
W = nmf.fit_transform(X_nn)
H = nmf.components_
print("NMF W shape:", W.shape, "H shape:", H.shape)
print("Reconstruction error:", nmf.reconstruction_err_)

# --- t-SNE (visualisation only) ---
tsne = TSNE(n_components=2, perplexity=30, learning_rate='auto',
            n_iter=1000, random_state=42)
X_tsne = tsne.fit_transform(X_d_sc[:500])   # subset for speed
plt.scatter(X_tsne[:, 0], X_tsne[:, 1], c=y_d[:500], cmap='tab10', s=5)
plt.title('t-SNE of Digits'); plt.colorbar(); plt.show()
```

---

## Feature Selection (`sklearn.feature_selection`)

- `SelectKBest(score_func, k=10)`: selects the `k` features with the highest univariate scores.
  - `score_func`: `f_classif` (ANOVA F-test), `chi2` (chi-squared, non-negative), `f_regression`, `mutual_info_classif`, `mutual_info_regression`.
  - `.scores_`, `.pvalues_`.

- `SelectPercentile(score_func, percentile=10)`: selects the top `percentile`% of features.

- `SelectFromModel(estimator, threshold=None, prefit=False, max_features=None, norm_order=1)`: selects features based on feature importances from a fitted estimator.
  - `threshold`: can be `'mean'`, `'median'`, a float, or `'1.5*mean'` style string.
  - `prefit`: if `True`, `estimator` is already fitted.

- `RFE(estimator, n_features_to_select=None, step=1, verbose=0)`: Recursive Feature Elimination — repeatedly fits and removes the least important feature.
  - `step`: number of features to remove per iteration.
  - `.support_`: boolean mask of selected features.
  - `.ranking_`: ranking of features (1 = selected).

- `RFECV(estimator, step=1, cv=5, scoring=None, n_jobs=None)`: RFE with cross-validation to select the optimal number of features.

- `VarianceThreshold(threshold=0.0)`: removes features with variance below a threshold. `threshold=0` removes constant features.

- `mutual_info_classif(X, y, discrete_features=False, random_state=None)`: estimates mutual information between each feature and the target.

```python
from sklearn.feature_selection import (SelectKBest, SelectFromModel, RFE, RFECV,
                                        VarianceThreshold, f_classif,
                                        mutual_info_classif, chi2)
from sklearn.ensemble import RandomForestClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.datasets import load_breast_cancer
from sklearn.pipeline import Pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.model_selection import train_test_split
import numpy as np

X, y = load_breast_cancer(return_X_y=True)
feat_names = load_breast_cancer().feature_names
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)

# --- VarianceThreshold ---
vt = VarianceThreshold(threshold=0.01)
X_vt = vt.fit_transform(X_tr)
print(f"VarianceThreshold: {X_vt.shape[1]} of {X_tr.shape[1]} features retained")

# --- SelectKBest (ANOVA F-test) ---
skb = SelectKBest(score_func=f_classif, k=10)
X_skb = skb.fit_transform(X_tr, y_tr)
print("Top 10 features (F-test):", feat_names[skb.get_support()])
print("F-scores:", np.round(skb.scores_[skb.get_support()], 1))

# Mutual information
mi = mutual_info_classif(X_tr, y_tr, random_state=42)
top_mi = np.argsort(mi)[-5:][::-1]
print("Top 5 by MI:", feat_names[top_mi])

# --- SelectFromModel (tree importances) ---
rf = RandomForestClassifier(n_estimators=100, random_state=42)
rf.fit(X_tr, y_tr)
sfm = SelectFromModel(rf, threshold='mean', prefit=True)
X_sfm = sfm.transform(X_tr)
print(f"SelectFromModel: {X_sfm.shape[1]} features retained")
print("Selected:", feat_names[sfm.get_support()])

# --- In a Pipeline ---
pipe = Pipeline([
    ('scaler', StandardScaler()),
    ('selector', SelectFromModel(RandomForestClassifier(n_estimators=50, random_state=42))),
    ('clf', LogisticRegression(max_iter=1000))
])
pipe.fit(X_tr, y_tr)
print("Pipeline with feature selection accuracy:", round(pipe.score(X_te, y_te), 4))

# --- RFE ---
rfe = RFE(LogisticRegression(max_iter=1000), n_features_to_select=10, step=1)
rfe.fit(StandardScaler().fit_transform(X_tr), y_tr)
print("RFE selected:", feat_names[rfe.support_])

# --- RFECV (cross-validated) ---
rfecv = RFECV(LogisticRegression(max_iter=1000), step=1, cv=5, scoring='accuracy', n_jobs=-1)
rfecv.fit(StandardScaler().fit_transform(X_tr), y_tr)
print("RFECV optimal features:", rfecv.n_features_)
```

---

## Metrics (`sklearn.metrics`)

### Classification Metrics

- `accuracy_score(y_true, y_pred, normalize=True)`: fraction (or count) of correctly classified samples.
- `precision_score(y_true, y_pred, average='binary', zero_division=0)`: TP / (TP + FP).
  - `average`: `'binary'`, `'micro'`, `'macro'`, `'weighted'`, `None` (returns per-class).
- `recall_score(y_true, y_pred, average='binary', zero_division=0)`: TP / (TP + FN). Also called sensitivity.
- `f1_score(y_true, y_pred, average='binary', zero_division=0)`: harmonic mean of precision and recall.
- `fbeta_score(y_true, y_pred, beta, average='binary')`: weighted F-score; `beta > 1` favours recall.
- `classification_report(y_true, y_pred, target_names=None, digits=4)`: text summary of per-class metrics.
- `confusion_matrix(y_true, y_pred, labels=None, normalize=None)`: N×N matrix counting predictions.
  - `normalize`: `'true'` (row normalisation), `'pred'`, `'all'`, `None`.
- `ConfusionMatrixDisplay.from_estimator(estimator, X, y, display_labels=None, normalize=None, ax=None)`: plots the confusion matrix directly.
- `roc_auc_score(y_true, y_score, average='macro', multi_class='raise')`: area under the ROC curve.
  - For binary: pass probability of positive class.
  - For multi-class: `multi_class='ovr'` or `'ovo'`.
- `roc_curve(y_true, y_score, pos_label=None, drop_intermediate=True)`: returns `(fpr, tpr, thresholds)`.
- `RocCurveDisplay.from_estimator(estimator, X, y, name=None, ax=None)`: plots ROC curve.
- `average_precision_score(y_true, y_score, average='macro')`: area under the precision-recall curve.
- `precision_recall_curve(y_true, probas_pred, pos_label=None)`: `(precision, recall, thresholds)`.
- `log_loss(y_true, y_pred, eps=1e-15, normalize=True)`: cross-entropy loss.
- `cohen_kappa_score(y1, y2, weights=None)`: inter-annotator agreement corrected for chance.
- `matthews_corrcoef(y_true, y_pred)`: MCC — reliable metric for imbalanced binary classification; range `[-1, 1]`.

### Regression Metrics

- `mean_squared_error(y_true, y_pred, squared=True)`: MSE (set `squared=False` for RMSE).
- `mean_absolute_error(y_true, y_pred)`: MAE.
- `mean_absolute_percentage_error(y_true, y_pred)`: MAPE.
- `median_absolute_error(y_true, y_pred)`: robust to outliers.
- `r2_score(y_true, y_pred)`: coefficient of determination R². 1 = perfect, 0 = predicts mean.
- `explained_variance_score(y_true, y_pred)`: similar to R² but not penalised for bias.
- `max_error(y_true, y_pred)`: maximum single-sample error.
- `mean_tweedie_deviance(y_true, y_pred, power=0)`: Tweedie deviance for insurance/count data.

### Clustering Metrics

- `silhouette_score(X, labels, metric='euclidean')`: mean ratio of intra-cluster distance to nearest-cluster distance. Range `[-1, 1]`; higher is better.
- `davies_bouldin_score(X, labels)`: average similarity between clusters; lower is better.
- `calinski_harabasz_score(X, labels)`: variance ratio; higher is better.
- `adjusted_rand_score(labels_true, labels_pred)`: ARI — similarity to ground truth. `0` = random, `1` = perfect.
- `adjusted_mutual_info_score(labels_true, labels_pred)`: AMI — mutual information adjusted for chance.
- `homogeneity_score`, `completeness_score`, `v_measure_score`: cluster quality w.r.t. ground truth.

```python
from sklearn.metrics import (
    accuracy_score, precision_score, recall_score, f1_score,
    classification_report, confusion_matrix, ConfusionMatrixDisplay,
    roc_auc_score, roc_curve, RocCurveDisplay, average_precision_score,
    log_loss, matthews_corrcoef,
    mean_squared_error, mean_absolute_error, r2_score,
    silhouette_score, adjusted_rand_score, davies_bouldin_score
)
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.datasets import load_breast_cancer, load_diabetes
from sklearn.model_selection import train_test_split
import numpy as np
import matplotlib.pyplot as plt

# ---- Classification ----
X, y = load_breast_cancer(return_X_y=True)
X_tr, X_te, y_tr, y_te = train_test_split(X, y, test_size=0.2, stratify=y, random_state=42)

clf = make_pipeline(StandardScaler(), LogisticRegression(max_iter=1000))
clf.fit(X_tr, y_tr)
y_pred  = clf.predict(X_te)
y_proba = clf.predict_proba(X_te)[:, 1]

print("Accuracy:", round(accuracy_score(y_te, y_pred), 4))
print("Precision:", round(precision_score(y_te, y_pred), 4))
print("Recall:", round(recall_score(y_te, y_pred), 4))
print("F1:", round(f1_score(y_te, y_pred), 4))
print("MCC:", round(matthews_corrcoef(y_te, y_pred), 4))
print("ROC-AUC:", round(roc_auc_score(y_te, y_proba), 4))
print("Log-loss:", round(log_loss(y_te, y_proba), 4))

print("\nClassification Report:\n",
      classification_report(y_te, y_pred, target_names=['malignant', 'benign'], digits=4))

# Confusion matrix
cm = confusion_matrix(y_te, y_pred, normalize='true')
print("Normalised CM:\n", cm.round(3))

ConfusionMatrixDisplay.from_estimator(
    clf, X_te, y_te, display_labels=['malignant', 'benign'],
    normalize='true', cmap='Blues'
)
plt.title('Confusion Matrix'); plt.show()

# ROC Curve
fpr, tpr, thresh = roc_curve(y_te, y_proba)
RocCurveDisplay.from_estimator(clf, X_te, y_te, name='Logistic Regression')
plt.plot([0,1],[0,1],'k--'); plt.show()

# Precision-Recall (better for imbalanced data)
ap = average_precision_score(y_te, y_proba)
print(f"Average Precision: {ap:.4f}")

# Multi-class (macro / weighted)
X_mc, y_mc = load_breast_cancer(return_X_y=True)   # just as example
print("Macro F1:", round(f1_score(y_te, y_pred, average='macro'), 4))
print("Weighted F1:", round(f1_score(y_te, y_pred, average='weighted'), 4))

# ---- Regression ----
X_r, y_r = load_diabetes(return_X_y=True)
X_tr_r, X_te_r, y_tr_r, y_te_r = train_test_split(X_r, y_r, test_size=0.2, random_state=42)

from sklearn.linear_model import Ridge
reg = make_pipeline(StandardScaler(), Ridge(alpha=1.0))
reg.fit(X_tr_r, y_tr_r)
y_pred_r = reg.predict(X_te_r)

print("MSE:",  round(mean_squared_error(y_te_r, y_pred_r), 2))
print("RMSE:", round(mean_squared_error(y_te_r, y_pred_r, squared=False), 2))
print("MAE:",  round(mean_absolute_error(y_te_r, y_pred_r), 2))
print("R²:",   round(r2_score(y_te_r, y_pred_r), 4))

# Residual plot
residuals = y_te_r - y_pred_r
plt.scatter(y_pred_r, residuals, alpha=0.5)
plt.axhline(0, color='r', linestyle='--')
plt.xlabel('Predicted'); plt.ylabel('Residual'); plt.title('Residual Plot')
plt.show()
```

---

## Scoring Strings Reference

| Task | String | Notes |
|---|---|---|
| Classification | `'accuracy'` | Fraction correct |
| Classification | `'balanced_accuracy'` | Macro recall; good for imbalanced |
| Classification | `'f1'` | Binary F1 |
| Classification | `'f1_macro'` | Macro-averaged F1 |
| Classification | `'f1_weighted'` | Weighted-averaged F1 |
| Classification | `'roc_auc'` | Area under ROC curve |
| Classification | `'average_precision'` | Area under PR curve |
| Classification | `'neg_log_loss'` | Negated cross-entropy |
| Classification | `'precision'` | Binary precision |
| Classification | `'recall'` | Binary recall |
| Regression | `'r2'` | Coefficient of determination |
| Regression | `'neg_mean_squared_error'` | Negated MSE |
| Regression | `'neg_root_mean_squared_error'` | Negated RMSE |
| Regression | `'neg_mean_absolute_error'` | Negated MAE |
| Clustering | — | Pass scorer manually |

> Metrics that must be maximised during grid search are negated (prefixed with `neg_`) so `GridSearchCV` always maximises.

---

## Saving & Loading Models

- `joblib.dump(estimator, filename, compress=0)`: serialises a fitted scikit-learn model to disk. More efficient than `pickle` for large NumPy arrays.
  - `compress`: compression level `0`–`9` (0 = no compression, 3 = good trade-off).
- `joblib.load(filename)`: deserialises from disk.

> Use `pickle` as an alternative. Never load a model from an untrusted source.

```python
import joblib
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.ensemble import RandomForestClassifier
from sklearn.datasets import load_iris

X, y = load_iris(return_X_y=True)
pipe = make_pipeline(StandardScaler(), RandomForestClassifier(n_estimators=50, random_state=42))
pipe.fit(X, y)

# Save
joblib.dump(pipe, 'model.joblib', compress=3)

# Load
loaded = joblib.load('model.joblib')
print("Loaded accuracy:", loaded.score(X, y))

# Save with pickle
import pickle
with open('model.pkl', 'wb') as f:
    pickle.dump(pipe, f)
with open('model.pkl', 'rb') as f:
    loaded_pkl = pickle.load(f)
print("Pickle accuracy:", loaded_pkl.score(X, y))
```
