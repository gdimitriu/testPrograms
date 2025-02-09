package gdimitriu.poc_karaf.moduleA;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {
    @Override
    public void start(BundleContext bundleContext) throws Exception {
        System.out.println("Apache Karaf starting moduleA bundle");
    }

    @Override
    public void stop(BundleContext bundleContext) throws Exception {
        System.out.println("Apache Karaf stopping moduleA bundle");
    }
}
