#ifndef ObjexxFCL_FArray5_hh_INCLUDED
#define ObjexxFCL_FArray5_hh_INCLUDED

// FArray5: Fortran-Compatible 5D Array Abstract Base Class
//
// Project: Objexx Fortran Compatibility Library (ObjexxFCL)
//
// Version: 4.0.0
//
// Language: C++
//
// Copyright (c) 2000-2014 Objexx Engineering, Inc. All Rights Reserved.
// Use of this source code or any derivative of it is restricted by license.
// Licensing is available from Objexx Engineering, Inc.:  http://objexx.com

// ObjexxFCL Headers
#include <ObjexxFCL/FArray5.fwd.hh>
#include <ObjexxFCL/FArray.hh>
#include <ObjexxFCL/FArray5S.hh>
#include <ObjexxFCL/MArray5.hh>

namespace ObjexxFCL {

// Forward
template< typename > class FArray5D;
template< typename > class FArray5P;
template< typename > class FArray5A;

// FArray5: Fortran-Compatible 5D Array Abstract Base Class
template< typename T >
class FArray5 : public FArray< T >
{

private: // Types

	typedef  FArray< T >  Super;
	typedef  FArray5D< T >  real_FArray;
	typedef  FArray5P< T >  proxy_FArray;
	typedef  FArray5A< T >  arg_FArray;

private: // Friend

	template< typename > friend class FArray5;
	template< typename > friend class FArray5D;
	template< typename > friend class FArray5P;
	template< typename > friend class FArray5A;

protected: // Types

	typedef  internal::InitializerSentinel  InitializerSentinel;
	typedef  internal::ProxySentinel  ProxySentinel;

public: // Types

	typedef  typename Super::Base  Base;
	typedef  typename Super::Tail  Tail;
	typedef  typename Super::IR  IR;
	typedef  typename Super::IS  IS;
	typedef  typename Super::DS  DS;

	// STL Style
	typedef  typename Super::value_type  value_type;
	typedef  typename Super::reference  reference;
	typedef  typename Super::const_reference  const_reference;
	typedef  typename Super::pointer  pointer;
	typedef  typename Super::const_pointer  const_pointer;
	typedef  typename Super::size_type  size_type;
	typedef  typename Super::difference_type  difference_type;

	// C++ Style
	typedef  typename Super::Value  Value;
	typedef  typename Super::Reference  Reference;
	typedef  typename Super::ConstReference  ConstReference;
	typedef  typename Super::Pointer  Pointer;
	typedef  typename Super::ConstPointer  ConstPointer;
	typedef  typename Super::Size  Size;
	typedef  typename Super::Difference  Difference;

	using Super::dimensions_initialized;
	using Super::isize;
	using Super::npos;
	using Super::overlap;
	using Super::size;
	using Super::slice_k;
	using Super::swapB;
	using Super::data_;
	using Super::data_size_;
	using Super::sdata_;
	using Super::shift_;
#ifdef OBJEXXFCL_PROXY_CONST_CHECKS
	using Super::not_const_proxy;
#endif // OBJEXXFCL_PROXY_CONST_CHECKS

protected: // Creation

	// Default Constructor
	inline
	FArray5() :
	 z1_( 0 ),
	 z2_( 0 ),
	 z3_( 0 ),
	 z4_( 0 )
	{}

	// Copy Constructor
	inline
	FArray5( FArray5 const & a ) :
	 Super( a ),
	 z1_( a.z1_ ),
	 z2_( a.z2_ ),
	 z3_( a.z3_ ),
	 z4_( a.z4_ )
	{}

	// Copy Constructor Template
	template< typename U, class = typename std::enable_if< std::is_constructible< T, U >::value >::type >
	inline
	explicit
	FArray5( FArray5< U > const & a ) :
	 Super( a ),
	 z1_( a.z1_ ),
	 z2_( a.z2_ ),
	 z3_( a.z3_ ),
	 z4_( a.z4_ )
	{}

	// Slice Constructor Template
	template< typename U, class = typename std::enable_if< std::is_constructible< T, U >::value >::type >
	inline
	explicit
	FArray5( FArray5S< U > const & a ) :
	 Super( a )
	{}

	// MArray Constructor Template
	template< class A, typename M >
	inline
	explicit
	FArray5( MArray5< A, M > const & a ) :
	 Super( a )
	{}

	// Size Constructor
	inline
	explicit
	FArray5( size_type const size ) :
	 Super( size )
	{}

	// Size + InitializerSentinel Constructor
	inline
	FArray5( size_type const size, InitializerSentinel const & initialized ) :
	 Super( size, initialized )
	{}

	// Initializer List Constructor Template
	template< typename U, class = typename std::enable_if< std::is_constructible< T, U >::value >::type >
	inline
	FArray5( std::initializer_list< U > const l ) :
	 Super( l )
	{}

	// Default Proxy Constructor
	inline
	FArray5( ProxySentinel const & proxy ) :
	 Super( proxy ),
	 z1_( 0 ),
	 z2_( 0 ),
	 z3_( 0 ),
	 z4_( 0 )
	{}

	// Copy Proxy Constructor
	inline
	FArray5( FArray5 const & a, ProxySentinel const & proxy ) :
	 Super( a, proxy )
	{}

	// Base Proxy Constructor
	inline
	FArray5( Base const & a, ProxySentinel const & proxy ) :
	 Super( a, proxy )
	{}

	// Tail Proxy Constructor
	inline
	FArray5( Tail const & s, ProxySentinel const & proxy ) :
	 Super( s, proxy )
	{}

	// Value Proxy Constructor
	inline
	FArray5( T const & t, ProxySentinel const & proxy ) :
	 Super( t, proxy )
	{}

#ifdef OBJEXXFCL_PROXY_CONST_CHECKS

	// Non-Const Copy Proxy Constructor
	inline
	FArray5( FArray5 & a, ProxySentinel const & proxy ) :
	 Super( a, proxy )
	{}

	// Non-Const Base Proxy Constructor
	inline
	FArray5( Base & a, ProxySentinel const & proxy ) :
	 Super( a, proxy )
	{}

	// Non-Const Tail Proxy Constructor
	inline
	FArray5( Tail & s, ProxySentinel const & proxy ) :
	 Super( s, proxy )
	{}

	// Non-Const Value Proxy Constructor
	inline
	FArray5( T & t, ProxySentinel const & proxy ) :
	 Super( t, proxy )
	{}

#endif // OBJEXXFCL_PROXY_CONST_CHECKS

public: // Creation

	// Destructor
	inline
	virtual
	~FArray5()
	{}

public: // Assignment: Array

