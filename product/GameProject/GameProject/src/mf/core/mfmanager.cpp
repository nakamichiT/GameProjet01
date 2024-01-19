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

/*******************************************************
* implements.
********************************************************/

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
bool mf::MfManager::create(const mf::MfCreateManagerDesc& mfCreateManagerDesc, mf::MfManager* mfManager)
{
    // Used to store processing results.
    bool result = false;

    return result;
}

/*!
* @brief Destroys all resources in the managed object.
*/
void mf::MfManager::release()
{
    // Todo
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
    // Todo
    return mf::MfClassId();
}

/*!
* @brief Register the object so that it can be obtained through MfManager.
* @param objectName: The name you use when registering.
* @param mfObject: Object to register.
*/
bool mf::MfManager::registerMfObject(const char* objectName, mf::MfObject* mfObject)
{
    // Todo
    return false;
}

/*!
* @brief Unregisters the object with the specified name.
* @param objectName: The name of the object to unregister. 
*                    (*Specify the name used in the *registerMfObject method)
* @return The registered object. 
*         (*Returns nullptr if no object is registered with the specified name)
*/
mf::MfObject* mf::MfManager::unregisterMfObject(const char* mf::MfStringId& objectName)
{
    return nullptr;
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
    return nullptr;
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
    return mf::MfClassId();    
}