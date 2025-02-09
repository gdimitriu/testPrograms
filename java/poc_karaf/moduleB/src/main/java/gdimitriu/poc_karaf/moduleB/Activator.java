package gdimitriu.poc_karaf.moduleB;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {
    @Override
    public void start(BundleContext bundleContext) throws Exception {
        System.out.println("Apache Karaf starting moduleB bundle");
    }

    @Override
    public void stop(BundleContext bundleContext) throws Exception {
        System.out.println("Apache Karaf stopping moduleB bundle");
    }
}
