# Data Science Cheatsheet

A quick reference guide for core concepts in data science.

---

## Definition
- **Data Science** is an interdisciplinary field that uses scientific methods, algorithms, and systems to extract knowledge and insights from structured and unstructured data.  
- Combines **statistics**, **computer science**, and **domain knowledge**.

---

## Goal
- Transform **raw data** into **actionable insights**.  
- Support **decision-making** with data-driven evidence.  
- Build **predictive models** and improve **automation**.  

---

## Big Data
- Refers to datasets too large/complex for traditional tools.  
- Defined by the **5 V’s**:
  - `Volume` – amount of data  
  - `Velocity` – speed of data generation  
  - `Variety` – structured, unstructured, semi-structured data  
  - `Veracity` – quality and reliability  
  - `Value` – actionable insights  

---

## Types of Data
- **Structured Data**: tabular, organized (e.g., SQL databases).  
- **Unstructured Data**: text, images, audio, video.  
- **Semi-structured Data**: JSON, XML, logs.  
- **Quantitative Data**: numeric, measurable.  
- **Qualitative Data**: descriptive, categorical.  

---

## Data Sources
- Databases (SQL/NoSQL)  
- APIs and Web Scraping  
- Sensors & IoT devices  
- Social Media platforms  
- Open Data repositories  
- Enterprise systems (CRM, ERP)  

---

## Methods
- **Descriptive Analysis** – summarizing data  
- **Exploratory Data Analysis (EDA)** – discovering patterns  
- **Predictive Modeling** – forecasting outcomes  
- **Machine Learning** – training models for automation  
- **Data Visualization** – communicating insights  
- **Data Engineering** – cleaning, transforming, and preparing data  

---

## Math Involved
Mathematics forms the backbone of data science models and analysis.

### 1. Linear Regression
- **Use case**: Predict continuous values.  
- **Formula**:  
```

y = β₀ + β₁x + ε

```
- `y`: dependent variable  
- `x`: independent variable  
- `β₀`: intercept  
- `β₁`: slope coefficient  
- `ε`: error term  

---

### 2. Logistic Regression
- **Use case**: Classification (binary outcomes).  
- **Formula**:  
```

P(y=1|x) = 1 / (1 + e^-(β₀ + β₁x))

```
- `P(y=1|x)`: probability of class 1  
- `β₀, β₁`: parameters  

---

### 3. Probability & Bayes’ Theorem
- **Use case**: Conditional probability, Naive Bayes classifier.  
- **Formula**:  
```

P(A|B) = (P(B|A) \* P(A)) / P(B)

```
- `P(A|B)`: probability of A given B  
- `P(B|A)`: probability of B given A  
- `P(A)`: prior probability of A  
- `P(B)`: probability of B  

---

### 4. Linear Algebra (Vectors & Matrices)
- **Use case**: Data representation, dimensionality reduction (PCA), neural networks.  
- **Formula (Matrix multiplication)**:  
```

C = A × B

```
- `A`, `B`: matrices  
- `C`: resulting matrix  

---

### 5. Gradient Descent
- **Use case**: Optimization for training models.  
- **Formula**:  
```

θ = θ - α \* ∇J(θ)

```
- `θ`: parameters  
- `α`: learning rate  
- `∇J(θ)`: gradient of cost function  

---

### 6. Distance Metrics
- **Use case**: Clustering (KNN, K-means).  
- **Euclidean Distance**:  
```

d(p,q) = √Σ (pi - qi)²

```
- `p, q`: vectors (points)  

---

### 7. Statistics
- **Mean**: `μ = (Σ xi) / n`  
- **Variance**: `σ² = Σ (xi - μ)² / n`  
- **Standard Deviation**: `σ = √σ²`  
- **Correlation (Pearson)**:  
```

r = Σ (xi - x̄)(yi - ȳ) / √\[Σ (xi - x̄)² Σ (yi - ȳ)²]

```

---

### 8. Neural Networks (Activation Functions)
- **Use case**: Deep learning.  
- **Sigmoid Function**:  
```

σ(x) = 1 / (1 + e^-x)

```
- **ReLU**:  
```

f(x) = max(0, x)

```

---

