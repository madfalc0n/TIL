# ValueError_The_estimator_KerasClassifier_should_be_a_classifier

- 에러증상

```python
#fit 할 경우 아래와 같은 에러가 발생

16 #fit model to training data
---> 17 eclf.fit(x_train, y_train)
18
19 #model for testing data

~/.local/lib/python3.6/site-packages/sklearn/ensemble/voting.py in fit(self, X, y, sample_weight)
220 transformed_y = self.le.transform(y)
221
--> 222 return super().fit(X, transformed_y, sample_weight)
223
224 def predict(self, X):

~/.local/lib/python3.6/site-packages/sklearn/ensemble/_voting.py in fit(self, X, y, sample_weight)
55 def fit(self, X, y, sample_weight=None):
56 """Get common fit operations."""
---> 57 names, clfs = self._validate_estimators()
58
59 if (self.weights is not None and

~/.local/lib/python3.6/site-packages/sklearn/ensemble/_base.py in _validate_estimators(self)
247 raise ValueError(
248 "The estimator {} should be a {}.".format(
--> 249 est.class.name, is_estimator_type.name[3:]
250 )
251 )

ValueError: The estimator KerasClassifier should be a classifier.
```

해당 원인은 skicit-learn 버전으로 인한 에러로  버전을 0.22 에서 0.21.3으로 맞추면 된다.