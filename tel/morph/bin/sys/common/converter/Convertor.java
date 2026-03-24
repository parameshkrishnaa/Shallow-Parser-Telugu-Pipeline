//package sanchay.adhoc;
/*
 * Convertor.java
 *
 * Created on January 28, 2008, 3:56 PM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author ilmt
 */
import sanchay.text.enc.conv.*;

import java.io.*;
import java.io.File;
import sanchay.util.*;

public class Convertor {
    Env environment = new Env();
    /** Creates a new instance of Convertor */
    public Convertor() {
    }
    public String doWX2UTFConvertor(String input,String lang){
        String convertString="";
        String langEnc = lang+"::utf8";
        //WX2UTF8 converter = new WX2UTF8(langEnc,"sanchay\\props\\isc-utf8-wx-map.txt", "UTF-8");
         WX2UTF8 converter = new WX2UTF8(langEnc);
         String utfText = converter.convert(input);
         return utfText;
        
    }
    public String doWX2UTFConvertor(String input,String lang,String props){
        String convertString="";
        String langEnc = lang+"::utf8";
        //WX2UTF8 converter = new WX2UTF8(langEnc,props,"UTF-8");
          WX2UTF8 converter = new WX2UTF8(langEnc);
         String utfText = converter.convert(input);
         return utfText;
        
    }
public String dotargetLangConvertor(String input){
        String convertString="";
        String lang=environment.getEnvironment("tlang");
        String langEnc = lang+"::utf8";
        WX2UTF8 converter = new WX2UTF8(langEnc);
         String utfText = converter.convert(input);
         return utfText;
        
    }    
    public String doUTF2WX(String input, String lang){
        String langEnc = lang+"::utf8";
        UTF82WX convertor= new UTF82WX(langEnc);
        String wxText = convertor.convert(input);
        return wxText;
    }
    public String doUTF2WX(String input, String lang, String props){
        String langEnc = lang+"::utf8";
    
        //UTF82WX convertor= new UTF82WX(langEnc,props,"UTF-8");
        UTF82WX convertor= new UTF82WX(langEnc);
        String wxText = convertor.convert(input);
    
       
        return wxText;
    }
    public String doUTF2WX(String input){
        String lang = environment.getEnvironment("slang");
        
        String langEnc = lang+"::utf8";
        UTF82WX convertor= new UTF82WX(langEnc);
        String wxText = convertor.convert(input);
        return wxText;
    }
    public void doWX2UTF(File inFile, File outFile){
        String lang = environment.getEnvironment("slang");
        String langEnc = lang+"::utf8";
        WX2UTF8 converter = new WX2UTF8(langEnc);
        try {
            converter.convert(inFile, outFile);
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    public void doUTF2WX(File inFile, File outFile){
        String lang = environment.getEnvironment("slang");
        String langEnc = lang+"::utf8";
        UTF82WX converter = new UTF82WX(langEnc);
        try {
            converter.convert(inFile, outFile);
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    public void doWX2UTF(File inFile, File outFile, String lang){
        
        String langEnc = lang+"::utf8";
        WX2UTF8 converter = new WX2UTF8(langEnc);
        try {
            converter.convert(inFile, outFile);
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    public void doUTF2WX(File inFile, File outFile, String lang){
                String langEnc = lang+"::utf8";
        UTF82WX converter = new UTF82WX(langEnc);
        try {
            converter.convert(inFile, outFile);
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
    public static void main(String args[]){
        Convertor conv = new Convertor();
        String test = conv.doWX2UTFConvertor("aruna","tel");
     //   String data = conv.doUTF2WX(kldsk)
        
    }
    
}
