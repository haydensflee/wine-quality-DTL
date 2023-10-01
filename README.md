# wine-quality-DTL
Decision Tree Learning model. Predicts wine quality rating of a wine sample based on its objective features.

## Context
A decision tree is one of the most powerful tools of supervised learning algorithms used for both classification and regression tasks. It builds a flowchart-like tree structure where each internal node denotes a test on an attribute, each branch represents an outcome of the test, and each leaf node (terminal node) holds a class label. It is constructed by recursively splitting the training data into subsets based on the values of the attributes until a stopping criterion is met, such as the maximum depth of the tree or the minimum number of samples required to split a node.

During training, the Decision Tree algorithm selects the best attribute to split the data based on a metric such as entropy or Gini impurity, which measures the level of impurity or randomness in the subsets. The goal is to find the attribute that maximizes the information gain or the reduction in impurity after the split. (source: GeeksForGeeks)

An example of a decision tree is given:
![Uploading image.png…]()

In this context, a decision tree is used to evaluate the quality of wine based on sensor data. A training dataset will be used to train the decision tree, then provide wine quality predictions on a test dataset. Wine quality rating is measured in the range of 0-9. In our dataset, we only keep the samples for quality ratings 5, 6 and 7. The 11 objective features are listed as follows:
- f acid: fixed acidity
- v acid: volatile acidity
- c acid: citric acid
- res sugar: residual sugar
- chlorides: chlorides
- fs dioxide: free sulfur dioxide
- ts dioxide: total sulfur dioxide
- density: density
- pH: pH
- sulphates: sulphates
- alcohol: alcohol

In both datsets, the first 11 columns represent the 11 features and the 12th column is the wine quality.

## Program
Makefile compiles the program into a linux executable binary named winequality.bin. The program can be compiled and run as follows:
```bash
$ make winequality
$ ./winequality.bin [train] [test] [minleaf]
```
**Inputs:**
- [train] specifies the path to a set of training data file.
- [test] specifies the path to a set of testing data file.
- [minleaf] is an integer greater than zero which species the second input parameter to the DTL algorithm.