	// Copy Assignment
	inline
	FArray5 &
	operator =( FArray5 const & a )
	{
		if ( this != &a ) {
			if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2(), a.I3(), a.I4(), a.I5() );
			Super::operator =( a );
		}
		return *this;
	}

	// Copy Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator =( FArray5< U > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2(), a.I3(), a.I4(), a.I5() );
		Super::operator =( a );
		return *this;
	}

	// Slice Assignment
	inline
	FArray5 &
	operator =( FArray5S< T > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2(), a.I3(), a.I4(), a.I5() );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								c[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] = c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// Slice Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator =( FArray5S< U > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2(), a.I3(), a.I4(), a.I5() );
		size_type l( 0 );
		for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
							data_[ l ] = a( i1, i2, i3, i4, i5 );
						}
					}
				}
			}
		}
		return *this;
	}

	// MArray Assignment Template
	template< class A, typename M >
	inline
	FArray5 &
	operator =( MArray5< A, M > const & a )
	{
		if ( ! conformable( a ) ) dimension_assign( a.I1(), a.I2(), a.I3(), a.I4(), a.I5() );
		if ( a.dimensions_initialized() ) {
			size_type l( 0 );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// Initializer List Assignment Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator =( std::initializer_list< U > const l )
	{
		Super::operator =( l );
		return *this;
	}

	// += Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator +=( FArray5< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator +=( a );
		return *this;
	}

	// -= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator -=( FArray5< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator -=( a );
		return *this;
	}

	// *= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator *=( FArray5< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator *=( a );
		return *this;
	}

	// /= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator /=( FArray5< U > const & a )
	{
		assert( conformable( a ) );
		Super::operator /=( a );
		return *this;
	}

	// += Slice
	inline
	FArray5 &
	operator +=( FArray5S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								c[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] += c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] += a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// -= Slice
	inline
	FArray5 &
	operator -=( FArray5S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								c[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] -= c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] -= a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// *= Slice
	inline
	FArray5 &
	operator *=( FArray5S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								c[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] *= c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] *= a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// /= Slice
	inline
	FArray5 &
	operator /=( FArray5S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								c[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] /= c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								assert( a( i1, i2, i3, i4, i5 ) != T( 0 ) );
								data_[ l ] /= a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// += Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator +=( FArray5S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
							data_[ l ] += a( i1, i2, i3, i4, i5 );
						}
					}
				}
			}
		}
		return *this;
	}

	// -= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator -=( FArray5S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
							data_[ l ] -= a( i1, i2, i3, i4, i5 );
						}
					}
				}
			}
		}
		return *this;
	}

	// *= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator *=( FArray5S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
							data_[ l ] *= a( i1, i2, i3, i4, i5 );
						}
					}
				}
			}
		}
		return *this;
	}

	// /= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	operator /=( FArray5S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
							assert( T( a( i1, i2, i3, i4, i5 ) ) != T( 0 ) );
							data_[ l ] /= a( i1, i2, i3, i4, i5 );
						}
					}
				}
			}
		}
		return *this;
	}

	// += MArray Template
	template< class A, typename M >
	inline
	FArray5 &
	operator +=( MArray5< A, M > const & a )
	{
		assert( conformable( a ) );
		if ( a.dimensions_initialized() ) {
			size_type l( 0 );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] += a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// -= MArray Template
	template< class A, typename M >
	inline
	FArray5 &
	operator -=( MArray5< A, M > const & a )
	{
		assert( conformable( a ) );
		if ( a.dimensions_initialized() ) {
			size_type l( 0 );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] -= a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// *= MArray Template
	template< class A, typename M >
	inline
	FArray5 &
	operator *=( MArray5< A, M > const & a )
	{
		assert( conformable( a ) );
		if ( a.dimensions_initialized() ) {
			size_type l( 0 );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] *= a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// /= MArray Template
	template< class A, typename M >
	inline
	FArray5 &
	operator /=( MArray5< A, M > const & a )
	{
		assert( conformable( a ) );
		if ( a.dimensions_initialized() ) {
			size_type l( 0 );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								assert( T( a( i1, i2, i3, i4, i5 ) ) != T( 0 ) );
								data_[ l ] /= a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

public: // Assignment: Array: Logical

	// &&= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	and_equals( FArray5< U > const & a )
	{
		assert( conformable( a ) );
		Super::and_equals( a );
		return *this;
	}

	// ||= Array Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	or_equals( FArray5< U > const & a )
	{
		assert( conformable( a ) );
		Super::or_equals( a );
		return *this;
	}

	// &&= Slice
	inline
	FArray5 &
	and_equals( FArray5S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								c[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] = data_[ i ] && c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] = data_[ l ] && a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// ||= Slice
	inline
	FArray5 &
	or_equals( FArray5S< T > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		if ( overlap( a ) ) { // Overlap-safe
			CArray< T > c( a.size() );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								c[ l ] = a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
			for ( size_type i = 0; i < c.size(); ++i ) {
				data_[ i ] = data_[ i ] || c[ i ];
			}
		} else { // Not overlap-safe
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] = data_[ l ] || a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// &&= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	and_equals( FArray5S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
							data_[ l ] = data_[ l ] && a( i1, i2, i3, i4, i5 );
						}
					}
				}
			}
		}
		return *this;
	}

	// ||= Slice Template
	template< typename U, class = typename std::enable_if< std::is_assignable< T&, U >::value >::type >
	inline
	FArray5 &
	or_equals( FArray5S< U > const & a )
	{
		assert( conformable( a ) );
		size_type l( 0 );
		for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
							data_[ l ] = data_[ l ] || a( i1, i2, i3, i4, i5 );
						}
					}
				}
			}
		}
		return *this;
	}

	// &&= MArray Template
	template< class A, typename M >
	inline
	FArray5 &
	and_equals( MArray5< A, M > const & a )
	{
		assert( conformable( a ) );
		if ( a.dimensions_initialized() ) {
			size_type l( 0 );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] = data_[ l ] && a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

	// ||= MArray Template
	template< class A, typename M >
	inline
	FArray5 &
	or_equals( MArray5< A, M > const & a )
	{
		assert( conformable( a ) );
		if ( a.dimensions_initialized() ) {
			size_type l( 0 );
			for ( int i5 = 1, e5 = a.u5(); i5 <= e5; ++i5 ) {
				for ( int i4 = 1, e4 = a.u4(); i4 <= e4; ++i4 ) {
					for ( int i3 = 1, e3 = a.u3(); i3 <= e3; ++i3 ) {
						for ( int i2 = 1, e2 = a.u2(); i2 <= e2; ++i2 ) {
							for ( int i1 = 1, e1 = a.u1(); i1 <= e1; ++i1, ++l ) {
								data_[ l ] = data_[ l ] || a( i1, i2, i3, i4, i5 );
							}
						}
					}
				}
			}
		}
		return *this;
	}

public: // Assignment: Value

	// = Value
	inline
	FArray5 &
	operator =( T const & t )
	{
		Super::operator =( t );
		return *this;
	}

	// += Value
	inline
	FArray5 &
	operator +=( T const & t )
	{
		Super::operator +=( t );
		return *this;
	}

	// -= Value
	inline
	FArray5 &
	operator -=( T const & t )
	{
		Super::operator -=( t );
		return *this;
	}

	// *= Value
	inline
	FArray5 &
	operator *=( T const & t )
	{
		Super::operator *=( t );
		return *this;
	}

	// /= Value
	inline
	FArray5 &
	operator /=( T const & t )
	{
		Super::operator /=( t );
		return *this;
	}

public: // Subscript

	// array( i1, i2, i3, i4, i5 ) const
	inline
	T const &
	operator ()( int const i1, int const i2, int const i3, int const i4, int const i5 ) const
	{
		assert( contains( i1, i2, i3, i4, i5 ) );
		return sdata_[ ( ( ( ( ( ( ( i5 * z4_ ) + i4 ) * z3_ ) + i3 ) * z2_ ) + i2 ) * z1_ ) + i1 ];
	}

	// array( i1, i2, i3, i4, i5 )
	inline
	T &
	operator ()( int const i1, int const i2, int const i3, int const i4, int const i5 )
	{
		proxy_const_assert( not_const_proxy() );
		assert( contains( i1, i2, i3, i4, i5 ) );
		return sdata_[ ( ( ( ( ( ( ( i5 * z4_ ) + i4 ) * z3_ ) + i3 ) * z2_ ) + i2 ) * z1_ ) + i1 ];
	}

	// Const Tail Starting at array( i1, i2, i3, i4, i5 )
	inline
	Tail const
	a( int const i1, int const i2, int const i3, int const i4, int const i5 ) const
	{
		assert( contains( i1, i2, i3, i4, i5 ) );
		size_type const offset( ( ( ( ( ( ( ( ( i5 * z4_ ) + i4 ) * z3_ ) + i3 ) * z2_ ) + i2 ) * z1_ ) + i1 ) - shift_ );
		return Tail( static_cast< T const * >( data_ + offset ), ( data_size_ != npos ? data_size_ - offset : npos ) );
	}

	// Tail Starting at array( i1, i2, i3, i4, i5 )
	inline
	Tail
	a( int const i1, int const i2, int const i3, int const i4, int const i5 )
	{
		proxy_const_assert( not_const_proxy() );
		assert( contains( i1, i2, i3, i4, i5 ) );
		size_type const offset( ( ( ( ( ( ( ( ( i5 * z4_ ) + i4 ) * z3_ ) + i3 ) * z2_ ) + i2 ) * z1_ ) + i1 ) - shift_ );
		return Tail( data_ + offset, ( data_size_ != npos ? data_size_ - offset : npos ) );
	}

	// Linear Index
	inline
	size_type
	index( int const i1, int const i2, int const i3, int const i4, int const i5 ) const
	{
		assert( dimensions_initialized() );
		return ( ( ( ( ( ( ( ( i5 * z4_ ) + i4 ) * z3_ ) + i3 ) * z2_ ) + i2 ) * z1_ ) + i1 ) - shift_;
	}

public: // Slice Proxy Generators

	// array( s1, s2, s3, s4, s5 ) const
	inline
	FArray5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, IS const & s5 ) const
	{
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray5S< T >( data_, -shift_, d1, d2, d3, d4, d5 );
	}

	// array( i1, s2, s3, s4, s5 ) const
	inline
	FArray4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d2, d3, d4, d5 );
	}

	// array( s1, i2, s3, s4, s5 ) const
	inline
	FArray4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d3, d4, d5 );
	}

	// array( s1, s2, i3, s4, s5 ) const
	inline
	FArray4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d2, d4, d5 );
	}

	// array( s1, s2, s3, i4, s5 ) const
	inline
	FArray4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d2, d3, d5 );
	}

	// array( s1, s2, s3, s4, i5 ) const
	inline
	FArray4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d2, d3, d4 );
	}

	// array( i1, i2, s3, s4, s5 ) const
	inline
	FArray3S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d3, d4, d5 );
	}

	// array( i1, s2, i3, s4, s5 ) const
	inline
	FArray3S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d2, d4, d5 );
	}

	// array( i1, s2, s3, i4, s5 ) const
	inline
	FArray3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d2, d3, d5 );
	}

	// array( i1, s2, s3, s4, i5 ) const
	inline
	FArray3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d2, d3, d4 );
	}

	// array( s1, i2, i3, s4, s5 ) const
	inline
	FArray3S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d4, d5 );
	}

	// array( s1, i2, s3, i4, s5 ) const
	inline
	FArray3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d3, d5 );
	}

	// array( s1, i2, s3, s4, i5 ) const
	inline
	FArray3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d3, d4 );
	}

	// array( s1, s2, i3, i4, s5 ) const
	inline
	FArray3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d2, d5 );
	}

	// array( s1, s2, i3, s4, i5 ) const
	inline
	FArray3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d2, d4 );
	}

	// array( s1, s2, s3, i4, i5 ) const
	inline
	FArray3S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d2, d3 );
	}

	// array( s1, s2, i3, i4, i5 ) const
	inline
	FArray2S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d2 );
	}

	// array( s1, i2, s3, i4, i5 ) const
	inline
	FArray2S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d3 );
	}

	// array( s1, i2, i3, s4, i5 ) const
	inline
	FArray2S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d4 );
	}

	// array( s1, i2, i3, i4, s5 ) const
	inline
	FArray2S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d5 );
	}

	// array( i1, s2, s3, i4, i5 ) const
	inline
	FArray2S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d2, d3 );
	}

	// array( i1, s2, i3, s4, i5 ) const
	inline
	FArray2S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d2, d4 );
	}

	// array( i1, s2, i3, i4, s5 ) const
	inline
	FArray2S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d2, d5 );
	}

	// array( i1, i2, s3, s4, i5 ) const
	inline
	FArray2S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d3, d4 );
	}

	// array( i1, i2, s3, i4, s5 ) const
	inline
	FArray2S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d3, d5 );
	}

	// array( i1, i2, i3, s4, s5 ) const
	inline
	FArray2S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d4, d5 );
	}

	// array( s1, i2, i3, i4, i5 ) const
	inline
	FArray1S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d1 );
	}

	// array( i1, s2, i3, i4, i5 ) const
	inline
	FArray1S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d2 );
	}

	// array( i1, i2, s3, i4, i5 ) const
	inline
	FArray1S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d3 );
	}

	// array( i1, i2, i3, s4, i5 ) const
	inline
	FArray1S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, int const i5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d4 );
	}

	// array( i1, i2, i3, i4, s5 ) const
	inline
	FArray1S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, IS const & s5 ) const
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray1S< T >( data_, k, d5 );
	}

	// array( s1, s2, s3, s4, s5 )
	inline
	FArray5S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, IS const & s5 )
	{
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray5S< T >( data_, -shift_, d1, d2, d3, d4, d5 );
	}

	// array( i1, s2, s3, s4, s5 )
	inline
	FArray4S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d2, d3, d4, d5 );
	}

	// array( s1, i2, s3, s4, s5 )
	inline
	FArray4S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d3, d4, d5 );
	}

	// array( s1, s2, i3, s4, s5 )
	inline
	FArray4S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d2, d4, d5 );
	}

	// array( s1, s2, s3, i4, s5 )
	inline
	FArray4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d2, d3, d5 );
	}

	// array( s1, s2, s3, s4, i5 )
	inline
	FArray4S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray4S< T >( data_, k, d1, d2, d3, d4 );
	}

	// array( i1, i2, s3, s4, s5 )
	inline
	FArray3S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d3, d4, d5 );
	}

	// array( i1, s2, i3, s4, s5 )
	inline
	FArray3S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d2, d4, d5 );
	}

	// array( i1, s2, s3, i4, s5 )
	inline
	FArray3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d2, d3, d5 );
	}

	// array( i1, s2, s3, s4, i5 )
	inline
	FArray3S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d2, d3, d4 );
	}

	// array( s1, i2, i3, s4, s5 )
	inline
	FArray3S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d4, d5 );
	}

	// array( s1, i2, s3, i4, s5 )
	inline
	FArray3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d3, d5 );
	}

	// array( s1, i2, s3, s4, i5 )
	inline
	FArray3S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d3, d4 );
	}

	// array( s1, s2, i3, i4, s5 )
	inline
	FArray3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d2, d5 );
	}

	// array( s1, s2, i3, s4, i5 )
	inline
	FArray3S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d2, d4 );
	}

	// array( s1, s2, s3, i4, i5 )
	inline
	FArray3S< T >
	operator ()( IS const & s1, IS const & s2, IS const & s3, int const i4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray3S< T >( data_, k, d1, d2, d3 );
	}

	// array( s1, s2, i3, i4, i5 )
	inline
	FArray2S< T >
	operator ()( IS const & s1, IS const & s2, int const i3, int const i4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d2 );
	}

	// array( s1, i2, s3, i4, i5 )
	inline
	FArray2S< T >
	operator ()( IS const & s1, int const i2, IS const & s3, int const i4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d3 );
	}

	// array( s1, i2, i3, s4, i5 )
	inline
	FArray2S< T >
	operator ()( IS const & s1, int const i2, int const i3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d4 );
	}

	// array( s1, i2, i3, i4, s5 )
	inline
	FArray2S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d1, d5 );
	}

	// array( i1, s2, s3, i4, i5 )
	inline
	FArray2S< T >
	operator ()( int const i1, IS const & s2, IS const & s3, int const i4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d2, d3 );
	}

	// array( i1, s2, i3, s4, i5 )
	inline
	FArray2S< T >
	operator ()( int const i1, IS const & s2, int const i3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d2, d4 );
	}

	// array( i1, s2, i3, i4, s5 )
	inline
	FArray2S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d2, d5 );
	}

	// array( i1, i2, s3, s4, i5 )
	inline
	FArray2S< T >
	operator ()( int const i1, int const i2, IS const & s3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray2S< T >( data_, k, d3, d4 );
	}

	// array( i1, i2, s3, i4, s5 )
	inline
	FArray2S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d3, d5 );
	}

	// array( i1, i2, i3, s4, s5 )
	inline
	FArray2S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray2S< T >( data_, k, d4, d5 );
	}

	// array( s1, i2, i3, i4, i5 )
	inline
	FArray1S< T >
	operator ()( IS const & s1, int const i2, int const i3, int const i4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		DS const d1( I1(), s1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d1 );
	}

	// array( i1, s2, i3, i4, i5 )
	inline
	FArray1S< T >
	operator ()( int const i1, IS const & s2, int const i3, int const i4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		DS const d2( I2(), s2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d2 );
	}

	// array( i1, i2, s3, i4, i5 )
	inline
	FArray1S< T >
	operator ()( int const i1, int const i2, IS const & s3, int const i4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		DS const d3( I3(), s3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d3 );
	}

	// array( i1, i2, i3, s4, i5 )
	inline
	FArray1S< T >
	operator ()( int const i1, int const i2, int const i3, IS const & s4, int const i5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		DS const d4( I4(), s4, z *= z3_ );
		k += slice_k( I5(), i5, z *= z4_ );
		return FArray1S< T >( data_, k, d4 );
	}

	// array( i1, i2, i3, i4, s5 )
	inline
	FArray1S< T >
	operator ()( int const i1, int const i2, int const i3, int const i4, IS const & s5 )
	{
		int k( -shift_ );
		size_type z( z1_ );
		k += slice_k( I1(), i1 );
		k += slice_k( I2(), i2, z );
		k += slice_k( I3(), i3, z *= z2_ );
		k += slice_k( I4(), i4, z *= z3_ );
		DS const d5( I5(), s5, z *= z4_ );
		return FArray1S< T >( data_, k, d5 );
	}

