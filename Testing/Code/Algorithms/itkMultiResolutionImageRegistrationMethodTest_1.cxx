/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkMultiResolutionImageRegistrationMethodTest_1.cxx
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Insight Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "itkMultiResolutionImageRegistrationMethod.h"
#include "itkAffineTransform.h"
#include "itkMutualInformationImageToImageMetric.h"
#include "itkLinearInterpolateImageFunction.h"
#include "itkGradientDescentOptimizer.h"
#include "itkRecursiveMultiResolutionPyramidImageFilter.h"

#include "itkOutputWindow.h"
#include "itkImageRegionIterator.h"
#include "itkCommandIterationUpdate.h"
#include "itkSimpleMultiResolutionImageRegistrationUI.h"

// this class is used to send output to stdout and not the itk window
class TextOutput : public itk::OutputWindow
{
public:
  typedef TextOutput              Self;
  typedef itk::SmartPointer<Self>  Pointer;
  typedef itk::SmartPointer<const Self>  ConstPointer;
  itkNewMacro(TextOutput);
  virtual void DisplayText(const char* s)
    {
      std::cout << s << std::endl;
    }
};


double F( itk::Vector<double,3> & v );


/** 
 *  This program test one instantiation of the 
 *  itk::MultiResolutionImageRegistrationMethod class
 * 
 *  This file tests the combination of:
 *   - MutualInformation
 *   - AffineTransform
 *   - GradientDescentOptimizer
 *   - LinearInterpolateImageFunction
 *   - RecursiveMultiResolutionPyramidImageFilter
 *
 *  The test image pattern consists of a 3D gaussian in the middle
 *  with some directional pattern on the outside.
 *  One image is scaled and shifted relative to the other.
 */ 

