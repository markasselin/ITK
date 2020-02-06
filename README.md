![ITK - The Insight Toolkit](Documentation/Art/itkBannerSmall.png)

ITK: The Insight Toolkit
========================

[![GitHub release](https://img.shields.io/github/release/InsightSoftwareConsortium/ITK.svg)](https://github.com/InsightSoftwareConsortium/ITK/releases/latest)
[![PyPI](https://img.shields.io/pypi/v/itk.svg)](https://pypi.python.org/pypi/itk)
[![Wheels](https://img.shields.io/pypi/wheel/itk.svg)](https://pypi.org/project/itk)
[![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://github.com/InsightSoftwareConsortium/ITK/blob/master/LICENSE)
[![DOI](https://zenodo.org/badge/800928.svg)](https://zenodo.org/badge/latestdoi/800928)

| | C++ | Python |
|:------:|:--------:|:--------:|
| Linux | [![Build Status](https://dev.azure.com/itkrobotlinux/ITK.Linux/_apis/build/status/ITK.Linux?branchName=master)](https://dev.azure.com/itkrobotlinux/ITK.Linux/_build/latest?definitionId=2&branchName=master) | [![Build Status](https://dev.azure.com/itkrobotlinuxpython/ITK.Linux.Python/_apis/build/status/ITK.Linux.Python?branchName=master)](https://dev.azure.com/itkrobotlinuxpython/ITK.Linux.Python/_build/latest?definitionId=3&branchName=master) |
| macOS | [![Build Status](https://dev.azure.com/itkrobotmacos/ITK.macOS/_apis/build/status/ITK.macOS?branchName=master)](https://dev.azure.com/itkrobotmacos/ITK.macOS/_build/latest?definitionId=2&branchName=master) | [![Build Status](https://dev.azure.com/itkrobotmacospython/ITK.macOS.Python/_apis/build/status/ITK.macOS.Python?branchName=master)](https://dev.azure.com/itkrobotmacospython/ITK.macOS.Python/_build/latest?definitionId=2&branchName=master) |
| Windows | [![Build Status](https://dev.azure.com/itkrobotwindow/ITK.Windows/_apis/build/status/ITK.Windows?branchName=master)](https://dev.azure.com/itkrobotwindow/ITK.Windows/_build/latest?definitionId=2&branchName=master) | [![Build Status](https://dev.azure.com/itkrobotwindowpython/ITK.Windows.Python/_apis/build/status/ITK.Windows.Python?branchName=master)](https://dev.azure.com/itkrobotwindowpython/ITK.Windows.Python/_build/latest?definitionId=1) |
| Linux (Code coverage)| [![Build Status](https://dev.azure.com/itkrobotbatch/ITK.Coverage/_apis/build/status/ITK.Coverage?branchName=master)](https://dev.azure.com/itkrobotbatch/ITK.Coverage/_build/latest?definitionId=3&branchName=master) | |

Links
-----

* [Homepage](https://itk.org)
* [Download](https://itk.org/download/)
* [Discussion](https://discourse.itk.org/)
* [Software Guide](https://itk.org/ItkSoftwareGuide.pdf)
* [Help](https://itk.org/resources/)
* [Examples](https://itk.org/ITKExamples/)
* [Issue tracking](https://github.com/InsightSoftwareConsortium/ITK/issues)
* [Submit a patch](CONTRIBUTING.md)


About
-----

The Insight Toolkit (ITK) is an open-source, cross-platform toolkit for
N-dimensional scientific image processing, segmentation, and registration.
Segmentation is the process of identifying and classifying data found in a
digitally sampled representation. Typically the sampled representation is an
image acquired from such medical instrumentation as CT or MRI scanners.
Registration is the task of aligning or developing correspondences between
data. For example, in the medical environment, a CT scan may be aligned with a
MRI scan in order to combine the information contained in both.

ITK is distributed in binary Python packages. To install:

```
pip install itk
```

or

```
conda install -c conda-forge itk
```

The cross-platform, C++ core of the toolkit may be built from source using
[CMake](https://cmake.org).


Copyright
---------

The [Insight Software Consortium](http://www.insightsoftwareconsortium.org)
holds the copyright of this software. This is a non-profit entity that
promotes the use of ITK for educational and research purposes. ITK is
distributed under a license that enables use for both non-commercial and
commercial applications. See [LICENSE](https://github.com/InsightSoftwareConsortium/ITK/blob/master/LICENSE)
and [NOTICE](https://github.com/InsightSoftwareConsortium/ITK/blob/master/NOTICE)
files for details.

Citation
--------

To cite ITK, please reference, as appropriate:

### The papers

> McCormick M, Liu X, Jomier J, Marion C, Ibanez L. ITK: enabling reproducible research and open science. Front Neuroinform. 2014;8:13. Published 2014 Feb 20. doi:10.3389/fninf.2014.00013

> Yoo TS, Ackerman MJ, Lorensen WE, Schroeder W, Chalana V, Aylward S, Metaxas D, Whitaker R. Engineering and Algorithm Design for an Image Processing API: A Technical Report on ITK – The Insight Toolkit. In Proc. of Medicine Meets Virtual Reality, J. Westwood, ed., IOS Press Amsterdam pp 586-592 (2002).

### The books

> Johnson, McCormick, Ibanez. "The ITK Software Guide: Design and Functionality." Fourth Edition. Published by Kitware, Inc. 2015 ISBN: 9781-930934-28-3.

> Johnson, McCormick, Ibanez. "The ITK Software Guide: Introduction and Development Guidelines." Fourth Edition. Published by Kitware, Inc. 2015 ISBN: 9781-930934-27-6.

### Specific software version

[![DOI](https://zenodo.org/badge/800928.svg)](https://zenodo.org/badge/latestdoi/800928)