public: // Predicate

	// contains( i )
	inline
	bool
	contains( int const i1, int const i2, int const i3, int const i4, int const i5 ) const
	{
		return ( I1().contains( i1 ) && I2().contains( i2 ) && I3().contains( i3 ) && I4().contains( i4 ) && I5().contains( i5 ) );
	}

	// Conformable?
	template< typename U >
	inline
	bool
	conformable( FArray5< U > const & a ) const
	{
		return ( ( size1() == a.size1() ) && ( size2() == a.size2() ) && ( size3() == a.size3() ) && ( size4() == a.size4() ) && ( size5() == a.size5() ) );
	}

	// Conformable?
	template< typename U >
	inline
	bool
	conformable( FArray5S< U > const & a ) const
	{
		return ( ( size1() == a.size1() ) && ( size2() == a.size2() ) && ( size3() == a.size3() ) && ( size4() == a.size4() ) && ( size5() == a.size5() ) );
	}

	// Conformable?
	template< class A, typename M >
	inline
	bool
	conformable( MArray5< A, M > const & a ) const
	{
		return ( ( size1() == a.size1() ) && ( size2() == a.size2() ) && ( size3() == a.size3() ) && ( size4() == a.size4() ) && ( size5() == a.size5() ) );
	}

	// Equal Dimensions?
	template< typename U >
	inline
	bool
	equal_dimensions( FArray5< U > const & a ) const
	{
		return ( ( I1() == a.I1() ) && ( I2() == a.I2() ) && ( I3() == a.I3() ) && ( I4() == a.I4() ) && ( I5() == a.I5() ) );
	}

