#======================================================================
#
#     This routine interfaces with the TASMANIAN Sparse grid
#     The crucial part is 
#
#     aVals[iI]=solveriter.iterate(aPoints[iI], n_agents)[0]  
#     => at every gridpoint, we solve an optimization problem
#
#     Simon Scheidegger, 11/16 ; 07/17
#======================================================================

import TasmanianSG
import numpy as np
from parameters import *
import nonlinear_solver_iterate as solveriter

#======================================================================

def sparse_grid_iter(n_agents, iDepth, lvalold, iG):
    
    grid  = TasmanianSG.TasmanianSparseGrid()

    k_range=np.array([k_bar, k_up])

    ranges=np.empty((n_agents, 2))


    for i in range(n_agents):
        ranges[i]=k_range

    iDim=n_agents
    iOut=1

    grid.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
    grid.setDomainTransform(ranges)

    # 1 : Make grid
    aPoints=grid.getPoints()
    # Nb points on your grid
    iNumP1=aPoints.shape[0]
    print(iNumP1)

    aVals=np.empty([iNumP1, 1])
    
    
    for iI in range(iNumP1):
        # 2 : Evaluate the function at each point
        print("succes 1")
        phi_i = phi[iG]
        print("succes 2")
        print(lvalold)
        aVals[iI]=solveriter.iterate(aPoints[iI], n_agents, lvalold, phi_i)[0]
        print("succes 3")
          
    # 3 : estimate the interpolant \alpha_{j,i} (the parameters)
    grid.loadNeededPoints(aVals)
    
    #refinement level --> adaptative part
    for iK in range(refinement_level):
        # 1.B.1 Where to add grid points
        grid.setSurplusRefinement(fTol, 1, "fds")  
        
        # 1.B.2 Create the new ADAPTIVE grid
        aPoints = grid.getNeededPoints()
        
        # Nb of points on this new grid
        print(iNumP1)
        iNumP1=aPoints.shape[0]
        aVals = np.empty([iNumP1, 1])
        
        for iI in range(iNumP1):    
            phi_i = phi[iG]
            aVals[iI] = solveriter.iterate(aPoints[iI], n_agents, lvalold, phi_i)[0]
            # 2.B Evaluate the value function at these new points
            
        print("Refinement level", iK)
        
        # 3.B : estimate the interpolant for these new points
        grid.loadNeededPoints(aVals)
    
    f=open("grid_iter.txt", 'w')
    np.savetxt(f, aPoints, fmt='% 2.16f')
    f.close()
    
    return grid

#======================================================================
