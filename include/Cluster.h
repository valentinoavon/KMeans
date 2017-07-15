#ifndef CLUSTER_H
#define CLUSTER_H
#include <vector>
#include <iostream>

using namespace std;

typedef vector<double> datarow;
typedef vector<datarow*> dataframe;

class Cluster
{
    unsigned id;
    datarow* centroid;
    dataframe* rows;
    bool changed;      // if last update changed centroid position

    public:
        Cluster(unsigned id, datarow* centroid);
        ~Cluster();
        unsigned get_id();
        datarow* get_centroid();
        void print_centroid();
        void clear();
        void add(datarow* row);
        double get_distance(datarow* row);
        void update();
        bool is_changed();
        void print();
        void print_table();

    protected:

    private:
};

#endif // CLUSTER_H
