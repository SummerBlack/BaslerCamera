

//-----------------------------------------------------------------------------
//  (c) 2004-2018 by Basler Vision Technologies
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Interface to video writer parameters.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_VideoWriterParams_PARAMS_H
#define Basler_VideoWriterParams_PARAMS_H

#include <GenApi/IEnumerationT.h>
#include <GenApi/NodeMapRef.h>
#include <GenApi/DLLLoad.h>

// common node types
#include <GenApi/IBoolean.h>
#include <GenApi/ICategory.h>
#include <GenApi/ICommand.h>
#include <GenApi/IEnumeration.h>
#include <GenApi/IEnumEntry.h>
#include <GenApi/IFloat.h>
#include <GenApi/IInteger.h>
#include <GenApi/IString.h>
#include <GenApi/IRegister.h>

#ifdef __GNUC__
#   undef GCC_VERSION
#   define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#   undef GCC_DIAGNOSTIC_AWARE
#   define GCC_DIAGNOSTIC_AWARE          (GCC_VERSION >= 40200)
#   undef GCC_DIAGNOSTIC_PUSH_POP_AWARE
#   define GCC_DIAGNOSTIC_PUSH_POP_AWARE (GCC_VERSION >= 40600)
#else
#   undef GCC_DIAGNOSTIC_AWARE
#   define GCC_DIAGNOSTIC_AWARE 0
#endif

#ifdef __GNUC__
    // GCC_DIAGNOSTIC_AWARE ensures that the internal deprecated warnings can be ignored by gcc.
    // As a result older gcc will not generate warnings about really used deprecated features.
#   if GCC_DIAGNOSTIC_AWARE
#       define GENAPI_DEPRECATED_FEATURE __attribute__((deprecated))
#   else
#       define GENAPI_DEPRECATED_FEATURE
#   endif
#elif defined(_MSC_VER)
#   define GENAPI_DEPRECATED_FEATURE __declspec(deprecated)
#else
#   define GENAPI_DEPRECATED_FEATURE
#endif

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic push
#   endif
#   pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif


