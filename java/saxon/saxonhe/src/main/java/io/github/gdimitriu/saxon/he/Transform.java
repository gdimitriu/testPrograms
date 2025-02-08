package io.github.gdimitriu.saxon.he;

import net.sf.saxon.TransformerFactoryImpl;
import net.sf.saxon.lib.FeatureKeys;
import net.sf.saxon.lib.StandardErrorListener;
import net.sf.saxon.lib.TraceListener;
import net.sf.saxon.trace.*;
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
             )
        {
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
        TransformerFactory transformerFactory = new TransformerFactoryImpl();
        TraceListener traceListener = null;
        //traceListener = TraceEventMulticaster.add(new MyTraceListener(), new XQueryTraceListener());
        //traceListener = new XSLTTraceListener();
        //traceListener =  new MyTraceListener();
        traceListener = new XQueryTraceListener();
        //traceListener = new TimingTraceListener();

        //settings
        transformerFactory.setAttribute(FeatureKeys.TRACE_LISTENER, traceListener);
        transformerFactory.setAttribute(FeatureKeys.LINE_NUMBERING, Boolean.TRUE);
        transformerFactory.setAttribute(FeatureKeys.TRACE_EXTERNAL_FUNCTIONS, Boolean.TRUE);
        transformerFactory.setAttribute(FeatureKeys.ALLOW_EXTERNAL_FUNCTIONS, Boolean.TRUE);
        transformerFactory.setAttribute(FeatureKeys.COMPILE_WITH_TRACING, Boolean.TRUE);

        Transformer transformer = transformerFactory.newTransformer(mappingSource);
        Source messageSource = new SAXSource(new InputSource(input));
        Result messageResult = new StreamResult(output);
        transformer.setErrorListener(new XsltErrorListener());
        transformer.transform(messageSource,messageResult);
    }
}
