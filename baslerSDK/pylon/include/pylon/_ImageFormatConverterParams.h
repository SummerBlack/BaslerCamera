

//-----------------------------------------------------------------------------
//  (c) 2004-2018 by Basler Vision Technologies
//  Section: Vision Components
//  Project: GenApi
//-----------------------------------------------------------------------------
/*!
\file
\brief Interface to image format converter parameters.
*/

//-----------------------------------------------------------------------------
//  This file is generated automatically
//  Do not modify!
//-----------------------------------------------------------------------------



#ifndef Basler_ImageFormatConverterParams_PARAMS_H
#define Basler_ImageFormatConverterParams_PARAMS_H

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
namespace Basler_ImageFormatConverterParams
{

    //**************************************************************************************************
    // Enumerations
    //**************************************************************************************************
    
    //! Valid values for OutputBitAlignment
    enum OutputBitAlignmentEnums
    {
        OutputBitAlignment_LsbAligned,  //!<Image data is aligned with the least significant bit.
        OutputBitAlignment_MsbAligned   //!<The data is aligned at the most significant bit.
        
    };

    //! Valid values for OutputOrientation
    enum OutputOrientationEnums
    {
        OutputOrientation_Unchanged,  //!<The orientation of the image remains the same.
        OutputOrientation_TopDown,  //!<The first row of the image is located at the start of the image buffer.
        OutputOrientation_BottomUp   //!<The last row of the image is located at the start of the image buffer.
        
    };

    //! Valid values for InconvertibleEdgeHandling
    enum InconvertibleEdgeHandlingEnums
    {
        InconvertibleEdgeHandling_SetZero,  //!<Rows and columns that can't be converted are set to zero.
        InconvertibleEdgeHandling_Clip,  //!<Rows and columns that can't be converted are removed from the output image.
        InconvertibleEdgeHandling_Extend   //!<Rows and columns that can't be converted are filled by extrapolating image data from neighboring rows and columns.
        
    };

    //! Valid values for MonoConversionMethod
    enum MonoConversionMethodEnums
    {
        MonoConversionMethod_Gamma,  //!<When converting images, Gamma conversion is used.
        MonoConversionMethod_Truncate   //!<When converting images, image data is shifted.
        
    };


    //**************************************************************************************************
    // Parameter class
    //**************************************************************************************************
    

    //! Interface to image format converter parameters.
    class CImageFormatConverterParams_Params
    {
    //----------------------------------------------------------------------------------------------------------------
    // Implementation
    //----------------------------------------------------------------------------------------------------------------
    protected:
        // If you want to show the following methods in the help file
        // add the string HIDE_CLASS_METHODS to the ENABLED_SECTIONS tag in the doxygen file
        //! \cond HIDE_CLASS_METHODS
        
            //! Constructor
            CImageFormatConverterParams_Params(void);

            //! Destructor
            ~CImageFormatConverterParams_Params(void);

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
        