//! The namespace containing the device's control interface and related enumeration types
namespace Basler_VideoWriterParams
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    
    //! Valid values for CompressionMode
    enum CompressionModeEnums
    {
        CompressionMode_Bitrate,  //!<The resulting stream has a constant bit rate.
        CompressionMode_Quality   //!<The resulting stream has a constant quality.
        
    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************
    

    //! Interface to video writer parameters.
    class CVideoWriterParams_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            CVideoWriterParams_Params(void);

            //! Destructor
            ~CVideoWriterParams_Params(void);

            //! Initializes the references
            void _Initialize(GENAPI_NAMESPACE::INodeMap*);

            //! Return the vendor of the camera
            const char* _GetVendorName(void);

            //! Returns the camera model name
            const char* _GetModelName(void);
        
        //! \endcond

    //----------------------------------------------------------------------------------------------------------------
    // References to features
    //----------------------------------------------------------------------------------------------------------------
    public:
        
    //! \name ImageParameters - Contains parameters for configuring the image.
    //@{
    /*!
        \brief Width of the image (in pixels).

        Width of the image (in pixels).
    
        \b Visibility = Invisible
    
    */
    GENAPI_NAMESPACE::IInteger &Width;
    
    //@}
    

    //! \name ImageParameters - Contains parameters for configuring the image.
    //@{
    /*!
        \brief Height of the image (in pixels).

        Height of the image (in pixels).
    
        \b Visibility = Invisible
    
    */
    GENAPI_NAMESPACE::IInteger &Height;
    
    //@}
    

    //! \name RecordingOptions - Contains parameters for configuring the recording.
    //@{
    /*!
        \brief Frame rate (in Hertz) of the video to be recorded.

        Frame rate (in Hertz) of the video to be recorded.
    
        \b Visibility = Beginner
    
    */
    GENAPI_NAMESPACE::IFloat &PlaybackFrameRate;
    
    //@}
    

    //! \name RecordingOptions - Contains parameters for configuring the recording.
    //@{
    /*!
        \brief Sets the compression mode.

        Sets the compression mode. You can choose whether to keep the bit rate or the quality of the resulting video stream constant.
    
        \b Visibility = Beginner
    
    */
    GENAPI_NAMESPACE::IEnumerationT<CompressionModeEnums > &CompressionMode;
    
    //@}
    

    //! \name RecordingOptions - Contains parameters for configuring the recording.
    //@{
    /*!
        \brief Quality of the resulting compressed stream.

        Quality of the resulting compressed stream. The quality has a direct influence on the resulting bit rate. The optimal bit rate is calculated based on the input values height, width, and playback frame rate (WIDTH * HEIGHT * PLAYBACKFRAMERATE * 0.25). This is then normalized to the quality value range 1-100, where 100 corresponds to the optimum bit rate and 1 to the lowest bit rate.
    
        \b Visibility = Beginner
    
    */
    GENAPI_NAMESPACE::IFloat &Quality;
    
    //@}
    

    //! \name RecordingOptions - Contains parameters for configuring the recording.
    //@{
    /*!
        \brief Bit rate of the resulting compressed stream.

        Bit rate of the resulting compressed stream.
    
        \b Visibility = Beginner
    
    */
    GENAPI_NAMESPACE::IInteger &Bitrate;
    
    //@}
    

    //! \name RecordingOptions - Contains parameters for configuring the recording.
    //@{
    /*!
        \brief Number of threads used for recording the video.

        Number of threads used for recording the video.
    
        \b Visibility = Expert
    
    */
    GENAPI_NAMESPACE::IInteger &ThreadCount;
    
    //@}
    

    //! \name Statistics - Contains parameters with statistical information about the recording.
    //@{
    /*!
        \brief Number of frames written since starting the recording.

        Number of frames written since starting the recording.
    
        \b Visibility = Beginner
    
    */
    GENAPI_NAMESPACE::IInteger &FrameCount;
    
    //@}
    

    //! \name Statistics - Contains parameters with statistical information about the recording.
    //@{
    /*!
        \brief Bytes written to file since starting the recording.

        Bytes written to file since starting the recording.
    
        \b Visibility = Beginner
    
    */
    GENAPI_NAMESPACE::IInteger &BytesWritten;
    
    //@}
    


    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            CVideoWriterParams_Params(CVideoWriterParams_Params&);

            //! not implemented assignment operator
            CVideoWriterParams_Params& operator=(CVideoWriterParams_Params&);

        //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CVideoWriterParams_Params::CVideoWriterParams_Params(void)
        : Width( *new GENAPI_NAMESPACE::CIntegerRef() )
        , Height( *new GENAPI_NAMESPACE::CIntegerRef() )
        , PlaybackFrameRate( *new GENAPI_NAMESPACE::CFloatRef() )
        , CompressionMode( *new GENAPI_NAMESPACE::CEnumerationTRef<CompressionModeEnums>() )
        , Quality( *new GENAPI_NAMESPACE::CFloatRef() )
        , Bitrate( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ThreadCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , FrameCount( *new GENAPI_NAMESPACE::CIntegerRef() )
        , BytesWritten( *new GENAPI_NAMESPACE::CIntegerRef() )
        
    {
    }

    inline CVideoWriterParams_Params::~CVideoWriterParams_Params(void)
    {
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&Width );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&Height );
        delete static_cast < GENAPI_NAMESPACE::CFloatRef*> (&PlaybackFrameRate );
        delete static_cast < GENAPI_NAMESPACE::CEnumerationTRef<CompressionModeEnums> *> (&CompressionMode );
        delete static_cast < GENAPI_NAMESPACE::CFloatRef*> (&Quality );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&Bitrate );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&ThreadCount );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&FrameCount );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&BytesWritten );
        
    }

    inline void CVideoWriterParams_Params::_Initialize(GENAPI_NAMESPACE::INodeMap* _Ptr)
    {
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Width )->SetReference(_Ptr->GetNode("Width"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Height )->SetReference(_Ptr->GetNode("Height"));
    static_cast<GENAPI_NAMESPACE::CFloatRef*> (&PlaybackFrameRate )->SetReference(_Ptr->GetNode("PlaybackFrameRate"));
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CompressionModeEnums> *> (&CompressionMode )->SetReference(_Ptr->GetNode("CompressionMode"));
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CompressionModeEnums> *> (&CompressionMode )->SetNumEnums(2);
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CompressionModeEnums> *> (&CompressionMode )->SetEnumReference( CompressionMode_Bitrate, "Bitrate" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<CompressionModeEnums> *> (&CompressionMode )->SetEnumReference( CompressionMode_Quality, "Quality" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&Quality )->SetReference(_Ptr->GetNode("Quality"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&Bitrate )->SetReference(_Ptr->GetNode("Bitrate"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&ThreadCount )->SetReference(_Ptr->GetNode("ThreadCount"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&FrameCount )->SetReference(_Ptr->GetNode("FrameCount"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&BytesWritten )->SetReference(_Ptr->GetNode("BytesWritten"));
    
    }

    inline const char* CVideoWriterParams_Params::_GetVendorName(void)
    {
        return "Basler";
    }

    inline const char* CVideoWriterParams_Params::_GetModelName(void)
    {
        return "VideoWriterParams";
    }

    //! \endcond

} // namespace Basler_VideoWriterParams

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_VideoWriterParams_PARAMS_H
