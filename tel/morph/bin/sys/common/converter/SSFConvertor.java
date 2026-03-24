//package sanchay.adhoc;
import java.io.PrintStream;
import java.util.Enumeration;
import javax.swing.tree.MutableTreeNode;

import javax.swing.tree.TreeNode;

import sanchay.corpus.ssf.SSFProperties;
import sanchay.corpus.ssf.SSFSentence;
import sanchay.corpus.ssf.SSFStory;
import sanchay.corpus.ssf.features.FeatureAttribute;
import sanchay.corpus.ssf.features.FeatureStructure;
import sanchay.corpus.ssf.features.FeatureValue;
import sanchay.corpus.ssf.features.impl.FSProperties;
import sanchay.corpus.ssf.features.impl.FeatureStructuresImpl;
import sanchay.corpus.ssf.features.impl.FeatureValueImpl;
import sanchay.corpus.ssf.impl.SSFSentenceImpl;
import sanchay.corpus.ssf.impl.SSFStoryImpl;
import sanchay.corpus.ssf.tree.SSFNode;
import sanchay.text.enc.conv.WX2UTF8;
import sanchay.util.*;
/*import in.ac.iitb.cfilt.multidict.data.POS;
import in.ac.iitb.cfilt.multidict.engine.LexicalTransfer;
import in.ac.iitb.cfilt.multidict.exception.MultilingualDictException;
import in.ac.iitb.cfilt.multidict.io.UTFConsole;*/


public class SSFConvertor {
Convertor con= new Convertor();
	public String dictionaryLookup (String word, String lang, String mod)
	{
            
        String translatedword="";
            if(mod.equalsIgnoreCase("WX")){
            translatedword = con.doWX2UTFConvertor(word,lang);
            }
            if(mod.equalsIgnoreCase("UTF-8")){
            translatedword = con.doUTF2WX(word,lang);
            }
            
		return translatedword;
		//word = word.ReplaceAll("'", "");
	}
	
	
	public void linkSen(SSFSentence sentence, String lang, String mod) {
{
			SSFSentence sen = sentence;
			//System.out.println(sen.toString());
			int ccount = sen.getRoot().countChildren();
			for (int j = 0; j < ccount; j++)
			{
				SSFNode node = sen.getRoot().getChild(j);
				String wordLex = node.getLexData();
				//System.out.println(ccount);
				if (node.getFeatureStructures() != null && node.getChildCount() == 0)
				{
					FeatureStructure fs = node.getFeatureStructures().getAltFSValue(0);
					FeatureAttribute fa = fs.getAttribute(1);
					FeatureValue catMorph = fa.getAltValue(0);
					FeatureAttribute faRoot = fs.getAttribute(0);
					FeatureValue wordLexical = faRoot.getAltValue(0);
					wordLex = wordLexical.toString();
					//PrintStream rand = new PrintStream(System.out);
					//catMorph.print(rand);
					//System.out.print(catMorph.toString());
					String POS = catMorph.toString();
					//System.out.println("postag===" + " " + POS);
					String translationWord = dictionaryLookup (wordLex,lang, mod);
					//node.setLexData(translationWord);
					//FeatureValue temp= new FeatureValueImpl();
					//temp.setValue(translationWord);
					//fs.modifyAttributeValue(temp,0,0);
                                                         FeatureValue temp = new FeatureValueImpl();
                                        temp.setValue(translationWord);
					if(translationWord !=null){
					node.setLexData(translationWord);
                                        fs.modifyAttributeValue(temp ,0,0);
					}
				}

				else 
				{
					int treecount = node.countChildren();
					
					for (int k = 0; k < treecount; k++)
					{
						SSFNode nodeChild = (SSFNode) node.getChildAt(k);
						String wordLexChild = nodeChild.getLexData();
						//System.out.println(treecount);
						if (nodeChild.getFeatureStructures() != null && nodeChild.getChildCount() == 0)
						{
							FeatureStructure fs = nodeChild.getFeatureStructures().getAltFSValue(0);
							FeatureAttribute fa = fs.getAttribute(1);
							FeatureValue catMorph = fa.getAltValue(0);
							FeatureAttribute faRoot = fs.getAttribute(0);
							FeatureValue wordLexical = faRoot.getAltValue(0);
							wordLex = wordLexical.toString();

							//PrintStream rand = new PrintStream(System.out);
							//catMorph.print(rand);
							//System.out.print(catMorph.toString());
							String POS = catMorph.toString();
						//	System.out.println(wordLex + " " + POS);
							String translationWord = dictionaryLookup (wordLex,lang,mod);
							//nodeChild.setLexData(translationWord);
							//wordLex.replaceAll()
						//	FeatureValue temp= new FeatureValueImpl();
						//	temp.setValue(translationWord);
						//	fs.modifyAttributeValue(temp,0,0);
                                                         FeatureValue temp = new FeatureValueImpl();
                                        temp.setValue(translationWord);
					if(translationWord !=null){
							nodeChild.setLexData(translationWord);
                                        fs.modifyAttributeValue(temp ,0,0);
					}
						}
					}
				}

			}
			
        
	PrintStream rand = new PrintStream(System.out);
        System.out.println("<Sentence id =\"1\">");
	sen.print(rand);
	//sen.makeString();
       System.out.println("</Sentence>");
}
	}
	
	public static void main(String[] args) {
		Env env = new Env();
		String sanchayProp= env.getEnvironment("sanchay_prop");
		FSProperties fsp = new FSProperties();
		SSFProperties ssfp = new SSFProperties();

		SSFSentence sentence = new SSFSentenceImpl();

		SSFConvertor link = new SSFConvertor();

		try {
			 fsp.read(sanchayProp+"/props/fs-mandatory-attribs.txt",
                    sanchayProp+"/props/fs-props.txt", "UTF-8"); //throws java.io.FileNotFoundException;
            ssfp.read(sanchayProp+"/props/ssf-props.txt", "UTF-8"); //throws java.io.FileNotFoundException;
            
            FeatureStructuresImpl.setFSProperties(fsp);
            SSFNode.setSSFProperties(ssfp);
            
            //story.readFile("/home/dashboard/Sanchay-0.2/Sanchay/prune.out"); //throws java.io.FileNotFoundException;
            //Read the input file which is valid SSF format.if it is not then it is use as RAW data
            //sentence.readFile("prune.out");
            sentence.readFile(args[0]);
            //story.readFile("/home/sanchay/Sanchay/LinkIn.txt"); //throws java.io.FileNotFoundException;
            //Call the linkSen function which do some processing on sentence
            link.linkSen(sentence,args[1],args[2]);
		}

		catch (Exception ex) {
			ex.printStackTrace();

		}
	}
}
