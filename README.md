# KMeans
A C++ implementation of the KMeans clustering algorithm.

## How to use:

### Instantiate a KMeans object:
KMeans km = KMeans( dataframe* df, const unsigned k )

The dataframe structure is a standard vector of pointers to vector of doubles (i.e. vector< vector<double>* >)
An example of dataframe generation is contained in the main.cpp (read_data function).


### Train KMeans:

km.execute( unsigned max_iter )

This will generate the clusters. The parameter indicates the maximum number of iterations which can be performed. Note that the algorithm could stop before reaching the max_iter iterations if the clusters centroids do not change their position (i.e. convergence already reached).


### Predictions (only after training):

vector<unsigned> km.predict ( dataframe* df );

This will assign the predicted cluster for each record contained in the data frame. Note that the data frame columns should be the same as the ones used in the training phase with execute(). This function will return a vector of clusters ids (predictions).


