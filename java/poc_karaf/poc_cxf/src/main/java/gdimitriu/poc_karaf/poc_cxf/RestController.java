package gdimitriu.poc_karaf.poc_cxf;

import javax.ws.rs.GET;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.MediaType;
import io.swagger.annotations.Api;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.media.ArraySchema;
import io.swagger.v3.oas.annotations.media.Content;
import io.swagger.v3.oas.annotations.media.Schema;
import io.swagger.v3.oas.annotations.responses.ApiResponse;

@Path("/cxf_test")
@Api(value = "/cxf_test", description = "CXF_TEST service with Swagger documentation")
public class RestController {

    @Path("/info")
    @GET
    public String getInfo() {
        return "server is alive";
    }

    @Path("/json")
    @GET
    @Produces({MediaType.APPLICATION_JSON})
    @Operation(
            summary = "get json test",
            description = "Get operation with Response and @Default value",
            responses = {
                    @ApiResponse(
                            content = @Content(array = @ArraySchema(schema = @Schema(implementation = JacksonTest.class))),
                            responseCode = "200"
                    )
            }
    )
    public JacksonTest jsonTest() {
        JacksonTest test = new JacksonTest("server","Server is alive");
        return test;
    }
}
