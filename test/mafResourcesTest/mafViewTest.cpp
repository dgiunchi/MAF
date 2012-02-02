/*
 *  mafViewTest.cpp
 *  mafResourcesTest
 *
 *  Created by Paolo Quadrani on 22/09/09.
 *  Copyright 2009 B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafResourcesRegistration.h>
#include <mafResourcesSingletons.h>
#include <mafProxy.h>
#include <mafView.h>
#include <mafToolHandler.h>
#include <mafVME.h>
#include <mafSceneNode.h>
#include <mafVisitorFindSceneNodeByVMEHash.h>

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;

/**
 Class name: mafViewTest
 This class implements the test suite for mafView.
 */

//! <title>
//mafView
//! </title>
//! <description>
//mafView defines the base class for the view in MAF3.
//! </description>

class mafViewTest : public QObject {
    Q_OBJECT

private Q_SLOTS:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        

        m_EventBus = mafEventBusManager::instance();
        m_VMEManager = mafVMEManager::instance();

        //Request hierarchy
        mafHierarchyPointer hierarchy;
        QGenericReturnArgument ret_val = mafEventReturnArgument(mafCore::mafHierarchyPointer, hierarchy);
        m_EventBus->notifyEvent("maf.local.resources.hierarchy.request", mafEventTypeLocal, NULL, &ret_val);

        //Select root
        mafObject *root;
        ret_val = mafEventReturnArgument(mafCore::mafObject *, root);
        m_EventBus->notifyEvent("maf.local.resources.hierarchy.root", mafEventTypeLocal, NULL, &ret_val);

        mafResourcesRegistration::registerResourcesObjects();
        m_BindingHash.insert("vtkPolyData","mafPipesLibrary::mafPipeVisualVTKSurface");
        m_View = mafNEW(mafResources::mafView);
        m_View->initialize();
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        mafToolHandler *handler = m_View->toolHandler();
        mafDEL(handler);
        mafDEL(m_View);
        
        m_EventBus->notifyEvent("maf.local.resources.hierarchy.request");
        m_EventBus->shutdown();
        mafMessageHandler::instance()->shutdown();
    }

    /// mafView allocation test case.
    void mafViewAllocationTest();

    /// mafView add & remove mafSceneNode test case.
    void mafViewAddRemoveSceneNodeTest();

    /// mafView show scene node test case.
    void mafViewShowSceneNodeTest();

    /// mafView show scene node test case.
    void mafViewPlugVisualPipeTest();

    /// mafView setRenderingWidget test case.
    void mafViewRenderingWidgetTest();

private:
    mafView *m_View; ///< Test var.
    QVariantHash m_BindingHash; ///< Test var.
    mafEventBusManager *m_EventBus;
    mafVMEManager *m_VMEManager;
};

void mafViewTest::mafViewAllocationTest() {
    QVERIFY(m_View != NULL);
}

void mafViewTest::mafViewAddRemoveSceneNodeTest() {
    mafVME *vme = mafNEW(mafResources::mafVME);
    
    //add VME
    mafEventArgumentsList argList;
    argList.append(mafEventArgument(mafCore::mafObjectBase *, vme));
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.vme.add", mafEventTypeLocal, &argList);

    // remove VME => authomatic will be removed the corresponding scene node
    // from the view and destroyed the eventually created visual pipe.
    mafDEL(vme);
}

void mafViewTest::mafViewShowSceneNodeTest() {
    mafVME *vme = mafNEW(mafResources::mafVME);
    mafSceneNode *node = new mafSceneNode(vme, NULL, mafCodeLocation);
    node->initialize();

    //try to show a node not added with a fake visual pipe.
    m_View->showSceneNode(node, true);

    mafDEL(node);

    // add vme and show (can not show, this is a base class)
    //add VME
    mafEventArgumentsList argList;
    argList.append(mafEventArgument(mafCore::mafObjectBase *, vme));
    mafEventBusManager::instance()->notifyEvent("maf.local.resources.vme.add", mafEventTypeLocal, &argList);

    // search the scene node associated with the vme added.
    mafVisitorFindSceneNodeByVMEHash *v = new mafVisitorFindSceneNodeByVMEHash(vme->objectHash(), mafCodeLocation);
    mafObjectRegistry::instance()->findObjectsThreaded(v);
    node = v->sceneNode();
    mafDEL(v);

    m_View->showSceneNode(node, false);

    // Remove the VME and its related classes.
    mafDEL(vme);
}

void mafViewTest::mafViewPlugVisualPipeTest() {
    m_View->setVisualPipeHash(m_BindingHash);
}

void mafViewTest::mafViewRenderingWidgetTest() {
    // Create a fake widget...
    QObject *obj = new QObject;
    obj->setObjectName("My Widget");

    // Assign the widget to the mafView.
    QVariant vw;
    vw.setValue<QObject*>(obj);
    m_View->setRenderingWidget(vw);

    // Try to retrieve the widget through the properties API
    mafObjectBase *v = m_View;
    // Result variable.
    QObject *widgetObj = m_View->property("renderWidget").value<QObject*>();

    QString name_result = widgetObj->objectName();
    QCOMPARE(name_result, QString("My Widget"));
    delete obj;
}

MAF_REGISTER_TEST(mafViewTest);
#include "mafViewTest.moc"
