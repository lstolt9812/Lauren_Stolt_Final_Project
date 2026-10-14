#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVTKOpenGLNativeWidget.h>

#include <vtkSmartPointer.h>

namespace Ui
{
class MainWindow;
}

class vtkActor;
class vtkDataSetSurfaceFilter;
class vtkGenericOpenGLRenderWindow;
class vtkPolyDataMapper;
class vtkRenderer;
class vtkStructuredGrid;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget* parent = nullptr);
        ~MainWindow();

    private slots:

        void updateVisualization();
        void updateOpacity(int value);
        void updateWireframe(bool enabled);

    private:
        void setup_vtk_pipeline();

        Ui::MainWindow* ui;

        QVTKOpenGLNativeWidget* mQVtkWidget;

        vtkSmartPointer<vtkStructuredGrid> mStructuredGrid;
        vtkSmartPointer<vtkDataSetSurfaceFilter> mSurfaceFilter;
        vtkSmartPointer<vtkPolyDataMapper> mMapper;
        vtkSmartPointer<vtkActor> mActor;
        vtkSmartPointer<vtkRenderer> mRenderer;
        vtkSmartPointer<vtkGenericOpenGLRenderWindow> mRenderWindow;
};

#endif