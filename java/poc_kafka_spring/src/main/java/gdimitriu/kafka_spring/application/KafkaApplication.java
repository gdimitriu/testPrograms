package gdimitriu.kafka_spring.application;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;

@SpringBootApplication
@ComponentScan(basePackages = "gdimitriu.kafka_spring")
public class KafkaApplication {
    public static void main(String...args) {
        SpringApplication.run(KafkaApplication.class, args);
    }
}
