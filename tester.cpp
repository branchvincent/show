#include <iostream>
#include <string>
// #include <cmath>
#include "src/Task.h"
// #include <boost/property_tree/ptree.hpp>
// #include <boost/property_tree/xml_parser.hpp>
// #include <vector>
// #include "src/Util.h"
// // #include "src/TaskType.h"
// // #include "src/Distribution.h"
// #include <random>
// #include <typeinfo>
// // #include "src/Parameters.h"
// #include <queue>
// // #include "src/Traffic.h"
// // #include "src/Flags.h"
// #include "src/TaskType.h"

using namespace std;

// typedef priority_queue<Task,vector<Task>> Queue;
// typedef <bool,string> pair;

void inner(int& x) {x++;}
void outer(int& x) {inner(x);}

int main()
{
    int x = 100;
    outer(x);
    cout << x << endl;
    // float x = 1;
    // cout << x/2 << endl;
    // ptree pt;
    // read_xml("../params.xml", pt);

    // Parameters p("params.xml");
    // cout << p << endl;

    // cout << INFINITY << endl;
    // Task t("MyType", 2, 1, INFINITY, 40);
    // cout << t << endl;
    // t.start(5);
    // t.pause(6);
    // t.finish(8);
    // t.pause(7);
    // t.start(9);
    // t.finish(15);
    // t.start(9);


    // TaskType t(pt.get_child("task"));
    //
    // for (int i = 0; i < 4; i++)
    //     cout << t.genTask(0) << endl;

    // Task t1("t1", 8, 0, 4, 100);
    // Task t2("t2", 10, 0, 4, 100);
    //
    // if (t1 < t2)
    //     cout << t1 << " is of lesser priority than " << t2 << endl;
    // else
    //     cout << t1 << " is of higher priority than " << t2 << endl;

    // for (auto& a : pt)
    // {
    //     cout << '[' << a.first << "]\n";
    //     for (auto& b : a.second)
    //     {
    //         cout << b.first << "=" << b.second.data() << "\n";
    //     }
    // }

    return 0;
}

void test()
{
    // struct Flight
    // {
    //     std::string  carrier;
    //     unsigned     number;
    //     // Date         date;
    //     bool         cancelled;
    // };
    // typedef std::vector<Flight> Sked;

    // Sked ans;
    // for (ptree::value_type v : pt.get_child("sked"))
    // {
    //     if(v.first == "flight")
    //     {
    //         Flight f;
    //         f.carrier = v.second.get<string>("carrier");
    //         f.number = v.second.get<unsigned>("number");
    //         // f.date = v.second.get<Date>("date");
    //         f.cancelled = v.second.get("<xmlattr>.cancelled", false);
    //         ans.push_back(f);
    //     }
    // }
}
