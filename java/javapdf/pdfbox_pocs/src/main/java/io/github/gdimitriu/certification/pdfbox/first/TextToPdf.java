package io.github.gdimitriu.certification.pdfbox.first;

import org.apache.pdfbox.tools.TextToPDF;
import picocli.CommandLine;

public class TextToPdf {
    public static void main(String...args) {
        System.setProperty("apple.awt.UIElement", "true");
        int exitCode = (new CommandLine(new TextToPDF())).execute(args);
        System.exit(exitCode);
    }
}
