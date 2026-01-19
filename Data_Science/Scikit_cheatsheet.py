##################################################################################################

# DATA LOADING & SPLIT

from sklearn.datasets import load_diabetes, load_iris, make_classification
from sklearn.model_selection import train_test_split

# Regression dataset
X_reg, y_reg = load_diabetes(return_X_y=True)
X_train_reg, X_test_reg, y_train_reg, y_test_reg = train_test_split(X_reg, y_reg, test_size=0.2, random_state=42)

# Classification dataset
X_clf, y_clf = make_classification(n_samples=1000, n_features=20, random_state=42)
X_train_clf, X_test_clf, y_train_clf, y_test_clf = train_test_split(X_clf, y_clf, test_size=0.2, random_state=42)

##################################################################################################

# PREPROCESSING

from sklearn.preprocessing import StandardScaler, MinMaxScaler, OneHotEncoder
from sklearn.impute import SimpleImputer
from sklearn.compose import ColumnTransformer
import numpy as np

# Example: scale numeric columns, one-hot encode categorical columns
numeric_features = [0, 1, 2]
categorical_features = [3]

preprocessor = ColumnTransformer([
    ("num", StandardScaler(), numeric_features),
    ("cat", OneHotEncoder(handle_unknown="ignore"), categorical_features)
])

##################################################################################################

# SIMPLE MODEL FITTING

from sklearn.neighbors import KNeighborsRegressor

knn = KNeighborsRegressor(n_neighbors=5)
knn.fit(X_train_reg, y_train_reg)
print("KNN train R^2:", knn.score(X_train_reg, y_train_reg))

##################################################################################################

# PIPELINES

from sklearn.pipeline import Pipeline

pipe = Pipeline([
    ("scaler", StandardScaler()),
    ("model", KNeighborsRegressor(n_neighbors=5))
])
pipe.fit(X_train_reg, y_train_reg)
print("Pipeline test R^2:", pipe.score(X_test_reg, y_test_reg))

##################################################################################################

# HYPERPARAMETER TUNING

from sklearn.model_selection import GridSearchCV, RandomizedSearchCV

param_grid = {"model__n_neighbors": range(1, 11)}
grid = GridSearchCV(pipe, param_grid, cv=5)
grid.fit(X_train_reg, y_train_reg)
print("Best params (GridSearch):", grid.best_params_)

##################################################################################################

# CLASSIFICATION MODEL & METRICS

from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

clf = LogisticRegression(max_iter=1000)
clf.fit(X_train_clf, y_train_clf)
y_pred = clf.predict(X_test_clf)

print("Accuracy:", accuracy_score(y_test_clf, y_pred))
print("Precision:", precision_score(y_test_clf, y_pred))
print("Recall:", recall_score(y_test_clf, y_pred))
print("F1 Score:", f1_score(y_test_clf, y_pred))
print("Confusion Matrix:\n", confusion_matrix(y_test_clf, y_pred))

##################################################################################################

# REGRESSION METRICS

from sklearn.metrics import mean_squared_error, r2_score

y_pred_reg = pipe.predict(X_test_reg)
print("MSE:", mean_squared_error(y_test_reg, y_pred_reg))
print("R^2:", r2_score(y_test_reg, y_pred_reg))

##################################################################################################

# FEATURE ENGINEERING EXAMPLES

from sklearn.preprocessing import PolynomialFeatures
poly = PolynomialFeatures(degree=2, include_bias=False)
X_poly = poly.fit_transform(X_train_reg)
print("Polynomial features shape:", X_poly.shape)

##################################################################################################

# ENSEMBLE MODELS (META-ESTIMATORS)

from sklearn.ensemble import RandomForestClassifier, BaggingClassifier, AdaBoostClassifier, StackingClassifier

rf = RandomForestClassifier(n_estimators=100)
bag = BaggingClassifier(estimator=LogisticRegression(max_iter=500), n_estimators=10)
ada = AdaBoostClassifier(n_estimators=50)
stack = StackingClassifier(estimators=[('lr', LogisticRegression()), ('rf', rf)], final_estimator=LogisticRegression())

rf.fit(X_train_clf, y_train_clf)
bag.fit(X_train_clf, y_train_clf)
ada.fit(X_train_clf, y_train_clf)
stack.fit(X_train_clf, y_train_clf)

print("Random Forest Accuracy:", rf.score(X_test_clf, y_test_clf))
print("Bagging Accuracy:", bag.score(X_test_clf, y_test_clf))
print("AdaBoost Accuracy:", ada.score(X_test_clf, y_test_clf))
print("Stacking Accuracy:", stack.score(X_test_clf, y_test_clf))

##################################################################################################

# CROSS-VALIDATION SHORTCUT

from sklearn.model_selection import cross_val_score

scores = cross_val_score(clf, X_clf, y_clf, cv=5, scoring='accuracy')
print("Cross-val Accuracy (mean):", scores.mean())
