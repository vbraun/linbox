/* -*- mode: C++; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*- */

/* linbox/solutions/solve.h
 * Copyright (C) 2002 Bradford Hovinen
 *
 * Written by Bradford Hovinen <hovinen@cis.udel.edu>
 *
 * ------------------------------------
 * 2002-08-09  Bradford Hovinen  <hovinen@cis.udel.edu>
 *
 * Renamed from solver.h to solve.h, tweak indentation,
 * Add argument SolverTraits for additional parameters,
 * Add header
 *
 * Moved solver code proper to linbox/algorithms/wiedemann.h; solve () is now
 * just a wrapper (consequently copyright notices have changed)
 * ------------------------------------
 * See COPYING for license information.
 */

#ifndef __SOLVE_H
#define __SOLVE_H

#include <vector>
#include <algorithm>

#include "linbox/algorithms/wiedemann.h"
#include "linbox/util/debug.h"
#include "linbox/field/vector-domain.h"
#include "linbox/solutions/methods.h"

namespace LinBox 
{

/** Solve a system Ax=b over the field F
 * 
 * This is a general interface for the linear system solving capabilities of
 * LinBox. If the system is nonsingular, it returns the unique solution, storing
 * it in the vector x. If the system is consistent and singular, it returns a
 * random solution. Repeated calls to this function can give a complete
 * description of the solution manifold. If the system is inconsistent and the
 * @ref{SolverTraits} structure supplied requests certification of
 * inconsistency, it throws an @ref{InconsistentSystem} exception, which
 * includes a certificate of inconsistency. Otherwise, it runs through the
 * number of iterations specified in @code{traits} and throws a
 * @ref{SolveFailed} exception if it cannot find a solution.
 *
 * @param A Black box matrix of the system
 * @param x Place to store solution vector
 * @param b Right-hand side
 * @param F Field over which to perform computations
 * @param traits @ref{SolverTraits} structure with user-specified parameters
 * @return Reference to solution vector
 */

template <class Field, class Blackbox, class Vector>
Vector &solve (const Blackbox     &A,
	       Vector             &x,		       
	       const Vector       &b,
	       const Field        &F,
	       const SolverTraits &traits = SolverTraits ())
{
	switch (traits.method ()) {
	    case SolverTraits::WIEDEMANN: 
	    {
		WiedemannSolver<Field, Vector> solver (F, traits);
		return solver.solve (A, x, b);
	    }

	    case SolverTraits::LANCZOS:
		throw LinboxError ("Lanczos-based solver not implemented");

	    case SolverTraits::ELIMINATION:
		throw LinboxError ("Elimination-based solver not implemented");
	}

	return x;
}

/** Enumeration of possible results of @ref{solve}
 *
 * SOLVE_SUCCESSFUL - System solution was succesful, @code{x} holds the solution
 * vector 
 * SOLVE_INCONSISTENT - System was inconsistent, @code{u} holds the certificate
 * of inconsistency and @code{x} is untouched
 * SOLVE_FAILED - Neither a system solution nor a certificate of inconsistency
 * could be obtained before the maximum number of trials elapsed. Both @code{x}
 * and @code{u} are untouched.
 */

enum SolveResult {
	SOLVE_SUCCESSFUL, SOLVE_INCONSISTENT, SOLVE_FAILED
};

/* Solve a linear system Ax=b over the field F
 *
 * This is a variant of @code{solve} that does not throw any exceptions unless
 * the user makes an error. It returns a @ref{SolveResult} enum indicating
 * whether the solve operation was successful, the system was inconsistent, or
 * the solve operation failed. The certificate of inconsistency, if requested,
 * is stored in a reference parameter supplied to this variant.
 *
 * @param A Black box matrix of the system
 * @param x Place to store solution vector
 * @param b Right-hand side
 * @param u Place to store certificate of inconsistency
 * @param F Field over which to perform computations
 * @param traits @ref{SolverTraits} structure with user-specified parameters
 * @return @ref{SolveResult} indicating whether the solve operation was
 * successful
 */

template <class Field, class Blackbox, class Vector>
SolveResult solve (const Blackbox     &A,
		   Vector             &x,		       
		   const Vector       &b,
		   const Field        &F,
		   Vector             &u,
		   const SolverTraits &traits = SolverTraits ())
{
	try {
		solve (A, x, b, F, traits);
	}
	catch (SolveFailed) {
		return SOLVE_FAILED;
	}
	catch (InconsistentSystem<Vector> e) {
		VectorDomain<Field> VD (F);
		F.copy (u, e.u ());
		return SOLVE_INCONSISTENT;
	}

	return SOLVE_SUCCESSFUL;
}

}

#endif // __SOLVE_H
