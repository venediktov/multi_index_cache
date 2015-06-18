/*
 * This is a sample file showing how to annotate your 
 * class to produce non-destributed Cache for your classes which can be 
 * shared not persisteed ( multiple processes acess running on the same host) 
 * shared persisted ( see CacheAccess.MEMORY_MAPPED )  or private e.g only accessible by your appications .
 */

package com.mpclmi.test;

import com.mpclmi.CacheAccess;
import com.mpclmi.CacheIndex;



/**
 *
 * @author vvenedict@gmail.com
 */

@CacheAccess(type = CacheAccess.Type.SHARED, name = "CachedRecord")
@CacheIndex(type = CacheIndex.Type.UNIQUE , fields={"name", "last_name", "dob"})
@CacheIndex(type = CacheIndex.Type.NON_UNIQUE , fields={"employer"})
@CacheIndex(type = CacheIndex.Type.NON_UNIQUE , fields={"dob"})        
class Record {
    public String name;
    public String last_name;
    public java.util.Date dob ;
    public String employer;
}




public class CacheTest {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
    }
    
    
}
