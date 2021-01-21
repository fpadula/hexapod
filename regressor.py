import pandas as pd
from sklearn.neural_network import MLPRegressor

data = pd.read_csv("data.csv", header = None)

data.info()

X = data.iloc[:, 0:2]
y = data.iloc[:, 2:]

print(X[0])
print(y[0])

# X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.33, random_state=42)

# reg = MLPRegressor(hidden_layer_sizes=(10,), tol=1e-2, max_iter=2500, random_state=0)
