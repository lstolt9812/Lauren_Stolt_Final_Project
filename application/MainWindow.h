#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkSmartPointer.h>

#include "Food.hpp"
#include "FoodGenerator.hpp"
#include "MapBounds.hpp"
#include "Position.hpp"

namespace Ui
{
class MainWindow;
}

class vtkActor;
class vtkCubeSource;
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
    Simulation::MapBounds mMapBounds;
    Simulation::FoodGenerator mFoodGenerator;
    Simulation::Food mFood;

    vtkSmartPointer<vtkRegularPolygonSource> mCircleSource;
    vtkSmartPointer<vtkPolyDataMapper> mCircleMapper;
    vtkSmartPointer<vtkActor> mCircleActor;

    vtkSmartPointer<vtkCubeSource> mFoodSource;
    vtkSmartPointer<vtkPolyDataMapper> mFoodMapper;
    vtkSmartPointer<vtkActor> mFoodActor;

    vtkSmartPointer<vtkRenderer> mRenderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
};

#endif