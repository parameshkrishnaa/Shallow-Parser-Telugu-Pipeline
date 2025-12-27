/*
 * Convertordemo.java
 *
 * Created on January 31, 2008, 2:50 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author ilmt
 */
import java.io.*;
public class UTF2WXConvertor {
    
    /** Creates a new instance of Convertordemo */
    public UTF2WXConvertor() {
    }
    public static void main(String args[]){
        File inFile = new File(args[0]);
        File outFile = new File(args[1]);
        Convertor conv = new Convertor();
        conv.doUTF2WX(inFile,outFile,args[2]);
       
        
        
        
        
    }
}
