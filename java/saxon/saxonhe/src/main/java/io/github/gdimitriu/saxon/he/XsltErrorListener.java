package io.github.gdimitriu.saxon.he;

import net.sf.saxon.lib.StandardErrorListener;
import net.sf.saxon.lib.StandardLogger;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import javax.xml.transform.TransformerException;
import java.io.ByteArrayOutputStream;
import java.io.PrintStream;
import java.util.ArrayList;
import java.util.List;

public class XsltErrorListener extends StandardErrorListener {
    private static final long serialVersionUID = 42L;
    private transient Logger log = LogManager.getLogger(XsltErrorListener.class);
    private transient List<TransformerException> errors = new ArrayList<>();
    private transient List<TransformerException> warnings = new ArrayList<>();

    @Override
    public void warning(final TransformerException exception) {
        ByteArrayOutputStream byteOut = initOutput();
        try {
            super.warning(exception);
        } finally {
            log.warn(new String(byteOut.toByteArray()));
            // use of default encoding is ok here since it is used on both ends
            // of the conversion (initOutput(), new String())
            warnings.add(exception);
        }
    }

    @Override
    public void error(final TransformerException exception) {
        ByteArrayOutputStream byteOut = initOutput();
        try {
            super.error(exception);
        } finally {
            log.error(new String(byteOut.toByteArray()));
            // use of default encoding is ok here since it is used on both ends
            // of the conversion (initOutput(), new String())
            errors.add(exception);
        }
    }

    @Override
    public void fatalError(final TransformerException exception) {
        ByteArrayOutputStream byteOut = initOutput();
        try {
            super.fatalError(exception);
        } finally {
            log.fatal(new String(byteOut.toByteArray()));
            // use of default encoding is ok here since it is used on both ends
            // of the conversion (initOutput(), new String())
            errors.add(exception);
        }
    }

    public List getErrors() {
        return errors;
    }

    public List getWarnings() {
        return warnings;
    }

    private ByteArrayOutputStream initOutput() {
        ByteArrayOutputStream byteOut = new ByteArrayOutputStream();
        setLogger(new StandardLogger(new PrintStream(byteOut)));
//        setErrorOutput(new PrintStream(byteOut));
        return byteOut;
    }
}
