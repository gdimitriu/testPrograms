open module poc.cxf {
    requires osgi.core;
    requires org.apache.cxf.rs.openapi.v3;
    requires org.apache.cxf.rs.swagger.ui;
    requires org.apache.cxf.rs.common.openapi;
    requires com.fasterxml.jackson.jaxrs.json;
    requires org.apache.cxf.frontend.jaxrs;
    requires org.apache.cxf.core;
    requires java.ws.rs;
    requires com.fasterxml.jackson.annotation;
    requires io.swagger.v3.jaxrs2;
    requires jakarta.activation;
    requires io.swagger.v3.core;
    requires swagger.annotations;
    requires org.apache.cxf.rs.swagger;
    requires io.swagger.v3.oas.annotations;
    exports gdimitriu.poc_karaf.poc_cxf;
}