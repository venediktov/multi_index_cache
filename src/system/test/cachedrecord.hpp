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

//namespace is generated from com.mpclmi.test.Record
namespace com { namespace mpclmi { namespace test {
    
//@CacheIndex(type = CacheIndex.Type.UNIQUE , fields={"name", "last_name", "dob"})
struct name_last_name_dob_tag {};
typedef boost::multi_index::ordered_unique<
    boost::multi_index::tag<name_last_name_dob_tag>,
    boost::multi_index::composite_key< 
    Record,
    BOOST_MULTI_INDEX_MEMBER(Record,std::string,bucket_id),
    BOOST_MULTI_INDEX_MEMBER(Record,std::string,variable) ,
    BOOST_MULTI_INDEX_MEMBER(Record,std::string,variable)
    >
> name_last_name_dob_index_t ;   

//@CacheIndex(type = CacheIndex.Type.NON_UNIQUE , fields={"employer"})
struct employer_tag {};
typedef boost::multi_index::ordered_non_unique<
    boost::multi_index::tag<employer_tag>,
    BOOST_MULTI_INDEX_MEMBER(Record,std::string,employer)
> employer_index_t ;

//@CacheIndex(type = CacheIndex.Type.NON_UNIQUE , fields={"dob"})   
struct dob_tag {};
typedef boost::multi_index::ordered_non_unique<
    boost::multi_index::tag<dob_tag>,
    BOOST_MULTI_INDEX_MEMBER(Record,boost::gregorian::date,dob)
> dob_index_t ;

//combine all above indexes in one structure
typedef boost::multi_index::indexed_by< 
    name_last_name_dob_index_t,
    employer_index_t,
    dob_index_t 
> RecordIndexes ; //generated name Record + Indexes

//@CacheAccess(type = CacheAccess.Type.SHARED, name = "CachedRecord")
typedef mpclmi::ipc::MultiIndexCache< mpclmi::ipc::Shared, Record, RecordIndexes> RecordMultiIndexCache ; 

 
 
}}} //end of namespaces

#endif	/* __COM_MPCLMI_TEST_CACHEDRECORD_HPP__ */

 