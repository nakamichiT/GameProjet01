/*---------------------------------------------------------------------------
* @file: mfmanager.h
* @author: T.Nakamichi
* @brief: Define classes for managing class information and objects specified by users.
* @create day:
*----------------------------------------------------------------------------*/
#if not defined ___MF_CORE_MANAGER_H___
#define ___MF_CORE_MANAGER_H___

/*******************************************************
* include file
********************************************************/
#include "mf/core/arch/mftype.h"
#include "mf/core/mfstringid.h"
#include "mf/core/mfclassid.h"
#include "mf/core/mfcreatemanagerdesc.h"


/*******************************************************
* implements.
********************************************************/
namespace mf
{
    /*!
    * @brief A class for managing class information and objects specified by users.
    */
    class MfManager
    {
    private:

        class Implement;

    private:

        mf::MfManager::Implement* mImplement;

    public:

        /*!
        * @brief Constructer.
        */
        MfManager( );

    public:

        /*!
        * @brief Create a managed object.
        * @param mfCreateManagerDesc: Information used when creating managed objects.
        * @param mfManager: Used to store created objects.
        * @return true: Object creation succeeded / false: Object creation failed
        */
        static bool create( const mf::MfCreateManagerDesc& mfCreateManagerDesc, mf::MfManager* mfManager );

    public:

        /*!
        * @brief Destroys all resources in the managed object.
        */
        void release( );

        /*!
        * @brief Create a class id for the specified class and keep it in the management class.
        *        (*Registration using the same class name is not possible.)
        *        (*If already registered, returns the registered class id.)
        * @param className: The name you use when registering.
        * @return The class id you created or the class id you have already created.
        *         (*Returns a class id named "Undefined" even if class id generation fails.)
        */
        template <class T>
        mf::MfClassId registerMfClass( const char* className )
        {
            if ( this->mImplement && T::ClassId.isValid( ) == false )
            {
                T::ClassId = this->internalRegisterMfClass( className, sizeof( T ), T::Parent::ClassId, (mf::MfCreateObjectProc)T::create );
            }
            return T::ClassId;
        }

        /*!
        * @brief Get the class ID corresponding to the specified name.
        * @param className: Name of the class to retrieve.
        *                   (*Specify the same name as when registering the class using the registerMfClass method)
        * @return Registered class id.
        *         (*If it is not registered, an "Undefined" class id is returned.)
        */
        mf::MfClassId findMfClass( const char* className );

        /*!
        * @brief Register the object so that it can be obtained through MfManager.
        * @param objectName: The name you use when registering.
        * @param mfObject: Object to register.
        */
        bool registerMfObject( const char* objectName, mf::MfObject* mfObject );

        /*!
        * @brief Unregisters the object with the specified name.
        * @param objectName: The name of the object to unregister.
        *                    (*Specify the name used in the *registerMfObject method)
        * @return The registered object.
        *         (*Returns nullptr if no object is registered with the specified name)
        */
        mf::MfObject* unregisterMfObject( const char* objectName );

        /*!
        * @brief Get the object registered with the registerMfObject method using the specified name.
        * @param objectName: The name of the object you want to retrieve.
        *                    (*Specify the name used in the *registerMfObject method)
        * @return The registered object.
        *         (*Returns nullptr if no object is registered with the specified name)
        */
        mf::MfObject* findMfObject( const char* objectName );

    private:

        /*!
        * @brief Create a class id for the specified class and keep it in the management class.
        *        (*Registration using the same class name is not possible.)
        *        (*If already registered, returns the registered class id.)
        * @param className: The name you use when registering.
        * @param instanceSize: Memory size required when creating an instance.
        * @param parentClassId: Class id of parent class.
        * @param mfCreateObjectProc: Creation function used when creating an instance.
        * @return Created class id.
        *         (*Returns a class id named "Undefined" even if class id generation fails.)
        */
        mf::MfClassId internalRegisterMfClass( const char* className, const mf::Size_T instanceSize, const mf::MfClassId& parentClassId, mf::MfCreateObjectProc mfCreateObjectProc );

    };
}

#endif