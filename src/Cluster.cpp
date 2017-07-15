#include "Cluster.h"
#include <math.h>
#include <iostream>
#include <assert.h>

Cluster::Cluster(unsigned id, datarow* centroid)
{
    this->id = id;
    this->centroid = centroid;
    this->rows = new dataframe();
    this->changed = false;
}

// delete cluster rows
Cluster::~Cluster()
{
    delete rows;
}

/**
* Update the centroid position based on the
* cluster records
*/
void Cluster::update()
{
    // update centroid position with the mean
    // of the data rows
    for ( unsigned i=0; i < centroid->size(); ++i )
    {
        // compute mean for i-th dimension
        double mean = 0;

        for ( unsigned j=0; j < rows->size(); ++j )
        {
            mean = mean + rows->at(j)->at(i);
        }

        mean = mean / rows->size();

        // update value of centroid
        // for the i-th dimension
        datarow& centroidRef = *centroid;

        // update changed flag
        this->changed = !( abs(centroidRef[i] - mean) < 0.001 );

        centroidRef[i] = mean;
    }
}

datarow* Cluster::get_centroid()
{
    return centroid;
}

unsigned Cluster::get_id()
{
    return id;
}

/**
* Add a record to the cluster
*/
void Cluster::add( datarow* row )
{
    rows->push_back(row);
}

/**
* Clear the clusters records
*/
void Cluster::clear()
{
    rows->clear();
}

/**
* Check if the centroid was changed
* during the last update
*/
bool Cluster::is_changed()
{
    return changed;
}

/**
* Get distance between record and centroid
*/
double Cluster::get_distance(datarow* row)
{
    // centroid and datarow same size
    assert( row->size() == centroid->size() );

    double distance = 0;

    // squared euclidean distance
    for ( unsigned i=0; i < centroid->size(); ++i )
    {

        double d1 = centroid->at(i);
        double d2 = row->at(i);

        distance = distance + pow(d1 - d2, 2);
    }

    return distance;
}

/**
* Print the centroid
*/
void Cluster::print_centroid()
{
    cout << "centroid " << id << "[";
    for ( unsigned j = 0; j < centroid->size(); ++j ) {

        cout << centroid->at(j);

        if ( j < centroid->size() - 1 )
            cout << ",";
    }

    cout << "] " << endl;
}

void Cluster::print_table()
{
    for ( unsigned i = 0; i < rows->size(); ++i )
    {
        datarow* row = rows->at(i);

        for ( unsigned j = 0; j < row->size(); ++j ) {
            cout << row->at(j);

            if ( j < row->size() - 1 )
                cout << ";";
        }

        cout << ";" << id;

        cout << endl;
    }
}

/**
* Print the centroid and the cluster records
*/
void Cluster::print()
{
    cout << "Cluster" << endl;

    print_centroid();

    cout << "Records " << endl;

    for ( unsigned i = 0; i < rows->size(); ++i )
    {

        datarow* row = rows->at(i);

        cout << "data row [";
        for ( unsigned j = 0; j < row->size(); ++j ) {
            cout << row->at(j);

            if ( j < row->size() - 1 )
                cout << ",";
        }
        cout << "]";
        cout << endl;
    }

    cout << endl;
}
