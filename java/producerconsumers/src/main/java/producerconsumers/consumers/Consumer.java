package producerconsumers.consumers;

import org.apache.kafka.clients.consumer.ConsumerRecord;
import org.apache.kafka.clients.consumer.ConsumerRecords;
import org.apache.kafka.clients.consumer.KafkaConsumer;
import org.apache.kafka.common.PartitionInfo;

import java.time.Duration;
import java.util.*;

public class Consumer {

    public static void main(String...args) {
        if (args.length != 3) {
            System.err.println("Call using : ip-address port groupId");
            System.exit(-1);
        }
        Properties kafkaProps = new Properties();
        kafkaProps.put("bootstrap.servers", args[0] + ":" + args[1]);
        kafkaProps.put("group.id", args[2]);
        kafkaProps.put("enable.auto.commit", "true");
        kafkaProps.put("auto.commit.interval.ms", "1000");
        kafkaProps.put("session.timeout.ms", "30000");
        kafkaProps.put("client.id", "my");
        kafkaProps.put("key.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        kafkaProps.put("value.deserializer", "org.apache.kafka.common.serialization.StringDeserializer");
        KafkaConsumer<String, String> consumer = new KafkaConsumer<String, String>(kafkaProps);
        Map<String, List<PartitionInfo>> topics = consumer.listTopics();
        System.out.println(topics);
        consumer.subscribe(Arrays.asList("CustomerCountry"));
        System.out.println("Consumer subscribed to topic " + "CustomerCountry");
        consumer.subscription().stream().forEach( System.out::println);
        try {
            while(true) {
                ConsumerRecords<String, String> records = consumer.poll(Duration.ofMillis(100));
                for(ConsumerRecord<String, String> record : records) {
                    System.out.println("topic=" + record.topic() + " key=" + record.key() + " value=" + record.value());
                }
            }
        } finally {
            consumer.close();
        }
    }
}
