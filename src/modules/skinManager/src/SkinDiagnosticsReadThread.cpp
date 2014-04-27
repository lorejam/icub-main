/* 
 * Copyright (C) 2014 Francesco Giovannini, iCub Facility - Istituto Italiano di Tecnologia
 * Authors: Francesco Giovannini
 * email:   francesco.giovannini@iit.it
 * website: www.robotcub.org 
 * Permission is granted to copy, distribute, and/or modify this program
 * under the terms of the GNU General Public License, version 2 or any
 * later version published by the Free Software Foundation.
 *
 * A copy of the license can be found at
 * http://www.robotcub.org/icub/license/gpl.txt
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
 * Public License for more details
 */

#include "iCub/skinManager/SkinDiagnosticsReadThread.h"
#include "iCub/skinManager/SkinDiagnosticsErrorCodes.h"


#include <iostream>
#include <sstream>

#include <yarp/os/Time.h>

using iCub::skinManager::SkinDiagnosticsReadThread;

using std::cerr;
using std::cout;

using yarp::os::RateThread;
using yarp::os::Time;

#define SKINMANAGER_TH_DIAGREAD_DEBUG 1


/* *********************************************************************************************************************** */
/* ******* Constructor                                                      ********************************************** */   
SkinDiagnosticsReadThread::SkinDiagnosticsReadThread(const int aPeriod, const yarp::os::ResourceFinder &aRf)
    : RateThread(aPeriod) {
    period = aPeriod;
    rf = aRf;

    dbgTag = "SkinDiagnosticsReadThread: ";
}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Destructor                                                       ********************************************** */   
SkinDiagnosticsReadThread::~SkinDiagnosticsReadThread() {}
/* *********************************************************************************************************************** */


/* *********************************************************************************************************************** */
/* ******* Initialise thread                                                ********************************************** */
bool SkinDiagnosticsReadThread::threadInit(void) {
    using std::string;
    using yarp::os::Value;

    cout << dbgTag << "Initialising. \n";

    // Get module name
    string moduleName = rf.check("name", Value("skiManager"), "module name (string)").asString();
    string portNameRoot = "/" + moduleName;

    // Open ports
    portSkinDiagnosticsErrorsIn.open((portNameRoot + "/diagnostics/skin/errors:i").c_str());
    portSkinManagerErrorsOut.open((portNameRoot + "/diagnostics/skin/errors:o").c_str());
    
    cout << dbgTag << "Initialised correctly. \n";
    
    return true;
}
/* *********************************************************************************************************************** */



/* *********************************************************************************************************************** */
/* ******* Run thread                                                       ********************************************** */
void SkinDiagnosticsReadThread::run(void) {
    using iCub::skin::diagnostics::SkinErrorCode;   // FG: Skin diagnostics error codes
    using std::deque;
    using std::stringstream;
    using yarp::sig::Vector;
    using yarp::os::Bottle;

    
    // Read sensor data from port
    Vector *data = portSkinDiagnosticsErrorsIn.read(false);
    if ((data) && (data->size() == 3)) {
#if SKINMANAGER_TH_DIAGREAD_DEBUG
        // Print out FT sensor data
        cout << dbgTag << "Skin diagnostics data: ";
        for (size_t i = 0; i < data->size(); ++i) {
            cout << (*data)[i] << " ";
        }
        cout << "\n";
#endif
    
        // Prepare output string
        Bottle &out = portSkinManagerErrorsOut.prepare();
        out.clear();

        // Extract skin errors
        deque<bool> errorTaxels;   // FG: Set to true if the taxel returned an error
        int errorCode = (*data)[2];
        if (!(errorCode & SkinErrorCode::StatusOK)) {
            // An error occurred
            // Handle stuck taxel data
            if (errorCode & 0xFFF0) {
                errorTaxels.resize(12, false);
                int errorMask = SkinErrorCode::TaxelStuck00;
                for (int tax = 0; tax < 12; ++tax) {
                    errorTaxels[tax] = errorCode & errorMask;
                    errorMask = errorMask * 2;  // Increment error mask
                }
            }

            if (errorTaxels.size() > 0) {
                // Errors occurred
                stringstream ss;
                ss << "ERROR: CanBusSkin: Board ID (" << (*data)[0] <<"): Sensor ID (" << (*data)[1] << "): The following taxels are stuck/faulty: \t";
                for (size_t i = 0; i < errorTaxels.size(); ++i) {
                    if (errorTaxels[i]) {
                        ss << i << " ";
                    }
                }

                out.addString(ss.str().c_str());
            }

            // Handle other data
            stringstream ss;
            if (errorCode & SkinErrorCode::ErrorReading12C) {
                ss << "ERROR: CanBusSkin: Board ID (" << (*data)[0] <<"): Sensor ID (" << (*data)[1] << "): Cannot read from this sensor."; 
            } else if (errorCode & SkinErrorCode::ErrorACK4C) {
                ss << "ERROR: CanBusSkin: Board ID (" << (*data)[0] <<"): Sensor ID (" << (*data)[1] << "): This sensor does not respond to the initialisation message (0x4C)."; 
            }
            out.addString(ss.str().c_str());
        } else {
    #ifndef NODEBUG
            stringstream ss;
            ss << "DEBUG: CanBusSkin: Skin is working fine.";
            out.addString(ss.str().c_str());
    #endif
        }

        // Write out errors
        portSkinManagerErrorsOut.write();
    }
}  
/* *********************************************************************************************************************** */



/* *********************************************************************************************************************** */
/* ******* Release thread                                                   ********************************************** */
void SkinDiagnosticsReadThread::threadRelease(void) {
    cout << dbgTag << "Releasing. \n";
    
    // Interrupt ports
    portSkinDiagnosticsErrorsIn.interrupt();
    portSkinManagerErrorsOut.interrupt();

    // Close ports
    portSkinDiagnosticsErrorsIn.close();
    portSkinManagerErrorsOut.close();

    cout << dbgTag << "Released. \n";
}
/* *********************************************************************************************************************** */