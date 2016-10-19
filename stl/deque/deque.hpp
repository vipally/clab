/********************************************************************
	created:	2016/10/19
	created:	19:10:2016   15:41
	filename: 	deque.hpp
	file base:	deque
	file ext:	hpp
	author:		Ally(vipally@gmail.com)
	
	purpose:	Cycle buffered deque implementation
*********************************************************************/
#ifndef _EXT_DEQUE_
#define _EXT_DEQUE_
#include <memory>
#include <stdexcept>

#ifdef _MSC_VER
#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma warning(disable: 4244)
#endif  /* _MSC_VER */

namespace ext{

//// TEMPLATE CLASS deque
//template<class _Ty,	class _Ax = allocator<_Ty> >
//class deque;
//
//template<class _Ty, class _Alloc>
//class _Deque_const_iterator
//:public _Ranit<_Ty, typename _Alloc::difference_type,
//	typename _Alloc::const_pointer, typename _Alloc::const_reference>
//{
//protected:
//	typedef deque<_Ty, _Alloc>						_Mycont;
//	typedef _Deque_const_iterator<_Ty, _Alloc>		_Myt;
//	typedef std::vector<_Ty, _Ax>::const_iterator	_MyBase;
//public:
//	typedef random_access_iterator_tag iterator_category;
//	typedef _Ty value_type;
//	typedef typename _MyBase::difference_type difference_type;
//	typedef typename _MyBase::pointer pointer;
//	typedef typename _MyBase::reference reference;
//public:
//
//};
//
//// TEMPLATE CLASS _Vector_val
//template<class _Ty,class _Alloc>
//class _Deque_val
//	: public _CONTAINER_BASE_AUX_ALLOC<_Alloc>
//{	// base class for vector to hold allocator _Alval
//protected:
//	_Deque_val(_Alloc _Al = _Alloc())
//		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Al), _Alval(_Al)
//	{	// construct allocator from _Al
//	}
//
//	typedef typename _Alloc::template
//		std::rebind<_Ty>::other _Alty;
//
//	_Alty _Alval;	// allocator object for values
//};
//
//// TEMPLATE CLASS _Deque_iterator
//template<class _Ty, class _Alloc>
//class _Deque_iterator
//	: public _Deque_const_iterator<_Ty, _Alloc>
//{	// iterator for mutable vector
//protected:
//	typedef deque<_Ty, _Alloc>					_Mycont;
//	typedef _Deque_iterator<_Ty, _Alloc>		_Myt;
//	typedef _Deque_const_iterator<_Ty, _Alloc>	_MyBase;
//public:
//	typedef random_access_iterator_tag iterator_category;
//	typedef _Ty value_type;
//	typedef typename _MyBase::difference_type difference_type;
//	typedef typename _MyBase::pointer pointer;
//	typedef typename _Alloc::reference reference;
//public:
//};

// TEMPLATE CLASS _Deque_val
template<class _Ty, class _Alloc>
class _Deque_val
	: public std::_CONTAINER_BASE_AUX_ALLOC<_Alloc>
{	// base class for vector to hold allocator _Alval
protected:
	_Deque_val(_Alloc _Al = _Alloc())
		: _CONTAINER_BASE_AUX_ALLOC<_Alloc>(_Al), _Alval(_Al)
	{	// construct allocator from _Al
	}

	typedef typename _Alloc::template
		std::rebind<_Ty>::other _Alty;

	_Alty _Alval;	// allocator object for values
};

template<class _Ty,class _Ax = std::allocator<_Ty> >
class deque
	: public _Deque_val<_Ty, _Ax>
{
protected:
	typedef _Ax					_Alloc;
	typedef deque<_Ty, _Alloc>	_Myt;
public:
	typedef typename _Alloc::difference_type difference_type;
	typedef _Alloc allocator_type;
	typedef typename _Alloc::size_type size_type;
	typedef typename _Alloc::pointer pointer;
	typedef typename _Alloc::const_pointer const_pointer;
	typedef typename _Alloc::reference reference;
	typedef typename _Alloc::const_reference const_reference;
	typedef typename _Alloc::value_type value_type;
	//typedef _Deque_iterator<_Ty, _Alloc> iterator;
	//typedef _Deque_const_iterator<_Ty, _Alloc> const_iterator;
	//	friend class _Deque_iterator<_Ty, _Alloc>;
	//friend class _Deque_const_iterator<_Ty, _Alloc>;
	//typedef std::reverse_iterator<iterator> reverse_iterator;
	//typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
public:
	deque()
		: _Myhead(0), _Mytail(0), _Mycap(0), _Myfirst(0)
	{}
	~deque(){
		_Tidy();
	}

	bool empty() const{
		return _Myhead ==_Mytail
	}

	size_type capacity() const{
		return _Mycap;
	}

	size_type size() const{
		if (_Mytail >= _Myhead){
			return (size_type)(_Mytail - _Myhead);
		} else{
			return _Mycap + (size_type)(_Myhead - _Mytail);
		}
	}

	reference front(){
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((reference)*(_Myfirst+_Myhead));
	}

	const_reference front() const{
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((const_reference)*(_Myfirst+_Myhead));
	}

	reference back(){
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((reference)*(_Myfirst+_Prev(_Mytail)));
	}

	const_reference back() const{
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((const_reference)*(_Myfirst+_Prev(_Mytail)));
	}
	
	void push_front(const value_type &_Val){
		_Myhead = _Prev(_Myhead);
		_STDEXT stdeunchecked_uninitialized_fill_n(_Myfirst+_Myhead, 1, _Val, this->_Alval);
		if (_Myhead = _Mytail){//buffer full
		}

	}

	void push_back(const value_type &_Val){
		_STDEXT stdeunchecked_uninitialized_fill_n(_Myfirst+_Mytail, 1, _Val, this->_Alval);
		_Mytail = _Next(_Mytail);
		if (_Myhead = _Mytail){//buffer full
		}
	}

	bool pop_front(const value_type &v){
		if (empty()){
			return false;
		}
		_Destroy(_Myhead);
		_Myhead++;
		if (_Myhead >= _Mycap)
		{
			_Myhead = 0;
		}
		
		return true;
	}

	bool pop_back(const value_type &v){
		if (empty()){
			return false;
		}
		_Mytail--;
		if (_Mytail < 0)
		{
			_Mytail = _Mycap - 1;
		}
		_Destroy(_Mytail);
		return true;
	}

	bool shrink(){
	}

protected:
	void _Destroy(difference_type idx)
	{	// destroy [_First, _Last) using allocator
		std::_Destroy_range(_Myfirst+idx, _Myfirst+idx+1, this->_Alval);
	}
	void _Tidy(){
		if (_Myfirst != 0){
			if (_Myhead != _Mytail)
			{
				if (_Mytail >= _Myhead)
				{
					std::_Destroy_range(_Myfirst+_Myhead, _Myfirst+_Mytail, this->_Alval);
				}else{
					std::_Destroy_range(_Myfirst+_Myhead, _Myfirst+_Mycap, this->_Alval);
					std::_Destroy_range(_Myfirst, _Myfirst+_Mytail, this->_Alval);
				}
			}
			this->_Alval.deallocate(_Myfirst, _Mycap);
		}
		_Myfirst = 0;
		_Mycap = 0;
		_Myhead = 0;
		_Mytail = 0;
	}
	difference_type _Next(difference_type d) const{
		if (++d >= _Mycap){
			d = 0;
		}
		return d;
	}
	difference_type _Prev(difference_type d) const{
		if (--d < 0){
			d = _Mycap - 1;
		}
		return d;
	}
private:
	pointer _Myfirst;	// pointer to beginning of array
	size_type _Mycap;	// pointer to current end of sequence
	difference_type _Myhead, _Mytail;//head and tail of deque
};//deque

}//namespace ext{
#endif /* _EXT_DEQUE_ */
