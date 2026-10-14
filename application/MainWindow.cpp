#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "DataGenerator.hpp"

#include <QCheckBox>
#include <QGridLayout>
#include <QSlider>
#include <QSpinBox>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkActor.h>
#include <vtkDataSetSurfaceFilter.h>
#include <vtkDoubleArray.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderer.h>
#include <vtkStructuredGrid.h>

#include <cstddef>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent),ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mQVtkWidget = new QVTKOpenGLNativeWidget(this);
    QGridLayout* layout = new QGridLayout(ui->frame);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(mQVtkWidget, 0, 0);

    ui->frame->setLayout(layout);

    setup_vtk_pipeline();

    connect(ui->sampleCountSpinBox,&QSpinBox::valueChanged,this,&MainWindow::updateVisualization);
    connect(ui->opacitySlider,&QSlider::valueChanged,this,&MainWindow::updateOpacity);
    connect(ui->wireframeCheckBox,&QCheckBox::toggled,this,&MainWindow::updateWireframe);

    updateOpacity(ui->opacitySlider->value());
    updateWireframe(ui->wireframeCheckBox->isChecked());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setup_vtk_pipeline()
{
    mStructuredGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    mSurfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
    mSurfaceFilter->SetInputData(mStructuredGrid);

    mMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    mMapper->SetInputConnection(mSurfaceFilter->GetOutputPort());
    mMapper->SetScalarRange(-1.0,1.0);mMapper->ScalarVisibilityOn();

    mActor = vtkSmartPointer<vtkActor>::New();
    mActor->SetMapper(mMapper);
    mActor->GetProperty()->SetEdgeColor(0.1,0.1,0.1);

    mRenderer =vtkSmartPointer<vtkRenderer>::New();
    mRenderer->AddActor(mActor);
    mRenderer->SetBackground(0.12,0.14,0.18);
    mRenderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    mRenderWindow->AddRenderer(mRenderer);
    mQVtkWidget->setRenderWindow(mRenderWindow);

    updateVisualization();

    mRenderer->ResetCamera();
    mRenderWindow->Render();
}

void MainWindow::updateVisualization()
{

    const int sampleCount = ui->sampleCountSpinBox->value();
    const ScientificData::ScalarFieldData data = ScientificData::generateData(
        -3.14159265358979323846,
        3.14159265358979323846,
        -3.14159265358979323846,
        3.14159265358979323846,
        static_cast<std::size_t>(sampleCount),
        static_cast<std::size_t>(sampleCount));

    vtkSmartPointer<vtkPoints> points = vtkSmartPointer<vtkPoints>::New();

    points->SetDataTypeToDouble();

    const std::size_t totalPointCount = data.xSampleCount * data.ySampleCount;
    points->SetNumberOfPoints(static_cast<vtkIdType>(totalPointCount));

    vtkSmartPointer<vtkDoubleArray> scalarValues = vtkSmartPointer<vtkDoubleArray>::New();

    scalarValues->SetName("Scalar values");
    scalarValues->SetNumberOfComponents(1);

    scalarValues->SetNumberOfTuples(static_cast<vtkIdType>(totalPointCount));

    for (std::size_t yIndex = 0;
        yIndex < data.ySampleCount;
        ++yIndex)

        {
            for (std::size_t xIndex = 0;
                xIndex < data.xSampleCount;
                ++xIndex)
        {
    const std::size_t index = yIndex * data.xSampleCount + xIndex;
    const double x = data.xCoordinates[xIndex];
    const double y = data.yCoordinates[yIndex];
    const double z = data.zValues[index];

    points->SetPoint(static_cast<vtkIdType>(index),x,y,z);
    scalarValues->SetValue(static_cast<vtkIdType>(index),z);
    }
}

    mStructuredGrid->SetDimensions(static_cast<int>(data.xSampleCount),static_cast<int>(data.ySampleCount),1);
    mStructuredGrid->SetPoints(points);mStructuredGrid->GetPointData()->SetScalars(scalarValues);
    mStructuredGrid->Modified();
    mSurfaceFilter->Update();
    mRenderWindow->Render();
}

void MainWindow::updateOpacity(int value)
{
    const double opacity =static_cast<double>(value) / 100.0;
    mActor->GetProperty()->SetOpacity(opacity);
    mRenderWindow->Render();
}

void MainWindow::updateWireframe(bool enabled)
{
    if (enabled)
    {
        mActor
            ->GetProperty()
            ->SetRepresentationToWireframe();
    }
    else
    {
        mActor
            ->GetProperty()
            ->SetRepresentationToSurface();
    }

    mRenderWindow->Render();
}