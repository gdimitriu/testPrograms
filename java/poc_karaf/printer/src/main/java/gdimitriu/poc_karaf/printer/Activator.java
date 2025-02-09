package gdimitriu.poc_karaf.printer;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {
    @Override
    public void start(BundleContext bundleContext) throws Exception {
        System.out.println("Apache Karaf starting printer bundle");
    }

    @Override
    public void stop(BundleContext bundleContext) throws Exception {
        System.out.println("Apache Karaf stopping printer bundle");
    }
}
