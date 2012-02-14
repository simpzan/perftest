/******************************************************************************** 
Copyright (c) 2012, Francisco Claude.
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

using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::wstring;
using std::string;

#include "perftest_runner.h"


using perftest::RunExperiments;

int main(int argc, char **argv) {
    // TODO: we can use optargs or something like that to support more flags. 
    // With the current interface it would be an overkill.
    if (argc!=3) {
        cout << "usage: " << argv[0] << " <input:json> <output:json>" << endl;
        return 0;
    }

    if (string(argv[1]) == string(argv[2])) {
        cerr << "You are trying to overwrite the input file." << endl;
        return 3;
    }

    ifstream input(argv[1]);
    if (!input.good()) {
        cerr << "Error opening " << argv[1] << " for reading" << endl;
        return 1;
    }

    // TODO: Check if output file exists and only allow overwrite with a specific flag?

    ofstream output(argv[2]);
    if (!output.good()) {
        cerr << "Error opening " << argv[2] << " for writing" << endl;
        return 2;
    }

    RunExperiments(input, output);

    input.close();
    output.close();

    return 0;
}
