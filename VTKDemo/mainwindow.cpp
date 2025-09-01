#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    renWin3D=vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
    current_actor=vtkSmartPointer<vtkActor>::New();

    main_render_3d=vtkSmartPointer<vtkRenderer>::New();

    ugrid=vtkSmartPointer<vtkUnstructuredGrid>::New();

    //Set Background Color
    main_render_3d->SetBackground(1.0,1.0,1.0);
    main_render_3d->SetBackground2(0.529,0.8078,0.92157);
    main_render_3d->SetGradientBackground(true);

    //关键：将含有数据的render传递给renWin
    //全局变量 建立一次关系
    renWin3D->AddRenderer(main_render_3d);

    //ui widget和vtk render的联系
    ui->openGLWidget->SetRenderWindow(renWin3D);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_loadfile_clicked()
{

    vtkSmartPointer<vtkUnstructuredGridReader>vtkReader=vtkSmartPointer<vtkUnstructuredGridReader>::New();
    vtkReader->SetFileName("D:/VTK/MyProject/VTKDemo/grid.vtk");

    vtkReader->Update();

    ugrid=vtkReader->GetOutput();

    vtkSmartPointer<vtkDataSetMapper>skinMapper=vtkSmartPointer<vtkDataSetMapper>::New();
    skinMapper->SetInputData(ugrid);

    vtkSmartPointer<vtkActor>skin=vtkSmartPointer<vtkActor>::New();
    skin->SetMapper(skinMapper);

    ////skin->GetProperty()->SetRepresentationToWireframe();

    main_render_3d->AddActor(skin);

    main_render_3d->ResetCamera();

    renWin3D->Render();
    ui->openGLWidget->update();

}

