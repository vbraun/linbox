# Demonstrational LinBox/Maple interface.
# by Rich Seagraves
# Note that this interface is a demo version.  A newer, cleaner implementation
# is in the works.  But this gets the job done

# Insert the location of your compiled LinBox library 
LinBoxLIBlocation := "/some/path/here/libmapleLB.so";


module LinBox()
	local create, lbXrank1, lbXrank2, lbXrank3, lbXdet1, lbXdet2, lbXdet3,
	 	lbXmp1, lbXmp2, lbXmp3, lbXapply, lbXapplyT, MapToEx, ExToMap;
	export LBrank, LBdet, LBminpoly, LBapply, LBapplyTranspose;
	option package, load=create;
	description "Demonstrational LinBox/Maple interface";

	create := proc()
		lbXrank1 := define_external(rank1,MAPLE,LIB=LinBoxLIBlocation);
		lbXrank2 := define_external(rank2,MAPLE,LIB=LinBoxLIBlocation);
		lbXrank3 := define_external(rank3,MAPLE,LIB=LinBoxLIBlocation);
		lbXmp1 := define_external(minpoly1,MAPLE,LIB=LinBoxLIBlocation);
		lbXmp2 := define_external(minpoly2, MAPLE,LIB=LinBoxLIBlocation);
		lbXmp3 := define_external(minpoly3, MAPLE,LIB=LinBoxLIBlocation);
		lbXdet1 := define_external(det1,MAPLE,LIB=LinBoxLIBlocation);
		lbXdet2 := define_external(det2,MAPLE,LIB=LinBoxLIBlocation);
		lbXdet3 := define_external(det3,MAPLE,LIB=LinBoxLIBlocation);
#		lbXapply := define_external(externApply,MAPLE,LIB=LinBoxLIBlocation);
#		lbXapplyT := define_external(externApplyTranspose,MAPLE,LIB=LinBoxLIBlocation);
	end proc;

	# Temporary testing line
	create();
	
	LBminpoly := proc(p::posint, M::Matrix(storage=sparse) )
		local L, R, C, D, rows, cols, q, l, i, x;

		if nargs = 3 and type( args[3], name) then
			x := args[3];
		else if nargs = 3 then
			error "Third arguement, if provided, must be name!";
		else 		  # assume there is no symbolic constant
			x := 'x'; # use a default
		end if;

		if op(3,M)[1] = 'datatype = integer[4]' then 
			L := lbXmp1(p,M,s);
			add(L[i]*x^(i-1),i=1..nops(L));
		elif p < kernelopts(maximmediate) then 
			rows := op(1,M)[1];
			cols := op(1,M)[2];
			q := op(2,M);
			l := nops(q);
			R := Array(1..l, datatype=integer[4]);
			C := Array(1..l, datatype=integer[4]);
			D := Array(1..l, datatype=integer[4]);
			for i from 1 to l do
				R[i] := op(q[i])[1]; C[i] := op(q[i])[2];
				D[i] := op(q[i])[3];
			od;
			L := lbXmp2(p,R,C,D,rows,cols);
			add(L[i]*x^(i-1),i=1..nops(L));;
		else 
			rows := op(1,M)[1];
			cols := op(1,M)[2];
			q := op(2,M);
			l := nops(q);
			R := Array(1..l, datatype=integer[4]);
			C := Array(1..l, datatype=integer[4]);
			D := [seq(MapToEx(op(q[i])[3]),i=1..l)];
			for i from 1 to l do
				R[i] := op(q[i])[1]; C[i] := op(q[i])[2];
			od;
			L := lbXmp3(MapToEx(p),R,C,D,rows,cols);
			add(ExToMap(L[i])*x^(i-1),i=1..nops(L));
		fi;
	end proc;

	LBrank := proc(p::posint, M::Matrix(storage=sparse) )
		local R, C, D, rows, cols, q, i, l;
		if op(3,M)[1] = 'datatype=integer[4]' then 
			lbXrank1(p,M);
		elif p < kernelopts(maximmediate) then
			q := op(2,M);
			l := nops(q);
			R := Array(1..l, datatype=integer[4]);
			C := Array(1..l, datatype=integer[4]);
			D := Array(1..l, datatype=integer[4]);
			for i from 1 to l do
				R[i] := op(q[i])[1];
				C[i] := op(q[i])[2];
				D[i] := op(q[i])[3];
			end do;
			rows := op(1,M)[1];
			cols := op(1,M)[2];
			lbXrank2(p,R,C,D,rows,cols);
		else 
			q := op(2,M);
			l := nops(q);
			R := Array(1..l,datatype=integer[4]);
			C := Array(1..l,datatype=integer[4]);
			D := [seq( MapToEx( op(q[i])[3]),i=1..l)];
			for i from 1 to l do
				R[i] := op(q[i])[1];
				C[i] := op(q[i])[2];
			end do;
			rows := op(1,M)[1];
			cols := op(1,M)[2];
			lbXrank3(MapToEx(p),R,C,D,rows,cols);
		end if;
	end proc;

	LBdet := proc(p::posint, M::Matrix(storage=sparse))
		local R, C, D, rows, cols, q, i, l, A;
		if op(3,M)[1] = 'datatype=integer[4]' then 
			lbXdet1(p,M);
		elif p < kernelopts(maximmediate) then 
			q := op(2,M);
			l := nops(q);
			R := Array(1..l,datatype=integer[4]);
			C := Array(1..l, datatype=integer[4]);
			D := Array(1..l,datatype=integer[4]);
			for i from 1 to l do
				R[i] := op(q[i])[1]; C[i] := op(q[i])[2];
				D[i] := op(q[i])[3];
			od;
			rows := op(1,M)[1]; cols := op(1,M)[2];
			lbXdet2(p,R,C,D,rows,cols);
		else 
			q := op(2,M);
			l := nops(q);
			R := Array(1..l, datatype=integer[4]);
			C := Array(1..l, datatype=integer[4]);
			D := [seq(MapToEx(op(q[i])[3]),i=1..l)];
			for i from 1 to l do
				R[i] := op(q[i])[1]; C[i] := op(q[i])[2];
			od;
			rows := op(1,M)[1]; cols := op(1,M)[2];
			A := detLBI(MapToEx(p),R,C,D,rows,cols);
			ExToMap(A);
		fi;
	end proc;



	MapToEx := proc(num::posint)
		local r, l, i, A;
		if num < kernelopts(maximmediate) then num;
		else
			r := [disassemble](addressof(num));
			l := nops(r) - 1;
			A := Array(1..l, datatype=integer[4]);
			for i from 1 to l do
				A[i] := r[i+1];
			od;
			A;
		fi;
	end proc;

	ExToMap := proc(A::Array(datatype=integer[4]))
		local b0, b, i, s, r;
		b0 := 2^kernelopts(wordsize); b := 1; s = A[1]; r := op(2,A);
		for i from lhs(r) + 1 to rhs(r) do
			b := b0 * b;
			s := s + b * A[i];
		od;
		s;
	end proc;

	LBapply := proc(M::Matrix(storage=sparse,datatype=integer[4]),x::Vector(datatype=integer[4]),p::posint)
	   lbXapply(p,M,x);
	end proc;

	LBapplyTranspose := proc(M::Matrix(storage=sparse,datatype=integer[4]),x::Vector(datatype=integer[4]),p::posint)
	   lbXapplyT(p,M,x);
	end proc;
end module;
