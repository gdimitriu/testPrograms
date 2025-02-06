package org.example.firstfop;

import org.apache.fop.apps.*;
import org.apache.fop.configuration.Configuration;
import org.apache.fop.configuration.ConfigurationException;
import org.apache.fop.configuration.DefaultConfigurationBuilder;
import org.apache.fop.render.intermediate.IFContext;
import org.apache.fop.render.intermediate.IFDocumentHandler;
import org.apache.fop.render.intermediate.IFSerializer;
import org.xml.sax.SAXException;

import javax.xml.transform.*;
import javax.xml.transform.sax.SAXResult;
import javax.xml.transform.stream.StreamSource;
import java.io.*;

public class FirstRun {

    public static void main(String...args) throws Exception {
        FirstRun runner = new FirstRun();
        runner.run(new File(args[0]), new File(args[1]), new File(args[2]), new File(args[3]));
    }
    public void run(File inputFile, File outputFile, File confFile, File xslFile) throws IOException, SAXException, TransformerException, ConfigurationException {

        // Step 1: Construct a FopFactory by specifying a reference to the configuration file
// (reuse if you plan to render multiple documents!)
       // FopFactory fopFactory = FopFactory.newInstance(confFile);
        FopFactoryBuilder builder = new FopFactoryBuilder(
                new File("/home/onion/micro/learning/language/java/certification/fop_pocs/src/main/resources").toURI());
        Configuration configuration = new DefaultConfigurationBuilder().buildFromFile(confFile);
        builder.setConfiguration(configuration);
        FopFactory fopFactory = builder.build();
        // Step 2: Set up output stream.
// Note: Using BufferedOutputStream for performance reasons (helpful with FileOutputStreams).


        try (OutputStream out = new BufferedOutputStream(new FileOutputStream(outputFile)) ){
            FOUserAgent userAgent = fopFactory.newFOUserAgent();
            IFDocumentHandler targetHandler = userAgent.getRendererFactory().createDocumentHandler(userAgent, MimeConstants.MIME_PDF);

            IFSerializer ifSerializer = new IFSerializer(new IFContext(userAgent));  //Create the IFSerializer to write the intermediate format
            ifSerializer.mimicDocumentHandler(targetHandler);   //Tell the IFSerializer to mimic the target format

            userAgent.setDocumentHandlerOverride(ifSerializer);  //Make sure the prepared document handler is used
            // Step 3: Construct fop with desired output format
            Fop fop = fopFactory.newFop(MimeConstants.MIME_PDF, out);

            // Step 4: Setup JAXP using identity transformer
            TransformerFactory factory = TransformerFactory.newInstance();
            //Transformer transformer = factory.newTransformer(); // identity transformer
            Source xslt = new StreamSource(xslFile);
            Transformer transformer = factory.newTransformer(xslt);
            // Step 5: Setup input and output for XSLT transformation
            // Setup input stream
            Source src = new StreamSource(inputFile);

            // Resulting SAX events (the generated FO) must be piped through to FOP
            Result res = new SAXResult(fop.getDefaultHandler());

            // Step 6: Start XSLT transformation and FOP processing
            transformer.transform(src, res);

        }
    }
}
