/* mafTextEditor.h --- 
 * 
 * Author: Julien Wintz
 * Copyright (C) 2008 - Julien Wintz, Inria.
 * Created: Fri Apr 10 09:23:52 2009 (+0200)
 * Version: $Id$
 * Last-Updated: Thu Jul 22 16:32:59 2010 (+0200)
 *           By: Julien Wintz
 *     Update #: 47
 */

/* Commentary: 
 * 
 */

/* Change log:
 * 
 */

#ifndef MAFTEXTEDITOR_H
#define MAFTEXTEDITOR_H

#include "mafGUI_global.h"
#include <QPlainTextEdit>

namespace mafGUI {

class mafTextEditorPreferencesWidget;
class mafTextEditorPrivate;

/**
 Class Name: mafTextEditor
 Class responsible to show the script console.
*/
class MAFGUISHARED_EXPORT mafTextEditor : public QPlainTextEdit {
    Q_OBJECT

public:
    /// Object constructor
    mafTextEditor(QWidget *parent = 0);
    /// Object destructor
    ~mafTextEditor(void);

    /// Return the current line number of the cursor.
    int currentLineNumber(void) const;
    /// Return the current column number of the cursor.
    int currentColumnNumber(void) const;

    /// 
    bool isReadOnly(void) const;
    /// 
    bool isModified(void) const;

    /// 
    bool showLineNumbers(void);
    /// 
    bool showCurrentLine(void);
    /// 
    bool showRevisions(void);

    /// 
    QString fileName(void) const;
    /// 
    QString currentLine(void) const;

    /// 
    int  backgroundOpacity(void) const;
    /// 
    QColor backgroundColor(void) const;
    /// 
    QColor foregroundColor(void) const;

    /// Return the widget of the console preferences.
    mafTextEditorPreferencesWidget *preferencesWidget(QWidget *parent = 0);

    /// Allows to visualize the line numbers.
    void setShowLineNumbers(bool show);
    /// Allows to visualize the current line number.
    void setShowCurrentLine(bool show);
    /// Allows to show the revision value.
    void setShowRevisions(bool show);

    /// Allows to set the background opacity
    void setBackgroundOpacity(int opacity);
    /// Allows to set the background color
    void setBackgroundColor(QColor color);
    /// Allows to set the foreground color
    void setForegroundColor(QColor color);

signals:
    /// Signal used to notify that the console title changed.
    void titleChanged(QString);
    /// Signal used to notify that the document associated with the text widget changed.
    void documentChanged(void);
    /// Signal emitted when the text widget is closed.
    void closed(void);

public slots:
    /// Allows to open a script stored into a file.
    bool open(const QString& fileName);
    /// Allows to save the console content into a file.
    bool save(const QString& fileName = QString());

    /// 
    bool close(void);

    /// Read the previous stored settings
    void  readSettings(void);
    /// Write the console settings.
    void writeSettings(void);

    /// 
    void zoomIn(int range = 1);
    /// 
    void zoomOut(int range = 1);

protected:
    /// 
    void closeEvent(QCloseEvent *event);
    /// 
    void wheelEvent(QWheelEvent *event);
    /// 
    void paintEvent(QPaintEvent *event);
    /// 
    void resizeEvent(QResizeEvent *event);
    /// 
    void changeEvent(QEvent *event);
    /// 
    void focusInEvent(QFocusEvent *event);
    /// 
    void keyPressEvent(QKeyEvent *event);

protected:
    friend class mafTextEditorExtraArea;
    /// 
    int  extraAreaWidth(void) const;
    /// 
    void extraAreaPaintEvent(QPaintEvent *event);

protected slots:
    /// 
    void onBlockCountChanged(int);
    /// 
    void onModificationChanged(bool);
    /// 
    void onUpdateExtraAreaWidth(void);
    /// 
    void onCursorPositionChanged(void);
    /// 
    void onUpdateRequest(const QRect&, int);

private:
    /// 
    QString textUnderCursor(void) const;

private:
    mafTextEditorPrivate *m_PrivateClassPointer; ///< private class pointer
};

} //end namespace
    
#endif // MAFTEXTEDITOR_H