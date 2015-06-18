/* 
 * File:   record.hpp
 * Author: vlad1819
 *
 * Created on June 17, 2015, 9:28 PM
 */

#ifndef __COM_MPCLMI_TEST_RECORD_HPP__
#define	__COM_MPCLMI_TEST_RECORD_HPP__

#include <string>
#include <boost/date_time/gregorian/greg_date.hpp>

//namespace is generated from com.mpclmi.test.Record
namespace com { namespace mpclmi { namespace test {

struct  Record {
    std::string name;
    std::string last_name;
    boost::gregorian::date dob ;
    std::string employer;
} ;

}}}

#endif	/* __COM_MPCLMI_TEST_RECORD_HPP__ */