int main()
{

  itk::OutputWindow::SetInstance(TextOutput::New().GetPointer());

  bool pass = true;

  const unsigned int dimension = 3;
  unsigned int j;

  typedef float  PixelType;

  // Fixed Image Type
  typedef itk::Image<PixelType,dimension>               FixedImageType;

  // Moving Image Type
  typedef itk::Image<PixelType,dimension>               MovingImageType;

  // Transform Type
  typedef itk::AffineTransform< double,dimension >  TransformType;

  // Optimizer Type
  typedef itk::GradientDescentOptimizer             OptimizerType;

  // Metric Type
  typedef itk::MutualInformationImageToImageMetric< 
                                    FixedImageType, 
                                    MovingImageType >    MetricType;

  // Interpolation technique
  typedef itk:: LinearInterpolateImageFunction< 
                                    MovingImageType,
                                    double          >    InterpolatorType;

  // Fixed Image Pyramid Type
  typedef itk::RecursiveMultiResolutionPyramidImageFilter<
                                    FixedImageType,
                                    FixedImageType  >    FixedImagePyramidType;

  // Moving Image Pyramid Type
  typedef itk::RecursiveMultiResolutionPyramidImageFilter<
                                    MovingImageType,
                                    MovingImageType  >   MovingImagePyramidType;


  // Registration Method
  typedef itk::MultiResolutionImageRegistrationMethod< 
                                    FixedImageType, 
                                    MovingImageType >    RegistrationType;


  MetricType::Pointer         metric        = MetricType::New();
  TransformType::Pointer      transform     = TransformType::New();
  OptimizerType::Pointer      optimizer     = OptimizerType::New();
  FixedImageType::Pointer     fixedImage    = FixedImageType::New();  
  MovingImageType::Pointer    movingImage   = MovingImageType::New();  
  InterpolatorType::Pointer   interpolator  = InterpolatorType::New();
  FixedImagePyramidType::Pointer fixedImagePyramid = 
    FixedImagePyramidType::New();
  MovingImagePyramidType::Pointer movingImagePyramid =
    MovingImagePyramidType::New();
  RegistrationType::Pointer   registration  = RegistrationType::New();

  /*********************************************************
   * Set up the two input images.
   * One image scaled and shifted with respect to the other.
   **********************************************************/
  double displacement[dimension] = {7,3,2};
  double scale[dimension] = { 0.80, 1.0, 1.0 };

  FixedImageType::SizeType size = {{100,100,40}};
  FixedImageType::IndexType index = {{0,0,0}};
  FixedImageType::RegionType region;
  region.SetSize( size );
  region.SetIndex( index );

  fixedImage->SetLargestPossibleRegion( region );
  fixedImage->SetBufferedRegion( region );
  fixedImage->SetRequestedRegion( region );
  fixedImage->Allocate();

  movingImage->SetLargestPossibleRegion( region );
  movingImage->SetBufferedRegion( region );
  movingImage->SetRequestedRegion( region );
  movingImage->Allocate();
  

  typedef itk::ImageRegionIterator<MovingImageType> MovingImageIterator;
  typedef itk::ImageRegionIterator<FixedImageType> FixedImageIterator;

  itk::Point<double,dimension> center;
  for ( j = 0; j < dimension; j++ )
    {
    center[j] = 0.5 *  (double)region.GetSize()[j];
    }

  itk::Point<double,dimension> p;
  itk::Vector<double,dimension> d;  

  MovingImageIterator mIter( movingImage, region );
  FixedImageIterator  fIter( fixedImage, region );

  while( !mIter.IsAtEnd() )
    {
    for ( j = 0; j < dimension; j++ )
      {
      p[j] = mIter.GetIndex()[j];
      }

    d = p - center;

    fIter.Set( (PixelType) F(d) );

    for ( j = 0; j < dimension; j++ )
      {
      d[j] = d[j] * scale[j] + displacement[j];
      }  

    mIter.Set( (PixelType) F(d) );

    ++fIter;
    ++mIter;

    }

  // set the image origin to be center of the image
  double transCenter[dimension];
  for ( j = 0; j < dimension; j++ )
    {
    transCenter[j] = -0.5 * double(size[j]);
    }

  movingImage->SetOrigin( transCenter );
  fixedImage->SetOrigin( transCenter );


  /******************************************************************
   * Set up the optimizer.
   ******************************************************************/

  // set the translation scale
  typedef OptimizerType::ScalesType ScalesType;
  ScalesType parametersScales( transform->GetNumberOfParameters() );

  parametersScales.Fill( 1.0 );

  for ( j = 9; j < 12; j++ )
    {
    parametersScales[j] = 0.0001;
    }

  optimizer->SetScales( parametersScales );
  
  // need to maximize for mutual information
  optimizer->MaximizeOn();

  /******************************************************************
   * Set up the optimizer observer
   ******************************************************************/
/*
  typedef itk::CommandIterationUpdate< OptimizerType > CommandIterationType;
  CommandIterationType::Pointer iterationCommand = 
    CommandIterationType::New();

  iterationCommand->SetOptimizer( optimizer );
  optimizer->AddObserver( itk::IterationEvent(), iterationCommand );
*/

  /******************************************************************
   * Set up the metric.
   ******************************************************************/
  metric->SetMovingImageStandardDeviation( 5.0 );
  metric->SetFixedImageStandardDeviation( 5.0 );
  metric->SetNumberOfSpatialSamples( 50 );

  /******************************************************************
   * Set up the registrator.
   ******************************************************************/

  // connect up the components
  registration->SetMetric( metric );
  registration->SetOptimizer( optimizer );
  registration->SetTransform( transform );
  registration->SetFixedImage( fixedImage );
  registration->SetMovingImage( movingImage );
  registration->SetInterpolator( interpolator );
  registration->SetFixedImagePyramid( fixedImagePyramid );
  registration->SetMovingImagePyramid( movingImagePyramid );
  
  // set initial parameters to identity
  RegistrationType::ParametersType initialParameters( 
    transform->GetNumberOfParameters() );

  initialParameters.Fill( 0.0 );
  initialParameters[0] = 1.0;
  initialParameters[4] = 1.0;
  initialParameters[8] = 1.0;

  /******************************************************************
   * Attach registration to a simple UI and run registration
   ******************************************************************/
  SimpleMultiResolutionImageRegistrationUI2<RegistrationType> 
    simpleUI( registration );

  unsigned short numberOfLevels = 3;

  itk::Array<unsigned int> niter( numberOfLevels );
  itk::Array<double>       rates( numberOfLevels );

  niter[0] = 100;
  niter[1] = 300;
  niter[2] = 550;

  rates[0] = 1e-3;
  rates[1] = 5e-4;
  rates[2] = 1e-4;

  simpleUI.SetNumberOfIterations( niter );
  simpleUI.SetLearningRates( rates );

  try
    {
    registration->SetNumberOfLevels( numberOfLevels );
    registration->SetInitialTransformParameters( initialParameters );
    registration->StartRegistration();
    }
  catch( itk::ExceptionObject & e )
    {
    std::cout << "Registration failed" << std::endl;
    std::cout << "Reason " << e.GetDescription() << std::endl;
    return EXIT_FAILURE;
    }


  /***********************************************************
   * Check the results
   ************************************************************/
  RegistrationType::ParametersType solution =
    registration->GetLastTransformParameters();

  std::cout << "Solution is: " << solution << std::endl;


  RegistrationType::ParametersType trueParameters( 
    transform->GetNumberOfParameters() );
  trueParameters.Fill( 0.0 );
  trueParameters[ 0] = 1/scale[0];
  trueParameters[ 4] = 1/scale[1];
  trueParameters[ 8] = 1/scale[2];
  trueParameters[ 9] = - displacement[0]/scale[0];
  trueParameters[10] = - displacement[1]/scale[1];
  trueParameters[11] = - displacement[2]/scale[2];

  std::cout << "True solution is: " << trueParameters << std::endl;

  for( j = 0; j < 9; j++ )
    {
    if( vnl_math_abs( solution[j] - trueParameters[j] ) > 0.025 )
      {
      pass = false;
      }
    }
  for( j = 9; j < 12; j++ )
    {
    if( vnl_math_abs( solution[j] - trueParameters[j] ) > 1.0 )
      {
      pass = false;
      }
    }

  if( !pass )
    {
    std::cout << "Test failed." << std::endl;
    return EXIT_FAILURE;
    }


  /*************************************************
   * Check for parzen window exception
   **************************************************/
  double oldValue = metric->GetMovingImageStandardDeviation();
  metric->SetMovingImageStandardDeviation( 0.005 );

  try
    {
    pass = false;
    registration->StartRegistration();
    }
  catch(itk::ExceptionObject& err)
    {
    std::cout << "Caught expected ExceptionObject" << std::endl;
    std::cout << err << std::endl;
    pass = true;
    }

  if( !pass )
    {
    std::cout << "Should have caught an exception" << std::endl;
    std::cout << "Test failed." << std::endl;
    return EXIT_FAILURE;
    }

  metric->SetMovingImageStandardDeviation( oldValue );


  /*************************************************
   * Check for mapped out of image error
   **************************************************/
  solution[5] = 1000;
  registration->SetInitialTransformParameters( solution );

  try
    {
    pass = false;
    registration->StartRegistration();
    }
  catch(itk::ExceptionObject& err)
    {
    std::cout << "Caught expected ExceptionObject" << std::endl;
    std::cout << err << std::endl;
    pass = true;
    }

  if( !pass )
    {
    std::cout << "Should have caught an exception" << std::endl;
    std::cout << "Test failed." << std::endl;
    return EXIT_FAILURE;
    }


  std::cout << "Test passed." << std::endl;
  return EXIT_SUCCESS;


}


/**
 * This function defines the test image pattern.
 * The pattern is a 3D gaussian in the middle
 * and some directional pattern on the outside.
 */
double F( itk::Vector<double,3> & v )
{
  double x = v[0]; 
  double y = v[1]; 
  double z = v[2];
  const double s = 50;
  double value = 200.0 * exp( - ( x*x + y*y + z*z )/(s*s) );
  x -= 8; y += 3; z += 0;
  double r = vnl_math_sqrt( x*x + y*y + z*z );
  if( r > 35 )
    {
    value = 2 * ( vnl_math_abs( x ) +
      0.8 * vnl_math_abs( y ) +
      0.5 * vnl_math_abs( z ) );
    }
  if( r < 4 )
    {
    value = 400;
    }

  return value;

}
