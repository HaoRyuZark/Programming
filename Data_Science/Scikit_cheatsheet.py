import numpy as np
import pandas as pd 
from copy import deepcopy

##################################################################################################

# DATA LOADING & SPLIT

from sklearn.datasets import load_diabetes, load_iris, make_classification
from sklearn.model_selection import train_test_split

# Regression dataset
X_reg, y_reg = load_diabetes(return_X_y=True)

# train_test_split accepts our data and labels, test_size= percentage of data for the test data, random_state 
X_train_reg, X_test_reg, y_train_reg, y_test_reg = train_test_split(X_reg, y_reg, test_size=0.2, random_state=42)

# Classification dataset
# This function make_classification gives you a data set with samples, features and their respective labels
X_clf, y_clf = make_classification(n_samples=1000, n_features=20, random_state=42)
X_train_clf, X_test_clf, y_train_clf, y_test_clf = train_test_split(X_clf, y_clf, test_size=0.2, random_state=42)

##################################################################################################

# PREPROCESSING
from sklearn.preprocessing import StandardScaler, MinMaxScaler, OneHotEncoder, QuantileTransformer, PolynomialFeatures
from sklearn.impute import SimpleImputer
from sklearn.compose import ColumnTransformer
import numpy as np

# Example: scale numeric columns, one-hot encode categorical columns
numeric_features = [0, 1, 2]
categorical_features = [3]

preprocessor = ColumnTransformer([
    ("num", StandardScaler(), numeric_features),
    ("cat", OneHotEncoder(handle_unknown="ignore"), categorical_features) # OneHotEncoders will transform categorical data into numerical values
])

# Scaling
# This refers to take a feature and mutipliyin it by some numeric value. 
# When we add or substract a value we are shifting the distribution either to right or 
# to the left

scaler = StandardScaler() # use for Z scoring
scaler.fit_transform(X_train_clf)


QuantileTransformer(n_quantiles=100).fit_transform(X_train_clf) # uses the quantiles for scaling

PolynomialFeatures(degree=3) # this allows us to increase the number of features using polynomial expansion 

##################################################################################################

# SIMPLE MODEL FITTING

from sklearn.neighbors import KNeighborsRegressor

knn = KNeighborsRegressor(n_neighbors=5)
knn.fit(X_train_reg, y_train_reg)
print("KNN train R^2:", knn.score(X_train_reg, y_train_reg))

##################################################################################################

# PIPELINES

from sklearn.pipeline import Pipeline
from sklearn.preprocessing import MinMaxScaler, FunctionTransformer
from sklearn.model_selection import LinearRegression

pipe = Pipeline([
    ("scaler", StandardScaler()),
    ("model", KNeighborsRegressor(n_neighbors=5))
])
pipe.fit(X_train_reg, y_train_reg)

print("Pipeline test R^2:", pipe.score(X_test_reg, y_test_reg))
print("Pipeline parametes:", pipe.get_params()) # get_params returns a dictionary with the parameters which can be accepted by our 
# objects in the pipeline dictionary. Their named using the pattern 'ste__paramter_x'

# More Complex Example 

X_train = np.array([])

std_scaler = StandardScaler()
std_scaler.fit(X_train[:,:2]) # using std_scaler for the first column 

min_max_scaler = MinMaxScaler()
min_max_scaler.fit(X_train[:,2:]) # using min_max_scaler for the rest of the columns

def preprocessor(X):
    A = np.copy(X)
    A[:, :2] = std_scaler.transform(X[:, :2])
    A[:, 2:] = min_max_scaler.transform(X[:, 2:])

    return A

preprocess_transformer = FunctionTransformer(preprocessor)

pipeline = Pipeline([('scale', preprocess_transformer), ('reg', LinearRegression())])

##################################################################################################

# HYPERPARAMETER TUNING

from sklearn.model_selection import GridSearchCV, RandomizedSearchCV

# Hyper parameters 

param_grid = {"model__n_neighbors": range(1, 11)} 
# The invididual paramters are the same as for the object it acts on but with their step name
# and a double underscore for the actual parameter: step__parameter

pipe = Pipeline([
    ("scaler", StandardScaler()),
    ("model", KNeighborsRegressor(n_neighbors=5))
])

pipe.fit(X_train_reg, y_train_reg)

grid = GridSearchCV(pipe, param_grid, cv=5, verbose=4) # you can also pass an array of scoring matrics for te scoring of the models

grid.fit(X_train_reg, y_train_reg)

pd.DataFrame(grid.cv_results_) # is an statistical overview of the data generated during our cross validation process

print("Best params (GridSearch):", grid.best_params_)
print("Best estimator (GridSearch):", grid.best_estimator_)
print("Best score (GridSearch):", grid.best_score_)

##################################################################################################

# CLASSIFICATION MODEL & METRICS

from sklearn.linear_model import LogisticRegression
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix

logistic_regression_classifier = LogisticRegression(max_iter=1000)
logistic_regression_classifier.fit(X_train_clf, y_train_clf)
y_pred = logistic_regression_classifier.predict(X_test_clf)

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
from sklearn.neighbors import KNeighborsClassifier

knn = KNeighborsClassifier()
scores = cross_val_score(knn, X_clf, y_clf, cv=5, scoring='accuracy')
print("Cross-val Accuracy (mean):", scores.mean())
