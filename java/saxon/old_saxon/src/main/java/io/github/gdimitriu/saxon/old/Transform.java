package io.github.gdimitriu.saxon.old;

//import net.sf.saxon.FeatureKeys;
//import net.sf.saxon.TransformerFactoryImpl;
import net.sf.saxon.FeatureKeys;
import org.xml.sax.InputSource;

import javax.xml.transform.*;
import javax.xml.transform.sax.SAXSource;
import javax.xml.transform.stream.StreamResult;
import java.io.*;

public class Transform {
    public static void main(String...args) {
        if(args.length != 3) {
            System.err.println("Call with: Transform <inputFile> <xslFile> <outputFile>");
            System.exit(1);
        }
        try (InputStream in = new FileInputStream(args[0]);
             InputStream xsl = new FileInputStream(args[1]);
             OutputStream out = new FileOutputStream(args[2]);
        ) {
            doTransform(in,xsl,out);
        } catch (IOException e) {
            e.printStackTrace();
            System.err.println("Call with: Transform <inputFile> <xslFile> <outputFile>");
            System.exit(1);
        } catch (TransformerException e) {
            e.printStackTrace();
        }
    }

    private static void doTransform(InputStream input, InputStream xsl, OutputStream output) throws TransformerException {
        Source mappingSource = new SAXSource(new InputSource(xsl));
        TransformerFactory transformerFactory = TransformerFactory.newInstance();//new TransformerFactoryImpl();
        transformerFactory.setAttribute("http://saxon.sf.net/feature/linenumbering", Boolean.TRUE);
        transformerFactory.setAttribute("http://saxon.sf.net/feature/traceListener", new MyOldTraceListener());
        Transformer transformer = transformerFactory.newTransformer(mappingSource);
        Source messageSource = new SAXSource(new InputSource(input));
        Result messageResult = new StreamResult(output);
        transformer.transform(messageSource,messageResult);
    }
}
