///********************************************************************
//	CopyRight 2016 @Ally Dale. All rights reserved.
//	created:	2016/10/19
//	created:	19:10:2016   15:41
//	filename: 	deque.hpp
//	author:		Ally Dale(vipally@gmail.com)
//	Blog   :    http://blog.csdn.net/vipally
//	Site   :    https://github.com/vipally
//	
//	purpose:	Cycle buffered deque implementation based on STL
//*********************************************************************/
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
		rebind<_Ty>::other _Alty;

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
		: _Myhead(0), _Mytail(0), _Mylast(0), _Myfirst(0)
	{
		_Buy(8);//initialze 8 space
	}
	~deque(){
		_Tidy();
	}

	bool empty() const{
		return _Myhead == _Mytail;
	}

	size_type capacity() const{
		return _Mylast - _Myfirst;
	}

	size_type size() const{
		if (_Mytail >= _Myhead){
			return (size_type)(_Mytail - _Myhead);
		} else{
			return capacity() - (size_type)(_Myhead - _Mytail);
		}
	}

	reference front(){
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((reference)*(_Myhead));
	}

	const_reference front() const{
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((const_reference)*(_Myhead));
	}

	reference back(){
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((reference)*(_Prev(_Mytail)));
	}

	const_reference back() const{
		if (empty()){
			_DEBUG_ERROR("empty deque not dereferencable");
			_SCL_SECURE_TRAITS_OUT_OF_RANGE;
		}
		return ((const_reference)*(_Prev(_Mytail)));
	}
	
	void push_front(const value_type &_Val){
		_Myhead = _Prev(_Myhead);
		_STDEXT unchecked_uninitialized_fill_n(_Myhead, 1, _Val, this->_Alval);
		if (_Myhead == _Mytail){//buffer full
			_Buy(2*capacity());
		}

	}

	void push_back(const value_type &_Val){
		_STDEXT unchecked_uninitialized_fill_n(_Mytail, 1, _Val, this->_Alval);
		_Mytail = _Next(_Mytail);
		if (_Myhead == _Mytail){//buffer full
			_Buy(2*capacity());
		}
	}

	bool pop_front(){
		if (empty()){
			return false;
		}
		_Destroy(_Myhead);
		_Myhead=_Next(_Myhead);
		
		return true;
	}

	bool pop_back(){
		if (empty()){
			return false;
		}
		_Mytail = _Prev(_Mytail);
		_Destroy(_Mytail);
		return true;
	}

	bool shrink(){
		size_type oldCap = capacity();
		size_type oldSize = size();
		if (oldCap > 8 && oldCap >= 3*oldSize){
			_Buy(oldCap/2);
			return true;
		}
		return false;
	}

protected:
	void _Destroy(pointer p)
	{	// destroy [_First, _Last) using allocator
		std::_Destroy_range(p, p+1, this->_Alval);
	}
	void _Tidy(){
		if (_Myfirst != 0){
			if (_Myhead != _Mytail)
			{
				if (_Mytail >= _Myhead)
				{
					std::_Destroy_range(_Myhead, _Mytail, this->_Alval);
				}else{
					std::_Destroy_range(_Myhead, _Mylast, this->_Alval);
					std::_Destroy_range(_Myfirst, _Mytail, this->_Alval);
				}
			}
			this->_Alval.deallocate(_Myfirst, capacity());
		}
		_Myfirst = 0;
		_Mylast = 0;
		_Myhead = 0;
		_Mytail = 0;
	}
	void _Buy(size_type cap){
		if (cap <= size()){
			//assert(0);
			//_DEBUG_ERROR("deque new cap <= size");
			return;
		}
		pointer old = _Myfirst;
		size_type oldCap = capacity();
		_Myfirst = this->_Alval.allocate(cap);
		if (_Myhead <= _Mytail){
			_STDEXT _Unchecked_uninitialized_move(_Myhead, _Mytail, _Myfirst, this->_Alval);
			_Mytail = _Myfirst + (_Mytail - _Myhead);
			_Myhead = _Myfirst;
		} else {
			size_type oldSize = size();
			size_type oldCap = capacity();

			_STDEXT _Unchecked_uninitialized_move(_Myhead, _Mylast, _Myfirst, this->_Alval);
			_STDEXT _Unchecked_uninitialized_move(old, _Mytail, _Myfirst + (_Mylast-_Myhead), this->_Alval);
			_Myhead = _Myfirst;
			_Mytail = _Myfirst + oldCap;
		}
		if (old!=0){
			this->_Alval.deallocate(old, oldCap);
		}
		_Mylast = _Myfirst + cap;
	}

	pointer _Next(pointer d) const{
		if (++d >= _Mylast){
			d = _Myfirst;
		}
		return d;
	}
	pointer _Prev(pointer d) const{
		if (--d < _Myfirst){
			d = _Mylast - 1;
		}
		return d;
	}

private:
	// pointer to range of storage array.
	//full storage is [_Myfirst, _Mylast)
	//buffer is cycle, that is to say, next(_Mylast-1)=_Myfirst, prev(_Myfirst)=_Mylast-1
	pointer _Myfirst, _Mylast;

	//head and tail of deque
	//real data is [_Myhead,_Mytail)
	//so if tail<head, data is [_Myhead, _Mylast-1, _Myfirst, _Mytail)
	//head points to the first elem  available for read
	//tail points to the first space available for write
	pointer _Myhead, _Mytail;
};//deque

}//namespace ext{
#endif /* _EXT_DEQUE_ */