public: // Inspector

	// Rank
	inline
	int
	rank() const
	{
		return 5;
	}

	// IndexRange of a Dimension
	inline
	IR const &
	I( int const d ) const
	{
		switch ( d ) {
		case 1:
			return I1();
		case 2:
			return I2();
		case 3:
			return I3();
		case 4:
			return I4();
		case 5:
			return I5();
		default:
			assert( false );
			return I1();
		}
	}

	// Lower Index of a Dimension
	inline
	int
	l( int const d ) const
	{
		switch ( d ) {
		case 1:
			return l1();
		case 2:
			return l2();
		case 3:
			return l3();
		case 4:
			return l4();
		case 5:
			return l5();
		default:
			assert( false );
			return l1();
		}
	}

	// Upper Index of a Dimension
	inline
	int
	u( int const d ) const
	{
		switch ( d ) {
		case 1:
			return u1();
		case 2:
			return u2();
		case 3:
			return u3();
		case 4:
			return u4();
		case 5:
			return u5();
		default:
			assert( false );
			return u1();
		}
	}

	// Size of a Dimension
	inline
	size_type
	size( int const d ) const
	{
		switch ( d ) {
		case 1:
			return size1();
		case 2:
			return size2();
		case 3:
			return size3();
		case 4:
			return size4();
		case 5:
			return size5();
		default:
			assert( false );
			return size1();
		}
	}

	// Size of a Dimension
	inline
	int
	isize( int const d ) const
	{
		switch ( d ) {
		case 1:
			return isize1();
		case 2:
			return isize2();
		case 3:
			return isize3();
		case 4:
			return isize4();
		case 5:
			return isize5();
		default:
			assert( false );
			return isize1();
		}
	}

	// IndexRange of Dimension 1
	virtual
	IR const &
	I1() const = 0;

	// Lower Index of Dimension 1
	virtual
	int
	l1() const = 0;

	// Upper Index of Dimension 1
	virtual
	int
	u1() const = 0;

	// Size of Dimension 1
	inline
	size_type
	size1() const
	{
		return z1_;
	}

	// Size of Dimension 1
	inline
	int
	isize1() const
	{
		return static_cast< int >( z1_ );
	}

	// IndexRange of Dimension 2
	virtual
	IR const &
	I2() const = 0;

	// Lower Index of Dimension 2
	virtual
	int
	l2() const = 0;

	// Upper Index of Dimension 2
	virtual
	int
	u2() const = 0;

	// Size of Dimension 2
	inline
	size_type
	size2() const
	{
		return z2_;
	}

	// Size of Dimension 2
	inline
	int
	isize2() const
	{
		return static_cast< int >( z2_ );
	}

	// IndexRange of Dimension 3
	virtual
	IR const &
	I3() const = 0;

	// Lower Index of Dimension 3
	virtual
	int
	l3() const = 0;

	// Upper Index of Dimension 3
	virtual
	int
	u3() const = 0;

	// Size of Dimension 3
	inline
	size_type
	size3() const
	{
		return z3_;
	}

	// Size of Dimension 3
	inline
	int
	isize3() const
	{
		return static_cast< int >( z3_ );
	}

	// IndexRange of Dimension 4
	virtual
	IR const &
	I4() const = 0;

	// Lower Index of Dimension 4
	virtual
	int
	l4() const = 0;

	// Upper Index of Dimension 4
	virtual
	int
	u4() const = 0;

	// Size of Dimension 4
	inline
	size_type
	size4() const
	{
		return z4_;
	}

	// Size of Dimension 4
	inline
	int
	isize4() const
	{
		return static_cast< int >( z4_ );
	}

	// IndexRange of Dimension 5
	virtual
	IR const &
	I5() const = 0;

	// Lower Index of Dimension 5
	virtual
	int
	l5() const = 0;

	// Upper Index of Dimension 5
	virtual
	int
	u5() const = 0;

	// Size of Dimension 5
	virtual
	size_type
	size5() const = 0;

	// Size of Dimension 5
	virtual
	int
	isize5() const = 0;

