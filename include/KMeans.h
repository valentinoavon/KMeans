#ifndef KMEANS_H
#define KMEANS_H
#include <vector>
#include "Cluster.h"

using namespace std;

typedef vector<double> datarow;
typedef vector<datarow*> dataframe;

class KMeans
{
    dataframe* df;               // data to analyze
    unsigned k;                  // number of clusters
    vector<Cluster*>* clusters;  // the kmeans clusters

    unsigned predict(datarow* row);
    void init_clusters();        // initialize clusters
    void update_clusters();      // make an update
    bool has_next();             // check if should go on

    // given a row, get the nearest cluster
    Cluster* get_nearest_cluster(datarow* row);

public:

    // initialize the algorithm data
    KMeans(dataframe* df, const unsigned k);
    ~KMeans();

    // execute the algorithm
    void execute( unsigned max_iter );

    vector<unsigned> predict( dataframe* df );

    // print clusters centroids
    void print() const;
};
#endif // KMEANS_H
