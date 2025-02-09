package gdimitriu.poc_karaf.printerclient;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {
    @Override
    public void start(BundleContext bundleContext) throws Exception {
        System.out.println("Starting bundle printerclient");
        new PrinterClient().printMyMessage();
    }

    @Override
    public void stop(BundleContext bundleContext) throws Exception {
        System.out.println("Stopping bundle printerclient");
    }
}