public: // Modifier

	// Clear
	inline
	FArray5 &
	clear()
	{
		Super::clear();
		z1_ = z2_ = z3_ = z4_ = 0;
		return *this;
	}

	// Assign Default Value to all Elements
	inline
	FArray5 &
	to_default()
	{
		Super::to_default();
		return *this;
	}

public: // MArray Generators

	// Template Helpers
	template< typename U > class Wrapper {};
	typedef  typename std::conditional< std::is_class< T >::value, T, Wrapper< T > >::type  ClassT;

	// MArray Generator
	template< typename M >
	inline
	MArray5< FArray5 const, M >
	ma( M ClassT::* pmem ) const
	{
		return MArray5< FArray5 const, M >( *this, pmem );
	}

	// MArray Generator
	template< typename M >
	inline
	MArray5< FArray5, M >
	ma( M ClassT::* pmem )
	{
		return MArray5< FArray5, M >( *this, pmem );
	}

public: // Comparison: Predicate

	// FArray5 == FArray5
	inline
	friend
	bool
	eq( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return eq( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 != FArray5
	inline
	friend
	bool
	ne( FArray5 const & a, FArray5 const & b )
	{
		return ! eq( a, b );
	}

	// FArray5 < FArray5
	inline
	friend
	bool
	lt( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return lt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 <= FArray5
	inline
	friend
	bool
	le( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return le( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 > FArray5
	inline
	friend
	bool
	gt( FArray5 const & a, FArray5 const & b )
	{
		return lt( b, a );
	}

	// FArray5 >= FArray5
	inline
	friend
	bool
	ge( FArray5 const & a, FArray5 const & b )
	{
		return le( b, a );
	}

public: // Comparison: Predicate: Any

	// FArray5 == FArray5
	inline
	friend
	bool
	any_eq( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return any_eq( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 != FArray5
	inline
	friend
	bool
	any_ne( FArray5 const & a, FArray5 const & b )
	{
		return ! eq( a, b );
	}

	// FArray5 < FArray5
	inline
	friend
	bool
	any_lt( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return any_lt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 <= FArray5
	inline
	friend
	bool
	any_le( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return any_le( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 > FArray5
	inline
	friend
	bool
	any_gt( FArray5 const & a, FArray5 const & b )
	{
		return any_lt( b, a );
	}

	// FArray5 >= FArray5
	inline
	friend
	bool
	any_ge( FArray5 const & a, FArray5 const & b )
	{
		return any_le( b, a );
	}

public: // Comparison: Predicate: All

	// FArray5 == FArray5
	inline
	friend
	bool
	all_eq( FArray5 const & a, FArray5 const & b )
	{
		return eq( a, b );
	}

	// FArray5 != FArray5
	inline
	friend
	bool
	all_ne( FArray5 const & a, FArray5 const & b )
	{
		return ! any_eq( a, b );
	}

	// FArray5 < FArray5
	inline
	friend
	bool
	all_lt( FArray5 const & a, FArray5 const & b )
	{
		return lt( a, b );
	}

	// FArray5 <= FArray5
	inline
	friend
	bool
	all_le( FArray5 const & a, FArray5 const & b )
	{
		return le( a, b );
	}

	// FArray5 > FArray5
	inline
	friend
	bool
	all_gt( FArray5 const & a, FArray5 const & b )
	{
		return gt( a, b );
	}

	// FArray5 >= FArray5
	inline
	friend
	bool
	all_ge( FArray5 const & a, FArray5 const & b )
	{
		return ge( a, b );
	}

public: // Comparison: Count

	// FArray5 == FArray5
	inline
	friend
	bool
	count_eq( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_eq( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 != FArray5
	inline
	friend
	bool
	count_ne( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_ne( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 < FArray5
	inline
	friend
	bool
	count_lt( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_lt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 <= FArray5
	inline
	friend
	bool
	count_le( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_le( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 > FArray5
	inline
	friend
	bool
	count_gt( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_gt( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

	// FArray5 >= FArray5
	inline
	friend
	bool
	count_ge( FArray5 const & a, FArray5 const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		return count_ge( static_cast< Super const & >( a ), static_cast< Super const & >( b ) );
	}

public: // Comparison: Predicate: Slice

	// FArray5 == FArray5S
	inline
	friend
	bool
	eq( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] == b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 != FArray5S
	inline
	friend
	bool
	ne( FArray5 const & a, FArray5S< T > const & b )
	{
		return ! eq( a, b );
	}

	// FArray5 < FArray5S
	inline
	friend
	bool
	lt( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] < b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 <= FArray5S
	inline
	friend
	bool
	le( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] <= b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 > FArray5S
	inline
	friend
	bool
	gt( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] > b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 >= FArray5S
	inline
	friend
	bool
	ge( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] >= b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5S == FArray5
	inline
	friend
	bool
	eq( FArray5S< T > const & a, FArray5 const & b )
	{
		return eq( b, a );
	}

	// FArray5S != FArray5
	inline
	friend
	bool
	ne( FArray5S< T > const & a, FArray5 const & b )
	{
		return ne( b, a );
	}

	// FArray5S < FArray5
	inline
	friend
	bool
	lt( FArray5S< T > const & a, FArray5 const & b )
	{
		return gt( b, a );
	}

	// FArray5S <= FArray5
	inline
	friend
	bool
	le( FArray5S< T > const & a, FArray5 const & b )
	{
		return ge( b, a );
	}

	// FArray5S > FArray5
	inline
	friend
	bool
	gt( FArray5S< T > const & a, FArray5 const & b )
	{
		return lt( b, a );
	}

	// FArray5S >= FArray5
	inline
	friend
	bool
	ge( FArray5S< T > const & a, FArray5 const & b )
	{
		return le( b, a );
	}

public: // Comparison: Predicate: Any: Slice

	// Any FArray5 == FArray5S
	inline
	friend
	bool
	any_eq( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] == b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 != FArray5S
	inline
	friend
	bool
	any_ne( FArray5 const & a, FArray5S< T > const & b )
	{
		return ! eq( a, b );
	}

	// Any FArray5 < FArray5S
	inline
	friend
	bool
	any_lt( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] < b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 <= FArray5S
	inline
	friend
	bool
	any_le( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] <= b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 > FArray5S
	inline
	friend
	bool
	any_gt( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] > b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 >= FArray5S
	inline
	friend
	bool
	any_ge( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] >= b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5S == FArray5
	inline
	friend
	bool
	any_eq( FArray5S< T > const & a, FArray5 const & b )
	{
		return any_eq( b, a );
	}

	// Any FArray5S != FArray5
	inline
	friend
	bool
	any_ne( FArray5S< T > const & a, FArray5 const & b )
	{
		return any_ne( b, a );
	}

	// Any FArray5S < FArray5
	inline
	friend
	bool
	any_lt( FArray5S< T > const & a, FArray5 const & b )
	{
		return any_gt( b, a );
	}

	// Any FArray5S <= FArray5
	inline
	friend
	bool
	any_le( FArray5S< T > const & a, FArray5 const & b )
	{
		return any_ge( b, a );
	}

	// Any FArray5S > FArray5
	inline
	friend
	bool
	any_gt( FArray5S< T > const & a, FArray5 const & b )
	{
		return any_lt( b, a );
	}

	// Any FArray5S >= FArray5
	inline
	friend
	bool
	any_ge( FArray5S< T > const & a, FArray5 const & b )
	{
		return any_le( b, a );
	}

public: // Comparison: Predicate: All: Slice

	// All FArray5 == FArray5S
	inline
	friend
	bool
	all_eq( FArray5 const & a, FArray5S< T > const & b )
	{
		return eq( a, b );
	}

	// All FArray5 != FArray5S
	inline
	friend
	bool
	all_ne( FArray5 const & a, FArray5S< T > const & b )
	{
		return ! any_eq( a, b );
	}

	// All FArray5 < FArray5S
	inline
	friend
	bool
	all_lt( FArray5 const & a, FArray5S< T > const & b )
	{
		return lt( a, b );
	}

	// All FArray5 <= FArray5S
	inline
	friend
	bool
	all_le( FArray5 const & a, FArray5S< T > const & b )
	{
		return le( a, b );
	}

	// All FArray5 > FArray5S
	inline
	friend
	bool
	all_gt( FArray5 const & a, FArray5S< T > const & b )
	{
		return gt( a, b );
	}

	// All FArray5 >= FArray5S
	inline
	friend
	bool
	all_ge( FArray5 const & a, FArray5S< T > const & b )
	{
		return ge( a, b );
	}

	// All FArray5S == FArray5
	inline
	friend
	bool
	all_eq( FArray5S< T > const & a, FArray5 const & b )
	{
		return all_eq( b, a );
	}

	// All FArray5S != FArray5
	inline
	friend
	bool
	all_ne( FArray5S< T > const & a, FArray5 const & b )
	{
		return all_ne( b, a );
	}

	// All FArray5S < FArray5
	inline
	friend
	bool
	all_lt( FArray5S< T > const & a, FArray5 const & b )
	{
		return all_gt( b, a );
	}

	// All FArray5S <= FArray5
	inline
	friend
	bool
	all_le( FArray5S< T > const & a, FArray5 const & b )
	{
		return all_ge( b, a );
	}

	// All FArray5S > FArray5
	inline
	friend
	bool
	all_gt( FArray5S< T > const & a, FArray5 const & b )
	{
		return all_lt( b, a );
	}

	// All FArray5S >= FArray5
	inline
	friend
	bool
	all_ge( FArray5S< T > const & a, FArray5 const & b )
	{
		return all_le( b, a );
	}

public: // Comparison: Count: Slice

	// Count FArray5 == FArray5S
	inline
	friend
	size_type
	count_eq( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] == b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 != FArray5S
	inline
	friend
	size_type
	count_ne( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] != b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 < FArray5S
	inline
	friend
	size_type
	count_lt( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] < b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 <= FArray5S
	inline
	friend
	size_type
	count_le( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] <= b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 > FArray5S
	inline
	friend
	size_type
	count_gt( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] > b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 >= FArray5S
	inline
	friend
	size_type
	count_ge( FArray5 const & a, FArray5S< T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] >= b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5S == FArray5
	inline
	friend
	size_type
	count_eq( FArray5S< T > const & a, FArray5 const & b )
	{
		return count_eq( b, a );
	}

	// Count FArray5S != FArray5
	inline
	friend
	size_type
	count_ne( FArray5S< T > const & a, FArray5 const & b )
	{
		return count_ne( b, a );
	}

	// Count FArray5S < FArray5
	inline
	friend
	size_type
	count_lt( FArray5S< T > const & a, FArray5 const & b )
	{
		return count_gt( b, a );
	}

	// Count FArray5S <= FArray5
	inline
	friend
	size_type
	count_le( FArray5S< T > const & a, FArray5 const & b )
	{
		return count_ge( b, a );
	}

	// Count FArray5S > FArray5
	inline
	friend
	size_type
	count_gt( FArray5S< T > const & a, FArray5 const & b )
	{
		return count_lt( b, a );
	}

	// Count FArray5S >= FArray5
	inline
	friend
	size_type
	count_ge( FArray5S< T > const & a, FArray5 const & b )
	{
		return count_le( b, a );
	}

public: // Comparison: Predicate: MArray

	// FArray5 == MArray5
	template< class A >
	inline
	friend
	bool
	eq( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] == b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 != MArray5
	template< class A >
	inline
	friend
	bool
	ne( FArray5 const & a, MArray5< A, T > const & b )
	{
		return ! eq( a, b );
	}

	// FArray5 < MArray5
	template< class A >
	inline
	friend
	bool
	lt( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] < b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 <= MArray5
	template< class A >
	inline
	friend
	bool
	le( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] <= b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 > MArray5
	template< class A >
	inline
	friend
	bool
	gt( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] > b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// FArray5 >= MArray5
	template< class A >
	inline
	friend
	bool
	ge( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return true;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( ! ( a[ l ] >= b( i1, i2, i3, i4, i5 ) ) ) return false;
						}
					}
				}
			}
		}
		return true;
	}

	// MArray5 == FArray5
	template< class A >
	inline
	friend
	bool
	eq( MArray5< A, T > const & a, FArray5 const & b )
	{
		return eq( b, a );
	}

	// MArray5 != FArray5
	template< class A >
	inline
	friend
	bool
	ne( MArray5< A, T > const & a, FArray5 const & b )
	{
		return ne( b, a );
	}

	// MArray5 < FArray5
	template< class A >
	inline
	friend
	bool
	lt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return gt( b, a );
	}

	// MArray5 <= FArray5
	template< class A >
	inline
	friend
	bool
	le( MArray5< A, T > const & a, FArray5 const & b )
	{
		return ge( b, a );
	}

	// MArray5 > FArray5
	template< class A >
	inline
	friend
	bool
	gt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return lt( b, a );
	}

	// MArray5 >= FArray5
	template< class A >
	inline
	friend
	bool
	ge( MArray5< A, T > const & a, FArray5 const & b )
	{
		return le( b, a );
	}

public: // Comparison: Predicate: Any: MArray

	// Any FArray5 == MArray5
	template< class A >
	inline
	friend
	bool
	any_eq( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] == b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 != MArray5
	template< class A >
	inline
	friend
	bool
	any_ne( FArray5 const & a, MArray5< A, T > const & b )
	{
		return ! eq( a, b );
	}

	// Any FArray5 < MArray5
	template< class A >
	inline
	friend
	bool
	any_lt( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] < b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 <= MArray5
	template< class A >
	inline
	friend
	bool
	any_le( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] <= b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 > MArray5
	template< class A >
	inline
	friend
	bool
	any_gt( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] > b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any FArray5 >= MArray5
	template< class A >
	inline
	friend
	bool
	any_ge( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return false;
		size_type l( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] >= b( i1, i2, i3, i4, i5 ) ) return true;
						}
					}
				}
			}
		}
		return false;
	}

	// Any MArray5 == FArray5
	template< class A >
	inline
	friend
	bool
	any_eq( MArray5< A, T > const & a, FArray5 const & b )
	{
		return any_eq( b, a );
	}

	// Any MArray5 != FArray5
	template< class A >
	inline
	friend
	bool
	any_ne( MArray5< A, T > const & a, FArray5 const & b )
	{
		return any_ne( b, a );
	}

	// Any MArray5 < FArray5
	template< class A >
	inline
	friend
	bool
	any_lt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return any_gt( b, a );
	}

	// Any MArray5 <= FArray5
	template< class A >
	inline
	friend
	bool
	any_le( MArray5< A, T > const & a, FArray5 const & b )
	{
		return any_ge( b, a );
	}

	// Any MArray5 > FArray5
	template< class A >
	inline
	friend
	bool
	any_gt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return any_lt( b, a );
	}

	// Any MArray5 >= FArray5
	template< class A >
	inline
	friend
	bool
	any_ge( MArray5< A, T > const & a, FArray5 const & b )
	{
		return any_le( b, a );
	}

public: // Comparison: Predicate: All: MArray

	// All FArray5 == MArray5
	template< class A >
	inline
	friend
	bool
	all_eq( FArray5 const & a, MArray5< A, T > const & b )
	{
		return eq( a, b );
	}

	// All FArray5 != MArray5
	template< class A >
	inline
	friend
	bool
	all_ne( FArray5 const & a, MArray5< A, T > const & b )
	{
		return ! any_eq( a, b );
	}

	// All FArray5 < MArray5
	template< class A >
	inline
	friend
	bool
	all_lt( FArray5 const & a, MArray5< A, T > const & b )
	{
		return lt( a, b );
	}

	// All FArray5 <= MArray5
	template< class A >
	inline
	friend
	bool
	all_le( FArray5 const & a, MArray5< A, T > const & b )
	{
		return le( a, b );
	}

	// All FArray5 > MArray5
	template< class A >
	inline
	friend
	bool
	all_gt( FArray5 const & a, MArray5< A, T > const & b )
	{
		return gt( a, b );
	}

	// All FArray5 >= MArray5
	template< class A >
	inline
	friend
	bool
	all_ge( FArray5 const & a, MArray5< A, T > const & b )
	{
		return ge( a, b );
	}

	// All MArray5 == FArray5
	template< class A >
	inline
	friend
	bool
	all_eq( MArray5< A, T > const & a, FArray5 const & b )
	{
		return all_eq( b, a );
	}

	// All MArray5 != FArray5
	template< class A >
	inline
	friend
	bool
	all_ne( MArray5< A, T > const & a, FArray5 const & b )
	{
		return all_ne( b, a );
	}

	// All MArray5 < FArray5
	template< class A >
	inline
	friend
	bool
	all_lt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return all_gt( b, a );
	}

	// All MArray5 <= FArray5
	template< class A >
	inline
	friend
	bool
	all_le( MArray5< A, T > const & a, FArray5 const & b )
	{
		return all_ge( b, a );
	}

	// All MArray5 > FArray5
	template< class A >
	inline
	friend
	bool
	all_gt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return all_lt( b, a );
	}

	// All MArray5 >= FArray5
	template< class A >
	inline
	friend
	bool
	all_ge( MArray5< A, T > const & a, FArray5 const & b )
	{
		return all_le( b, a );
	}

public: // Comparison: Count: MArray

	// Count FArray5 == MArray5
	template< class A >
	inline
	friend
	size_type
	count_eq( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] == b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 != MArray5
	template< class A >
	inline
	friend
	size_type
	count_ne( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] != b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 < MArray5
	template< class A >
	inline
	friend
	size_type
	count_lt( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] < b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 <= MArray5
	template< class A >
	inline
	friend
	size_type
	count_le( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] <= b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 > MArray5
	template< class A >
	inline
	friend
	size_type
	count_gt( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] > b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count FArray5 >= MArray5
	template< class A >
	inline
	friend
	size_type
	count_ge( FArray5 const & a, MArray5< A, T > const & b )
	{
		assert( a.size_bounded() );
		assert( a.conformable( b ) );
		if ( a.empty() ) return 0;
		size_type l( 0 ), n( 0 );
		for ( int i5 = 1, e5 = b.u5(); i5 <= e5; ++i5 ) {
			for ( int i4 = 1, e4 = b.u4(); i4 <= e4; ++i4 ) {
				for ( int i3 = 1, e3 = b.u3(); i3 <= e3; ++i3 ) {
					for ( int i2 = 1, e2 = b.u2(); i2 <= e2; ++i2 ) {
						for ( int i1 = 1, e1 = b.u1(); i1 <= e1; ++i1, ++l ) {
							if ( a[ l ] >= b( i1, i2, i3, i4, i5 ) ) ++n;
						}
					}
				}
			}
		}
		return n;
	}

	// Count MArray5 == FArray5
	template< class A >
	inline
	friend
	size_type
	count_eq( MArray5< A, T > const & a, FArray5 const & b )
	{
		return count_eq( b, a );
	}

	// Count MArray5 != FArray5
	template< class A >
	inline
	friend
	size_type
	count_ne( MArray5< A, T > const & a, FArray5 const & b )
	{
		return count_ne( b, a );
	}

	// Count MArray5 < FArray5
	template< class A >
	inline
	friend
	size_type
	count_lt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return count_gt( b, a );
	}

	// Count MArray5 <= FArray5
	template< class A >
	inline
	friend
	size_type
	count_le( MArray5< A, T > const & a, FArray5 const & b )
	{
		return count_ge( b, a );
	}

	// Count MArray5 > FArray5
	template< class A >
	inline
	friend
	size_type
	count_gt( MArray5< A, T > const & a, FArray5 const & b )
	{
		return count_lt( b, a );
	}

	// Count MArray5 >= FArray5
	template< class A >
	inline
	friend
	size_type
	count_ge( MArray5< A, T > const & a, FArray5 const & b )
	{
		return count_le( b, a );
	}

protected: // Functions

	// Dimension by IndexRange
	virtual
	void
	dimension_assign( IR const & I1, IR const & I2, IR const & I3, IR const & I4, IR const & I5 ) = 0;

	// Swap
	inline
	void
	swap5DB( FArray5 & v )
	{
		swapB( v );
		std::swap( z1_, v.z1_ );
		std::swap( z2_, v.z2_ );
		std::swap( z3_, v.z3_ );
		std::swap( z4_, v.z4_ );
	}

protected: // Data

	size_type z1_; // Size of dim 1
	size_type z2_; // Size of dim 2
	size_type z3_; // Size of dim 3
	size_type z4_; // Size of dim 4

}; // FArray5

// Conformable?
template< typename U, typename V >
inline
bool
conformable( FArray5< U > const & a, FArray5< V > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< typename U, typename V >
inline
bool
conformable( FArray5< U > const & a, FArray5S< V > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< typename U, typename V >
inline
bool
conformable( FArray5S< U > const & a, FArray5< V > const & b )
{
	return b.conformable( a );
}

// Conformable?
template< typename U, class A, typename M >
inline
bool
conformable( FArray5< U > const & a, MArray5< A, M > const & b )
{
	return a.conformable( b );
}

// Conformable?
template< class A, typename M, typename V >
inline
bool
conformable( MArray5< A, M > const & a, FArray5< V > const & b )
{
	return b.conformable( a );
}

// Equal Dimensions?
template< typename U, typename V >
inline
bool
equal_dimensions( FArray5< U > const & a, FArray5< V > const & b )
{
	return a.equal_dimensions( b );
}

} // ObjexxFCL

#endif // ObjexxFCL_FArray5_hh_INCLUDED
