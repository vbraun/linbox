/* linbox/blackbox/mapleBB.h
 *
 * Written by David Saunders <saunders@cis.udel.edu>
 * See COPYING
 */

#ifndef __COMPANION_H
#define __COMPANION_H

#include "linbox/blackbox/triplesbb.h"
#include <vector>

namespace LinBox {

template<class Field, class Vector>
struct Companion: public TriplesBB<Field, Vector> {

	/// n by n companion matrix from given degree n polynomial.
	template<class Polynomial>
	Companion(const Field& F =Field(), const Polynomial& P =Polynomial(1))
        : TriplesBB<Field,Vector>(F, P.size()-1, P.size()-1)
	{	size_t n = P.size() - 1;
		const size_t indexbase = 1;
		typename Field::Element one; F.init(one, 1);
	 	for (size_t i = 1; i < n; ++i) addEntry(one, i+indexbase, i-1+indexbase); 
	 	for (size_t i = 0; i < n; ++i)
		{	typename Field::Element x;
			F.init(x, 0);
			F.neg(x, P[i]); 
			addEntry(x, i+indexbase, n-1+indexbase); 
		}
	}// Companion cstor
 
	


	/** Companion cstor from random poly.  
	 Builds n by n matrix from degree n monic poly with other coefficients random.
	*/
	Companion(const Field& F, size_t n, 
		  typename Field::RandIter r )
	: TriplesBB<Field, Vector>(F, n, n)
	{				
		std::vector<typename Field::Element> p(n+1);	       
		for (typename std::vector<typename Field::Element>::iterator i = p.begin(); i != p.end(); ++i)
			r.random(*i); // we'll pretend p[n] == 1, ok?
		
		const size_t indexbase = 1;
		typename Field::Element one; F.init(one, 1);
	 	for (size_t i = 1; i < n; ++i) addEntry(one, i+indexbase, i-1+indexbase); 
	 	for (size_t i = 0; i < n; ++i)
		{	typename Field::Element x;
			F.init(x, 0);
			F.neg(x, p[i]); 
			addEntry(x, i+indexbase, n-1+indexbase); 
		}
	
	}

	Companion(const Field& F, size_t n) :TriplesBB<Field,Vector>(F,n,n) 
	{
		typename Field::RandIter r(F);
		std::vector<typename Field::Element> p(n+1);	       
		for (typename std::vector<typename Field::Element>::iterator i = p.begin(); i != p.end(); ++i)
			r.random(*i); // we'll pretend p[n] == 1, ok?

		const size_t indexbase = 1;
		typename Field::Element one; F.init(one, 1);
	 	for (size_t i = 1; i < n; ++i) addEntry(one, i+indexbase, i-1+indexbase); 
	 	for (size_t i = 0; i < n; ++i)
		{	typename Field::Element x;
			F.init(x, 0);
			F.neg(x, p[i]); 
			addEntry(x, i+indexbase, n-1+indexbase); 
		}

	}
	

// companion would be faster if built direct, using one axpy per entry: y_i = x_i-1 + p_i*x_n

}; //Companion class

} //LinBox
#endif //__COMPANION_H

