package gdimitriu.poc_karaf.poc_cxf;

import com.fasterxml.jackson.jaxrs.json.JacksonJaxbJsonProvider;
import org.apache.cxf.Bus;
import org.apache.cxf.bus.CXFBusFactory;
import org.apache.cxf.endpoint.Server;
import org.apache.cxf.jaxrs.JAXRSServerFactoryBean;
import org.apache.cxf.jaxrs.openapi.OpenApiFeature;
import org.apache.cxf.jaxrs.swagger.ui.SwaggerUiConfig;
import org.apache.cxf.jaxrs.swagger.Swagger2Feature;

import java.net.InetAddress;
import java.net.UnknownHostException;
import java.util.Arrays;
import java.util.HashSet;
import java.util.Set;

public class CxfServer {
    private JAXRSServerFactoryBean restServer;
    private Server server;
    private Bus bus;
    private OpenApiFeature feature;
    private Swagger2Feature swagger2Feature;
    private RestController restController;
    public void start() {
        restController = new RestController();
        bus = CXFBusFactory.newInstance().createBus();
        restServer = new JAXRSServerFactoryBean();
        restServer.setBus(bus);
        restServer.setProviders(Arrays.asList(new JacksonJaxbJsonProvider(),new ApiOriginFilter()));
        restServer.setServiceBean(restController);
        feature = new OpenApiFeature();
        swagger2Feature = new Swagger2Feature();
        swagger2Feature.setBasePath("/api");
        feature.setSwaggerUiConfig(
                new SwaggerUiConfig()
                        .url("/openapi.json"));
        Set<String> propsClasses = new HashSet<>();
        propsClasses.add(restController.getClass().getCanonicalName());
        feature.setResourceClasses(propsClasses);
        feature.setReadAllResources(true);
        restServer.getFeatures().add(feature);
        restServer.getFeatures().add(swagger2Feature);
        String hostname = "localhost";
        try {
            hostname = InetAddress.getLocalHost().getCanonicalHostName();
        } catch (UnknownHostException e) {
        }
        restServer.setAddress("http://" + hostname + ":8080");
        server = restServer.create();
    }

    public void stop() {
        server.stop();
        server.destroy();
        bus.shutdown(true);
        restController = null;
        feature = null;
        swagger2Feature = null;
    }
}