    //! \name Root - Image Format Converter parameters.
    //@{
    /*!
        \brief Sets the alignment of the bits in the target pixel type.

        Sets the alignment of the bits in the target pixel type if the target bit depth is greater than the source bit depth, e.g., if you are converting from a 10-bit to a 16-bit format.
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IEnumerationT<OutputBitAlignmentEnums > &OutputBitAlignment;
    
    //@}
    

    //! \name Root - Image Format Converter parameters.
    //@{
    /*!
        \brief Number of additional data bytes at the end of each line.

        Number of additional data bytes at the end of each line. These bytes are set to zero during the conversion.
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IInteger &OutputPaddingX;
    
    //@}
    

    //! \name Root - Image Format Converter parameters.
    //@{
    /*!
        \brief Sets the vertical orientation of the output image in the buffer.

        Sets the vertical orientation of the output image in the buffer.
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IEnumerationT<OutputOrientationEnums > &OutputOrientation;
    
    //@}
    

    //! \name Root - Image Format Converter parameters.
    //@{
    /*!
        \brief Sets how to handle rows and columns that can't be converted.

        Sets how to handle rows and columns that can't be converted.
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IEnumerationT<InconvertibleEdgeHandlingEnums > &InconvertibleEdgeHandling;
    
    //@}
    

    //! \name MonoConversion - Parameters for converting monochrome images.
    //@{
    /*!
        \brief Sets the conversion method for monochrome images.

        Sets the conversion method for monochrome images.
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IEnumerationT<MonoConversionMethodEnums > &MonoConversionMethod;
    
    //@}
    

    //! \name MonoConversion - Parameters for converting monochrome images.
    //@{
    /*!
        \brief Gamma value for converting monochrome images.

        Gamma value for converting monochrome images. The image data is converted using a lookup table.
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IFloat &Gamma;
    
    //@}
    

    //! \name MonoConversion - Parameters for converting monochrome images.
    //@{
    /*!
        \brief Additional shifting value used for converting monochrome images.

        Additional shifting value used for converting monochrome images. Only effective if the Mono Conversion Method parameter is set to Truncate. If the parameter value isn't zero, the image data is converted using a lookup table. Shifted values exceeding the maximum output value boundary are set to the maximum allowed value. Negative values are treated as right-shifted values.
    
        \b Visibility = Beginner
        
    
    */
    GENAPI_NAMESPACE::IInteger &AdditionalLeftShift;
    
    //@}
    


    private:
        //! \cond HIDE_CLASS_METHODS

            //! not implemented copy constructor
            CImageFormatConverterParams_Params(CImageFormatConverterParams_Params&);

            //! not implemented assignment operator
            CImageFormatConverterParams_Params& operator=(CImageFormatConverterParams_Params&);

        //! \endcond
    };


    //**************************************************************************************************
    // Parameter class implementation
    //**************************************************************************************************

    //! \cond HIDE_CLASS_METHODS

    inline CImageFormatConverterParams_Params::CImageFormatConverterParams_Params(void)
        : OutputBitAlignment( *new GENAPI_NAMESPACE::CEnumerationTRef<OutputBitAlignmentEnums>() )
        , OutputPaddingX( *new GENAPI_NAMESPACE::CIntegerRef() )
        , OutputOrientation( *new GENAPI_NAMESPACE::CEnumerationTRef<OutputOrientationEnums>() )
        , InconvertibleEdgeHandling( *new GENAPI_NAMESPACE::CEnumerationTRef<InconvertibleEdgeHandlingEnums>() )
        , MonoConversionMethod( *new GENAPI_NAMESPACE::CEnumerationTRef<MonoConversionMethodEnums>() )
        , Gamma( *new GENAPI_NAMESPACE::CFloatRef() )
        , AdditionalLeftShift( *new GENAPI_NAMESPACE::CIntegerRef() )
        
    {
    }

