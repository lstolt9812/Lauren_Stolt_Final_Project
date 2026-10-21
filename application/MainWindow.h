#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkSmartPointer.h>

#include "Position.hpp"

namespace Ui
{
class MainWindow;
}

class vtkActor;
class vtkGenericOpenGLRenderWindow;
class vtkPolyDataMapper;
class vtkRegularPolygonSource;
class vtkRenderer;
class vtkCamera;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    void setupVtkPipeline();

    Ui::MainWindow* ui;

    QVTKOpenGLNativeWidget* mQVtkWidget;

    Simulation::Position mCreaturePosition;

    vtkSmartPointer<vtkRegularPolygonSource> mCircleSource;
    vtkSmartPointer<vtkPolyDataMapper> mCircleMapper;
    vtkSmartPointer<vtkActor> mCircleActor;
    vtkSmartPointer<vtkRenderer> mRenderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
};

#endif