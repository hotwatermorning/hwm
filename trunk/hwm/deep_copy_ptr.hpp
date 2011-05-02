//          Copyright hotwatermorning 2011.
//  Distributed under the Boost Software License, Version 1.0.
//      (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//! Deep copyable, deep comparable pointer.

//! based on http://zakio.net/blog/2009/04/15-222117.html

//! @file

#ifndef HWM_DEEPCOPYPTR_HPP
#define HWM_DEEPCOPYPTR_HPP

#include <memory>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/operators.hpp>

#include "safe_bool.hpp"

namespace hwm {

//undocumented.
//! @cond NOT_GENERATED
namespace detail {

class deep_copy_ptr_holder_base
    :   boost::noncopyable
{
public:
    virtual ~deep_copy_ptr_holder_base      () {}
    virtual std::auto_ptr<deep_copy_ptr_holder_base>
                            clone           () const = 0;
    virtual void *          get_ptr         () = 0;
    virtual const void *    get_ptr         () const = 0;
};

template <class T, class Y = T>
class deep_copy_ptr_holder
    :   public deep_copy_ptr_holder_base
{
    typedef deep_copy_ptr_holder<T, Y>  this_type;
    typedef deep_copy_ptr_holder_base   base_type;
    
    std::auto_ptr<T> ptr_;              //pointer used by deep_copy_ptr

public:
    explicit deep_copy_ptr_holder   (Y  *ptr) : ptr_(ptr) {}
    explicit deep_copy_ptr_holder   (std::auto_ptr<Y> p) : ptr_(p) {}

    std::auto_ptr<Y>    clone_detail() const    {
        return
            (ptr_.get())
            ?   std::auto_ptr<Y>( new Y(static_cast<Y const &>(*ptr_.get())) )
            :   std::auto_ptr<Y>();
    }
    
    virtual std::auto_ptr<base_type>
                        clone       () const    { return std::auto_ptr<base_type>(new this_type(clone_detail())); }

    virtual void*       get_ptr     ()          { return ptr_.get(); }
    virtual const void* get_ptr     () const    { return ptr_.get(); }
};

}   //namespace detail
//! @endcond

//! A deep copy pointer
//! @tparam T is pointer_type of deep_copy_pointer<T>.
//! pointer that deep_copy_pointer<T> having evaluated T when pointer used, but when pointer will be copied, copied as a type that deep_copy_ptr had received(typename Y).
template <class T>
class deep_copy_ptr
    :   public safe_bool< deep_copy_ptr<T> >
    ,   public boost::equality_comparable< deep_copy_ptr<T> >
{
public:
    //! @brief Default constructor
    deep_copy_ptr               () : holder_(new detail::deep_copy_ptr_holder<T>(0)) {}

    //! @brief Construct from raw pointer.
    //! @tparam Y must be comparable to T.
    template<typename Y>
    explicit    deep_copy_ptr   (Y *p) : holder_(new detail::deep_copy_ptr_holder<T, Y>(std::auto_ptr<Y>(p)))   {}

    //! @brief Construct from auto_ptr.
    //! @tparam Y must be comparable to T.
    template<typename Y>
    explicit    deep_copy_ptr   (std::auto_ptr<Y> p) : holder_(new detail::deep_copy_ptr_holder<T, Y>(p))       {}

    //! @brief Copy constructor
    deep_copy_ptr               (this_type const &rhs) : holder_(rhs.holder_->clone()) {}

    //! @brief Construct from deep_copy_ptr.
    //! @tparam Y must be comparable to T.
    //! @note Not a copy constructor.
    template<typename Y>
    explicit     deep_copy_ptr  (deep_copy_ptr<Y> const &rhs) : holder_(rhs.holder_->clone()) {}

    //! @brief Assignment operator
    //! Exception guarantee : strong
    this_type & operator =  (this_type const &rhs) {
        BOOST_ASSERT(rhs.holder_.get());
        deep_copy_ptr<T>(rhs).swap(*this);
        return *this;
    }

    //! @brief Exception guarantee : no-throw
    void        swap            (this_type &rhs) throw()
    {
        std::swap(holder_, rhs.holder_);
    }

    //! @brief Evaluable in boolean context.
    bool        boolean_test    () const {
        return holder_->get_ptr() != 0;
    }

    //! @brief Reset pointer
    //! Exception guarantee : strong
    template<typename Y>
    void        reset           (Y* p = 0) {
        deep_copy_ptr(p).swap(*this);
    }

    //! @brief Get a pointer.
    T *         get             ()          { return static_cast<T *>(holder_->get_ptr()); }
    //! @brief Get a pointer.
    T   const * get             () const    { return static_cast<T const*>(holder_->get_ptr()); }
    //! @brief Get member.
    T *         operator ->     ()          { return get(); }
    //! @brief Get member.
    T   const * operator ->     () const    { return get(); }

    //! @brief Get reference.
    T &         operator *      ()          {
        BOOST_ASSERT(get());
        return *get();
    }

    //! @brief Get reference.
    T   const & operator *      () const    {
        BOOST_ASSERT(get());
        return *get();
    }

    //! @brief Deep comparison
    bool        operator==      (this_type const &rhs) const
    {
        return
            (!*this && !rhs) ||
            (*this && rhs && (
                (this->get() == rhs.get()) ||
                (**this == *rhs) ) );
    }

private:
    typedef deep_copy_ptr<T>    this_type;
    std::auto_ptr<detail::deep_copy_ptr_holder_base> holder_;
};

//! swap
template<typename T>
void swap(deep_copy_ptr<T> &lhs, deep_copy_ptr<T> &rhs)
{
    lhs.swap(rhs);
}

}   //hwm

#endif  //HWM_DEEPCOPYPTR_HPP
