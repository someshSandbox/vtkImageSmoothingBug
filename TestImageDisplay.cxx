#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkImageViewer2.h>
#include <vtkDICOMImageReader.h>
#include <vtkInteractorStyleImage.h>
#include <vtkImageActor.h>
#include <vtkImageMapper3D.h>
#include <vtkImageData.h> 
#include <vtksys/ios/sstream>

// true = Display Image using vtkImageViewer2
// false = Display Image using vtkImageActor
const bool USE_VTKIMAGE_VIEWER = true;

int main(int, char *[]) {

    // Read all the DICOM files from data directory.
    vtkSmartPointer<vtkDICOMImageReader> reader =
            vtkSmartPointer<vtkDICOMImageReader>::New();
    reader->SetFileName("../data/image.dcm");
    reader->Update();

    // Setup Render window
    vtkSmartPointer<vtkRenderWindow> renderWindow =
            vtkSmartPointer<vtkRenderWindow>::New();

    // Trying out setting to turn off smoothing
    renderWindow->PointSmoothingOff();
    renderWindow->LineSmoothingOff();
    renderWindow->PolygonSmoothingOff();
    renderWindow->SetMultiSamples(0);
    renderWindow->SetAAFrames(0);

    // Setup interactor
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
            vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Setup renderer
    vtkSmartPointer<vtkRenderer> renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow->AddRenderer(renderer);


    if (USE_VTKIMAGE_VIEWER) {
        // Display Image using vtkImageViewer2
        vtkSmartPointer<vtkImageViewer2> imageViewer = vtkSmartPointer<vtkImageViewer2>::New();
        imageViewer->SetInputConnection(reader->GetOutputPort());
        imageViewer->SetupInteractor(renderWindowInteractor);
        imageViewer->SetRenderer(renderer);
        imageViewer->GetRenderer()->ResetCamera();
        imageViewer->Render();
    } else {

        // Display Image using vtkImageActor
        vtkSmartPointer<vtkImageActor> imageActor = vtkSmartPointer<vtkImageActor>::New();
#if VTK_MAJOR_VERSION <= 5
        imageActor->SetInput(reader->GetOutput());
#else
        imageActor->GetMapper()->SetInputData(reader->GetOutput());
#endif

        vtkSmartPointer<vtkInteractorStyleImage> style =
                vtkSmartPointer<vtkInteractorStyleImage>::New();
        renderWindowInteractor->SetInteractorStyle(style);

        renderer->AddActor(imageActor);
        renderer->ResetCamera();
        renderWindow->Render();
        renderWindowInteractor->Initialize();
    }



    renderWindowInteractor->Start();



    return EXIT_SUCCESS;
}
