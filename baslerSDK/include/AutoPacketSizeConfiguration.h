/*
    Note: Before getting started, Basler recommends reading the Programmer's Guide topic
    in the pylon C++ API documentation that gets installed with pylon.
    If you are upgrading to a higher major version of pylon, Basler also
    strongly recommends reading the Migration topic in the pylon C++ API documentation.

    This configuration enables auto packet size in the stream grabber node map
    When AutoPacketSize is enabled, pylon will automatically determine the optimum packet size
    for GigE cameras.
*/
#pragma once

#include <pylon/ConfigurationEventHandler.h>

namespace Pylon
{
    class CInstantCamera;
}

class CAutoPacketSizeConfiguration : public Pylon::CConfigurationEventHandler
{
public:    
    void OnOpened( Pylon::CInstantCamera& camera) 
    {
        try
        {
            // The AutoPacketSize feature is in the stream grabber node map
            // If the feature isn't available for the current camera,
            // a NULL pointer will be returned. The IsWritable() call below handles the 
            // NULL argument correctly and returns false.
            GenApi::CBooleanPtr ptrAutoPacketSize = camera.GetStreamGrabberNodeMap().GetNode("AutoPacketSize");
            
            if (GenApi::IsWritable(ptrAutoPacketSize))
            {
                ptrAutoPacketSize->SetValue(true);
            }
        }
        catch (Pylon::GenericException& /*e*/)
        {
            throw GENICAM_NAMESPACE::RuntimeException("Could not apply AutoPacketSizeConfiguration.", __FILE__, __LINE__);
        }
    }
};

