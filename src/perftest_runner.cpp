/******************************************************************************** 
Copyright (c) 2012, Francisco Claude, Roberto Konow.
All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    * Neither the name of perftest. nor the names of its
      contributors may be used to endorse or promote products derived from this
      software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

********************************************************************************/


#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdlib.h>
#include <JSON.h>
#include <JSONValue.h>

using std::ifstream;
using std::ofstream;
using std::wstring;
using std::endl;
using std::cerr;
using std::ios;
using std::cout;

#include "perftest_runner.h"


namespace perftest {

    map<string, fnptr> &RegisterExperiment(const char *name, fnptr function) {
        static map<string, fnptr> registeredExperiments;
        if (function == NULL) return registeredExperiments;
        registeredExperiments[string(name)] = function;
        return registeredExperiments;
    }

    void RunExperiments(ifstream &input, ofstream &output) {
        // Read input file
        input.seekg(0, ios::end);
        size_t input_length = input.tellg();
        input.seekg(0, ios::beg);
        char * input_content = new char[input_length+1];
        input.read(input_content, input_length);
        input_content[input_length] = 0;

        map<string, fnptr> &registeredExperiments = RegisterExperiment("", NULL);
        cout << "Registered experiments: " << endl;
        for(map<string, fnptr>::iterator it = registeredExperiments.begin(); it != registeredExperiments.end(); ++it)
            cout << "\t- " << it->first << endl;

        // Create JSON object
        JSONValue *root = JSON::Parse(input_content);
        delete [] input_content;

        // Iterate over each object
        if (!root->IsObject()) {
            cerr << "Error, the input file does not contain objects." << endl;
            return;
        }

        cout << endl;
        cout << "* Running Experiments" << endl;
        output << "{" << endl;
        // This is a vector of <sdt::wstring, JSONValue>
        JSONObject objects = root->AsObject();
      
        Timer overall_time;        
        for(JSONObject::iterator it = objects.begin(); it != objects.end(); ++it) {
            string tmp((it->first).begin(), (it->first).end());
            output << "experiment_name: \"" << tmp << "\"" << endl;
            if (registeredExperiments.count(tmp) == 0) {
                cout << "\tExperiment " << tmp << " is not registered." << endl;
                output << "result: \"error\"" << endl;
            } else {
                cout << "\tRunning experiment " << tmp << endl;
                Timer experiment_time;
                wstring result = registeredExperiments[tmp](it->second->Stringify());

                experiment_time.stop();
                
                string tmp_result(result.begin(), result.end());
                output << "result: " << tmp_result << endl;
                output << "experiment_time:" << experiment_time.elapsedTime() << endl;
            }
        }
        overall_time.stop();
        output << "overall_time:" << overall_time.elapsedTime() << endl;
        output << GetSystemInformation();
        output << "}" << endl;
    }
};
