	/******************************************************************************** 
Copyright (c) 2012, Roberto Konow, Francisco Claude
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
#include <sstream>

#include "system_information.h"

using std::stringstream;
using std::endl;
using std::string;

namespace perftest { 
	// TODO: Add CPU speed , OS Version , Compilation options

	const char *GetUserName()
	{
		#if defined(WIN32) && !defined(__GNUC__)
			return "Not Available\0";
		#else
			return getenv("USER");
		#endif
	}
	const int GetNumProcessors()
	{
		#if defined(WIN32) && !defined(__GNUC__)
			return -1;
		#else
			return sysconf(_SC_NPROCESSORS_ONLN);
		#endif
	}
	const int GetMemory()
	{
		#if defined(WIN32) && !defined(__GNUC__)
			return -1;
		#else
			return (sysconf(_SC_PHYS_PAGES) * sysconf(_SC_PAGESIZE))/(1024*1024);
		#endif
		
	}
	const string GetSystemInformation()
	{
		stringstream result;
		result <<  "num_processors: "<< GetNumProcessors() << endl << 
		"memory: " << GetMemory()  << endl << 
		"username: \"" << GetUserName() << "\"" << endl;
		return result.str();
	}

}