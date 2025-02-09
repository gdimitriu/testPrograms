package gdimitriu.poc_karaf.printerclient;

import gdimitriu.poc_karaf.printer.Printer;

public class PrinterClient {
    public void printMyMessage() {
        new Printer().print("Hello World!");
    }
}
