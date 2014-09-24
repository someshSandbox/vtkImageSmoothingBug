vtkImageSmoothingBug
====================

vtkImageSmoothingBug

When displaying images with sharp edges, a smoothing / anti-aliasing effect is seen.
The same image, when viewed in ITK-SNAP, shows sharp edges.

See screenshots folder for screenshots for VTK and ITK-SNAP rendering.

This test program displays the DICOM image in "data" folder.

Toggle variable USE_VTKIMAGE_VIEWER to display data using either vtkImageViewer2
or vtkImageActor. The smoothing/anti-aliasing effect is visible in both cases.



