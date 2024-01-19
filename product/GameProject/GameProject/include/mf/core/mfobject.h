/*---------------------------------------------------------------------------
* @file: mfobject.h
* @author: T.Nakamichi
* @brief: Define a base class.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_OBJECT_H___
#define ___MF_CORE_OBJECT_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/mftype.h"
#include "mf/core/mfclassid.h"

/*******************************************************
* macro.
********************************************************/

/*!
* @brief Macros for defining common members and methods.
* Class: Specify the class to be defined.
* ParentClass: Specify the parent class of the class to be defined.
*/
#define MF_CLASS_DECLARE(Class, ParentClass)\
private:\
    using Parent = ParentClass;\
    friend class mf::MfManager;\
public:\
    static mf::MfClassId ClassId;\
public:\
    mf::MfClassId getClassId()const{ return Class::ClassId };\

/*!
* @brief Macro for defining the members and methods required for instantiable classes.
* Class: Specify the class to be defined.
* ParentClass: Specify the parent class of the class to be defined.
*/
#define MF_OBJECT_DECLARE(Class, ParentClass)\
private:\
    MF_CLASS_DECLARE(Class, ParentClass)\
    static Class* create(MF_CREATE_OBJECT_PROC_PARAMETERS);\
protected:
    Class(const mf::MfObject* mfFromObject);
private:\

/*!
* @brief Macro for defining members and methods in classes for which instantiation is prohibited.
* Class: Specify the class to be defined.
* ParentClass: Specify the parent class of the class to be defined.
*/
#define MF_ABSTRACT_OBJECT_DECLARE(Class, ParentClass)\
private:\
    MF_CLASS_DECLARE(Class, ParentClass)\
    static mf::MfCreateObjectProc create;\
private:\

/*!
* @brief A macro that defines common methods for instantiable classes.
*/
#define MF_OBJECT_IMPLEMENT(Class)\
mf::MfClassId Class::ClassId;\
Class* Class::create(MF_CREATE_OBJECT_PROC_PARAMETERS){\
    Class* instance = nullptr;\
    void* memory = placement;\
    if( memory == nullptr )\
    {\
        memory = mf::MfMalloc(sizeof(Class));\
    }\
    if( memory ){\
        instance = new (memory) Class(mfFromObject);\
        if(mfManager){\
            mfManager->registerMfObject(name, instance);\
        }\
    }\
}\

/*!
* @brief A macro that defines common processing for classes that prohibit the creation of instances.
*/
#define MF_ABSTRACT_OBJECT_IMPLEMENT(Class)\
mf::MfClassId Class::ClassId;\
mf::MfCreateObjectProc Class::create = nullptr;\

/*******************************************************
* implement.
********************************************************/

namespace mf 
{
    /*!
    * @brief Base object class.
    */
    class MfObject
    {
    public:
        
        /*!
        * @brief Used to hold an ID that identifies the type of object.
        */
        static mf::MfClassid ClassId;

    protected:

        /*!
        * @brief Constructer.
        * @param mfFromObject: The object from which the instance is created.
        */
        MfObject(const mf::MfObject* mfFromObject);

    public:

        /*!
        * @brief Get the id that identifies the type of the class.
        * @return An id that identifies the type of the class.
        */
        virtual mf::MfClassId getClassId()const;

    }
}

#endif