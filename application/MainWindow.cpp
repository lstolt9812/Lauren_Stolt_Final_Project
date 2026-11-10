#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGridLayout>
#include <QKeyEvent>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkCubeSource.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRegularPolygonSource.h>
#include <vtkRenderer.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCreature {Simulation::Position { 0.0, 0.0 }},
    mMapBounds { -100.0, 100.0, -100.0, 100.0 },
    mFoodGenerator { 1234 },
    mFoods { mFoodGenerator.generateMultiple(mMapBounds, 20)
      }
{
    ui->setupUi(this);

    mQVtkWidget = new QVTKOpenGLNativeWidget(this);

    mQVtkWidget->setFocusPolicy(Qt::NoFocus);
    setFocusPolicy(Qt::StrongFocus);
    setFocus();

    QGridLayout* layout = new QGridLayout(ui->frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mQVtkWidget, 0, 0);

    ui->frame->setLayout(layout);

    setupVtkPipeline();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event)
{
    bool creatureMoved = false;

    if (event->key() == Qt::Key_Right)
    {
        mCreature.moveBy(2.0, 0.0, mMapBounds);
        creatureMoved = true;
    }
    else if (event->key() == Qt::Key_Left)
    {
        mCreature.moveBy(-2.0, 0.0, mMapBounds);
        creatureMoved = true;
    }
    else if (event->key() == Qt::Key_Up)
    {
        mCreature.moveBy(0.0, 2.0, mMapBounds);
        creatureMoved = true;
    }
    else if (event->key() == Qt::Key_Down)
    {
        mCreature.moveBy(0.0, -2.0, mMapBounds);
        creatureMoved = true;
    }
    else
    {
        QMainWindow::keyPressEvent(event);
        return;
    }

    if (creatureMoved)
    {
        const Simulation::Position creaturePosition =
            mCreature.position();

        mCircleActor->SetPosition(
            creaturePosition.x,
            creaturePosition.y,
            0.0
            );

        mRenderWindow->Render();
    }
}

void MainWindow::setupVtkPipeline()
{
    mCircleSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    mCircleSource->SetNumberOfSides(50);
    mCircleSource->SetRadius(2.0);
    mCircleSource->SetCenter(0.0, 0.0, 0.0);
    mCircleSource->GeneratePolygonOn();

    mCircleMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mCircleMapper->SetInputConnection(mCircleSource->GetOutputPort());

    mCircleActor = vtkSmartPointer<vtkActor>::New();
    mCircleActor->SetMapper(mCircleMapper);

    mCircleActor->GetProperty()->SetColor(0.2, 0.7, 1.0);

    const Simulation::Position creaturePosition =
        mCreature.position();

    mCircleActor->SetPosition(
        creaturePosition.x,
        creaturePosition.y,
        0.0
        );

    mFoodSource = vtkSmartPointer<vtkCubeSource>::New();

    mFoodSource->SetXLength(1.0);
    mFoodSource->SetYLength(1.0);
    mFoodSource->SetZLength(0.01);

    mFoodMapper = vtkSmartPointer<vtkPolyDataMapper>::New();

    mFoodMapper->SetInputConnection(
        mFoodSource->GetOutputPort()
        );

    mRenderer = vtkSmartPointer<vtkRenderer>::New();

    mRenderer->AddActor(mCircleActor);

    for (const Simulation::Food& food : mFoods)
    {
        vtkSmartPointer<vtkActor> foodActor =
            vtkSmartPointer<vtkActor>::New();

        foodActor->SetMapper(mFoodMapper);

        foodActor->GetProperty()->SetColor(
            1.0,
            0.2,
            0.2
            );

        const Simulation::Position foodPosition =
            food.position();

        foodActor->SetPosition(
            foodPosition.x,
            foodPosition.y,
            0.0
            );

        mRenderer->AddActor(foodActor);
        mFoodActors.push_back(foodActor);
    }

    mRenderer->SetBackground(0.12, 0.14, 0.18);

    mRenderWindow =
        vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    mRenderWindow->AddRenderer(mRenderer);

    mQVtkWidget->setRenderWindow(mRenderWindow);

    const double minimumX = -100.0;
    const double maximumX = 100.0;
    const double minimumY = -100.0;
    const double maximumY = 100.0;

    const double centerX = (minimumX + maximumX) / 2.0;
    const double centerY = (minimumY + maximumY) / 2.0;

    const double mapWidth = maximumX - minimumX;
    const double mapHeight = maximumY - minimumY;

    vtkSmartPointer<vtkCamera> camera =
        vtkSmartPointer<vtkCamera>::New();

    camera->SetPosition(
        centerX,
        centerY,
        100.0
        );

    camera->SetFocalPoint(
        centerX,
        centerY,
        0.0
        );

    camera->SetViewUp(
        0.0,
        1.0,
        0.0
        );

    camera->ParallelProjectionOn();

    camera->SetParallelScale(
        mapHeight / 2.0
        );

    mRenderer->SetActiveCamera(camera);

    mRenderer->ResetCameraClippingRange();

    mRenderWindow->Render();
}