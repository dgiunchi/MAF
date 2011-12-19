/*
 *  mafPipeVisualVTKSliceVolume.cpp
 *  mafPluginVTK
 *
 *  Created by Paolo Quadrani on 09/11/11.
 *  Copyright 2011 B3C. All rights reserved.
 *
 *  See License at: http://tiny.cc/QXJ4D
 *
 */

#include "mafPipeVisualVTKSliceVolume.h"

#include <mafVME.h>
#include <mafDataSet.h>
#include <mafDataSetCollection.h>

#include <vtkActor.h>
#include <vtkPolyDataMapper.h>

#include <vtkAlgorithm.h>
#include <vtkAlgorithmOutput.h>
#include <vtkDataObject.h>
#include <vtkDataSet.h>
#include <vtkProperty.h>
#include <vtkTexture.h>

using namespace mafCore;
using namespace mafResources;
using namespace mafPluginVTK;


mafPipeVisualVTKSliceVolume::mafPipeVisualVTKSliceVolume(const QString code_location) : mafPipeVisualVTK(code_location) {
//    m_UIFilename = "mafPipeVisualVTKSliceVolume.ui";

    m_Origin[0] = m_Origin[1]= m_Origin[2] = 0.;

    m_SlicerPipe = mafNEW(mafPluginVTK::mafPipeDataSliceVolume);
    m_SlicerPipe->setParent(this);

    m_Mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    m_Mapper->ScalarVisibilityOff();

    mafProxyInterfacePointer t = m_SlicerPipe->textureOutput();
    mafProxy<vtkAlgorithmOutput> *tp = mafProxyPointerTypeCast(vtkAlgorithmOutput, t);

    vtkSmartPointer<vtkTexture> texture = vtkSmartPointer<vtkTexture>::New();
    texture->SetInputConnection(*tp);

    m_Prop3D = vtkActor::New();
    m_Prop3D.setDestructionFunction(&vtkActor::Delete);
    vtkActor::SafeDownCast(m_Prop3D)->SetMapper(m_Mapper);
    vtkActor::SafeDownCast(m_Prop3D)->SetTexture(texture);
    m_Output = &m_Prop3D;
}

mafPipeVisualVTKSliceVolume::~mafPipeVisualVTKSliceVolume() {
    mafDEL(m_SlicerPipe);
}

bool mafPipeVisualVTKSliceVolume::acceptObject(mafCore::mafObjectBase *obj) {
    mafVME *vme = qobject_cast<mafVME*>(obj);
    if(vme != NULL) {
        QString dataType = vme->dataSetCollection()->itemAtCurrentTime()->externalDataType();
        if(dataType == "vtkImageData" || dataType == "vtkStructuredPoints" || dataType == "vtkRectilinearGrid") {
            return true;
        }
    }
    return false;
}

QString mafPipeVisualVTKSliceVolume::originZ() {
    //    return QString::number(m_SlicerPipe->sliceOrigin()[2]);

    //////////////////////////////////////////////////////////////////////////
    // Convert into macro with 3 parameters
    QString sig("originZ()");
    QString ret;
    QGenericReturnArgument ret_val;
    mafCore::mafDelegatePointer delegateObj = delegateObject();
    if (delegateObj && delegateObj->isMethodDefined(sig)) {
        ret_val = mafEventReturnArgument(QString, ret);
        QString method = sig.split("(").at(0);
        delegateObj->metaObject()->invokeMethod(delegateObj, method.toAscii(), Qt::DirectConnection, ret_val);
        if (!delegateObj->shouldExecuteLocalCode()) {
            return ret;
        }
    }
    //////////////////////////////////////////////////////////////////////////
    
    return QString::number(m_Origin[2]);
}

void mafPipeVisualVTKSliceVolume::updatePipe(double t) {
    Superclass::updatePipe(t);

    double b[6];
    mafVME *vme = input();
    vme->bounds(b, t);
    m_Origin[0] = (b[0] + b[1]) / 2;
    m_Origin[1] = (b[2] + b[3]) / 2;
    m_Origin[2] = (b[4] + b[5]) / 2;

    m_SlicerPipe->setInput(input());
    m_SlicerPipe->setSliceOrigin(originX().toDouble(), originY().toDouble(), originZ().toDouble());
    m_SlicerPipe->updatePipe(t);

    mafVME *output = m_SlicerPipe->output();
    mafDataSetCollection *collection = output->dataSetCollection();
    mafDataSet *dataSet = collection->itemAt(t);
    mafProxy<vtkAlgorithmOutput> *data = mafProxyPointerTypeCast(vtkAlgorithmOutput, dataSet->dataValue());
    m_Mapper->SetInputConnection(*data);

    vtkActor *actor = vtkActor::SafeDownCast(m_Prop3D);
}

void mafPipeVisualVTKSliceVolume::setSlice(double *origin) {
    m_SlicerPipe->setSliceOrigin(origin);
}

void mafPipeVisualVTKSliceVolume::setNormal(double *normal) {
    m_SlicerPipe->setNormal(normal);
}
