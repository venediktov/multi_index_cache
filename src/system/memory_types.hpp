/* 
 * File:   memory_types.hpp
 * Author: vvenedict@gmail.com
 *
 * Created on March 19, 2014, 4:02 PM
 */

#ifndef _MPClMI_IPC_MEMORY_TYPES_HPP_
#define	_MPCLMI_IPC_MEMORY_TYPES_HPP_

#include <boost/interprocess/managed_shared_memory.hpp> //Variant-I , shm_open(), mmap()
#include <boost/interprocess/managed_mapped_file.hpp> //Variant-II , open(), mmap()
#include <boost/interprocess/managed_heap_memory.hpp> // Variant III for heap
#include <boost/interprocess/creation_tags.hpp>

#include <boost/thread/locks.hpp>
#include <boost/thread/shared_mutex.hpp>

namespace mpclmi { namespace ipc {
   
struct Shared {
    typedef boost::interprocess::managed_shared_memory   segment_t;
    typedef boost::interprocess::managed_shared_memory::segment_manager  segment_manager_t;
    typedef boost::shared_mutex lock_t ;
    typedef boost::unique_lock<lock_t>  scoped_exclusive_locker_t;
    typedef boost::shared_lock<lock_t>  scoped_shared_locker_t;
    static segment_t * open_or_create_segment (const std::string &path, size_t size) {
        return new segment_t(boost::interprocess::open_or_create, path.c_str(), size) ; 
    }
    static segment_t * open_segment (const std::string &path) {
        return new segment_t(boost::interprocess::open_only, path.c_str()) ; 
    }
    static segment_t * create_segment (const std::string &path, size_t size) {
        return new segment_t(boost::interprocess::create_only, path.c_str(), size) ; 
    }
    template <typename MemPtr>
    static void grow(MemPtr &mem_ptr , const std::string &path, size_t size) {
        mem_ptr.reset() ;
        segment_t::grow(path.c_str(), size) ;
        mem_ptr.reset(open_segment(path)) ;
        return ;
    }
    static std::string convert_base_dir(const std::string &base_dir) {
        return "" ;
    }
};  

struct Mapped {
    typedef boost::interprocess::managed_mapped_file   segment_t;  
    typedef boost::interprocess::managed_mapped_file::segment_manager segment_manager_t;
    typedef boost::shared_mutex lock_t ;
    typedef boost::unique_lock<lock_t>  scoped_exclusive_locker_t;
    typedef boost::shared_lock<lock_t>  scoped_shared_locker_t;
    static segment_t * open_or_create_segment (const std::string &path, size_t size) {
        return new segment_t(boost::interprocess::open_or_create, path.c_str(), size) ; 
    }
    static segment_t * open_segment (const std::string &path) {
        return new segment_t(boost::interprocess::open_only, path.c_str()) ; 
    }
    static segment_t * create_segment (const std::string &path, size_t size) {
        return new segment_t(boost::interprocess::create_only, path.c_str(), size) ; 
    }
    template <typename MemPtr>
    static void grow( MemPtr &mem_ptr, const std::string &path, size_t size) {
        mem_ptr.reset() ;
        segment_t::grow(path.c_str(), size) ;
        mem_ptr.reset(open_segment(path)) ;
        return ;
    }
    static std::string convert_base_dir(const std::string &base_dir) {
        return base_dir + "/";
    }
};

struct Heap {
    typedef boost::interprocess::managed_heap_memory   segment_t;
    typedef boost::interprocess::managed_heap_memory::segment_manager  segment_manager_t;
    typedef boost::shared_mutex lock_t ;
    typedef boost::unique_lock<lock_t>  scoped_exclusive_locker_t;
    typedef boost::shared_lock<lock_t>  scoped_shared_locker_t;
    static segment_t * open_or_create_segment (const std::string &path, size_t size) {
        return new segment_t(size) ; 
    }
    static segment_t * create_segment (const std::string &path, size_t size) {
        return new segment_t(size) ; 
    }
    template <typename MemPtr>
    static void grow( MemPtr &mem_ptr, const std::string &path, size_t size) {
        mem_ptr->grow(size) ;
        return ;
    }
    static std::string convert_base_dir(const std::string &base_dir) {
        return "" ;
    }
};

}}
#endif	/* _SYSTEM_IPC_MEMORY_TYPES_HPP_ */

