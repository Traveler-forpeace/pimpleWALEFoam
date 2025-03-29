#include "createRDeltaT.H"

Info<< "Reading field p\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

#include "createPhi.H"

pressureReference pressureReference(p, pimple.dict());

mesh.schemes().setFluxRequired(p.name());


autoPtr<viscosityModel> viscosity(viscosityModel::New(mesh));

autoPtr<incompressible::momentumTransportModel> turbulence
(
    incompressible::momentumTransportModel::New(U, phi, viscosity)
);



const volScalarField nuLam(turbulence->nu());

const volScalarField kSmall
(
    IOobject
    (
        "kSmall",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE

    ),
    mesh,
           dimensionedScalar
      (
           "kSmall",
           dimVelocity*dimVelocity,
           SMALL
      )
);

const volScalarField deltaSmall
(
    IOobject
    (
        "deltaSmall",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE

    ),
    mesh,
           dimensionedScalar
      (
           "deltaSmall",
           dimLength,
           SMALL
      )
);

volScalarField nuTot
(
    IOobject
    (
        "nuTot",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "nuTot",
           dimLength*dimLength/dimTime,
           0.0
      )
);

volScalarField V
(
    IOobject
    (
        "V",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "V",
           dimLength*dimLength*dimLength,
           0.0
      )
);

volScalarField deltaMesh
(
    IOobject
    (
        "deltaMesh",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "deltaMesh",
           dimLength,
           0.0
      )
);

volScalarField kSGS
(
    IOobject
    (
        "kSGS",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "kSGS",
           dimVelocity*dimVelocity,
           0.0
      )
);

volScalarField kRes
(
    IOobject
    (
        "kRes",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "kRes",
           dimVelocity*dimVelocity,
           0.0
      )
);

volScalarField kTot
(
    IOobject
    (
        "kTot",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "kTot",
           dimVelocity*dimVelocity,
           0.0
      )
);

volScalarField epsilonSGS
(
    IOobject
    (
        "epsilonSGS",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "epsilonSGS",
           dimVelocity*dimVelocity/dimTime,
           0.0
      )
);

volScalarField epsilonTot
(
    IOobject
    (
        "epsilonTot",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "epsilonTot",
           dimVelocity*dimVelocity/dimTime,
           0.0
      )
);

volScalarField eta
(
    IOobject
    (
        "eta",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "eta",
           dimLength,
           0.0
      )
);

volScalarField LESResIndex_k
(
    IOobject
    (
        "LESResIndex_k",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "LESResIndex_k",
           dimless,
           0.0
      )
);

volScalarField LESResIndex_eta
(
    IOobject
    (
        "LESResIndex_eta",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "LESResIndex_eta",
           dimless,
           0.0
      )
);

volScalarField LESResIndex_nut
(
    IOobject
    (
        "LESResIndex_nut",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
     mesh,
           dimensionedScalar
      (
           "LESResIndex_nut",
           dimless,
           0.0
      )
);

#include "createMRF.H"
#include "createFvModels.H"
#include "createFvConstraints.H"
