#include "benchmark.h"
#include "textstyle.h"
#include "cpuinfo.h"
#include<chrono>
#include<cmath>
#include<iomanip>
#include<algorithm>


void process_benchmark(
    ostream & cout){
        print_service_info(cout);
        print_first_row(cout);

        vector<tuple<int, string, double> > results;
       
        auto benchmark_results = 
            get_benchmark_results_microseconds(get_functions_to_test(), results);
        int64_t min_time = *min_element(benchmark_results.begin(), benchmark_results.end());

        for(int i = 0; i < (int)results.size(); i++)
            print_row(cout, results[i], benchmark_results[i], min_time);

        print_last_row(cout);
}

int64_t measure_time_microseconds(
    const function<tuple<int, string, double>() > & func,
    tuple<int, string, double> & result){
        
    auto begin = chrono::high_resolution_clock::now();
    result = func();
    auto end = chrono::high_resolution_clock::now();
        
    return  chrono::duration_cast<chrono::microseconds>(end - begin).count();
}

vector<int64_t> get_benchmark_results_microseconds(
    const vector<function<tuple<int, string, double>() > > & functions,
    vector<tuple<int, string, double> > & results){
        
    results.resize(functions.size());
    vector<int64_t> execution_time;
    for(int i = 0; i < (int)functions.size(); i++)
        execution_time.push_back(
            measure_time_microseconds(functions[i], results[i])
        );

    return execution_time;
}

string get_color_by_code(int code){
    switch(code){
        case 0 : return TEXT::REGULAR; break;
        case 1 : return TEXT::RED; break;
        case 2 : return TEXT::GREEN; break;
        case 3 : return TEXT::YELLOW; break;
        case 4 : return TEXT::BLUE; break;
        case 5 : return TEXT::MAGENTA; break;
        case 6 : return TEXT::CYAN; break;
        case 7 : return TEXT::BLACK; break;
        default :
            throw "WRONG TEXT COLOR CODE";
    }
}

void print_service_info(ostream & cout){
    cout << TEXT::RED 
        << "CPU vendor : "
        << get_cpu_vendor() 
        << "    TYPE : " 
        << get_bit_capacity() 
        << "-BIT" 
        << endl;
    cout << TEXT::GREEN 
        << "Count of iterations : " 
        << COUNT_OF_ITERATIONS 
        << "(10^" << (int)log10(COUNT_OF_ITERATIONS) << ')'
        << TEXT::REGULAR
        << endl;
}

void print_last_row(ostream & cout){
    cout << TEXT::CORNER<90>() << endl;
}


void print_first_row(ostream & cout){
    cout << TEXT::BLACK << TEXT::WHITE_BACKGROUND << 
    "   OPERATION :"
    "  TIME (ms)  :"
    "REAL TIME (ms):"
    "OP PER SEC:"
    "   %   :"
    " " 
    << TEXT::perfomance_line(MAX_COUNT_OF_MARKS, 0) 
    << "  "
    << TEXT::REGULAR
    << endl;
}



void print_row(
    ostream & cout, 
    tuple<int, string, double> & function_info, 
    int64_t time,
    int64_t min_time){

    string color = get_color_by_code(get<0>(function_info));

    int64_t real_time = time - min_time;
    if(time == min_time)
        real_time = time;
    double percent = 100.0 * min_time / real_time;
    double operations_per_second = COUNT_OF_ITERATIONS * 1e6 / real_time;

    int perfomance;
    if(percent > 100)
        perfomance = MAX_COUNT_OF_MARKS;
    else
        perfomance = ceil(percent * MAX_COUNT_OF_MARKS / 100);

    
    cout << TEXT::CORNER()
        << color 
        << setw(12)
        << get<1>(function_info)
        << TEXT::REGULAR
        << ":"
        << setprecision(3) << (fixed) << setw(12)
        << time / 1e3
        << " : "
        << setw(12)
        << real_time / 1e3 
        << " :"
        << setw(9)
        << setprecision(2) <<  (scientific) <<  operations_per_second
        << " : "
        << setprecision(1) << (fixed) << setw(5)
        << percent
        << " : "
        << TEXT::perfomance_line(perfomance, MAX_COUNT_OF_MARKS - perfomance)
        << " " 
        << TEXT::CORNER()
        << endl;
}