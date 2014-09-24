vtkImageSmoothingBug
====================

vtkImageSmoothingBug

When displaying images with sharp edges, a smoothing / anti-aliasing effect is seen.
The same image, when viewed in ITK-SNAP, shows sharp edges.

See screenshots folder for screenshots for VTK and ITK-SNAP rendering.

This test program displays the DICOM image in "data" folder.

Toggle variable USE_VTKIMAGE_VIEWER to display data using either vtkImageViewer2
or vtkImageActor. The smoothing/anti-aliasing effect is visible in both cases.


Update : Based on discussion on vtk users list, I found that this is not a bug.
However, if you want the data not to be interpolated, see below :


Reply From David Gobbi on vtkusers@vtk.org

It's definitely not a bug.  Interpolation is turned on by default, in order to
reduce a certain artifact known as "pixels" that can occur when displaying
a uniformly sampled data set ;)

In VTK 5, use this method:

actor->InterpolateOff();

In VTK 6, you can have even more control via the Property and the Mapper
for the image:

actor->GetProperty()->SetInterpolationTypeToNearest();
actor->GetMapper()->BorderOn();
