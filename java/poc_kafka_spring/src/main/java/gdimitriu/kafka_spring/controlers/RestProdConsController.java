package gdimitriu.kafka_spring.controlers;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.kafka.annotation.KafkaListener;
import org.springframework.kafka.core.KafkaTemplate;
import org.springframework.web.bind.annotation.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.messaging.handler.annotation.Payload;
import javax.annotation.PostConstruct;
import javax.validation.Valid;

@RestController
@RequestMapping("/kafka")
public class RestProdConsController {
    private static final Logger log = LoggerFactory.getLogger(RestProdConsController.class);

    @Autowired
    private KafkaTemplate<String,String> kafkaTemplate;

    @RequestMapping(value = "/topics/{topic}", method = RequestMethod.POST, consumes ={MediaType.TEXT_PLAIN_VALUE})
    public void postTopic(@Valid @PathVariable("topic") String topicName, @Valid @RequestBody String value) {
        kafkaTemplate.send(topicName,value);
    }

    @PostConstruct
    public void printStartup() {
        log.info("After constructed!");
    }

    @KafkaListener(topics ="test")
    public void listener(@Payload String message) {
        log.info("Received Message:" + message);
    }
}
