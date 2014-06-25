/*
 *  mafMatrixTest.cpp
 *  mafMatrixsTest
 *
 *  Created by Daniele Giunchi on 15/06/11.
 *  Copyright 2011 SCS-B3C. All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#include <mafTestSuite.h>
#include <mafResourcesDefinitions.h>
#include <mafMatrix4x4.h>

using namespace mafCore;
using namespace mafEventBus;
using namespace mafResources;

/**
 Class name: mafMatrixTest
 This class implements the test suite for mafMatrix4x4.
 */

//! <title>
//mafMatrix4x4
//! </title>
//! <description>
//mafMatrix4x4 is the class that wrap third party library matrix.
//! </description>
/*
class mafMatrixTest: public QObject {
    Q_OBJECT

private Q_SLOTS:
    /// Initialize test variables
    void initTestCase() {
        mafMessageHandler::instance()->installMessageHandler();
        mafEventBusManager::instance();
        m_Matrix = new mafMatrix4x4();
        m_Matrix->setToIdentity();
    }

    /// Cleanup test variables memory allocation.
    void cleanupTestCase() {
        delete m_Matrix;
        mafEventBusManager::instance()->shutdown();
        mafMessageHandler::instance()->shutdown();
    }

    /// mafMatrix4x4 allocation test case.
    void mafMatrixAllocationTest();
    
    /// mafMatrix4x4 clone test
    void mafMatrixCloneTest();
    
    /// mafMatrix4x4 clone test
    void mafMatrixElementAccessors();
    
    /// identity test
    void mafMatrixIdentityTest();
    
    /// test matrix multiplication and assignment
    void mafMatrixMultiplicationAndAssignmentTest();
    
    /// test rawData matrix extraction
    void mafMatrixRawDataExtractionTest();

    /// Test the row and column extraction.
    void mafMatrixRowColumnExtractionTest();

private:
    mafMatrix4x4 *m_Matrix; ///< Test var.
};

void mafMatrixTest::mafMatrixAllocationTest() {
    QVERIFY(m_Matrix != NULL);
}

void mafMatrixTest::mafMatrixCloneTest() {
    mafMatrix4x4 *clonedMat = m_Matrix->cclone();
    clonedMat->description();
    QVERIFY(clonedMat != NULL);
    QVERIFY(m_Matrix->isEqual(*clonedMat));
    m_Matrix->description();
    delete clonedMat;
}

void mafMatrixTest::mafMatrixElementAccessors() {
    double valueToCheck = 5.36;
    m_Matrix->setElement(2, 3, valueToCheck);
    QVERIFY(valueToCheck == m_Matrix->element(2,3));
}

void mafMatrixTest::mafMatrixIdentityTest() {
    m_Matrix->setToIdentity();
    
    mafMatrix4x4 identity;
    identity.setElement(0, 0, 1.0); identity.setElement(0, 1, 0.0); identity.setElement(0, 2, 0.0); identity.setElement(0, 3, 0.0);
    identity.setElement(1, 0, 0.0); identity.setElement(1, 1, 1.0); identity.setElement(1, 2, 0.0); identity.setElement(1, 3, 0.0);
    identity.setElement(2, 0, 0.0); identity.setElement(2, 1, 0.0); identity.setElement(2, 2, 1.0); identity.setElement(2, 3, 0.0);
    identity.setElement(3, 0, 0.0); identity.setElement(3, 1, 0.0); identity.setElement(3, 2, 0.0); identity.setElement(3, 3, 1.0);
    
    QVERIFY(m_Matrix->isEqual(identity));
}

void mafMatrixTest::mafMatrixMultiplicationAndAssignmentTest() {
    mafMatrix4x4 identity;
    identity.setToIdentity();

    mafMatrix4x4 first;
    first.setElement(0, 0, 2.0); first.setElement(0, 1, 2.0); first.setElement(0, 2, 0.0); first.setElement(0, 3, 2.0);
    first.setElement(1, 0, 2.0); first.setElement(1, 1, 2.0); first.setElement(1, 2, 2.0); first.setElement(1, 3, 2.0);
    first.setElement(2, 0, 0.0); first.setElement(2, 1, 2.0); first.setElement(2, 2, 2.0); first.setElement(2, 3, 2.0);
    first.setElement(3, 0, 2.0); first.setElement(3, 1, 0.0); first.setElement(3, 2, 2.0); first.setElement(3, 3, 2.0);
    
    mafMatrix4x4 second;
    second.setElement(0, 0, 0.0); second.setElement(0, 1, 0.5); second.setElement(0, 2, -0.5);second.setElement(0, 3, 0.0);
    second.setElement(1, 0, 0.0); second.setElement(1, 1, 0.5); second.setElement(1, 2, 0.0); second.setElement(1, 3, -0.5);
    second.setElement(2, 0, -0.5);second.setElement(2, 1, 0.5); second.setElement(2, 2, 0.0); second.setElement(2, 3, 0.0);
    second.setElement(3, 0, 0.5); second.setElement(3, 1, -1.0);second.setElement(3, 2, 0.5); second.setElement(3, 3, 0.5);
    
    mafMatrix4x4 result;
    result = first * second;
    QVERIFY(result.isEqual(identity));

}

void mafMatrixTest::mafMatrixRawDataExtractionTest() {
    // | 2.0 2.0 0.0 2.0 |
    // | 3.0 2.0 2.0 2.0 |
    // | 0.0 2.0 2.0 5.0 |
    // | 1.0 0.0 2.0 2.0 |
    mafMatrix4x4 matrtix;
    matrtix.setElement(0, 0, 2.0); matrtix.setElement(0, 1, 2.0); matrtix.setElement(0, 2, 0.0); matrtix.setElement(0, 3, 2.0);
    matrtix.setElement(1, 0, 3.0); matrtix.setElement(1, 1, 2.0); matrtix.setElement(1, 2, 2.0); matrtix.setElement(1, 3, 2.0);
    matrtix.setElement(2, 0, 0.0); matrtix.setElement(2, 1, 2.0); matrtix.setElement(2, 2, 2.0); matrtix.setElement(2, 3, 5.0);
    matrtix.setElement(3, 0, 1.0); matrtix.setElement(3, 1, 0.0); matrtix.setElement(3, 2, 2.0); matrtix.setElement(3, 3, 2.0);
    
    double *val = matrtix.rawData();
    bool ok(false);
    ok = val[0] == 2.0;
    QVERIFY(ok);
    ok = val[4] == 3.0;
    QVERIFY(ok);
    ok = val[11] == 5.0;
    QVERIFY(ok);
    ok = val[12] == 1.0;
    QVERIFY(ok);
    ok = val[14] == 2.0;
    QVERIFY(ok);
}

void mafMatrixTest::mafMatrixRowColumnExtractionTest() {
    // | 2.0 2.0 0.0 2.0 |
    // | 3.0 2.0 2.0 2.0 |
    // | 0.0 2.0 2.0 5.0 |
    // | 1.0 0.0 2.0 2.0 |
    mafMatrix4x4 matrtix;
    matrtix.setElement(0, 0, 2.0); matrtix.setElement(0, 1, 2.0); matrtix.setElement(0, 2, 0.0); matrtix.setElement(0, 3, 2.0);
    matrtix.setElement(1, 0, 3.0); matrtix.setElement(1, 1, 2.0); matrtix.setElement(1, 2, 2.0); matrtix.setElement(1, 3, 2.0);
    matrtix.setElement(2, 0, 0.0); matrtix.setElement(2, 1, 2.0); matrtix.setElement(2, 2, 2.0); matrtix.setElement(2, 3, 5.0);
    matrtix.setElement(3, 0, 1.0); matrtix.setElement(3, 1, 0.0); matrtix.setElement(3, 2, 2.0); matrtix.setElement(3, 3, 2.0);

    // Extract a row in the range of matrix.
    mafMatrix4x4 resultRowMatrix(1,4);
    resultRowMatrix.setElement(0, 0, 2.0); resultRowMatrix.setElement(0, 1, 2.0); resultRowMatrix.setElement(0, 2, 0.0); resultRowMatrix.setElement(0, 3, 2.0);

    mafMatrix4x4 mRow = matrtix.extractRow(0);
    bool ok = mRow.isEqual(resultRowMatrix);
    QVERIFY(ok);

    mafMatrix4x4 resultColMatrix(4,1);
    resultColMatrix.setElement(0, 0, 2.0);
    resultColMatrix.setElement(1, 0, 3.0);
    resultColMatrix.setElement(2, 0, 0.0);
    resultColMatrix.setElement(3, 0, 1.0);

    mafMatrix4x4 mCol = matrtix.extractColumn(0);
    ok = mCol.isEqual(resultColMatrix);
    QVERIFY(ok);
}*/

//MAF_REGISTER_TEST(mafMatrixTest);
#include "mafMatrixTest.moc"
