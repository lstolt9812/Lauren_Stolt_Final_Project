#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGridLayout>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkActor.h>
#include <vtkCamera.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRegularPolygonSource.h>
#include <vtkRenderer.h>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow),
    mCreaturePosition { 0.0, 0.0 }
{
    ui->setupUi(this);

    mQVtkWidget = new QVTKOpenGLNativeWidget(this);

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

void MainWindow::setupVtkPipeline()
{
    mCircleSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    mCircleSource->SetNumberOfSides(50);
    mCircleSource->SetRadius(10.0);
    mCircleSource->SetCenter(0.0, 0.0, 0.0);
    mCircleSource->GeneratePolygonOn();

    mCircleMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mCircleMapper->SetInputConnection(mCircleSource->GetOutputPort());

    mCircleActor = vtkSmartPointer<vtkActor>::New();
    mCircleActor->SetMapper(mCircleMapper);

    mCircleActor->GetProperty()->SetColor(0.2, 0.7, 1.0);

    mCircleActor->SetPosition(
        mCreaturePosition.x,
        mCreaturePosition.y,
        0.0
        );

    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    mRenderer->AddActor(mCircleActor);
    mRenderer->SetBackground(0.12, 0.14, 0.18);

    mRenderWindow =
        vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    mRenderWindow->AddRenderer(mRenderer);

    mQVtkWidget->setRenderWindow(mRenderWindow);

    const double minimumX = -10.0;
    const double maximumX = 10.0;
    const double minimumY = -10.0;
    const double maximumY = 10.0;

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