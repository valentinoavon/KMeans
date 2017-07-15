#include "KMeans.h"
#include <assert.h>
#include <iostream>
#include <limits>
#include <stdlib.h>

using namespace std;

/**
* initialize the clusters
*/
KMeans::KMeans(dataframe* df, const unsigned k)
{
    // at least k data row
    assert(df->size() > k);
    this->df = df;
    this->k = k;

    // init clusters
    this->clusters = new vector<Cluster*>;
}

// delete clusters
KMeans::~KMeans()
{
    for ( unsigned i = 0; i < k; ++i )
    {
        delete clusters->at(i);
    }

    delete clusters;
}

/**
* start the k means algorithm
*/
void KMeans::execute( unsigned max_iter )
{
    unsigned iter = 0;

    // initialize centroids
    KMeans::init_clusters();

    // iterate the procedure
    while ( iter < max_iter && has_next() )
    {
        cout << "#iteration " << iter << endl;
        update_clusters();

        ++iter;
    }
}

/**
* Predict in which cluster the new data row belogs to
*/
unsigned KMeans::predict(datarow* row)
{
    Cluster* cluster = get_nearest_cluster(row);
    return cluster->get_id();
}

/**
* Predict for each row in which cluster
* they belong to
*/
vector<unsigned> KMeans::predict( dataframe* df )
{
    vector<unsigned> out;

    for( unsigned i = 0; i < df->size(); ++i )
        out.push_back( predict( df->at(i) ) );

    return out;
}

/**
* Randomly initialize centroids
*/
void KMeans::init_clusters()
{
    cout << "initializing clusters" << endl;

    // randomly decide centroids
    for ( unsigned i = 0; i < k; ++i )
    {
        // get a random row from the df
        unsigned index = rand() % df->size();

        // init cluster
        Cluster* cluster = new Cluster( i, df->at(index) );
        clusters->push_back( cluster );
    }

    // update data rows according to centroids
    update_clusters();
}

/**
* update clusters data rows and centroid
*/
void KMeans::update_clusters()
{
    // clear clusters data
    for ( unsigned i = 0; i < k; ++i )
    {
        Cluster* cluster = clusters->at(i);
        cluster->clear();
    }

    // STEP 1 assign data rows to clusters
    for ( unsigned i = 0; i < df->size(); ++i )
    {
        datarow* row = df->at(i);
        Cluster* cluster = get_nearest_cluster(row);
        cluster->add(row);
    }

    // STEP 2 update clusters centroids
    for ( unsigned i = 0; i < k; ++i )
    {
        Cluster* cluster = clusters->at(i);
        cluster->update();
        cluster->print_centroid();
    }
}

/**
* Check if clusters changed their centroids
*/
bool KMeans::has_next()
{
    // check if at least one cluster changed
    bool changed = false;
    for ( unsigned i = 0; i < k; ++i )
    {
        if ( clusters->at(i)->is_changed() ) {
            changed = true;
            break;
        }
    }

    return changed;
}

/**
* Get the nearest cluster compared to current row
*/
Cluster* KMeans::get_nearest_cluster(datarow* row)
{
    Cluster* nearest = nullptr;
    double min_distance = std::numeric_limits<double>::max();

    // for each cluster
    for ( unsigned i = 0; i < k; ++i )
    {
        Cluster* cluster = clusters->at(i);

        // compute distance between cluster and row
        double distance = cluster->get_distance( row );

        // if smaller save it
        if (distance < min_distance)
        {
            min_distance = distance;
            nearest = cluster;
        }
    }

    return nearest;
}

/**
* print all the clusters centroids
*/
void KMeans::print() const
{
    cout << "current clusters centroids" << endl;

    for ( unsigned i = 0; i < clusters->size(); ++i ) {
        clusters->at(i)->print();
    }
}
