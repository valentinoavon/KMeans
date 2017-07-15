#include <iostream>
#include <vector>
#include <stdlib.h>
#include "KMeans.h"

using namespace std;

typedef vector<double> datarow;
typedef vector<datarow*> dataframe;

/**
* Read the train data
*/
dataframe* readData()
{
    dataframe* df = new dataframe();

    for ( unsigned i = 0; i < 50; ++i )
    {
        // create a row
        datarow * row = new datarow();
        
        // populate row with 3 columns
        row->push_back ( i * 5 );
        row->push_back ( i * 1.5 );
        row->push_back ( i * rand() );
        
        // add row
        df->push_back(row);
    }

    return df;
}

/**
* Read the test data
*/
dataframe* readTestData()
{
    dataframe* df = new dataframe();

    for ( unsigned i = 0; i < 20; ++i )
    {
        datarow* row = new datarow();
        row->push_back ( i * 5 );
        row->push_back ( i * 1 );
        row->push_back ( i * rand() );
        df->push_back(row);
    }

    return df;
}

int main()
{
    dataframe* df = readData();

    // search 3 clusters in max 100 iterations
    KMeans km( df, 3 );
    
    // train model
    km.execute(100);

    // read test
    dataframe* test = readTestData();

    // get predictions of test
    vector<unsigned> pred = km.predict(test);

    // print predictions
    for ( unsigned i=0; i < pred.size(); ++i )
    {
        for ( unsigned j=0; j < test->at(i)->size(); ++j )
        {
            cout << test->at(i)->at(j) << ",";
        }

        cout << " cluster " << pred[i];

        cout << endl;
    }
    
    // delete data frames
    delete test;
    delete df;
    return 0;
}
