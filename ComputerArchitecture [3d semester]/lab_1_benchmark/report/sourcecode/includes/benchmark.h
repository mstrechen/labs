#ifndef BENCHMARK_H_
#define BENCHMARK_H_

#include<vector>
#include<tuple>
#include<functional>
#include<ostream>
#include "listoftests.h"

using namespace std;

#ifndef MAX_COUNT_OF_MARKS
    #define MAX_COUNT_OF_MARKS (25)
#endif

string get_color_by_code(int code);

void process_benchmark(ostream & out);


int64_t measure_time_microseconds(
    const function<tuple<int, string, double>() > & func,
    tuple<int, string, double> & result);

vector<int64_t> get_benchmark_results_microseconds(
    const vector<function<tuple<int, string, double>() > > & functions,
    vector<tuple<int, string, double> > & results);


void print_service_info(ostream &);
void print_first_row(ostream &);
void print_last_row(ostream &);
void print_row(
    ostream & cout, 
    tuple<int, string, double> & function_info, 
    int64_t time_microseconds,
    int64_t min_time_microseconds);



#endif