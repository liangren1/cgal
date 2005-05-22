// Copyright (c) 2005 University of Crete (Greece).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $Source$
// $Revision$ $Date$
// $Name$
//
// Author(s)     : Menelaos Karavelas <mkaravel@tem.uoc.gr>

#ifndef CGAL_DELAUNAY_TRIANGULATION_VORONOI_TRAITS_2_H
#define CGAL_DELAUNAY_TRIANGULATION_VORONOI_TRAITS_2_H 1

#include <CGAL/Voronoi_diagram_adaptor_2/basic.h>
#include <CGAL/Voronoi_diagram_adaptor_2/Default_Voronoi_traits_2.h>
#include <cstdlib>
#include <algorithm>

CGAL_BEGIN_NAMESPACE


//=========================================================================
//=========================================================================

template<class DG>
class DT_Edge_degeneracy_tester
{
  // tests whether a dual edge has zero length
 public:
  typedef DG                                          Dual_graph;

  typedef typename Dual_graph::Edge                   Edge;
  typedef typename Dual_graph::Face_handle            Face_handle;
  typedef typename Dual_graph::Edge_circulator        Edge_circulator;
  typedef typename Dual_graph::All_edges_iterator     All_edges_iterator;
  typedef typename Dual_graph::Finite_edges_iterator  Finite_edges_iterator;

  typedef bool           result_type;
  typedef Arity_tag<2>   Arity;

 private:
  typedef DT_Edge_degeneracy_tester<Dual_graph>    Self;

  typedef typename Dual_graph::Geom_traits         Geom_traits;
  typedef typename Dual_graph::Vertex_handle       Vertex_handle;
  typedef typename Geom_traits::Point_2            Point_2;

 public:
  bool operator()(const Dual_graph& dual, const Face_handle& f, int i) const
  {
    if ( dual.is_infinite(f, i) ) { return false; }

    Vertex_handle v3 = f->vertex(     i  );
    Vertex_handle v4 = dual.tds().mirror_vertex(f, i);

    if ( dual.is_infinite(v3) || dual.is_infinite(v4) ) {
      return false;
    }

    Vertex_handle v1 = f->vertex( dual.ccw(i) );
    Vertex_handle v2 = f->vertex( dual.cw(i) );

    Point_2 p1 = v1->point();
    Point_2 p2 = v2->point();
    Point_2 p3 = v3->point();
    Point_2 p4 = v4->point();
    Oriented_side os =
      dual.geom_traits().side_of_oriented_circle_2_object()(p1,p2,p3,p4);
    return os == ON_ORIENTED_BOUNDARY;
  }

  bool operator()(const Dual_graph& dual, const Edge& e) const {
    return operator()(dual, e.first, e.second);
  }

  bool operator()(const Dual_graph& dual,
		  const All_edges_iterator& eit) const {
    return operator()(dual, *eit);
  }

  bool operator()(const Dual_graph& dual,
		  const Finite_edges_iterator& eit) const {
    return operator()(dual, *eit);
  }

  bool operator()(const Dual_graph& dual, const Edge_circulator& ec) const {
    return operator()(dual, *ec);
  }
};

//=========================================================================
//=========================================================================

template<class DG>
class DT_Face_degeneracy_tester
{
  // tests whether a face has zero area
 public:
  typedef DG                                   Dual_graph;
  typedef typename Dual_graph::Vertex_handle   Vertex_handle;
  typedef typename Dual_graph::Edge            Edge;

  typedef typename Dual_graph::Finite_vertices_iterator
  Finite_vertices_iterator;

  typedef typename Dual_graph::All_vertices_iterator  All_vertices_iterator;
  typedef typename Dual_graph::Vertex_circulator      Vertex_circulator;

  typedef bool           result_type;
  typedef Arity_tag<2>   Arity;

 public:
  template<class A>
  bool operator()(const Dual_graph&, const A&) const {
    return false;
  }
};


//=========================================================================
//=========================================================================


template<class DT2>
class Delaunay_triangulation_Voronoi_traits_2
  : public CGAL_VORONOI_DIAGRAM_2_NS::Default_Voronoi_traits_2
  <DT2, DT_Edge_degeneracy_tester<DT2>, DT_Face_degeneracy_tester<DT2>
  >
{
 private:
  typedef DT_Edge_degeneracy_tester<DT2>              Edge_tester;
  typedef DT_Face_degeneracy_tester<DT2>              Face_tester;

  typedef CGAL_VORONOI_DIAGRAM_2_NS::Default_Voronoi_traits_2
  <DT2,Edge_tester,Face_tester>
  Base;

  typedef Delaunay_triangulation_Voronoi_traits_2<DT2>  Self;
};


//=========================================================================
//=========================================================================

template<class DT2>
class Delaunay_triangulation_cached_Voronoi_traits_2
  : public CGAL_VORONOI_DIAGRAM_2_NS::Default_cached_Voronoi_traits_2
  <DT2, DT_Edge_degeneracy_tester<DT2>, DT_Face_degeneracy_tester<DT2>
  >
{
 private:
  typedef DT_Edge_degeneracy_tester<DT2>              Edge_tester;
  typedef DT_Face_degeneracy_tester<DT2>              Face_tester;

  typedef
  CGAL_VORONOI_DIAGRAM_2_NS::Default_cached_Voronoi_traits_2
  <DT2,Edge_tester,Face_tester>
  Base;

  typedef Delaunay_triangulation_cached_Voronoi_traits_2<DT2>  Self;
};

//=========================================================================
//=========================================================================

template<class DT2>
class Delaunay_triangulation_ref_counted_Voronoi_traits_2
  : public CGAL_VORONOI_DIAGRAM_2_NS::Default_ref_counted_Voronoi_traits_2
  <DT2, DT_Edge_degeneracy_tester<DT2>, DT_Face_degeneracy_tester<DT2>
  >
{
 private:
  typedef DT_Edge_degeneracy_tester<DT2>               Edge_tester;
  typedef DT_Face_degeneracy_tester<DT2>               Face_tester;

  typedef
  CGAL_VORONOI_DIAGRAM_2_NS::Default_ref_counted_Voronoi_traits_2
  <DT2,Edge_tester,Face_tester>
  Base;

  typedef Delaunay_triangulation_ref_counted_Voronoi_traits_2<DT2>  Self;
};

//=========================================================================
//=========================================================================


CGAL_END_NAMESPACE

#endif // CGAL_DELAUNAY_TRIANGULATION_VORONOI_TRAITS_2_H
