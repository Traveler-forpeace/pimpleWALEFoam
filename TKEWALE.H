if (U.db().foundObject<volVectorField>("UMean"))
{

    const objectRegistry& db = U.db();

    volVectorField UPrime = (U - db.lookupObject<volVectorField>("UMean"));

    volScalarField nuSGS = db.lookupObject<volScalarField>("nut"); //get nut
	
	nuTot = nuSGS + nuLam;
	
	V.ref() = mesh.V();
	
	deltaMesh = pow(V, 1.0/3.0); //get mesh delta
		
    //volScalarField kSGS = turbulence->k(); //Instantaneous subgrid-scale tke
    kSGS = sqr(nuSGS/max(0.094*deltaMesh,deltaSmall)); //estimate kSGS
    
    kRes = 0.5*(UPrime & UPrime); //Instantaneous resolved tke

    kTot = kRes + kSGS;

    //volScalarField epsilonSGS = turbulence->epsilon();
    
    volSymmTensorField SRes = symm(fvc::grad(UPrime)); //Instantaneous resolved fluctuating rate of strain
	
    volScalarField epsilonRes = 2*nuLam*(SRes && SRes); //Instantaneous resolved dissipation rate

    epsilonSGS = 2*nuSGS*(SRes && SRes); //Instantaneous modeled dissipation rate

    epsilonTot = epsilonRes + epsilonSGS; //mag(epsilonRes + epsilonSGS);

    LESResIndex_k = kRes/max(kSmall,kTot); //Instantaneous ratio of resolved to total (Resolved + SGS) tke

    eta = pow(pow3(nuTot)/epsilonTot, 1.0/4.0);
	
	LESResIndex_eta = deltaMesh/max(eta,deltaSmall);
	
	LESResIndex_nut = nuSGS/nuLam;

    Info << "ESTIMATED LESResIndex_k min, max, avg: " << min(LESResIndex_k).value()
					    << ", " << max(LESResIndex_k).value()
					    << ", " << LESResIndex_k.weightedAverage(mesh.V()).value()
					    << endl;
						
	Info << "ESTIMATED LESResIndex_eta min, max: " << min(LESResIndex_eta).value() 
						<< ", " << max(LESResIndex_eta).value()
                    	<< endl;

    Info << "ESTIMATED LESResIndex_nut min, max: " << min(LESResIndex_nut).value() 
						<< ", " << max(LESResIndex_nut).value()
                    	<< endl;
						
	Info << "nuSGS min, max: " << min(nuSGS).value() 
						<< ", " << max(nuSGS).value()
                    	<< endl;
						
	Info << "deltaMesh min, max: " << min(deltaMesh).value() 
						<< ", " << max(deltaMesh).value()
                    	<< endl;
						
}

else
{
     Warning << "Averaging of velocity U is not active in controlDict." << endl 
             << "This is necessary to calculate resolved TKE and dissipation rate." << endl
             << "Add field U to the fieldAverage utility iin controlDict." << endl;
}
