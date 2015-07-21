//******************************************************************
//
// Copyright 2015 Samsung Electronics All Rights Reserved.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

#include "BundleInfoInternal.h"

namespace OIC
{
    namespace Service
    {

        BundleInfoInternal::BundleInfoInternal()
        {
            m_activator = nullptr;
            m_deactivator = nullptr;
            m_bundleHandle = nullptr;

            m_loaded = false;
            m_activated = false;
        }

        BundleInfoInternal::~BundleInfoInternal()
        {
            m_activator = nullptr;
            m_deactivator = nullptr;
            m_bundleHandle = nullptr;
        }

        void BundleInfoInternal::setID(string id)
        {
            m_ID = id;
        }

        string BundleInfoInternal::getID()
        {
            return m_ID;
        }

        void BundleInfoInternal::setPath(string path)
        {
            m_path = path;
        }
        string BundleInfoInternal::getPath()
        {
            return m_path;
        }

        void BundleInfoInternal::setVersion(string version)
        {
            m_version = version;
        }

        string BundleInfoInternal::getVersion()
        {
            return m_version;
        }

        void BundleInfoInternal::setLoaded(bool loaded)
        {
            m_loaded = loaded;
        }

        bool BundleInfoInternal::isLoaded()
        {
            return m_loaded;
        }

        void BundleInfoInternal::setActivated(bool activated)
        {
            m_activated = activated;
        }

        bool BundleInfoInternal::isActivated()
        {
            return m_activated;
        }

        void BundleInfoInternal::setBundleActivator(activator_t *activator)
        {
            m_activator = activator;
        }

        activator_t *BundleInfoInternal::getBundleActivator()
        {
            return m_activator;
        }

        void BundleInfoInternal::setBundleDeactivator(deactivator_t *deactivator)
        {
            m_deactivator = deactivator;
        }

        deactivator_t *BundleInfoInternal::getBundleDeactivator()
        {
            return m_deactivator;
        }

        void BundleInfoInternal::setResourceCreator(resourceCreator_t *resourceCreator)
        {
            m_resourceCreator = resourceCreator;
        }

        resourceCreator_t *BundleInfoInternal::getResourceCreator()
        {
            return m_resourceCreator;
        }

        void BundleInfoInternal::setResourceDestroyer(resourceDestroyer_t *resourceDestroyer)
        {
            m_resourceDestroyer = resourceDestroyer;
        }

        resourceDestroyer_t *BundleInfoInternal::getResourceDestroyer()
        {
            return m_resourceDestroyer;
        }

        void BundleInfoInternal::setBundleHandle(void *handle)
        {
            m_bundleHandle = handle;
        }

        void *BundleInfoInternal::getBundleHandle()
        {
            return m_bundleHandle;
        }

        void BundleInfoInternal::setJavaBundle(bool javaBundle)
        {
            m_java_bundle = javaBundle;
        }

        bool BundleInfoInternal::getJavaBundle()
        {
            return m_java_bundle;
        }

        void BundleInfoInternal::setActivatorName(string activatorName)
        {
            m_activator_name = activatorName;
        }

        string BundleInfoInternal::getActivatorName()
        {
            return m_activator_name;
        }

        void BundleInfoInternal::setLibraryPath(string libpath)
        {
            m_library_path = libpath;
        }

        string BundleInfoInternal::getLibraryPath()
        {
            return m_library_path;
        }

#if (JAVA_SUPPORT)
        void BundleInfoInternal::setJavaBundleActivatorMethod(jmethodID javaBundleActivator)
        {
            m_java_activator = javaBundleActivator;
        }

        jmethodID BundleInfoInternal::getJavaBundleActivatorMethod()
        {
            return m_java_activator;
        }

        void BundleInfoInternal::setJavaBundleDeactivatorMethod(jmethodID javaBundleActivator)
        {
            m_java_deactivator = javaBundleActivator;
        }

        jmethodID BundleInfoInternal::getJavaBundleDeactivatorMethod()
        {
            return m_java_deactivator;
        }

        void BundleInfoInternal::setJavaBundleActivatorObject(jobject activator_object)
        {
            m_java_activator_object = activator_object;
        }

        jobject BundleInfoInternal::getJavaBundleActivatorObject()
        {
            return m_java_activator_object;
        }
#endif

        void BundleInfoInternal::setBundleInfo(BundleInfo *bundleInfo)
        {
            m_ID = bundleInfo->getID();
            m_path = bundleInfo->getPath();
            m_version = bundleInfo->getPath();
        }
    }
}