#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGridLayout>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkActor.h>
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
    // Create a flat circle centered on its own local origin.
    mCircleSource = vtkSmartPointer<vtkRegularPolygonSource>::New();
    mCircleSource->SetNumberOfSides(50);
    mCircleSource->SetRadius(10.0);
    mCircleSource->SetCenter(0.0, 0.0, 0.0);
    mCircleSource->GeneratePolygonOn();

    // Connect the circle geometry to a VTK mapper.
    mCircleMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mCircleMapper->SetInputConnection(mCircleSource->GetOutputPort());

    // Create the visible circle actor.
    mCircleActor = vtkSmartPointer<vtkActor>::New();
    mCircleActor->SetMapper(mCircleMapper);

    // Give the creature a blue color.
    mCircleActor->GetProperty()->SetColor(0.2, 0.7, 1.0);

    // Put the graphical circle at the simulation position.
    mCircleActor->SetPosition(
        mCreaturePosition.x,
        mCreaturePosition.y,
        0.0
        );

    // Create the scene and add the circle.
    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    mRenderer->AddActor(mCircleActor);
    mRenderer->SetBackground(0.12, 0.14, 0.18);

    // Create the VTK render window.
    mRenderWindow =
        vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();

    mRenderWindow->AddRenderer(mRenderer);

    // Connect VTK's render window to the Qt widget.
    mQVtkWidget->setRenderWindow(mRenderWindow);

    mRenderer->ResetCamera();
    mRenderWindow->Render();
}