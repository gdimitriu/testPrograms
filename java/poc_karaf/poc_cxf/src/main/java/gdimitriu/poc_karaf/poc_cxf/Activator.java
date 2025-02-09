package gdimitriu.poc_karaf.poc_cxf;

import org.osgi.framework.BundleActivator;
import org.osgi.framework.BundleContext;

public class Activator implements BundleActivator {
    private CxfServer server;
    @Override
    public void start(BundleContext bundleContext) throws Exception {
        server = new CxfServer();
        server.start();
    }

    @Override
    public void stop(BundleContext bundleContext) throws Exception {
        server.stop();
        server = null;
    }
}
