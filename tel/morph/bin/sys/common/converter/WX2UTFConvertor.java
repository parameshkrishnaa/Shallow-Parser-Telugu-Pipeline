/*
 * WX2UTFConvertor.java
 *
 * Created on January 31, 2008, 3:24 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author ilmt
 */
import java.io.*;
public class WX2UTFConvertor {
    
    /** Creates a new instance of WX2UTFConvertor */
    public WX2UTFConvertor() {
    }
     public static void main(String args[]){
        File inFile = new File(args[0]);
        File outFile = new File(args[1]);
        Convertor conv = new Convertor();
        conv.doWX2UTF(inFile,outFile,args[2]);
        
        
        
        
        
    }
    
}
