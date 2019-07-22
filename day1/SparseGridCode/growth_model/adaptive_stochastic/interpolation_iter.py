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

def sparse_grid_iter(n_agents, iDepth, iG, Lvalold):
    
    grid  = TasmanianSG.TasmanianSparseGrid()

    k_range=np.array([k_bar, k_up])

    ranges=np.empty((n_agents, 2))


    for i in range(n_agents):
        ranges[i]=k_range

    iDim=n_agents

    grid.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
    grid.setDomainTransform(ranges)

    aPoints=grid.getPoints()
    iNumP1=aPoints.shape[0]
    aVals=np.empty([iNumP1, iOut])
    
    file=open("comparison1.txt", 'w')
    for iI in range(iNumP1):
        aVals[iI]=solveriter.iterate(aPoints[iI], n_agents, Lvalold, phi[iG])[0]
            
    grid.loadNeededPoints(aVals) # Get interpolant at sparse grid
    
    #refinement level
    for iK in range(refinement_level):
        
        grid.setSurplusRefinement(fTol, 1, "fds")   #also use fds, or other rules
        aPoints = grid.getNeededPoints()
        #grid.plotPoints2D()
        print("Number of Points",grid.getNumPoints())
        aVals=np.empty([aPoints.shape[0], iOut])
        
        for iI in range(aPoints.shape[0]):
            # Solve the value function problem for all grid points
            aVals[iI] = solveriter.iterate(aPoints[iI], n_agents, Lvalold, phi[iG])[0]

        # Update interpolant
        grid.loadNeededPoints(aVals)


    #print(" {0:9d} {1:9d}  {2:1.2e}".format(iK+1, grid.getNumPoints()))
    grid2 = TasmanianSG.TasmanianSparseGrid()
    grid2.makeLocalPolynomialGrid(iDim, iOut, refinement_level+iDepth, which_basis, "localp")
    print("Max Number of Points",grid2.getNumPoints())
    
    #f=open("grid_iter.txt", 'w')
    #np.savetxt(f, aPoints, fmt='% 2.16f')
    #f.close()
    
    return grid

#======================================================================