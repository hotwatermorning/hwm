// Pointer to make deep-copy
// 参考: http://zakio.net/blog/2009/04/15-222117.html

#ifndef HWM_DEEPCOPYPTR_HPP
#define HWM_DEEPCOPYPTR_HPP

#include <memory>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>

namespace hwm {

namespace detail {

class deep_copy_ptr_holder_base
	:	boost::noncopyable
{
public:
	virtual ~deep_copy_ptr_holder_base	() {}
	virtual std::auto_ptr<deep_copy_ptr_holder_base>
						clone			() const = 0;
	virtual void*		get_ptr			() = 0;
	virtual const void* get_ptr			() const = 0;
};

template <class T>
class deep_copy_ptr_holder
	:	public deep_copy_ptr_holder_base
{
	typedef deep_copy_ptr_holder 		this_type;
	typedef deep_copy_ptr_holder_base	base_type;
	
	std::auto_ptr<T> ptr_;				//pointer used by deep_copy_ptr

public:
	explicit this_type	(T* ptr) : ptr_(ptr) {}
	explicit this_type	(std::auto_ptr<T> p) : ptr_(p) {}

	std::auto_ptr<T>	clone_detail() const	{
		return
			(ptr_.get())
			?	std::auto_ptr<T>( new T(*ptr_) )
			:	std::auto_ptr<T>();
	}
	
	virtual std::auto_ptr<base_type>
						clone		() const	{ return std::auto_ptr<base_type>(new this_type(clone_detail())); }

	virtual void*		get_ptr		()			{ return ptr_.get(); }
	virtual const void* get_ptr		() const	{ return ptr_.get(); }
};

}	//namespace detail

// Pimpl クラスの実体
template <class T>
class deep_copy_ptr
{
private:
	typedef void (deep_copy_ptr::*bool_type)() const;
	void 		bool_func		() const {}
	
	std::auto_ptr<detail::deep_copy_ptr_holder_base> holder_;
public:
	deep_copy_ptr				() : holder_(new detail::deep_copy_ptr_holder<T>(0)) {}
	template<typename Y>
	explicit 	deep_copy_ptr	(Y* p) : holder_(new detail::deep_copy_ptr_holder<T>(std::auto_ptr<T>(p)))	{}
	template<typename Y>
	explicit 	deep_copy_ptr	(std::auto_ptr<Y> p) : holder_(new detail::deep_copy_ptr_holder<T>(p))		{}

	deep_copy_ptr				(const deep_copy_ptr& rhs) : holder_(rhs.holder_->clone()) {}

	template<typename Y>
	explicit	 deep_copy_ptr	(const deep_copy_ptr<Y>& rhs) : holder_(rhs.holder_->clone()) {}

	deep_copy_ptr &	operator = 	(const deep_copy_ptr& rhs) {
		BOOST_ASSERT(rhs.holder_.get());
		deep_copy_ptr<T> tmp(rhs);
		this->swap(tmp);
		return *this;
	}

	void		swap			(deep_copy_ptr &rhs) {
		std::swap(holder_, rhs.holder_);
	}

	operator	bool_type		() const {
		BOOST_ASSERT(holder_.get());
		return (holder_->get_ptr()) ? &deep_copy_ptr::bool_func : 0;
	}

	template<typename Y>
	void		reset			(Y* p = 0) {
		deep_copy_ptr tmp(p);
		swap(tmp);
	}

	T *			get				()			{ return static_cast<T *>(holder_->get_ptr()); }
	T	const *	get				() const	{ return static_cast<T const*>(holder_->get_ptr()); }
	T *			operator ->		()			{ return get(); }
	T	const *	operator ->		() const	{ return get(); }

	T &			operator *		()			{
		BOOST_ASSERT(get());
		return *get();
	}

	T	const &	operator *		() const	{
		BOOST_ASSERT(get());
		return *get();
	}
};

template<typename T>
void swap(deep_copy_ptr<T> &lhs, deep_copy_ptr<T> &rhs)
{
	lhs.swap(rhs);
}

}	//hwm

#endif	//HWM_DEEPCOPYPTR_HPP
