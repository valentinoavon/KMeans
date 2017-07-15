#include <iostream>
#include <vector>
#include "KMeans.h"
#include <stdlib.h>

using namespace std;

typedef vector<double> datarow;
typedef vector<datarow*> dataframe;


/**
* read the data
*/
dataframe* readData()
{
    dataframe* df = new dataframe();

    for ( unsigned i = 0; i < 50; ++i )
    {
        datarow * row = new datarow();
        row->push_back ( i * rand() );
        row->push_back ( i * rand() );
        row->push_back ( i * rand() );
        row->push_back ( i * rand() );
        row->push_back ( i * rand() );
        df->push_back(row);
    }

    return df;
}

/**
* read the data
*/
dataframe* readTestData()
{
    dataframe* df = new dataframe();

    for ( unsigned i = 0; i < 5; ++i )
    {
        datarow* row = new datarow();
        row->push_back ( i * 5 );
        row->push_back ( i * 1 );
        df->push_back(row);
    }

    for ( unsigned i = 40; i < 50; ++i )
    {
        datarow* row = new datarow();
        row->push_back ( i * rand() );
        row->push_back ( i * 13 );
        df->push_back(row);
    }

    return df;
}

int main()
{
    dataframe* df = readData();

    KMeans km( df, 3 );
    km.execute(100);

   /* dataframe* test = readTestData();

    vector<unsigned> pred = km.predict(test);

    for ( unsigned i=0; i < pred.size(); ++i )
    {
        for ( unsigned j=0; j < test->at(i)->size(); ++j )
        {
            cout << test->at(i)->at(j) << ",";
        }

        cout << " cluster " << pred[i];

        cout << endl;
    }
    delete test;
    */

    delete df;
    return 0;
}
