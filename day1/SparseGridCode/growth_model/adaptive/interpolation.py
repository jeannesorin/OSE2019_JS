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

def sparse_grid(n_agents, iDepth):
    
    grid  = TasmanianSG.TasmanianSparseGrid()

    k_range=np.array([k_bar, k_up])

    ranges=np.empty((n_agents, 2))


    for i in range(n_agents):
        ranges[i]=k_range

    iDim=n_agents

    grid.makeLocalPolynomialGrid(iDim, iOut, iDepth, which_basis, "localp")
    grid.setDomainTransform(ranges) # Change domain to K low and upper bar

    aPoints=grid.getPoints()
    iNumP1=aPoints.shape[0]
    aVals=np.empty([iNumP1, 1])
    
    file=open("comparison0.txt", 'w')
    for iI in range(iNumP1):
        aVals[iI]=solver.initial(aPoints[iI], n_agents)[0]# Solve the value function problem for all grid points
        v=aVals[iI]*np.ones((1,1))
        to_print=np.hstack((aPoints[iI].reshape(1,n_agents), v))
        np.savetxt(file, to_print, fmt='%2.16f')
        
    file.close()
    grid.loadNeededPoints(aVals) # evaluate interpolant at grid points
    
    #refinement level
    for iK in range(refinement_level):
        grid.setSurplusRefinement(fTol, 1, "fds")   #also use fds, or other rules
        aPoints = grid.getNeededPoints()
        aVals=np.empty([aPoints.shape[0], 1])
        
        for iI in range(aPoints.shape[0]):
            aVals[iI]=solver.initial(aPoints[iI], n_agents)[0]# Solve the value function problem for all grid points
        
        # Update interpolant
        grid.loadNeededPoints(aVals)

    #print(" {0:9d} {1:9d}  {2:1.2e}".format(iK+1, grid.getNumPoints()))
    #grid2 = TasmanianSG.TasmanianSparseGrid()
    #grid2.makeLocalPolynomialGrid(iDim, iOut, refinement_level+iDepth, which_basis, "localp")
    #a = grid2.getNumPoints()
    
    #f=open("grid.txt", 'w')
    #np.savetxt(f, aPoints, fmt='% 2.16f')
    #f.close()
    
    return grid
#======================================================================