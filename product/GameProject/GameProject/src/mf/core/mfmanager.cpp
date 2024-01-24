/*---------------------------------------------------------------------------
* @file: mfmanager.cpp
* @author: T.Nakamichi
* @brief: Define classes for managing class information and objects specified by users.
* @create day:
*----------------------------------------------------------------------------*/
/*******************************************************
* include file
********************************************************/
#include "mf/core/mfmanager.h"
#include "mf/core/mfobject.h"
#include "mf/core/mfclassinfo.h"
#include "mf/core/collections/mfdictionary.h"

/*******************************************************
* implements.
********************************************************/

class mf::MfManager::Implement
{
private:

    /*!
    * @brief 
    */
    mf::collections::MfDictionary<mf::MfStringId, mf::MfObject*> mObjects;

    /*!
    * @brief 
    */
    mf::collections::MfDictionary<mf::MfStringId, mf::MfClassInfo*> mClassInfos;

public:

    /*!
    * @brief Constructer.
    * @param mfCreateManagerDesc: Information used when creating managed objects.
    */
    Implement( const mf::MfCreateManagerDesc& mfCreateManagerDesc ) :
        mObjects( mfCreateManagerDesc.RegisteredObjects ),
        mClassInfos( mfCreateManagerDesc.RegisteredClasses )
    {
    }

    /*!
    * @brief Destructer.
    */
    ~Implement( )
    {
        // Scan for all registered class information.
        for ( auto itr = this->mClassInfos.begin( ); itr != this->mClassInfos.end( ); itr++ )
        {
            // Discard class information.
            ( *itr ).value->~MfClassInfo( );
            mf::MfFree( ( *itr ).value );
            ( *itr ).value = nullptr;
        }

        // Scan for all registered objects.
        for ( auto itr = this->mObjects.begin( ); itr != this->mObjects.end( ); itr++ )
        {
            // Discard object.
            mf::MfDelete<mf::MfObject>( ( *itr ).value );
        }
    }

public:

    /*!
    * @brief Register class information.
    * @param mfClassInfo: Class information to be registered.
    */
    void registerMfClass( mf::MfClassInfo* mfClassInfo )
    {
        this->mClassInfos.insert( mfClassInfo->ClassNameId, mfClassInfo );
    }

    /*!
    * @brief Get the class ID corresponding to the specified name.
    * @param className: Name of the class to retrieve.
    *                   (*Specify the same name as when registering the class using the registerMfClass method)
    * @return Registered class id.
    *         (*If it is not registered, an "Undefined" class id is returned.)
    */
    mf::MfClassId findMfClass( const mf::MfStringId& className )
    {
        // Variable used to store registered class information.
        mf::MfClassInfo* mfClassInfo = nullptr;

        // Obtain registered class information.
        this->mClassInfos.containts( className, &mfClassInfo );

        return mf::MfClassId( mfClassInfo );
    }

    /*!
    * @brief Get the object registered with the registerMfObject method using the specified name.
    * @param objectName: The name of the object you want to retrieve.
    *                    (*Specify the name used in the *registerMfObject method)
    * @return The registered object.
    *         (*Returns nullptr if no object is registered with the specified name)
    */
    mf::MfObject* findMfObject( const mf::MfStringId& objectName )
    {
        // Used to store registered objects.
        mf::MfObject* object = nullptr;

        // Get registered objects.
        this->mObjects.containts( objectName, &object );

        return object;
    }

    /*!
    * @brief Register the object so that it can be obtained through MfManager.
    * @param objectName: The name you use when registering.
    * @param mfObject: Object to register.
    */
    void registerMfObject( const mf::MfStringId& objectName, mf::MfObject* mfObject )
    {
        this->mObjects.insert( objectName, mfObject );
    }

    /*!
    * @brief Unregisters the object with the specified name.
    * @param objectName: The name of the object to unregister.
    *                    (*Specify the name used in the *registerMfObject method)
    */
    void unregisterMfObject( const mf::MfStringId& objectName )
    {
        this->mObjects.remove( objectName );
    }

};

/*!
* @brief Constructer.
*/
mf::MfManager::MfManager() :
    mImplement(nullptr)
{
}

