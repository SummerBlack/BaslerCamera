

//-----------------------------------------------------------------------------
//  (c) 2004-2018 by Basler Vision Technologies
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Interface to instant camera parameters
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_InstantCameraParams_PARAMS_H
#define Basler_InstantCameraParams_PARAMS_H

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
namespace Basler_InstantCameraParams
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    

    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************
    

    //! Interface to instant camera parameters
    class CInstantCameraParams_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            CInstantCameraParams_Params(void);

            //! Destructor
            ~CInstantCameraParams_Params(void);

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
        
    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The maximum number of buffers that are allocated and used for grabbing.

        
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IInteger &MaxNumBuffer;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The maximum number of buffers that are queued in the stream grabber input queue.

        
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IInteger &MaxNumQueuedBuffer;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The maximum number of grab results available at any time during a grab session. This value can be limited to save resources. Furthermore, it can be used to check that the grab results are returned correctly.

        
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IInteger &MaxNumGrabResults;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief Enables/disables the use of a chunk node map for each grab result. Grab result chunk node maps can be disabled to save resources.

        
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IBoolean &ChunkNodeMapsEnable;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief If larger than 0, a static chunk node map pool is used instead of dynamic chunk node map creation.

        
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IInteger &StaticChunkNodeMapPoolSize;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief Enables/disables the grabbing of camera events while images are grabbed. Is writable when the camera object is closed.

        
    
        \b Visibility = Expert
    
    */
    GENAPI_NAMESPACE::IBoolean &GrabCameraEvents;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The camera object is set to monitor mode when enabled, e.g. when using the GigE multicast feature. Is writable when the camera object is closed.

        
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IBoolean &MonitorModeActive;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The number of buffers queued at Low Level API stream grabber.

        
        
            This is the number of buffers that are queued for grabbing in the stream grabber.
            The number is influenced by the number of available free buffers and the
            maximum number of buffers that can be queued.
            See also the MaxNumBuffer and MaxNumQueuedBuffer parameters.

            This parameter can be used to check whether the number of buffers ready for grabbing
            is stable, which means that the image processing is fast enough to keep up with the
            rate of incoming images when using the GrabStrategy_OneByOne grab strategy.
        
        
    
        \b Visibility = Expert
    
    */
    GENAPI_NAMESPACE::IInteger &NumQueuedBuffers;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The number of grab result buffers in the output queue that are ready for retrieval.

        
    
        \b Visibility = Expert
    
    */
    GENAPI_NAMESPACE::IInteger &NumReadyBuffers;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The number of empty buffers that are not used for grabbing yet.

        
    
        \b Visibility = Expert
    
    */
    GENAPI_NAMESPACE::IInteger &NumEmptyBuffers;
    
    //@}
    

    //! \name Root - Instant camera parameters.
    //@{
    /*!
        \brief The size of the grab result buffer output queue.

        
    
        \b Visibility = Expert
    
    */
    GENAPI_NAMESPACE::IInteger &OutputQueueSize;
    
    //@}
    

    //! \name InternalGrabEngineThread - Parameters of the internal grab engine thread.
    //@{
    /*!
        \brief If enabled, the user can set a custom priority for the internal grab engine thread operating the stream grabber. Otherwise the priority defaults to 25.

        
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IBoolean &InternalGrabEngineThreadPriorityOverride;
    
    //@}
    

    //! \name InternalGrabEngineThread - Parameters of the internal grab engine thread.
    //@{
    /*!
        \brief The internal grab engine thread priority.

        This value sets the absolute thread priority for the internal grab engine thread operating the stream grabber.
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IInteger &InternalGrabEngineThreadPriority;
    
    //@}
    

    //! \name GrabLoopThread - Parameters of the optional grab loop  thread.
    //@{
    /*!
        \brief If enabled, the user can set a custom timeout for the grab loop thread's call to RetrieveResult. RetrieveResult is configured to throw an exception on timeout, which will stop the grab session.

        
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IBoolean &GrabLoopThreadUseTimeout;
    
    //@}
    

    //! \name GrabLoopThread - Parameters of the optional grab loop  thread.
    //@{
    /*!
        \brief A custom timeout for the grab loop thread's call to RetrieveResult. RetrieveResult is configured to throw an exception on timeout, which will stop the grab session.

        
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IInteger &GrabLoopThreadTimeout;
    
    //@}
    

    //! \name GrabLoopThread - Parameters of the optional grab loop  thread.
    //@{
    /*!
        \brief If enabled, the user can set a custom priority for the grab loop thread. Otherwise, the priority of the newly created thread is not changed.

        
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IBoolean &GrabLoopThreadPriorityOverride;
    
    //@}
    

    //! \name GrabLoopThread - Parameters of the optional grab loop  thread.
    //@{
    /*!
        \brief The grab loop thread priority.

        This value sets the absolute thread priority for the grab loop thread.
    
        \b Visibility = Guru
    
    */
    GENAPI_NAMESPACE::IInteger &GrabLoopThreadPriority;
    
    //@}
    


    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            CInstantCameraParams_Params(CInstantCameraParams_Params&);

            //! not implemented assignment operator
            CInstantCameraParams_Params& operator=(CInstantCameraParams_Params&);

        //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CInstantCameraParams_Params::CInstantCameraParams_Params(void)
        : MaxNumBuffer( *new GENAPI_NAMESPACE::CIntegerRef() )
        , MaxNumQueuedBuffer( *new GENAPI_NAMESPACE::CIntegerRef() )
        , MaxNumGrabResults( *new GENAPI_NAMESPACE::CIntegerRef() )
        , ChunkNodeMapsEnable( *new GENAPI_NAMESPACE::CBooleanRef() )
        , StaticChunkNodeMapPoolSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GrabCameraEvents( *new GENAPI_NAMESPACE::CBooleanRef() )
        , MonitorModeActive( *new GENAPI_NAMESPACE::CBooleanRef() )
        , NumQueuedBuffers( *new GENAPI_NAMESPACE::CIntegerRef() )
        , NumReadyBuffers( *new GENAPI_NAMESPACE::CIntegerRef() )
        , NumEmptyBuffers( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OutputQueueSize( *new GENAPI_NAMESPACE::CIntegerRef() )
        , InternalGrabEngineThreadPriorityOverride( *new GENAPI_NAMESPACE::CBooleanRef() )
        , InternalGrabEngineThreadPriority( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GrabLoopThreadUseTimeout( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GrabLoopThreadTimeout( *new GENAPI_NAMESPACE::CIntegerRef() )
        , GrabLoopThreadPriorityOverride( *new GENAPI_NAMESPACE::CBooleanRef() )
        , GrabLoopThreadPriority( *new GENAPI_NAMESPACE::CIntegerRef() )
        
    {
    }

    inline CInstantCameraParams_Params::~CInstantCameraParams_Params(void)
    {
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&MaxNumBuffer );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&MaxNumQueuedBuffer );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&MaxNumGrabResults );
        delete static_cast < GENAPI_NAMESPACE::CBooleanRef*> (&ChunkNodeMapsEnable );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&StaticChunkNodeMapPoolSize );
        delete static_cast < GENAPI_NAMESPACE::CBooleanRef*> (&GrabCameraEvents );
        delete static_cast < GENAPI_NAMESPACE::CBooleanRef*> (&MonitorModeActive );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&NumQueuedBuffers );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&NumReadyBuffers );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&NumEmptyBuffers );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&OutputQueueSize );
        delete static_cast < GENAPI_NAMESPACE::CBooleanRef*> (&InternalGrabEngineThreadPriorityOverride );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&InternalGrabEngineThreadPriority );
        delete static_cast < GENAPI_NAMESPACE::CBooleanRef*> (&GrabLoopThreadUseTimeout );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&GrabLoopThreadTimeout );
        delete static_cast < GENAPI_NAMESPACE::CBooleanRef*> (&GrabLoopThreadPriorityOverride );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&GrabLoopThreadPriority );
        
    }

    inline void CInstantCameraParams_Params::_Initialize(GENAPI_NAMESPACE::INodeMap* _Ptr)
    {
        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&MaxNumBuffer )->SetReference(_Ptr->GetNode("MaxNumBuffer"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&MaxNumQueuedBuffer )->SetReference(_Ptr->GetNode("MaxNumQueuedBuffer"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&MaxNumGrabResults )->SetReference(_Ptr->GetNode("MaxNumGrabResults"));
    static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&ChunkNodeMapsEnable )->SetReference(_Ptr->GetNode("ChunkNodeMapsEnable"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&StaticChunkNodeMapPoolSize )->SetReference(_Ptr->GetNode("StaticChunkNodeMapPoolSize"));
    static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GrabCameraEvents )->SetReference(_Ptr->GetNode("GrabCameraEvents"));
    static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&MonitorModeActive )->SetReference(_Ptr->GetNode("MonitorModeActive"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&NumQueuedBuffers )->SetReference(_Ptr->GetNode("NumQueuedBuffers"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&NumReadyBuffers )->SetReference(_Ptr->GetNode("NumReadyBuffers"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&NumEmptyBuffers )->SetReference(_Ptr->GetNode("NumEmptyBuffers"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OutputQueueSize )->SetReference(_Ptr->GetNode("OutputQueueSize"));
    static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&InternalGrabEngineThreadPriorityOverride )->SetReference(_Ptr->GetNode("InternalGrabEngineThreadPriorityOverride"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&InternalGrabEngineThreadPriority )->SetReference(_Ptr->GetNode("InternalGrabEngineThreadPriority"));
    static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GrabLoopThreadUseTimeout )->SetReference(_Ptr->GetNode("GrabLoopThreadUseTimeout"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GrabLoopThreadTimeout )->SetReference(_Ptr->GetNode("GrabLoopThreadTimeout"));
    static_cast<GENAPI_NAMESPACE::CBooleanRef*> (&GrabLoopThreadPriorityOverride )->SetReference(_Ptr->GetNode("GrabLoopThreadPriorityOverride"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&GrabLoopThreadPriority )->SetReference(_Ptr->GetNode("GrabLoopThreadPriority"));
    
    }

    inline const char* CInstantCameraParams_Params::_GetVendorName(void)
    {
        return "Basler";
    }

    inline const char* CInstantCameraParams_Params::_GetModelName(void)
    {
        return "InstantCameraParams";
    }

    //! \endcond

} // namespace Basler_InstantCameraParams

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_InstantCameraParams_PARAMS_H
