/* 
 * File:   MultiIndexCache.hpp
 * Author: vvenedict@gmail.com
 *
 * Created on March 19, 2014, 3:57 PM
 */

#ifndef __MPCLMI_IPC_MULTI_INDEX_CACHE_HPP
#define	__MPCLMI_IPC_MULTI_INDEX_CACHE_HPP

#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/map.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/interprocess/sync/named_upgradable_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/sharable_lock.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <boost/multi_index_container.hpp>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

namespace {
    namespace bip = boost::interprocess ;
}

namespace mpclmi { namespace ipc {



template<typename Memory, template<class> class Data, typename IndexedBy>
class MultiIndexCache : private boost::noncopyable
{
    
public:
    typedef bip::bad_alloc bad_alloc_exception_t ;
    typedef typename Memory::segment_manager_t segment_manager_t;
    typedef typename Memory::segment_t segment_t;
    typedef bip::allocator<char, segment_manager_t>  char_allocator;
    typedef bip::basic_string<char, std::char_traits<char>, char_allocator>   char_string;
    typedef Data<Memory> Data_t ;
    //Definition of the boost::multi_index_container holding Data_t
    typedef bip::allocator<Data_t, segment_manager_t>  data_allocator;
    typedef boost::multi_index_container< Data_t, IndexedBy, data_allocator>  Container_t ;
  
    template<typename AnyData> 
    bool Insert   ( const AnyData &row ) 
    {
        bip::scoped_lock<bip::named_upgradable_mutex> guard(_named_mutex) ;
        bool is_success = false;
        
        try {
            is_success = insert_data(row) ;
        } catch (const  bad_alloc_exception_t &e) {
            std::cerr << "Data Was not inserted , MEMORY AVAILABLE="
                      << boost::lexical_cast<std::string>(_segment_ptr->get_free_memory()) ;
            grow_memory(MEMORY_SIZE);
            is_success = insert_data(row) ;
        }
        return is_success ;
    }
    template<typename Key , typename AnyData, typename Tag>
    bool Retrieve ( const Key &key, std::vector<AnyData> & rows, const Tag &) {
        typedef typename Container_t::template index<Tag>::type tag_index_t ;
        typedef typename tag_index_t::iterator iterator ;           
 
        bip::sharable_lock<bip::named_upgradable_mutex> guard(_named_mutex) ;
        Data_t item(_segment_ptr->get_segment_manager());
        std::pair<iterator, iterator> p = _container_ptr->template get<Tag>().equal_range(item.template cache_key<Key>(key)) ;
        std::transform(p.first, p.second, std::back_inserter(rows), boost::bind(&Data_t::convert, _1)) ;  
        return !rows.empty() ;
    }
    static MultiIndexCache &instance() {
        static MultiIndexCache impl;
        return impl;    
    }
private:
    MultiIndexCache() : _segment_ptr(), _container_ptr(), _store_name(), 
        _named_mutex(bip::open_or_create, "MultiIndexCacheMutex")
    {
        //TODO: addd to ctor to switch between mmap and shm
        std::string data_base_dir = "/tmp/CACHE" ; 
        _store_name =  Memory::convert_base_dir(data_base_dir) + "MPCLMI" ;
        _segment_ptr.reset(new segment_t(bip::open_or_create, _store_name.c_str(), MEMORY_SIZE) ) ;
        _container_ptr = _segment_ptr->template find_or_construct<Container_t>("CACHE")
            (typename Container_t::allocator_type(_segment_ptr->get_segment_manager()));
    }
 
    void attach() {
        _segment_ptr.reset(new segment_t(bip::open_only,_store_name.c_str()) ) ;
        _container_ptr = _segment_ptr->template find_or_construct<Container_t>("CACHE")
            (typename Container_t::allocator_type(_segment_ptr->get_segment_manager()));
    }
     
    void grow_memory(size_t size) {
        try {
          _segment_ptr.reset() ;
          segment_t::grow(_store_name.c_str(), size) ;
        } catch ( const std::exception &e) {
            std::cerr <<"FAILED TO GROW="
                      <<boost::lexical_cast<std::string>(_segment_ptr->get_free_memory()) ;
        }
        attach() ; // reattach to newly created
    }
    
    template<typename AnyData> 
    bool insert_data(const AnyData &row) {
        bool is_success=false;
        attach() ;
        try {
            Data_t item(_segment_ptr->get_segment_manager());
            item  = row;
            is_success = _container_ptr->insert(item).second ;
        } catch (const  bad_alloc_exception_t &e) {
            grow_memory(MEMORY_SIZE);
            Data_t item(_segment_ptr->get_segment_manager());
            item = row;
            is_success = _container_ptr->insert(item).second ;
        }
        
        return is_success; 
    }
    
    boost::scoped_ptr<segment_t> _segment_ptr;
    Container_t  *_container_ptr ;
    std::string _store_name ;
    boost::interprocess::named_upgradable_mutex _named_mutex;
    static const size_t MEMORY_SIZE = 67108864 ; //64M
};



}}

#endif	/* __MPClMI_IPC_MULTI_INDEX_CACHE_HPP */