/*!
* @brief Create a managed object.
* @param mfCreateManagerDesc: Information used when creating managed objects.
* @param mfManager: Used to store created objects.
* @return true: Object creation succeeded / false: Object creation failed
*/
bool mf::MfManager::create( const mf::MfCreateManagerDesc& mfCreateManagerDesc, mf::MfManager* mfManager )
{
    // Used to store processing results.
    bool result = false;

    // Variable used to store the implementation object created.
    mf::MfManager::Implement* implement = nullptr;

    // Used to store allocated memory.
    void* memory = nullptr;

    // Used to store the class information of the created mf::MfObject.
    mf::MfClassInfo* classInfo = nullptr;

    // Allocate memory for creating implementation objects.
    if ( memory = mf::MfMalloc( sizeof( mf::MfManager::Implement ) ) )
    {
        // Creation of implementation objects.
        implement = new ( memory ) mf::MfManager::Implement( mfCreateManagerDesc );

        // Allocates memory used to create class information for mf::MfObject.
        if ( memory = mf::MfMalloc( sizeof( mf::MfClassInfo ) ) )
        {
            // Generate class information of mf::MfObject class.
            classInfo = new ( memory ) mf::MfClassInfo{ sizeof( mf::MfObject ), "MfObject", mf::MfClassId( ), nullptr };

            implement->registerMfClass( classInfo );

            // Set the created class information to mf::MfObject.
            mf::MfObject::ClassId = mf::MfClassId( classInfo );

            mfManager->mImplement = implement;
            result = true;
        }
    }

    return result;
}

/*!
* @brief Destroys all resources in the managed object.
*/
void mf::MfManager::release()
{
    // Release of created implementation objects
    if ( this->mImplement )
    {
        this->mImplement->~Implement( );
        mf::MfFree( this->mImplement );
        this->mImplement = nullptr;
    }
}

/*!
* @brief Get the class ID corresponding to the specified name.
* @param className: Name of the class to retrieve. 
*                   (*Specify the same name as when registering the class using the registerMfClass method)
* @return Registered class id.
*         (*If it is not registered, an "Undefined" class id is returned.)
*/
mf::MfClassId mf::MfManager::findMfClass(const char* className)
{
    return this->mImplement ? this->mImplement->findMfClass( className ) : mf::MfClassId( );
}

/*!
* @brief Register the object so that it can be obtained through MfManager.
* @param objectName: The name you use when registering.
* @param mfObject: Object to register.
*/
bool mf::MfManager::registerMfObject(const char* objectName, mf::MfObject* mfObject)
{
    // Used to store processing results
    bool result = false;

    if ( this->mImplement && this->mImplement->findMfObject( objectName ) == nullptr )
    {
        // Registers the specified object.
        this->mImplement->registerMfObject( objectName, mfObject );

        result = true;
    }

    return result;
}

/*!
* @brief Unregisters the object with the specified name.
* @param objectName: The name of the object to unregister. 
*                    (*Specify the name used in the *registerMfObject method)
* @return The registered object. 
*         (*Returns nullptr if no object is registered with the specified name)
*/
mf::MfObject* mf::MfManager::unregisterMfObject(const char* objectName)
{
    // Used to store registered objects
    mf::MfObject* mfObject = nullptr;

    // Check if the implementation object has been created
    // Checks to see if an implementation object has been created and obtains a registered object.
    if ( this->mImplement && ( mfObject = this->mImplement->findMfObject( objectName ) ) )
    {
        // Deregistration.
        this->mImplement->unregisterMfObject( objectName );
    }

    return mfObject;
}

/*!
* @brief Get the object registered with the registerMfObject method using the specified name.
* @param objectName: The name of the object you want to retrieve.
*                    (*Specify the name used in the *registerMfObject method)
* @return The registered object. 
*         (*Returns nullptr if no object is registered with the specified name)
*/
mf::MfObject* mf::MfManager::findMfObject(const char* objectName)
{
    return this->mImplement ? this->mImplement->findMfObject( objectName ) : nullptr;
}

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
mf::MfClassId mf::MfManager::internalRegisterMfClass(const char* className, const mf::Size_T instanceSize, const mf::MfClassId& parentClassId , mf::MfCreateObjectProc mfCreateObjectProc)
{
    // Used to store allocated memory.
    void* memory = nullptr;

    // Used to store created or registered class id.
    mf::MfClassId classId;

    // Used to store the class information of the created mf::MfObject.
    mf::MfClassInfo* classInfo = nullptr;

    // Allocates memory used to create class information for mf::MfObject.
    if ( this->mImplement  )
    {
        // Retrieve registered class information.
        classId = this->mImplement->findMfClass( className );

        // If it is a valid class id, it is not registered and the registration process is performed.
        if ( classId.isValid( ) == false && ( memory = mf::MfMalloc( sizeof( mf::MfClassInfo ) ) ) )
        {
            // Generate class information of mf::MfObject class.
            classInfo = new ( memory ) mf::MfClassInfo{ instanceSize, className, parentClassId, mfCreateObjectProc };

            // Register class information.
            this->mImplement->registerMfClass( classInfo );

            classId = mf::MfClassId( classInfo );
        }
    }

    return classId;
}