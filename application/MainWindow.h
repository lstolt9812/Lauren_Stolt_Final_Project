#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>

#include <vector>
#include <vtkSmartPointer.h>

#include "Creature.hpp"
#include "Food.hpp"
#include "FoodGenerator.hpp"
#include "MapBounds.hpp"
#include "Position.hpp"

namespace Ui
{
class MainWindow;
}

class QKeyEvent;
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

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    void setupVtkPipeline();
    bool consumeFirstOverlappingFood();

    Ui::MainWindow* ui;

    QVTKOpenGLNativeWidget* mQVtkWidget;

    Simulation::Creature mCreature;
    Simulation::MapBounds mMapBounds;
    Simulation::FoodGenerator mFoodGenerator;
    std::vector<Simulation::Food> mFoods;
    std::vector<Simulation::Creature> mNpcCreatures;

    vtkSmartPointer<vtkRegularPolygonSource> mCircleSource;
    vtkSmartPointer<vtkPolyDataMapper> mCircleMapper;
    vtkSmartPointer<vtkActor> mCircleActor;

    vtkSmartPointer<vtkRegularPolygonSource> mNpcCircleSource;
    vtkSmartPointer<vtkPolyDataMapper> mNpcCircleMapper;
    std::vector<vtkSmartPointer<vtkActor>> mNpcActors;

    vtkSmartPointer<vtkCubeSource> mFoodSource;
    vtkSmartPointer<vtkPolyDataMapper> mFoodMapper;
    std::vector<vtkSmartPointer<vtkActor>> mFoodActors;

    vtkSmartPointer<vtkRenderer> mRenderer;
    vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
};

#endif