    inline CImageFormatConverterParams_Params::~CImageFormatConverterParams_Params(void)
    {
        delete static_cast < GENAPI_NAMESPACE::CEnumerationTRef<OutputBitAlignmentEnums> *> (&OutputBitAlignment );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&OutputPaddingX );
        delete static_cast < GENAPI_NAMESPACE::CEnumerationTRef<OutputOrientationEnums> *> (&OutputOrientation );
        delete static_cast < GENAPI_NAMESPACE::CEnumerationTRef<InconvertibleEdgeHandlingEnums> *> (&InconvertibleEdgeHandling );
        delete static_cast < GENAPI_NAMESPACE::CEnumerationTRef<MonoConversionMethodEnums> *> (&MonoConversionMethod );
        delete static_cast < GENAPI_NAMESPACE::CFloatRef*> (&Gamma );
        delete static_cast < GENAPI_NAMESPACE::CIntegerRef*> (&AdditionalLeftShift );
        
    }

    inline void CImageFormatConverterParams_Params::_Initialize(GENAPI_NAMESPACE::INodeMap* _Ptr)
    {
        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputBitAlignmentEnums> *> (&OutputBitAlignment )->SetReference(_Ptr->GetNode("OutputBitAlignment"));
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputBitAlignmentEnums> *> (&OutputBitAlignment )->SetNumEnums(2);
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputBitAlignmentEnums> *> (&OutputBitAlignment )->SetEnumReference( OutputBitAlignment_LsbAligned, "LsbAligned" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputBitAlignmentEnums> *> (&OutputBitAlignment )->SetEnumReference( OutputBitAlignment_MsbAligned, "MsbAligned" );        static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&OutputPaddingX )->SetReference(_Ptr->GetNode("OutputPaddingX"));
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputOrientationEnums> *> (&OutputOrientation )->SetReference(_Ptr->GetNode("OutputOrientation"));
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputOrientationEnums> *> (&OutputOrientation )->SetNumEnums(3);
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputOrientationEnums> *> (&OutputOrientation )->SetEnumReference( OutputOrientation_Unchanged, "Unchanged" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputOrientationEnums> *> (&OutputOrientation )->SetEnumReference( OutputOrientation_TopDown, "TopDown" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<OutputOrientationEnums> *> (&OutputOrientation )->SetEnumReference( OutputOrientation_BottomUp, "BottomUp" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InconvertibleEdgeHandlingEnums> *> (&InconvertibleEdgeHandling )->SetReference(_Ptr->GetNode("InconvertibleEdgeHandling"));
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InconvertibleEdgeHandlingEnums> *> (&InconvertibleEdgeHandling )->SetNumEnums(3);
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InconvertibleEdgeHandlingEnums> *> (&InconvertibleEdgeHandling )->SetEnumReference( InconvertibleEdgeHandling_SetZero, "SetZero" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InconvertibleEdgeHandlingEnums> *> (&InconvertibleEdgeHandling )->SetEnumReference( InconvertibleEdgeHandling_Clip, "Clip" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<InconvertibleEdgeHandlingEnums> *> (&InconvertibleEdgeHandling )->SetEnumReference( InconvertibleEdgeHandling_Extend, "Extend" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<MonoConversionMethodEnums> *> (&MonoConversionMethod )->SetReference(_Ptr->GetNode("MonoConversionMethod"));
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<MonoConversionMethodEnums> *> (&MonoConversionMethod )->SetNumEnums(2);
    static_cast<GENAPI_NAMESPACE::CEnumerationTRef<MonoConversionMethodEnums> *> (&MonoConversionMethod )->SetEnumReference( MonoConversionMethod_Gamma, "Gamma" );        static_cast<GENAPI_NAMESPACE::CEnumerationTRef<MonoConversionMethodEnums> *> (&MonoConversionMethod )->SetEnumReference( MonoConversionMethod_Truncate, "Truncate" );        static_cast<GENAPI_NAMESPACE::CFloatRef*> (&Gamma )->SetReference(_Ptr->GetNode("Gamma"));
    static_cast<GENAPI_NAMESPACE::CIntegerRef*> (&AdditionalLeftShift )->SetReference(_Ptr->GetNode("AdditionalLeftShift"));
    
    }

    inline const char* CImageFormatConverterParams_Params::_GetVendorName(void)
    {
        return "Basler";
    }

    inline const char* CImageFormatConverterParams_Params::_GetModelName(void)
    {
        return "ImageFormatConverterParams";
    }

    //! \endcond

} // namespace Basler_ImageFormatConverterParams

#if GCC_DIAGNOSTIC_AWARE
#   if GCC_DIAGNOSTIC_PUSH_POP_AWARE
#       pragma GCC diagnostic pop
#   else
#       pragma GCC diagnostic warning "-Wdeprecated-declarations"
#   endif
#endif

#undef GENAPI_DEPRECATED_FEATURE
#endif // Basler_ImageFormatConverterParams_PARAMS_H
