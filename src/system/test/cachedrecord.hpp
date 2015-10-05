/* 
 * File:   cachedrecord.hpp
 * Author: vlad1819
 *
 * Created on June 17, 2015, 9:38 PM
 */

#ifndef __COM_MPCLMI_TEST_CACHEDRECORD_HPP__
#define	__COM_MPCLMI_TEST_CACHEDRECORD_HPP__

#include <system/memory_types.hpp>
#include <system/multi_index_cache.hpp> 
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/ordered_index.hpp> //TODO: select between ordered and non-ordered in Annotation
#include <boost/multi_index/composite_key.hpp> //This one is included if composite key is on the Record  
#include <boost/multi_index/indexed_by.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/utility.hpp>
#include <boost/type_traits.hpp>
#include "record.hpp"

namespace {
    namespace bip = boost::interprocess ;
}

//namespace is generated from com.mpclmi.test.Record
namespace com { namespace mpclmi { namespace test {
//@CacheAccess(type = CacheAccess.Type.SHARED, name = "CachedRecord")
template<typename Memory>
struct  CachedRecord {
    typedef typename Memory::segment_manager_t segment_manager_t;
    typedef bip::allocator<char, segment_manager_t>  char_allocator;
    typedef bip::basic_string<char, std::char_traits<char>, char_allocator>   string_type;
    typedef boost::gregorian::date date_type; //TODO: check if interprocess can store this type
    string_type name;
    string_type last_name;
    boost::gregorian::date dob ;
    string_type employer;
    CachedRecord(typename Memory::segment_manager_t *mgr) : 
        mgr_(mgr) , a_(mgr) , name(a_) , last_name(a_) , employer(a_) 
    {}
    CachedRecord<Memory> &operator=(const Record &r) {
        return *this; //TODO: implement it 
    }
    static Record convert(const CachedRecord &cr) {
        Record r ;
        r.name = cr.name.c_str() ;
        r.last_name = cr.last_name.c_str() ;
        r.dob = cr.dob ;
        r.employer = cr.employer.c_str() ;
        return r;
    }
    //TODO: this must be simplified even if it is generated
    template<typename Tuple>
    typename boost::enable_if<
        boost::is_same<Tuple,boost::tuple<std::string> > , 
        boost::tuple<string_type>
    >::type
    cache_key(const Tuple & t) {
        return boost::make_tuple(string_type(boost::get<0>(t).c_str(), char_allocator(mgr_))) ;
    }
    
    template<typename Tuple>
    typename boost::enable_if<
        boost::is_same<Tuple,
        boost::tuple<std::string, std::string> > , 
        boost::tuple<string_type, string_type> 
    >::type 
    cache_key(const Tuple & t) {
        return boost::make_tuple(string_type(boost::get<0>(t).c_str(), char_allocator(mgr_)) , 
                                 string_type(boost::get<1>(t).c_str(), char_allocator(mgr_)) ) ;
    }
    
    template<typename Tuple>
    typename boost::enable_if<
        boost::is_same<Tuple,boost::tuple<std::string, std::string, boost::gregorian::date> > , 
        boost::tuple<string_type, string_type, date_type> 
    >::type
    cache_key(const Tuple & t) {
        return boost::make_tuple(string_type(boost::get<0>(t).c_str(), char_allocator(mgr_)) , 
                                 string_type(boost::get<1>(t).c_str(), char_allocator(mgr_)) ,
                                 boost::get<2>(t)) ;
    }
    private:
        typename Memory::segment_manager_t *mgr_ ;
        char_allocator a_ ;
    
} ;
typedef CachedRecord< ::mpclmi::ipc::Shared > Record_t;

//@CacheIndex(type = CacheIndex.Type.UNIQUE , fields={"name", "last_name", "dob"})
struct name_last_name_dob_tag {};
typedef boost::multi_index::ordered_unique<
    boost::multi_index::tag<name_last_name_dob_tag>,
    boost::multi_index::composite_key< 
    Record_t,
    BOOST_MULTI_INDEX_MEMBER(Record_t,Record_t::string_type,name), 
    BOOST_MULTI_INDEX_MEMBER(Record_t,Record_t::string_type,last_name) , 
    BOOST_MULTI_INDEX_MEMBER(Record_t,Record_t::date_type,dob)
    >
> name_last_name_dob_index_t ;   

//@CacheIndex(type = CacheIndex.Type.NON_UNIQUE , fields={"employer"})
struct employer_tag {};
typedef boost::multi_index::ordered_non_unique<
    boost::multi_index::tag<employer_tag>,
    BOOST_MULTI_INDEX_MEMBER(Record_t,Record_t::string_type,employer)
> employer_index_t ;

//@CacheIndex(type = CacheIndex.Type.NON_UNIQUE , fields={"dob"})   
struct dob_tag {};
typedef boost::multi_index::ordered_non_unique<
    boost::multi_index::tag<dob_tag>,
    BOOST_MULTI_INDEX_MEMBER(Record_t,Record_t::date_type,dob)
> dob_index_t ;

//combine all above indexes in one structure
typedef boost::multi_index::indexed_by< 
    name_last_name_dob_index_t,
    employer_index_t,
    dob_index_t 
> RecordIndexes ; //generated name Record + Indexes

//@CacheAccess(type = CacheAccess.Type.SHARED, name = "CachedRecord")
typedef ::mpclmi::ipc::MultiIndexCache< ::mpclmi::ipc::Shared, CachedRecord, RecordIndexes> RecordMultiIndexCache ; 

 
 
}}} //end of namespaces

#endif	/* __COM_MPCLMI_TEST_CACHEDRECORD_HPP__ */

 
