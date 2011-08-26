/*
 *  mafInteractorVTKTransform.h
 *  mafPluginVTK
 *
 *  Created by Daniele Giunchi - Paolo Quadrani on 7/7/11.
 *  Copyright 2011 B3C.s All rights reserved.
 *
 *  See Licence at: http://tiny.cc/QXJ4D
 *
 */

#ifndef MAFINTERACTORVTKTRANSFORM_H
#define MAFINTERACTORVTKTRANSFORM_H

// Includes list
#include "mafPluginVTKDefinitions.h"

// Foundation Class forwarding list
class vtkRenderer;

namespace mafPluginVTK {

/**
Class name: mafInteractorVTKTransform
This class represent an interactor implementing a picking operation.
*/

class MAFPLUGINVTKSHARED_EXPORT mafInteractorVTKTransform : public mafResources::mafInteractor {
    Q_OBJECT
    /// typedef macro.
    mafSuperclassMacro(mafResources::mafInteractor);

public:
    /// Object constructor.
    mafInteractorVTKTransform(const QString code_location = "");

public slots:
    /// Called when the any mouse button is pressed
    /*virtual*/ void mousePress(double *pickPos, unsigned long modifiers, mafCore::mafObjectBase *obj, QEvent *e);

    /// Called when the any mouse button is released
    /*virtual*/ void mouseRelease(double *pickPos, unsigned long modifiers, mafCore::mafObjectBase *obj, QEvent *e);

    /// Called when mouse is moved
    /*virtual*/ void mouseMove(double *pickPos, unsigned long modifiers, mafCore::mafObjectBase *obj, QEvent *e);

protected:
    /// Object destructor.
    /* virtual */~mafInteractorVTKTransform();

private:    
    /// method for translate the vme, giving the new screen coordinates
    void Translate(QPoint point2D);
     
    double m_LastPosition3D[3]; ///< represents the previous 3D position
    bool m_PositionInitialized;
    vtkRenderer *m_Renderer; ///< renderer initialized on mouse press and put to NULL in mouse release
};

/////////////////////////////////////////////////////////////
// Inline methods
/////////////////////////////////////////////////////////////

} // namespace mafPluginVTK

#endif // MAFINTERACTORVTKTRANSFORM_H