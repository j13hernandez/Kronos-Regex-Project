/** Copyright 2015 Prof. Ayat Hatem Website & Daniel Santos
 *  @file     kronos_parse_class.cpp
 *  @author   Daniel Santos (dsantos) Some of the work
 *  @date     04/15/2016
 *  @version  1.0
 *
 *  @brief    This program parse through the log of the InTouch
 *  device to get information about its boot and services
 * */
#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "kronos_parse_class.hpp"

using std::string;
using boost::regex;
using std::ifstream;
using std::ofstream;
using boost::posix_time::ptime;
using boost::posix_time::time_duration;
using boost::posix_time::time_from_string;

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "ps4a [file name]" << std::endl;
        return -1;
    }

    string f_name = argv[1];
    ifstream input(f_name.c_str() );
    ofstream output((f_name + ".rpt").c_str());


    string header = "=== Device boot ===\n";
    string incomplete = "**** Incomplete boot **** \n\n";
    string boot_time = "   Boot Time: ";
    bool visited_start = false;

    regex start_boot("([0-9]{4})-([0-9]{1,2})-([0-9]{1,2}) "
    "([0-9]{1,2}):([0-9]{1,2}):([0-9]{1,2}): \\(log.c.166\\) server started.*");
    regex end_boot("([0-9]{4})-([0-9]{1,2})-([0-9]{1,2}) "
    "([0-9]{1,2}):([0-9]{1,2}):([0-9]{1,2}).*"
    ":.*oejs.AbstractConnector:Started SelectChannelConnector.*");

    // My regex for the service boot and service started
    regex service_boot("Starting\\ Service\\.\\ \\ ([a-zA-z]+).+");
    regex service_started("Service\\ started\\ successfully\\.\\ \\ "
                              "([a-zA-Z]+).+\\(([0-9]+).+");

    int i = 1;
    string line, start, end;
    int num_of_boot = 0;
    int num_of_completed = 0;
    boost::smatch m;
    int current_boot = 0;
    std::vector<Boot> vBoot;

    // Parse input file line by line.
    while (getline(input, line)) {
        if ( regex_match(line, m, start_boot) && !visited_start ) {
            visited_start = true;
            num_of_boot++;
            start = m[1] + '-' + m[2] + '-' + m[3] + ' ';
            start  += m[4] + ':'  + m[5] + ':'  + m[6];
            // Here I create a new Boot and append it to the vector
            vBoot.push_back(Boot(f_name));
            // Here I set the information gotten of the start of the boot
            vBoot[current_boot].setFileName(f_name);
            vBoot[current_boot].setStartLine(i);
            vBoot[current_boot].setStartTime(time_from_string(start));

        } else if (regex_match(line, m, end_boot) && visited_start) {
            visited_start = false;
            end = m[1] + '-' + m[2] + '-' + m[3] + ' ';
            end += m[4] + ':'  + m[5] + ':'  + m[6];

            ptime s_time(time_from_string(start));
            ptime e_time(time_from_string(end));
            time_duration time_difference = e_time - s_time;

            // Here I am settings the information aobut the end of the boot
            vBoot[current_boot].setEndLine(i);
            vBoot[current_boot].setEndTime(time_from_string(end));
            vBoot[current_boot].setDuration(time_difference);
            vBoot[current_boot].completed();
            // Becuase the boot is complete, increment current boot
            current_boot++;
            num_of_completed++;  // Increment the completed variable

        } else if (regex_match(line, m, start_boot) && visited_start) {
            current_boot++;  // Found another boot
            num_of_boot++;  // Found another boot
            start = m[1] + '-' + m[2] + '-' + m[3] + ' ';
            start  += m[4] + ':'  + m[5] + ':'  + m[6];

            // Here I create a new Boot and append it to the vector
            vBoot.push_back(Boot(f_name));
            // Here I set the information gotten of the start of the boot
            vBoot[current_boot].setFileName(f_name);
            vBoot[current_boot].setStartLine(i);
            vBoot[current_boot].setStartTime(time_from_string(start));
        } else if (regex_match(line, m, service_boot) && visited_start) {
            // Here I get the service by the name found in the log
            Service &service = vBoot[current_boot].getService(m[1]);
            // Change the state of the service to started
            service.started();
            // Set the start line
            service.setStartLine(i);
        } else if (regex_match(line, m, service_started) && visited_start) {
            // Here I get the service found in the log
            Service &service = vBoot[current_boot].getService(m[1]);
            // Set the duration
            service.setDuration(m[2]);
            // And change its state to completed
            service.completed();
            // Set the line in which it was completed
            service.setEndLine(i);
        }
        ++i;
    }
    if (regex_match(line, m, start_boot) && visited_start) {
        current_boot++;
        num_of_boot++;
        start = m[1] + '-' + m[2] + '-' + m[3] + ' ';
        start  += m[4] + ':'  + m[5] + ':'  + m[6];

        vBoot.push_back(Boot(f_name));
        vBoot[current_boot].setFileName(f_name);
        vBoot[current_boot].setStartLine(i);
        vBoot[current_boot].setStartTime(time_from_string(start));
    } else if (regex_match(line, m, service_boot) && visited_start) {
        // Here I get the service by the name found in the log
        Service &service = vBoot[current_boot].getService(m[1]);
        // Change the state of the service to started
        service.started();
        // Set the start line
        service.setStartLine(i);
    }

    // Format the header of the put file
    std::stringstream ss;
    output << "Device Boot Report" << std::endl << std::endl
        << "InTouch log file: " << f_name << std::endl
        << "Lines Scanned: " << i << std::endl << std::endl
        << "Device boot count: initiated = " << num_of_boot
        << ", completed: " << num_of_completed << "\n\n\n";

    // Prints all the boots from the vector.
    for (unsigned int k = 0; k < vBoot.size(); k++)
        output << vBoot.at(k) << std::endl;

    input.close();
    output.close();
    return 0;
}
