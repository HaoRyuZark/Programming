"""
- Scikit-learn is python library for machine learning.

- X,Y notations 

The diagrams looks like 

          The prediction I want 
Processed  | 
data -> x, y -----------------------> model -> prediction 
        |                               |
      Data used for                 Create -> Object
      the prediction                Learn -> fit(x,y)

"""

"""
Loading data
"""
from sklearn.datasets import load_boston

X, y = load_boston(return_X_y=True)

"""
Simple Model fitting
"""
from sklearn.neighbors import KNeighborsRegressor 
import matplotlib.pylab as plt

mod = KNeighborsRegressor() 

mod.fit(X,y) 

pred = mod.predict(X)

plt.scatter(pred, y)


"""
Model with prepocessing data for more accuracy
"""

from sklearn.preprocessing import StandardScaler, QuantileTransformer
from sklearn.pipeline import Pipeline 

X, y = load_boston(return_X_y=True)

mod = KNeighborsRegressor()

pipe = Pipeline([("scale",StandardScaler()), ("model",KNeighborsRegressor())])

pipe.fit(X,y)

pred = pipe.predict(X)

plt.scatter(pred, y)

"""
Grid Search 

Until know the model predicts on the same data it is given, which is a problem. We want to 
split the input data into different sections and each time the model is going to use some sections for training and the others for predcitions. And this is going to be 
repeated to improve the accuracy. 
"""

from sklearn.model_selection import GridSearchCV 
import pandas as pd 

X, y = load_boston(return_X_y=True)

mod = KNeighborsRegressor()

pipe = Pipeline([("scale",StandardScaler()), ("model",KNeighborsRegressor())])

pipe.get_params()

mod = GridSearchCV(estimator=pipe, param_grid={"model__n_nieghbors": [1,2,3,4,5,6,7,8,9,10]}, cv=3)

mod.fit(X,y)

pred = mod.predict(X)

pd.DataFrame(mod.cv_results_)

plt.scatter(pred, y)


"""
Data Pre-processing 

It is import to analyse and curate the data before a model is used to predict on the data 
"""

import numpy as np 

df = pd.read_csv("mydata.csv")

x_1 = df[['x','y']].values 
y_1 = df[['z']] == "a"

"""
Scaling: StandardScaler 
"""

x_new = StandardScaler().fit_transform(x_1)
x_new = QuantileTransformer(n_quantiles=100).fit_transform(x_1)

"""
Transforming non numerical data 
"""

from sklearn.preprocessing import OneHotEncoder 

arr = np.array(["a", "b", "c", "d", "e"])
enc = OneHotEncoder(sparse_output=False, handle_unknown="ignore")
m = enc.fit_transform(arr)

"""
Metrics 

We are going to take a dataset, then create 26 models which we are going to test using a matric. 
"""

from sklearn.linear_model import LogisticRegression


"""
precision_score: given that I predict froud how accurate I am 
recall_score: did I get all the fraud cases
"""
from sklearn.metrics import precision_score, recall_score, make_scorer 


ds = pd.read_csv("creditcards.csv")[:80_000]

x = df.drop(columns=['Time', 'Amount', 'Class']).values 
y = df['Class'].values 

mod = LogisticRegression(class_weight={0: 1, 1:2}, max_iter=1000) # 0: not froud, 1: fraud 
mod.fit(x,y).predict(x).sum()

grid = GridSearchCV(estimator=LogisticRegression(max_iter=1000), param_grid={'class_weigth':[{0:1,1:v} for v in range(1,4)]}, scoring={'precision':make_scorer(precision_score), 'recall_score':make_scorer(recall_score)},refit=True ,cv=4, n_jobs=-1)

grid.fit(x,y)

pd.DataFrame(grid.cv_results_)

