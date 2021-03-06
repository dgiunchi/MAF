/*
 *  mafPluginTest.cpp
 *  mafResourcesTest
 *
 *  Created by Paolo Quadrani on 22/09/09.
 *  Copyright 2009 SCS-B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafCoreSingletons.h>
#include <mafResourcesRegistration.h>
#include <mafResourcesSingletons.h>
#include <mafEventBusManager.h>
#include <mafPlugin.h>

#define TEST_LIBRARY_NAME "mafPluginTest.mafplugin"

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;

/**
 Class name: mafPluginTest
 This class implements the test suite for mafPlugin.
 */
class mafPluginTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafEventBusManager::instance();
        mafResourcesSingletons::mafSingletonsInitialize();
        // Initialize the plug-in name with prefix and extension.
        m_PluginName.append(TEST_LIBRARY_NAME);
        m_Plugin = NULL;
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        // Free allocated memory
        mafDEL(m_Plugin);

        // Shutdown event bus singleton and core singletons.
        mafResourcesSingletons::mafSingletonsShutdown();

        //restore vme manager status
        mafEventBusManager::instance()->notifyEvent("maf.local.resources.hierarchy.request");

        mafEventBusManager::instance()->shutdown();
        mafMessageHandler::instance()->shutdown();
    }

    /// mafPlugin allocation test case.
    void mafPluginAllocationTest();
    /// Plug in Registration and info
    void pluginRegistrationTest();

private:
    mafPlugin *m_Plugin; ///< Test var.
    QString m_PluginName; ///< Test var.
};

void mafPluginTest::mafPluginAllocationTest() {
    m_Plugin = new mafPlugin("myLibrary", mafCodeLocation);
    mafDEL(m_Plugin);

    // instantiate the plug in and load the library.
    m_Plugin = new mafPlugin(m_PluginName, mafCodeLocation);
    QVERIFY(m_Plugin != NULL);
}

void mafPluginTest::pluginRegistrationTest() {
    m_Plugin->registerPlugin();
    mafPluginInfo info = m_Plugin->pluginInfo();
    QVERIFY(info.m_Author.length() > 0);
}

MAF_REGISTER_TEST(mafPluginTest);
#include "mafPluginTest.moc"
