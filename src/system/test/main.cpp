/* 
 * File:   main.cpp
 * Author: vvenedict@gmail.com
 *
 * Created on March 5, 2015, 2:09 PM
 */

#include "record.hpp"
#include "cachedrecord.hpp"

using com::mpclmi::test::RecordMultiIndexCache ;
using com::mpclmi::test::Record ;

std::ostream &operator<<(std::ostream &os, const Record &r) {
    return os << r.name << r.last_name << r.employer << r.dob ;
}
/*
 * 
 */
int main(int argc, char** argv) {

    RecordMultiIndexCache cache;
    //1
    Record record;
    record.name = "Vladimir" ;
    record.last_name = "Venediktov" ;
    record.employer = "NAC" ;
    record.dob = boost::gregorian::date(1,1,1900) ;
    cache.Insert(record_1) ;
    //2
    record.name = "Vladimir" ;
    record.last_name = "Venediktov-2" ;
    record.employer = "NAC-2" ;
    record.dob = boost::gregorian::date(1,1,1902) ;
    cache.Insert(record_1) ;
    
    //partial search using unique_index and print
    std::vector<Record> records;
    cache.Retrieve(boost::make_tuple("Vladimir") , records, com::mpclmi::test::name_last_name_dob_tag() ) ;
    std::copy( records.begin(), records.end() , std::ostream_iterator<Record>(std::cout , ",") ) ;
    
    //partial search using unique_index and print 
    cache.Retrieve(boost::make_tuple("Vladimir", "Venediktov") , records, com::mpclmi::test::name_last_name_dob_tag() ) ;
    std::copy( records.begin(), records.end() , std::ostream_iterator<Record>(std::cout , ",") ) ;
    
    //exact search and print
    cache.Retrieve(boost::make_tuple("Vladimir", "Venediktov", boost::gregorian::date(1,1,1902) ) , records, com::mpclmi::test::name_last_name_dob_tag() ) ;
    std::copy( records.begin(), records.end() , std::ostream_iterator<Record>(std::cout , ",") ) ;
    
    return 0;
}

