/* -*- mode: C++; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */

/* linbox/algorithms/localsmith.h
 *
 * Written by David Saunders
 *
 * ------------------------------------
 *
 * See COPYING for license information.
 */

#ifndef __2LOCALSMITH_H
#define __2LOCALSMITH_H

#include <vector>
#include <list>
//#include <algorithm>

#include "linbox/matrix/dense-submatrix.h"
#include "linbox/field/local2_32.h"

namespace LinBox 
{

/** 
 @memo Smith normal form (invariant factors) of a matrix over a local ring.
 * @doc
 */
template<class Local>
class LocalSmith;
 
template <> 
class LocalSmith<Local2_32>
{
    public:
	typedef Local2_32 LocalPID;
	typedef LocalPID::Element Elt;

	template<class Matrix>
	list<Elt>& operator()(list<Elt>& L, Matrix& A, const LocalPID& R)
	{   Elt d; R.init(d, 1);
	    return smithStep(L, d, A, R);
	}

	template<class Matrix>
	list<Elt>& 
	smithStep(list<Elt>& L, Elt& d, Matrix& A, const LocalPID& R)
	{
	    //std::cout << "Dimension: " << A.rowdim() << " " << A.coldim() <<"\n";
	    if ( A.rowdim() == 0 || A.coldim() == 0 ) 
		return L;

	    //std::cout << "Matrix:\n";
	    //A.write(std::cout);

	    LocalPID::Exponent g = LocalPID::Exponent(32); //R.init(g, 0); // must change to 2^31 maybe.
	    typename Matrix::RowIterator p;
	    typename Matrix::Row::iterator q, r;
    	    for ( p = A.rowBegin(); p != A.rowEnd(); ++p) 
	    {
                for (q = p->begin(); q != p->end(); ++q) 
		{
       	            R.gcdin(g, *q);
		    if ( R.isUnit(g) ) break;
		}
		if ( R.isUnit(g) ) break;
	    }
	    //std::cout << "g = " << (int)g <<"\n"; 
	    if ( R.isZero(g) ) 
	    {
		  //  std::cout << " R.isZero(g) is used\n";
		   // std::cout << A.rowdim() << " " << A.coldim() << "\n";
		L.insert(L.end(), 
			 (A.rowdim() < A.coldim()) ? A.rowdim() : A.coldim(),
			 0 
			 );
		return L;
	    }
    	    if ( p != A.rowEnd() ) // g is a unit and, 
	    // because this is a local ring, value at which this first happened 
	    // also is a unit.
    	    {
	        if ( p != A.rowBegin() ) 
		    swap_ranges(A.rowBegin()->begin(), A.rowBegin()->end(),
				    p->begin());
	        if ( q != p->begin() ) 
		    swap_ranges(A.colBegin()->begin(), A.colBegin()->end(),
				    (A.colBegin() + (q - p->begin()))->begin());

	        // eliminate step - crude and for dense only - fix later
		// Want to use a block method or "left looking" elimination.
		//std::cout << " Value of A[0][0]: " << *(A.rowBegin() -> begin()) <<"\n";
		Elt f; R.inv(f, *(A.rowBegin()->begin() ) );
		R.negin(f);
		// normalize first row to -1, ...
		//std::cout << "f = " << f << "\n";
		//A.write(std::cout);

	        for ( q = A.rowBegin()->begin() /*+ 1*/; q != A.rowBegin()->end(); ++q) 
	            R.mulin(*q, f);
		//
		// eliminate in subsequent rows
	        for ( p = A.rowBegin() + 1; p != A.rowEnd(); ++p)
	            for ( q = p->begin() + 1, r = A.rowBegin()->begin() + 1, f = *(p -> begin()); 
				    q != p->end(); ++q, ++r )
		        R.axpyin( *q, f, *r );

	        DenseSubmatrix<Elt> Ap(A, 1, 1, A.rowdim() - 1, A.coldim() - 1);
		L.push_back(d);
	        return smithStep(L, d, Ap, R); 
    	    }
    	    else  
    	    { 
		typename Matrix::RawIterator p;
	        for (p = A.rawBegin(); p != A.rawEnd(); ++p) R.divin(*p, g); 
	        return smithStep(L, R.mulin(d, g), A, R);
    	    }
    	}

}; // end LocalSmith

} // end LinBox

	/* Constructor
	 * @param F Field over which to operate
	 * @param traits @ref{SolverTraits} structure describing user
	 *               options for the solver 
	LocalSmith(
		   ???
		   const Field &F, const SolverTraits<LanczosTraits> &traits)
		: _traits (traits), _F (F), _randiter (F), _VD (F)
	{}
	 */

#endif // __LOCALSMITH_H
