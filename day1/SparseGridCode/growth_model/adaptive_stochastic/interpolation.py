#======================================================================
#
#     This routine interfaces with the TASMANIAN Sparse grid
#     The crucial part is 
#
#     aVals[iI]=solver.initial(aPoints[iI], n_agents)[0]  
#     => at every gridpoint, we solve an optimization problem
#
#     Simon Scheidegger, 11/16 ; 07/17
#======================================================================

import TasmanianSG
import numpy as np
from parameters import *
import nonlinear_solver_initial as solver

#======================================================================



def sparse_grid(n_agents, iDepth, iG):
    
    grid  = TasmanianSG.TasmanianSparseGrid()

    k_range=np.array([k_bar, k_up])

    ranges=np.empty((n_agents, 2))


    for i in range(n_agents):
        ranges[i]=k_range

    iDim=n_agents

    grid.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
    grid.setDomainTransform(ranges)

 
    # 1 : Make grid
    aPoints=grid.getPoints()
    # Nb points on your grid
    iNumP1=aPoints.shape[0]
    aVals=np.empty([iNumP1, iOut])
    
    grid.plotPoints2D()
    
    for iI in range(iNumP1):
        # 2 : Evaluate the function at each point
        phi_i = phi[iG]
        aVals[iI] = solver.initial(aPoints[iI], n_agents, phi_i)[0]
            #aVals[iI,:]=solver.initial(aPoints[iI,:], n_agents)[0] 

    
    # 3 : estimate the interpolant \alpha_{j,i} (the parameters)
    grid.loadNeededPoints(aVals)
    
    
    #refinement level --> adaptative part

    for iK in range(refinement_level):
        #also use fds, or other rules
        # 1.B.1 Where to add grid points
        grid.setSurplusRefinement(fTol, 1, "fds")  
        
        # 1.B.2 Create the new ADAPTIVE grid
        aPoints = grid.getNeededPoints()
        #grid.plotPoints2D()

        # Nb of points on this new grid
        iNumP1=aPoints.shape[0]
        #print(iNumP1)
        aVals = np.empty([iNumP1, iOut])
        
        for iI in range(iNumP1):
            phi_i = phi[iG]
            aVals[iI] = solver.initial(aPoints[iI], n_agents, phi_i)[0]
                #aVals[iI,:]=solver.initial(aPoints[iI,:], n_agents)[0] 
        print("Refinement level", iK)
        
        # 3.B : estimate the interpolant for these new points
        grid.loadNeededPoints(aVals)
    
    
    return grid
#======================================================================

